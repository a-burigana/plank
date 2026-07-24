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

#include "../../../../include/frontend/bfs-planner/signatures/signature.h"

using namespace search::utils;

signature::signature(const label_id label_id, agents_signature_set signature_set) :
    m_label_id{label_id},
    m_signature_set{std::move(signature_set)} {}

const label_id &signature::get_label_id() const {
    return m_label_id;
}

signature_set_id signature::get_signature_set_id(del::agent ag) const {
    return m_signature_set[ag];
}

bool signature::operator==(const signature &rhs) const {
    return m_label_id == rhs.m_label_id and m_signature_set == rhs.m_signature_set;
}

bool signature::operator!=(const signature &rhs) const {
    return not (*this == rhs);
}

bool signature::operator<(const signature &rhs) const {
    if (m_label_id != rhs.m_label_id) return m_label_id < rhs.m_label_id;
    return m_signature_set < rhs.m_signature_set;
}

bool signature::operator>(const signature &rhs) const {
    if (m_label_id != rhs.m_label_id) return m_label_id > rhs.m_label_id;
    return m_signature_set > rhs.m_signature_set;
}

bool signature::operator<=(const signature &rhs) const {
    return *this < rhs or *this == rhs;
}

bool signature::operator>=(const signature &rhs) const {
    return *this > rhs or *this == rhs;
}
