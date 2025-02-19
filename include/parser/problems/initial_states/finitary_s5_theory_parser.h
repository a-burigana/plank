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

#ifndef EPDDL_FINITARY_S5_THEORY_PARSER_H
#define EPDDL_FINITARY_S5_THEORY_PARSER_H

#include "../../parser_helper.h"
#include "../../../ast/problems/initial_states/finitary_s5_theory_ast.h"

namespace epddl::parser {
    class finitary_s5_theory_parser {
    public:
        static ast::finitary_s5_theory_ptr parse(parser_helper &helper);

        static ast::theory_formula_ptr parse_theory_formula(parser_helper &helper);
        static ast::ck_formula_ptr parse_ck_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_atomic_formula(parser_helper &helper);

        static ast::atomic_formula_ptr parse_pred_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_not_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_and_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_or_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_imply_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_forall_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_exists_atomic_formula(parser_helper &helper);

        static ast::ck_formula_ptr parse_K_or_Kw_formula(parser_helper &helper);
        static ast::ck_not_Kw_formula_ptr parse_not_Kw_formula(parser_helper &helper);
    };
}

#endif //EPDDL_FINITARY_S5_THEORY_PARSER_H
