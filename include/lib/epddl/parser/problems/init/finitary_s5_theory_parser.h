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

#ifndef PLANK_FINITARY_S5_THEORY_PARSER_H
#define PLANK_FINITARY_S5_THEORY_PARSER_H

#include "ast/problems/init/finitary_s5_theory_ast.h"
#include "parser/parser_helper.h"

namespace epddl::parser {
    class finitary_s5_theory_parser {
    public:
        static ast::finitary_S5_theory parse(parser_helper &helper);

    private:
        static ast::finitary_S5_formula parse_formula(parser_helper &helper);

        static ast::prop_formula_ptr parse_prop_formula(parser_helper &helper);
        static ast::ck_formula_ptr parse_ck_formula(parser_helper &helper);
        static ast::ck_k_formula_ptr parse_ck_k_formula(parser_helper &helper);
        static ast::ck_kw_formula_ptr parse_ck_kw_formula(parser_helper &helper);
        static ast::ck_not_kw_formula_ptr parse_ck_not_kw_formula(parser_helper &helper);
    };
}

#endif //PLANK_FINITARY_S5_THEORY_PARSER_H
