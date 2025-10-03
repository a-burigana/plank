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

#ifndef EPDDL_ATOM_FORMULA_H
#define EPDDL_ATOM_FORMULA_H

#include "../formula.h"
#include "../../language/language_types.h"

namespace del {
    class atom_formula : public formula {
    public:
        explicit atom_formula(atom atom) :
                m_atom{atom} {
            m_type = formula_type::atom_formula;
            m_modal_depth = 0;
        }

        atom_formula(const atom_formula&) = delete;
        atom_formula& operator=(const atom_formula&) = delete;

        atom_formula(atom_formula&&) = default;
        atom_formula& operator=(atom_formula&&) = default;

        [[nodiscard]] const atom &get_atom() const { return m_atom; }

    private:
        atom m_atom;
    };
}

#endif //EPDDL_ATOM_FORMULA_H
