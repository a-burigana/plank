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

#ifndef EPDDL_NOT_FORMULA_H
#define EPDDL_NOT_FORMULA_H

#include "../formula.h"

namespace del {
    class not_formula : public formula {
    public:
        explicit not_formula(formula_ptr f) :
                m_f{std::move(f)} {
            m_type = formula_type::not_formula;
            m_modal_depth = m_f->get_modal_depth();
        }

        not_formula(const not_formula&) = delete;
        not_formula& operator=(const not_formula&) = delete;

        not_formula(not_formula&&) = default;
        not_formula& operator=(not_formula&&) = default;

        [[nodiscard]] const formula_ptr &get_f() const { return m_f; }

    private:
        formula_ptr m_f;
    };
}

#endif //EPDDL_NOT_FORMULA_H
