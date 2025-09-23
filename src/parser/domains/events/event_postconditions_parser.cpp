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

std::optional<ast::postconditions> event_postconditions_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::effects>();
    helper.check_next_token<punctuation_token::lpar>();
    auto post = helper.parse_optional<ast::postconditions,
            ast_token::identifier, connective_token::negation, post_connective_token::when,
            post_connective_token::iff, quantifier_token::forall, connective_token::conjunction>(
            [&]() { return event_postconditions_parser::parse_event_postcondition(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return post;
}

ast::postconditions event_postconditions_parser::parse_event_postcondition(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    ast::postconditions post;

    if (tok->has_either_type<ast_token::identifier, connective_token::negation>())
        post = event_postconditions_parser::parse_literal_postcondition(helper);
    else if (tok->has_type<post_connective_token::when>())
        post = event_postconditions_parser::parse_when_postcondition(helper);
    else if (tok->has_type<post_connective_token::iff>())
        post = event_postconditions_parser::parse_iff_postcondition(helper);
    else if (tok->has_type<quantifier_token::forall>())
        post = event_postconditions_parser::parse_forall_postcondition(helper);
    else if (tok->has_type<connective_token::conjunction>())
        post = event_postconditions_parser::parse_and_postcondition(helper);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(),
                                   "Expected postconditions. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return post;
}

ast::literal_postcondition_ptr event_postconditions_parser::parse_literal_postcondition(parser_helper &helper) {
    ast::literal_ptr literal = formulas_parser::parse_literal(helper, false);
    return std::make_shared<ast::literal_postcondition>(std::move(literal));
}

ast::iff_postcondition_ptr event_postconditions_parser::parse_iff_postcondition(parser_helper &helper) {
    helper.check_next_token<post_connective_token::iff>();
    ast::formula_ptr cond = formulas_parser::parse_formula(helper);
    ast::literal_list literals = helper.parse_list<ast::literal_ptr>(
            [&]() { return formulas_parser::parse_literal(helper); });

    return std::make_shared<ast::iff_postcondition>(std::move(cond), std::move(literals));
}

ast::when_postcondition_ptr event_postconditions_parser::parse_when_postcondition(parser_helper &helper) {
    helper.check_next_token<post_connective_token::when>();
    ast::formula_ptr cond = formulas_parser::parse_formula(helper);
    ast::literal_list literals = helper.parse_list<ast::literal_ptr>(
            [&]() { return formulas_parser::parse_literal(helper); });

    return std::make_shared<ast::when_postcondition>(std::move(cond), std::move(literals));
}

ast::forall_postcondition_ptr event_postconditions_parser::parse_forall_postcondition(parser_helper &helper) {
    helper.check_next_token<quantifier_token::forall>();
    helper.check_next_token<punctuation_token::lpar>();
    auto list_comprehension = formulas_parser::parse_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();
    auto post = event_postconditions_parser::parse_event_postcondition(helper);

    return std::make_shared<ast::forall_postcondition>(std::move(list_comprehension), std::move(post));
}

ast::and_postcondition_ptr event_postconditions_parser::parse_and_postcondition(epddl::parser::parser_helper &helper) {
    helper.check_next_token<connective_token::conjunction>();
    auto post_list = helper.parse_list<ast::postconditions>([&]() { return event_postconditions_parser::parse_event_postcondition(helper); });

    return std::make_shared<ast::and_postcondition>(std::move(post_list));
}
