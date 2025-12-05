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

#ifndef EPDDL_BIT_DEQUE_H
#define EPDDL_BIT_DEQUE_H

#include <boost/dynamic_bitset.hpp>
#include <cstddef>
#include <deque>
#include <unordered_set>

class bit_deque {
public:
    using index       = unsigned long long;
    using index_deque = std::deque<index>;
    using index_set   = std::unordered_set<index>;
    using iterator    = index_deque::const_iterator;

    bit_deque() : m_id{0} {}

    explicit bit_deque(unsigned long long size, unsigned long id = 0) :
            m_bitset{boost::dynamic_bitset<>(size)},
            m_id{id} {}

    bit_deque(unsigned long long size, index_deque deque, unsigned long id = 0) :
            m_bitset{boost::dynamic_bitset<>(size)},
            m_deque{std::move(deque)},
            m_id{id} {
        for (const index i : m_deque)
            if (not m_bitset[i])
                m_bitset[i].flip();
    }

    bit_deque(unsigned long long size, const index_set &set, unsigned long id = 0) :
            m_bitset{boost::dynamic_bitset<>(size)},
            m_id{id} {
        for (index i : set) {
            m_deque.push_back(i);
            if (not m_bitset[i]) m_bitset[i].flip();
        }
    }

    explicit bit_deque(const boost::dynamic_bitset<> &bitset, unsigned long id = 0) : m_id{id} {
        m_bitset = boost::dynamic_bitset<>(bitset.size());

        for (size_t b = 0; b < bitset.size(); ++b)
            if (bitset[b])
                push_back(b);
    }

    bit_deque(const bit_deque&) = default;
    bit_deque& operator=(const bit_deque&) = default;

    bit_deque(bit_deque&&) = default;
    bit_deque& operator=(bit_deque&&) = default;

    ~bit_deque() = default;

    [[nodiscard]] const boost::dynamic_bitset<> &get_bitset() const { return m_bitset; }
    [[nodiscard]] bool empty() const { return m_deque.empty(); }
    [[nodiscard]] size_t size() const { return m_deque.size(); }

    [[nodiscard]] bool find(index i) const {
        return m_bitset[i];
    }

    void push_back(const index i) {
        if (not m_bitset[i]) {
            m_bitset[i].flip();
            m_deque.push_back(i);
        }
    }

    void remove(const index i) {
        if (m_bitset[i]) {
            m_bitset[i].flip();
            m_deque.erase(std::find(m_deque.begin(), m_deque.end(), i));
        }
    }

    void resize(const size_t size) {
        m_bitset.resize(size, false);
    }

    [[nodiscard]] unsigned long get_id() const { return m_id; }
    void set_id(const unsigned long id) { m_id = id; }

    boost::dynamic_bitset<> operator&(const bit_deque &rhs) { return this->m_bitset & rhs.m_bitset; }
    boost::dynamic_bitset<> operator-(const bit_deque &rhs) { return this->m_bitset - rhs.m_bitset; }

    bool operator< (const bit_deque &rhs) const { return m_bitset.to_ulong() <  rhs.m_bitset.to_ulong(); }
    bool operator<=(const bit_deque &rhs) const { return m_bitset.to_ulong() <= rhs.m_bitset.to_ulong(); }
    bool operator> (const bit_deque &rhs) const { return m_bitset.to_ulong() >  rhs.m_bitset.to_ulong(); }
    bool operator>=(const bit_deque &rhs) const { return m_bitset.to_ulong() >= rhs.m_bitset.to_ulong(); }
    bool operator==(const bit_deque &rhs) const { return m_bitset.to_ulong() == rhs.m_bitset.to_ulong(); }
    bool operator!=(const bit_deque &rhs) const { return m_bitset.to_ulong() != rhs.m_bitset.to_ulong(); }

    const boost::dynamic_bitset<> &operator*() const { return m_bitset; }
    index operator[](const size_t i) const { return m_deque[i]; }

    [[nodiscard]] iterator begin() const { return m_deque.begin(); }
    [[nodiscard]] iterator end()   const { return m_deque.end();   }

    [[nodiscard]] index front() const { return m_deque[0]; }

private:
    boost::dynamic_bitset<> m_bitset;
    index_deque m_deque;
    unsigned long m_id{};
};

#endif //EPDDL_BIT_DEQUE_H
