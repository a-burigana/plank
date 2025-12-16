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

#ifndef EPDDL_FINITARY_S5_THEORY_H
#define EPDDL_FINITARY_S5_THEORY_H

#include "../../language/formulas.h"
#include <vector>

namespace del {
    class finitary_s5_theory;
    using finitary_s5_theory_ptr = std::shared_ptr<finitary_s5_theory>;

    using formula_map = std::vector<formula_deque>;

    class finitary_s5_theory {
    public:
        finitary_s5_theory(formula_deque type_1_formulas, formula_deque type_2_formulas,
                           formula_map type_3_formulas);

        [[nodiscard]] const formula_deque &get_type_1_formulas() const;
        [[nodiscard]] const formula_deque &get_type_2_formulas() const;
        [[nodiscard]] const formula_deque &get_type_3_formulas(del::agent i) const;

    private:
        formula_deque m_type_1_formulas, m_type_2_formulas;
        formula_map m_type_3_formulas;
    };
}

#endif //EPDDL_FINITARY_S5_THEORY_H
