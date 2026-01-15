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

#include "../../../../include/lib/del/language/label.h"

using namespace del;

label::label(boost::dynamic_bitset<> bitset) :
        m_bitset{std::move(bitset)} {}

boost::dynamic_bitset<> label::get_bitset() const {
    return m_bitset;
}

bool label::operator[](const del::atom &p) const {
    return m_bitset[p];
}

bool label::operator==(const label &rhs) const {
    return m_bitset == rhs.m_bitset;
}

bool label::operator!=(const label &rhs) const {
    return m_bitset != rhs.m_bitset;
}

bool label::operator<(const label &rhs) const {
    return m_bitset < rhs.m_bitset;
}

bool label::operator>(const label &rhs) const {
    return m_bitset > rhs.m_bitset;
}

bool label::operator<=(const label &rhs) const {
    return m_bitset <= rhs.m_bitset;
}

bool label::operator>=(const label &rhs) const {
    return m_bitset >= rhs.m_bitset;
}
