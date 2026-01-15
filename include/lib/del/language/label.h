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

#ifndef PLANK_LABEL_H
#define PLANK_LABEL_H

#include "boost/dynamic_bitset.hpp"
#include "language_types.h"

namespace del {
    class label;

    class label {
    public:
        label() = default;

        explicit label(boost::dynamic_bitset<> bitset);

        label(const label&) = default;
        label& operator=(const label&) = default;

        label(label&&) = default;
        label& operator=(label&&) = default;

        ~label() = default;

        [[nodiscard]] boost::dynamic_bitset<> get_bitset() const;

        bool operator[](const del::atom &p) const;

        bool operator==(const label &rhs) const;
        bool operator!=(const label &rhs) const;
        bool operator< (const label &rhs) const;
        bool operator> (const label &rhs) const;
        bool operator<=(const label &rhs) const;
        bool operator>=(const label &rhs) const;
    private:
        boost::dynamic_bitset<> m_bitset;
    };
}

#endif //PLANK_LABEL_H
