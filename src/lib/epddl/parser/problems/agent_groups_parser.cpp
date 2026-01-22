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

#include "parser/problems/agent_groups_parser.h"
#include "parser/tokens/tokens_parser.h"
#include "parser/common/formulas_parser.h"
#include "error-manager/epddl_exception.h"

using namespace epddl;
using namespace epddl::parser;

ast::agent_groups_decl_ptr agent_groups_parser::parse(parser_helper &helper) {
    // Problem agent groups
    ast::info info = helper.get_next_token_info();
    const std::string err_info = error_manager::get_error_info(decl_type::agents_decl);

    helper.check_next_token<keyword_token::agent_groups>();

    auto agent_groups = helper.parse_sequence<ast::agent_group_decl_ptr>([&] () {
        return agent_groups_parser::parse_agent_group_decl(helper);
    });

    // End problem agent groups
    helper.check_right_par(err_info);

    if (not agent_groups.empty())
        info.add_requirement(":agent-groups", error_manager::get_requirement_warning(requirement_warning::agent_groups));

    return std::make_shared<ast::agent_groups_decl>(std::move(info), std::move(agent_groups));
}

ast::agent_group_decl_ptr agent_groups_parser::parse_agent_group_decl(parser_helper &helper) {
    // Problem agent group
    ast::info info = helper.get_next_token_info();
    helper.check_left_par(error_manager::get_error_info(decl_type::anon_agent_group_decl));

    // Agent group name
    ast::identifier_ptr group_name = tokens_parser::parse_identifier(helper, error_manager::get_error_info(decl_type::agent_group_name));
    const std::string err_info = error_manager::get_error_info(decl_type::agent_group_decl, group_name->get_token().get_lexeme());
    helper.push_error_info(err_info);

    // Agent group type (optional)
    auto group_type = helper.parse_optional<ast::identifier_ptr, punctuation_token::dash>(
            [&]() {
                return agent_groups_parser::parse_agent_group_type(helper);
            });

    // Agent list
    auto agents = formulas_parser::parse_list<ast::simple_agent_group_ptr, ast_token::identifier, ast_token::variable>(
            helper, "agent terms", error_manager::get_error_info(decl_type::agent_list_decl), [&]() {
                return formulas_parser::parse_simple_agent_group(helper);
            });

    // End predicate declaration
    helper.pop_error_info();
    helper.check_right_par(err_info);

    return std::make_shared<ast::agent_group_decl>(std::move(info), std::move(group_name), std::move(group_type), std::move(agents));
}

ast::identifier_ptr agent_groups_parser::parse_agent_group_type(parser_helper &helper) {
    helper.check_next_token<punctuation_token::dash>();
    return tokens_parser::parse_identifier(helper, error_manager::get_error_info(decl_type::type_name));
}
