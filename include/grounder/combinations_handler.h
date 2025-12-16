// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef EPDDL_COMBINATIONS_HANDLER_H
#define EPDDL_COMBINATIONS_HANDLER_H

#include "../type-checker/context/context.h"
#include <algorithm>
#include <deque>
#include <type_traits>
#include <utility>

using namespace epddl::type_checker;

namespace epddl::grounder {
    using combination = std::deque<unsigned long>;
    using combination_deque = std::deque<combination>;
    using bitset_vector = std::vector<boost::dynamic_bitset<>>;

    class combinations_handler {
    public:
        /*combinations_handler(typed_var_list typed_vars, bitset_vector entities_with_type) :
                m_typed_vars{std::move(typed_vars)},
                m_entities_with_type{std::move(entities_with_type)} {
            m_combination = combination(m_typed_vars.size());
            m_entities_no = std::deque<size_t>(m_typed_vars.size());
            m_counter = std::deque<size_t>(m_typed_vars.size());
            m_has_next = boost::dynamic_bitset<>(m_typed_vars.size());
            restart();
        }*/

        combinations_handler(typed_var_list typed_vars, context &context) :
                m_typed_vars{std::move(typed_vars)} {
            if (m_typed_vars.empty())
                m_empty = true;
            else {
                m_elements_no = context.entities.get_entities_no();
                m_types_no = m_typed_vars.size();
                m_entities_with_type = bitset_vector(m_types_no,
                                                     boost::dynamic_bitset<>(m_elements_no));

                unsigned long count = 0;
                // We compute m_entities_with_type[i] so that it is a bitset where the k-th bit is true iff the entity
                // with id 'k' has type t, being one of the required types in 'et'
                for (const auto &[var, et]: m_typed_vars) {
                    for (const type_id &t: et)
                        m_entities_with_type[count] |=
                                context.entities.get_entities_with_type(context.types, t).get_bitset();

                    ++count;
                }

                m_combination = combination(m_types_no);
                m_counter = std::deque<size_t>(m_types_no);
                m_has_next = boost::dynamic_bitset<>(m_types_no);
                m_is_first_comb = true;

                // In 'm_entities_no' we keep track of the total number of entities of each type
                m_entities_no = std::deque<size_t>(m_types_no);

                for (size_t type_id = 0; type_id < m_combination.size(); ++type_id)
                    m_entities_no[type_id] = m_entities_with_type[type_id].count();

                m_empty = std::any_of(m_entities_no.begin(), m_entities_no.end(),
                                      [&](const size_t entities_no) {
                    return entities_no == 0;
                });
            }
        }

        combinations_handler(const ast::formal_param_list &params, context &context,
                             const type_checker::either_type &default_type) :
                combinations_handler(context.types.build_typed_var_list(params, default_type),
                                     context) {}

        [[nodiscard]] const typed_var_list &get_typed_vars() const {
            return m_typed_vars;
        }

        [[nodiscard]] bool empty() const {
            return m_empty;
        }

        [[nodiscard]] bool has_next() const {
            return not m_empty and (m_is_first_comb or m_has_next.any());
        }

        void restart() {
            // Initialization of the first combination
            for (size_t type_id = 0; type_id < m_combination.size(); ++type_id)
                reset(type_id);

            m_is_first_comb = true;
        }

        [[nodiscard]] const combination &current() const {
            return m_combination;
        }

        [[nodiscard]] const combination &next() {
            assert(not empty());

            if (m_is_first_comb)
                return first();

            if (has_next()) {
                size_t index = m_combination.size();

                while (index > 0 and not m_has_next[--index])
                    reset(index);

                increment(index);
            }
            return m_combination;
        }

        [[nodiscard]] combination_deque all() {
            restart();

            combination_deque all;
            while (has_next()) all.emplace_back(next());
            return all;
        }

    private:
        bitset_vector m_entities_with_type;
        combination m_combination;
        std::deque<size_t> m_counter, m_entities_no;
        boost::dynamic_bitset<> m_has_next;
        bool m_empty, m_is_first_comb;
        typed_var_list m_typed_vars;
        unsigned long m_elements_no;
        unsigned long m_types_no;

        [[nodiscard]] const combination &first() {
            restart();
            m_is_first_comb = false;
            return m_combination;
        }

        void reset(size_t index) {
            m_combination[index] = m_entities_with_type[index].find_first();
            m_counter[index] = 1;

            bool has_next = m_counter[index] < m_entities_no[index];
            m_has_next.set(index, has_next);
        }

        void increment(size_t index) {
            m_combination[index] = m_entities_with_type[index].find_next(m_combination[index]);
            ++m_counter[index];

            bool has_next = m_counter[index] < m_entities_no[index];
            m_has_next.set(index, has_next);
        }
    };
}

#endif //EPDDL_COMBINATIONS_HANDLER_H
