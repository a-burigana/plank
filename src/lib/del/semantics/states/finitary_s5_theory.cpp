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

#include "../../../../../include/lib/del/semantics/states/finitary_s5_theory.h"

using namespace del;

finitary_s5_theory::finitary_s5_theory(formula_deque type_1_formulas, formula_deque type_2_formulas,
        formula_map type_3_formulas) :
        m_type_1_formulas{std::move(type_1_formulas)},
        m_type_2_formulas{std::move(type_2_formulas)},
        m_type_3_formulas{std::move(type_3_formulas)} {}

const formula_deque &finitary_s5_theory::get_type_1_formulas() const {
    return m_type_1_formulas;
}

const formula_deque &finitary_s5_theory::get_type_2_formulas() const {
    return m_type_2_formulas;
}

const formula_deque &finitary_s5_theory::get_type_3_formulas(const del::agent i) const {
    return m_type_3_formulas[i];
}
