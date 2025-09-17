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

#ifndef EPDDL_FORMULAS_PARSER_H
#define EPDDL_FORMULAS_PARSER_H

#include "../../ast/common/formulas_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class formulas_parser {
    public:
        static ast::formula_ptr parse_formula(parser_helper &helper);

        static ast::formula_ptr parse_true_formula(parser_helper &helper);
        static ast::formula_ptr parse_false_formula(parser_helper &helper);

        static ast::formula_ptr parse_predicate_formula(parser_helper &helper);
        static ast::formula_ptr parse_eq_formula(parser_helper &helper);
        static ast::formula_ptr parse_neq_formula(parser_helper &helper);
        static ast::formula_ptr parse_not_formula(parser_helper &helper);
        static ast::formula_ptr parse_and_formula(parser_helper &helper);
        static ast::formula_ptr parse_or_formula(parser_helper &helper);
        static ast::formula_ptr parse_imply_formula(parser_helper &helper);
        static ast::formula_ptr parse_box_formula(parser_helper &helper);
        static ast::formula_ptr parse_diamond_formula(parser_helper &helper);

        static ast::formula_ptr parse_such_that(parser_helper &helper);
        static ast::ext_list_comprehension_ptr parse_ext_list_comprehension(parser_helper &helper, ast::variable_list &&prefix = ast::variable_list{});
        static ast::int_list_comprehension_ptr parse_int_list_comprehension(parser_helper &helper, bool allow_empty_params = false);
        static ast::list_comprehension_ptr parse_list_comprehension(parser_helper &helper);
        static ast::formula_ptr parse_in_formula(parser_helper &helper);

        static ast::formula_ptr parse_forall_formula(parser_helper &helper);
        static ast::formula_ptr parse_exists_formula(parser_helper &helper);

        static ast::predicate_ptr parse_predicate(parser_helper &helper, bool parse_outer_pars = true);
        static ast::literal_ptr parse_literal(parser_helper &helper);
        static ast::term parse_term(parser_helper &helper);

        static ast::modality_ptr parse_modality(parser_helper &helper);
        static ast::modality_index_ptr parse_modality_index(parser_helper &helper);

        static ast::single_modality_index_ptr parse_single_modality(parser_helper &helper);
        static ast::group_modality_index_ptr parse_group_modality(parser_helper &helper);
    };
}

#endif //EPDDL_FORMULAS_PARSER_H
