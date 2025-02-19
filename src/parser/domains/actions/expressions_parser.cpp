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

/*#include "../../../../include/parser/domains/actions/expressions_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/parser/domains/actions/action_postconditions_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::expression expressions_parser::parse(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::expression expr;

    if (tok->has_type<keyword_token::object_type>())           expr = expressions_parser::parse_object_expr(helper);
    else if (tok->has_type<keyword_token::agent_type>())       expr = expressions_parser::parse_agent_expr(helper);
    else if (tok->has_type<keyword_token::agent_group_type>()) expr = expressions_parser::parse_agent_group_expr(helper);
    else if (tok->has_type<keyword_token::predicate_type>())   expr = expressions_parser::parse_predicate_expr(helper);
    else if (tok->has_type<keyword_token::literal_type>())     expr = expressions_parser::parse_literal_expr(helper);
    else if (tok->has_type<keyword_token::formula_type>())     expr = expressions_parser::parse_formula_expr(helper);
    else if (tok->has_type<keyword_token::effects>())          expr = expressions_parser::parse_effects_expr(helper);
    else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected expression type. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return expr;
}

ast::expression expressions_parser::parse_object_expr(parser_helper &helper) {
    helper.check_next_token<keyword_token::object_type>();
    return tokens_parser::parse_token<ast::identifier>(helper);
}

ast::expression expressions_parser::parse_agent_expr(parser_helper &helper) {
    helper.check_next_token<keyword_token::agent_type>();
    return tokens_parser::parse_token<ast::identifier>(helper);
}

ast::expression expressions_parser::parse_agent_group_expr(parser_helper &helper) {
    helper.check_next_token<keyword_token::agent_group_type>();
    return tokens_parser::parse_token<ast::identifier>(helper);
}

ast::expression expressions_parser::parse_predicate_expr(parser_helper &helper) {
    helper.check_next_token<keyword_token::predicate_type>();
    return formulas_parser::parse_predicate(helper);
}

ast::expression expressions_parser::parse_literal_expr(parser_helper &helper) {
    helper.check_next_token<keyword_token::literal_type>();
    return formulas_parser::parse_literal(helper);
}

ast::expression expressions_parser::parse_formula_expr(parser_helper &helper) {
    helper.check_next_token<keyword_token::formula_type>();
    return formulas_parser::parse_formula(helper);
}

ast::expression expressions_parser::parse_effects_expr(parser_helper &helper) {
    helper.check_next_token<keyword_token::effects>();
    return action_postconditions_parser::parse_postcondition(helper);
}*/
