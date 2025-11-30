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
#include <deque>
#include <type_traits>

using namespace epddl::type_checker;

namespace epddl::grounder {
    using combination       = std::deque<unsigned long>;
    using combination_deque = std::deque<combination>;
    using bitset_vector     = std::vector<boost::dynamic_bitset<>>;

    class combinations_handler {
    public:
        combinations_handler(const typed_var_list &typed_vars, const context &context) :
                m_typed_vars{typed_vars} {
            unsigned long entities_no = context.entities.get_entities_with_type(context.types, "entity").size(), count = 0;
            m_entities_with_type = bitset_vector(m_typed_vars.size(), boost::dynamic_bitset<>(entities_no));

            // We compute m_entities_with_type[i] so that it is a bitset where the k-th bit is true iff the entity
            // with id 'k' has type t, being one of the required types in 'et'
            for (const auto &[var, et] : m_typed_vars)
                for (const type_ptr &t : et)
                    m_entities_with_type[count++] |= context.entities.get_entities_with_type(context.types, t->get_name()).get_bitset();

            m_combination = combination(m_typed_vars.size());
            m_threshold = std::deque<size_t>(m_typed_vars.size());
            m_counter = std::deque<size_t>(m_typed_vars.size());
            m_has_next = boost::dynamic_bitset<>(m_typed_vars.size());
            restart();
        }

        combinations_handler(const ast::formal_param_list &params, const context &context, const type_ptr &types_tree,
                             const type_checker::either_type &default_type) :
                combinations_handler(types_context::build_typed_var_list(params, types_tree, default_type),
                                     context) {}

        [[nodiscard]] const typed_var_list &get_typed_vars() const {
            return m_typed_vars;
        }

        [[nodiscard]] bool has_next() {
            return m_has_next.any();
        }

        void restart() {
            // We then initialize the first combination, and we keep track in 'm_threshold' of the number of
            // entities of each type
            for (size_t type_id = 0; type_id < m_combination.size(); ++type_id) {
                m_combination[type_id] = m_entities_with_type[type_id].find_first();
                m_threshold[type_id]   = m_entities_with_type[type_id].count() - 1;
                m_counter[type_id]     = 0;
            }

            m_has_next.set();
            m_is_first_comb = true;
            m_has_peeked = false;
        }

        [[nodiscard]] const combination &current() {
            return m_combination;
        }

        [[nodiscard]] const combination &next() {
            if (m_is_first_comb)
                return first();

            if (not m_has_peeked and has_next()) {
                size_t index = m_combination.size();

                while (index >= 1 and not m_has_next[--index])
                    reset(index);

                increment(index);
                m_has_peeked = false;
            }
            return m_combination;
        }

        [[nodiscard]] const combination &peek_next() {
            if (m_has_peeked)
                return m_combination;

            m_has_peeked = true;
            return next();
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
        std::deque<size_t> m_counter, m_threshold;
        boost::dynamic_bitset<> m_has_next;
        bool m_is_first_comb, m_has_peeked;
        typed_var_list m_typed_vars;


        [[nodiscard]] const combination &first() {
            m_is_first_comb = false;
            return m_combination;
        }

        void reset(size_t index) {
            m_combination[index] = m_entities_with_type[index].find_first();
            m_counter[index] = 0;
            m_has_next.set(index, true);
        }

        void increment(size_t index) {
            m_combination[index] = m_entities_with_type[index].find_next(m_combination[index]);
            ++m_counter[index];
            m_has_next.set(index, m_counter[index] < m_threshold[index]);
        }
    };
}

#endif //EPDDL_COMBINATIONS_HANDLER_H
