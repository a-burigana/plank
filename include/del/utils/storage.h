// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano_
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

#ifndef EPDDL_STORAGE_H
#define EPDDL_STORAGE_H

#include <memory>
#include <deque>
#include <map>

namespace del {
    template<typename Elem>
    class storage {
        using storage_ptr = std::shared_ptr<storage<Elem>>;
        using Elem_ptr = std::shared_ptr<Elem>;
        using Elem_id = unsigned long long;

    public:
        storage() {
            m_elements.emplace_back(nullptr);
            m_count = 1;
        }

        explicit storage(Elem &&null) {
            m_count = 0;
            emplace(std::move(null));
        }

        storage(const storage &) = default;
        storage &operator=(const storage &) = default;

        storage(storage &&) noexcept = default;
        storage &operator=(storage &&) noexcept = default;

        ~storage() = default;

        typename storage<Elem>::Elem_id emplace(Elem &&elem) {
            if (m_elements_ids.find(elem) != m_elements_ids.end())          // If the element is already stored, then we simply
                return m_elements_ids.at(elem);                             // return its id

            const auto &[it, _] = m_elements_ids.emplace(std::move(elem), m_count);
            m_elements.emplace_back(std::make_shared<Elem>(it->first));     // Otherwise, we assign the new element a fresh id,
            return m_count++;                                               // we add it to the deque to ensure constant time
        }                                                                   // retrieval from id and we return its id

        typename storage<Elem>::Elem_ptr get(Elem_id id) const {
            return m_elements[id];
        }

        [[nodiscard]] bool is_null(Elem_id id) const {
            return id == 0;
        }

    private:
        std::map<Elem, Elem_id> m_elements_ids;
        std::deque<Elem_ptr> m_elements;
        unsigned long m_count;
    };
}

#endif //EPDDL_STORAGE_H
