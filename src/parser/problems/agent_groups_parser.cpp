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

#include "../../../include/parser/problems/agent_groups_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/formulas_parser.h"
#include "../../../include/error-manager/epddl_exception.h"

using namespace epddl;
using namespace epddl::parser;

ast::agent_groups_decl_ptr agent_groups_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::agent_groups>();
    auto agent_groups = helper.parse_list<ast::agent_group_decl_ptr>([&] () { return agent_groups_parser::parse_agent_group_decl(helper); });

    return std::make_unique<ast::agent_groups_decl>(std::move(agent_groups));
}

ast::agent_group_decl_ptr agent_groups_parser::parse_agent_group_decl(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    ast::identifier_ptr group_name = tokens_parser::parse_identifier(helper);
    ast::agent_group agents = agent_groups_parser::parse_agent_group(helper);
    helper.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::agent_group_decl>(std::move(group_name), std::move(agents));
}

ast::agent_group agent_groups_parser::parse_agent_group(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();

    const token_ptr &tok = helper.peek_next_token();
    ast::agent_group agents;

    if (tok->has_type<ast_token::identifier>())
        agents = agent_groups_parser::parse_simple_agent_group(helper);
    else if (tok->has_type<quantifier_token::forall>())
        agents = agent_groups_parser::parse_forall_agent_group(helper, false);
    else if (tok->has_type<connective_token::conjunction>())
        agents = agent_groups_parser::parse_agent_group_list(helper);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected agent group declaration. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return agents;
}

ast::single_agent_group agent_groups_parser::parse_single_agent_group(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();

    const token_ptr &tok = helper.peek_next_token();
    ast::single_agent_group agents;

    if (tok->has_type<ast_token::identifier>())
        agents = agent_groups_parser::parse_simple_agent_group(helper);
    else if (tok->has_type<quantifier_token::forall>())
        agents = agent_groups_parser::parse_forall_agent_group(helper, false);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected agent group declaration. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return agents;
}

ast::agent_group_list agent_groups_parser::parse_agent_group_list(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    helper.check_next_token<connective_token::conjunction>();
    auto agent_groups = helper.parse_list<ast::single_agent_group>([&] () { return agent_groups_parser::parse_single_agent_group(helper); });
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return agent_groups;
}

ast::simple_agent_group_ptr agent_groups_parser::parse_simple_agent_group(parser_helper &helper) {
    auto agents = helper.parse_list<ast::term>([&] () { return formulas_parser::parse_term(helper); });
    return std::make_unique<ast::simple_agent_group>(std::move(agents));
}

ast::forall_agent_group_ptr agent_groups_parser::parse_forall_agent_group(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();

    helper.check_next_token<quantifier_token::forall>();
    helper.check_next_token<punctuation_token::lpar>();
    ast::int_list_comprehension_ptr params = formulas_parser::parse_int_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();

    auto agents = agent_groups_parser::parse_agent_group(helper);
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::forall_agent_group>(std::move(params), std::move(agents));
}
