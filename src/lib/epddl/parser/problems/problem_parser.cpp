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

#include "parser/problems/problem_parser.h"
#include "parser/tokens/tokens_parser.h"
#include "error-manager/epddl_exception.h"
#include "parser/problems/problem_domain_parser.h"
#include "parser/domains/requirements_parser.h"
#include "parser/problems/objects_parser.h"
#include "parser/problems/agents_parser.h"
#include "parser/problems/agent_groups_parser.h"
#include "parser/problems/init/initial_state_parser.h"
#include "parser/problems/goal_parser.h"
#include "parser/problems/init/facts_init_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::problem_ptr problem_parser::parse(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    // Problem
    helper.check_left_par(error_manager::get_error_info(decl_type::anon_problem_decl));
    helper.check_next_token<keyword_token::define>();

    // Problem name
    helper.check_left_par(error_manager::get_error_info(decl_type::problem_name));
    helper.check_next_token<keyword_token::problem>();
    ast::identifier_ptr problem_name = tokens_parser::parse_identifier(helper, error_manager::get_error_info(decl_type::problem_name));
    const std::string err_info = error_manager::get_error_info(decl_type::problem_decl, problem_name->get_token().get_lexeme());

    // End problem name
    helper.check_right_par(err_info);
    helper.push_error_info(err_info);

    // Problem domain
    auto domain = problem_domain_parser::parse(helper);

    // Problem items
    auto problem_items = helper.parse_list<ast::problem_item>([&] () {
        return problem_parser::parse_problem_item(helper);
    });

    // End problem
    helper.pop_error_info();
    helper.check_right_par(err_info);
    helper.check_eof(err_info);

    return std::make_shared<ast::problem>(std::move(info), std::move(problem_name), std::move(domain), std::move(problem_items));
}

ast::problem_item problem_parser::parse_problem_item(parser_helper &helper) {
    // Problem item
    const std::string err_info = error_manager::get_error_info(decl_type::problem_item_decl);
    helper.check_left_par(err_info);
    const token_ptr &tok = helper.peek_next_token();

    ast::problem_item item;

    if (tok->has_type<keyword_token::requirements>())
        item = requirements_parser::parse(helper);
    else if (tok->has_type<keyword_token::objects>())
        item = objects_parser::parse(helper);
    else if (tok->has_type<keyword_token::agents>())
        item = agents_parser::parse(helper);
    else if (tok->has_type<keyword_token::agent_groups>())
        item = agent_groups_parser::parse(helper);
    else if (tok->has_type<keyword_token::init>())
        item = initial_state_parser::parse(helper);
    else if (tok->has_type<keyword_token::facts_init>())
        item = facts_init_parser::parse(helper);
    else if (tok->has_type<keyword_token::goal>())
        item = goal_parser::parse(helper);
    else
        helper.throw_error(error_type::token_mismatch, tok, err_info);

    return item;
}
