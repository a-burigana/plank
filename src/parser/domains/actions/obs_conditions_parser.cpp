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

#include "../../../../include/parser/domains/actions/obs_conditions_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/typed_elem_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::obs_cond obs_conditions_parser::parse_action_obs_cond(parser_helper &helper) {
    helper.check_next_token<keyword_token::obs_conditions>();
    return obs_conditions_parser::parse_obs_cond(helper);
}

ast::obs_cond obs_conditions_parser::parse_obs_cond(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::obs_cond obs_cond;

    if (tok->has_type<ast_token::identifier>())                  obs_cond = obs_conditions_parser::parse_static_obs_cond(helper);
    else if (tok->has_type<observability_token::if_cond>())      obs_cond = obs_conditions_parser::parse_if_then_else_obs_cond(helper);
    else if (tok->has_type<quantifier_token::forall>())          obs_cond = obs_conditions_parser::parse_forall_obs_cond(helper);
    else if (tok->has_type<observability_token::default_cond>()) obs_cond = obs_conditions_parser::parse_default_obs_cond(helper);
    else if (tok->has_type<connective_token::conjunction>())     obs_cond = obs_conditions_parser::parse_and_obs_cond(helper);
    else if (tok->has_type<observability_token::else_if_cond>())
        throw EPDDLParserException("", tok->get_row(), tok->get_col(),
                                   "Ill formed observability condition: 'else-if' must be preceded by 'if'.");
    else if (tok->has_type<observability_token::else_cond>())
        throw EPDDLParserException("", tok->get_row(), tok->get_col(),
                                   "Ill formed observability condition: 'else' must be preceded by 'if'.");
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(),
                                   "Expected observability condition. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return obs_cond;
}

ast::static_obs_cond_ptr obs_conditions_parser::parse_static_obs_cond(parser_helper &helper) {
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(helper);
    ast::term ag = formulas_parser::parse_term(helper);

    return std::make_shared<ast::static_obs_condition>(std::move(obs_group), std::move(ag));
}

ast::if_then_else_obs_cond_ptr obs_conditions_parser::parse_if_then_else_obs_cond(parser_helper &helper) {
    ast::if_obs_cond_ptr if_cond = obs_conditions_parser::parse_if_obs_cond(helper);
    auto else_if_cond_list = helper.parse_list<ast::else_if_obs_cond_ptr, observability_token::else_cond>([&]() { return obs_conditions_parser::parse_else_if_obs_cond(helper); }, true);
    auto else_cond = helper.parse_optional<ast::else_obs_cond_ptr, observability_token::else_cond>([&] () { return obs_conditions_parser::parse_else_obs_cond(helper); });

    return std::make_shared<ast::if_then_else_obs_condition>(std::move(if_cond), std::move(else_if_cond_list), std::move(else_cond));
}

ast::if_obs_cond_ptr obs_conditions_parser::parse_if_obs_cond(parser_helper &helper) {
    helper.check_next_token<observability_token::if_cond>();
    ast::formula_ptr cond = formulas_parser::parse_formula(helper);
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(helper);
    ast::term ag = formulas_parser::parse_term(helper);

    return std::make_shared<ast::if_obs_condition>(std::move(cond), std::move(obs_group), std::move(ag));
}

ast::else_if_obs_cond_ptr obs_conditions_parser::parse_else_if_obs_cond(parser_helper &helper) {
    helper.check_next_token<observability_token::else_if_cond>();
    ast::formula_ptr cond = formulas_parser::parse_formula(helper);
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(helper);
    ast::term ag = formulas_parser::parse_term(helper);

    return std::make_shared<ast::else_if_obs_condition>(std::move(cond), std::move(obs_group), std::move(ag));
}

ast::else_obs_cond_ptr obs_conditions_parser::parse_else_obs_cond(parser_helper &helper) {
    helper.check_next_token<observability_token::else_cond>();
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(helper);
    ast::term ag = formulas_parser::parse_term(helper);

    return std::make_shared<ast::else_obs_condition>(std::move(obs_group), std::move(ag));
}

ast::forall_obs_cond_ptr obs_conditions_parser::parse_forall_obs_cond(parser_helper &helper) {
    helper.check_next_token<quantifier_token::forall>();
    helper.check_next_token<punctuation_token::lpar>();
    auto list_comprehension = formulas_parser::parse_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();
    ast::obs_cond obs_cond = obs_conditions_parser::parse_obs_cond(helper);

    return std::make_shared<ast::forall_obs_condition>(std::move(list_comprehension), std::move(obs_cond));
}

ast::default_obs_cond_ptr obs_conditions_parser::parse_default_obs_cond(parser_helper &helper) {
    helper.check_next_token<observability_token::default_cond>();
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(helper);

    return std::make_shared<ast::default_obs_condition>(std::move(obs_group));
}

ast::and_obs_cond_ptr obs_conditions_parser::parse_and_obs_cond(epddl::parser::parser_helper &helper) {
    helper.check_next_token<connective_token::conjunction>();
    auto obs_cond_list = helper.parse_list<ast::obs_cond>([&]() { return obs_conditions_parser::parse_obs_cond(helper); });

    return std::make_shared<ast::and_obs_condition>(std::move(obs_cond_list));
}

//ast::observing_agent obs_conditions_parser::parse_observing_agent(parser_helper &helper) {
//    const token_ptr &tok = helper.peek_next_token();
//    ast::observing_agent ag;
//
//    if (tok->has_type<ast_token::identifier>())    ag = std::move(tokens_parser::parse_token<ast::identifier>(helper));
//    else if (tok->has_type<ast_token::variable>()) ag = std::move(tokens_parser::parse_token<ast::variable>(helper));
//    else if (tok->has_type<agent_group_token::all>()) {
//        helper.check_next_token<agent_group_token::all>();
//        ag = agent_group_token::all{};
//    } else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected variable or agent identifier. Found: " + tok->to_string());
//
//    return ag;
//}
