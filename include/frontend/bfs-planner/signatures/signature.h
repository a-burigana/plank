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

#ifndef PLANK_SIGNATURE_H
#define PLANK_SIGNATURE_H

#include <vector>
#include "signature_types.h"
#include "del/language/language.h"
#include "del/language/formulas.h"

using namespace plank;

namespace search::utils {
    class signature {
    public:
        signature(label_id label_id, agents_signature_set signature_set);

        signature(const signature&) = default;
        signature& operator=(const signature&) = default;

        signature(signature&&) = default;
        signature& operator=(signature&&) = default;

        ~signature() = default;

        [[nodiscard]] const label_id &get_label_id() const;
        [[nodiscard]] signature_set_id get_signature_set_id(del::agent ag) const;

        bool operator==(const signature &rhs) const;
        bool operator!=(const signature &rhs) const;
        bool operator< (const signature &rhs) const;
        bool operator> (const signature &rhs) const;
        bool operator<=(const signature &rhs) const;
        bool operator>=(const signature &rhs) const;

    private:
        label_id m_label_id;
        agents_signature_set m_signature_set;
    };
}

#endif //PLANK_SIGNATURE_H
