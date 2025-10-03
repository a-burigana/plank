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

#ifndef EPDDL_IMPLY_FORMULA_H
#define EPDDL_IMPLY_FORMULA_H

#include "../formula.h"

namespace del {
    class imply_formula : public formula {
    public:
        imply_formula(formula_ptr f1, formula_ptr f2) :
                m_f1{std::move(f1)},
                m_f2{std::move(f2)} {
            m_type = formula_type::imply_formula;
            m_modal_depth = std::max(m_f1->get_modal_depth(), m_f2->get_modal_depth());
        }

        imply_formula(const imply_formula&) = delete;
        imply_formula& operator=(const imply_formula&) = delete;

        imply_formula(imply_formula&&) = default;
        imply_formula& operator=(imply_formula&&) = default;

        [[nodiscard]] const formula_ptr &get_f1() const { return m_f1; }
        [[nodiscard]] const formula_ptr &get_f2() const { return m_f2; }

    private:
        formula_ptr m_f1, m_f2;
    };
}

#endif //EPDDL_IMPLY_FORMULA_H
