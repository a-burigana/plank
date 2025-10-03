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

#ifndef EPDDL_FORMULA_H
#define EPDDL_FORMULA_H

#include <deque>
#include <variant>
#include "formula_types.h"

namespace del {
    class formula;
    using formula_ptr   = std::shared_ptr<formula>;
    using formula_deque = std::deque<formula_ptr>;

    class formula {
    public:
        formula() :
            m_type{formula_type::true_formula},
            m_modal_depth{0} {}

        formula(const formula&) = delete;
        formula& operator=(const formula&) = delete;

        formula(formula&&) = default;
        formula& operator=(formula&&) = default;

        virtual ~formula() = default;

        [[nodiscard]] virtual formula_type get_type() const { return m_type; }
        [[nodiscard]] virtual unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] virtual bool is_propositional() const { return m_modal_depth == 0; }

    protected:
        formula_type m_type;
        unsigned long m_modal_depth;
    };
}

#endif //EPDDL_FORMULA_H
