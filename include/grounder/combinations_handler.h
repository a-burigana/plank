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

#include "../type-checker/context.h"
#include <deque>
#include <type_traits>

using namespace epddl::type_checker;

namespace epddl::grounder {
    using combination   = std::deque<unsigned long>;
    using bitset_vector = std::vector<boost::dynamic_bitset<>>;

    class combinations_handler {
    public:
        explicit combinations_handler(const either_type_list &types, const context &context) {
            unsigned long entities_no = context.get_entities_with_type("entity").size(), count = 0;
            m_entities_with_type = bitset_vector(types.size(), boost::dynamic_bitset<>(entities_no));

            // We compute m_entities_with_type[i] so that it is a bitset where the k-th bit is true iff the entity
            // with id 'k' has type t, being one of the required types in 'et'
            for (const type_checker::either_type &et : types)
                for (const type_ptr &t : et)
                    m_entities_with_type[count++] |= context.get_entities_with_type(t->get_name()).get_bitset();

            // We then initialize the first combination, and we keep track in 'm_threshold' of the number of
            // entities of each type
            for (size_t type_id = 0; type_id < types.size(); ++type_id) {
                m_combination.emplace_back(m_entities_with_type[type_id].find_first());
                m_threshold.emplace_back(m_entities_with_type[type_id].count() - 1);
                m_counter.emplace_back(0);
            }

            m_has_next = boost::dynamic_bitset<>(types.size());
            m_has_next.set();
            m_is_first_comb = true;
        }

        [[nodiscard]] bool has_next() {
            return m_has_next.any();
        }

        [[nodiscard]] const combination &next() {
            if (m_is_first_comb)
                return first();

            if (has_next()) {
                size_t index = m_combination.size();

                while (index >= 1 and not m_has_next[--index])
                    reset(index);

                increment(index);
            }
            return m_combination;
        }

    private:
        bitset_vector m_entities_with_type;
        combination m_combination;
        std::deque<size_t> m_counter, m_threshold;
        boost::dynamic_bitset<> m_has_next;
        bool m_is_first_comb;


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
