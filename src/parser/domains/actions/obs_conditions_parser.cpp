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

ast::list<ast::obs_cond> obs_conditions_parser::parse_action_obs_cond(parser_helper &helper,
                                                                      const std::string &action_name) {
    // Action observability conditions
    helper.check_next_token<keyword_token::obs_conditions>();
    const std::string what = "observability conditions of action '" + action_name + "'";

    helper.push_error_info(what);

    auto obs_conditions = formulas_parser::parse_list<ast::obs_cond, ast_token::identifier,
        ast_token::variable, observability_token::default_cond>(helper, what, [&]() {
            return obs_conditions_parser::parse_obs_cond(helper, false);
        });

    // End action observability conditions
    helper.pop_error_info();

    return obs_conditions;
}

ast::obs_cond obs_conditions_parser::parse_obs_cond(parser_helper &helper, bool parse_outer_pars) {
    // Action observability condition
    ast::obs_cond obs_cond;
    const std::string what = "observability condition declaration";

    if (parse_outer_pars) helper.check_left_par(what);
    const token_ptr &tok = helper.peek_next_token();

    if (tok->has_either_type<ast_token::identifier, ast_token::variable>())
        obs_cond = obs_conditions_parser::parse_static_or_ite_obs_cond(helper, false);
    else if (tok->has_type<observability_token::default_cond>())
        obs_cond = obs_conditions_parser::parse_default_obs_cond(helper);
    else if (tok->has_type<observability_token::if_cond>())
        helper.throw_error(error_type::bad_obs_cond, tok, "expected agent term before if-then-else condition");
    else if (tok->has_type<observability_token::else_if_cond>())
        helper.throw_error(error_type::bad_obs_cond, tok, "expected 'if' condition before 'else-if' condition");
    else if (tok->has_type<observability_token::else_cond>())
        helper.throw_error(error_type::bad_obs_cond, tok, "expected 'if' condition before 'else' condition");
    else
        helper.throw_error(error_type::token_mismatch, tok, "observability condition");

    // End action observability condition
    if (parse_outer_pars) helper.check_right_par(what);

    return obs_cond;
}

ast::obs_cond obs_conditions_parser::parse_static_or_ite_obs_cond(parser_helper &helper, bool parse_outer_pars) {
    // Static of if-then-else observability condition
    ast::info info = helper.get_next_token_info();
    const std::string what = "observability condition declaration";

    if (parse_outer_pars) helper.check_left_par(what);

    // Agent
    ast::term ag = formulas_parser::parse_term(helper, "agent term");

    // Condition
    const token_ptr &tok = helper.peek_next_token();
    obs_cond obs_cond;

    if (tok->has_type<ast_token::identifier>()) {
        ast::identifier_ptr obs_type = tokens_parser::parse_identifier(helper, "observability type name");

        obs_cond = std::make_shared<ast::static_obs_condition>(
                std::move(info), std::move(ag), std::move(obs_type));
    } else if (tok->has_type<punctuation_token::lpar>()) {
        const std::string what_ = "observability condition";
        helper.check_left_par(what_);

        // If condition
        ast::if_obs_cond_ptr if_cond = obs_conditions_parser::parse_if_obs_cond(helper);

        // Else-if condition list
        auto else_if_cond_list = helper.parse_list<ast::else_if_obs_cond_ptr, observability_token::else_cond>(
            [&]() {
                    return obs_conditions_parser::parse_else_if_obs_cond(helper);
                }, true);

        auto else_cond = helper.parse_optional<ast::else_obs_cond_ptr, observability_token::else_cond>(
            [&] () {
                    return obs_conditions_parser::parse_else_obs_cond(helper);
                });

        helper.check_right_par(what_);

        obs_cond = std::make_shared<ast::if_then_else_obs_condition>(
                std::move(info), std::move(ag), std::move(if_cond),
                std::move(else_if_cond_list), std::move(else_cond));
    } else
        helper.throw_error(error_type::token_mismatch, tok, "static or if-then-else condition");

    // End static of if-then-else observability condition
    if (parse_outer_pars) helper.check_right_par(what);

    return obs_cond;
}

ast::if_obs_cond_ptr obs_conditions_parser::parse_if_obs_cond(parser_helper &helper) {
    // If observability condition
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<observability_token::if_cond>();
    ast::formula_ptr cond = formulas_parser::parse_formula(helper, formula_type::obs_condition);
    ast::identifier_ptr obs_type = tokens_parser::parse_identifier(helper, "observability type name");

    return std::make_shared<ast::if_obs_condition>(std::move(info), std::move(cond), std::move(obs_type));
}

ast::else_if_obs_cond_ptr obs_conditions_parser::parse_else_if_obs_cond(parser_helper &helper) {
    // Else if observability condition
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<observability_token::else_if_cond>();
    ast::formula_ptr cond = formulas_parser::parse_formula(helper, formula_type::obs_condition);
    ast::identifier_ptr obs_type = tokens_parser::parse_identifier(helper, "observability type name");

    return std::make_shared<ast::else_if_obs_condition>(std::move(info), std::move(cond), std::move(obs_type));
}

ast::else_obs_cond_ptr obs_conditions_parser::parse_else_obs_cond(parser_helper &helper) {
    // Else observability condition
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<observability_token::else_cond>();
    ast::identifier_ptr obs_type = tokens_parser::parse_identifier(helper, "observability type name");

    return std::make_shared<ast::else_obs_condition>(std::move(info), std::move(obs_type));
}

ast::default_obs_cond_ptr obs_conditions_parser::parse_default_obs_cond(parser_helper &helper) {
    // Default observability condition
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<observability_token::default_cond>();
    ast::identifier_ptr obs_type = tokens_parser::parse_identifier(helper, "observability type name");

    return std::make_shared<ast::default_obs_condition>(std::move(info), std::move(obs_type));
}
