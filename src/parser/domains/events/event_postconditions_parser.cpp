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

#include "../../../../include/parser/domains/events/event_postconditions_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/parser/common/typed_elem_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::list<ast::postcondition> event_postconditions_parser::parse(parser_helper &helper) {
    // Event effects list
    return formulas_parser::parse_list<
            ast::postcondition, ast_token::identifier, connective_token::negation,
            post_connective_token::when, post_connective_token::iff>(
        helper, error_manager::get_error_info(decl_type::effects_decl), [&]() {
            return event_postconditions_parser::parse_event_postcondition(helper);
        }, false);
}

ast::postcondition event_postconditions_parser::parse_event_postcondition(parser_helper &helper) {
    // Event effects
    const token_ptr &tok = helper.peek_next_token();
    bool found_lpar = tok->has_type<punctuation_token::lpar>();
    ast::postcondition post;

    // When 'parse_event_postcondition' is called from 'event_decl_parser::parse_effects', the outer parentheses
    // are checked by the caller function to verify whether we are in the case ":effects ()". Otherwise, if the
    // caller is the lambda function passed to 'event_postconditions_parser::parse', the outer parentheses have
    // to be taken care of here
    const std::string err_info = error_manager::get_error_info(decl_type::effects_decl);
    if (found_lpar) helper.check_left_par(err_info);

    if (tok->has_either_type<ast_token::identifier, connective_token::negation>())
        post = event_postconditions_parser::parse_literal_postcondition(helper);
    else if (tok->has_type<post_connective_token::when>())
        post = event_postconditions_parser::parse_when_postcondition(helper);
    else if (tok->has_type<post_connective_token::iff>())
        post = event_postconditions_parser::parse_iff_postcondition(helper);
    else
        helper.throw_error(error_type::token_mismatch, tok, err_info);

    // End event effects
    if (found_lpar) helper.check_right_par(err_info);

    return post;
}

ast::literal_postcondition_ptr event_postconditions_parser::parse_literal_postcondition(parser_helper &helper) {
    // Literal effect
    ast::info info = helper.get_next_token_info();

    ast::literal_ptr literal = formulas_parser::parse_literal(helper, false);
    return std::make_shared<ast::literal_postcondition>(std::move(info), std::move(literal));
}

ast::iff_postcondition_ptr event_postconditions_parser::parse_iff_postcondition(parser_helper &helper) {
    // Conditional (iff) effect
    ast::info info = helper.get_next_token_info();
    info.add_requirement(":conditional-effects", error_manager::get_requirement_warning(requirement_warning::conditional_effects_iff));

    helper.check_next_token<post_connective_token::iff>();

    // Condition
    ast::formula_ptr cond = formulas_parser::parse_formula(helper, formula_type::postcondition);

    // Literal list
    ast::list<ast::literal_ptr> literals = formulas_parser::parse_list<ast::literal_ptr,
            ast_token::identifier, connective_token::negation>(
            helper, error_manager::get_error_info(decl_type::literal_list), [&]() {
                return formulas_parser::parse_literal(helper, false);
            });

    return std::make_shared<ast::iff_postcondition>(std::move(info), std::move(cond), std::move(literals));
}

ast::when_postcondition_ptr event_postconditions_parser::parse_when_postcondition(parser_helper &helper) {
    // Conditional (when) effect
    ast::info info = helper.get_next_token_info();
    info.add_requirement(":conditional-effects", error_manager::get_requirement_warning(requirement_warning::conditional_effects_when));

    helper.check_next_token<post_connective_token::when>();

    // Condition
    ast::formula_ptr cond = formulas_parser::parse_formula(helper, formula_type::postcondition);

    // Literal list
    ast::list<ast::literal_ptr> literals = formulas_parser::parse_list<ast::literal_ptr,
            ast_token::identifier, connective_token::negation>(
            helper, error_manager::get_error_info(decl_type::literal_list), [&]() {
                return formulas_parser::parse_literal(helper, false);
            });

    return std::make_shared<ast::when_postcondition>(std::move(info), std::move(cond), std::move(literals));
}
