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

#include "../../../include/parser/common/relations_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/formulas_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::agent_relation_list relations_parser::parse_model_relations(parser_helper &helper) {
    helper.check_next_token<keyword_token::relations>();
    helper.check_next_token<punctuation_token::lpar>();
    auto agents_relations = helper.parse_list<ast::agent_relation_ptr>([&]() { return relations_parser::parse_agent_relation(helper); }, true);
    helper.check_next_token<punctuation_token::rpar>();
    return agents_relations;
}

ast::agent_relation_ptr relations_parser::parse_agent_relation(epddl::parser::parser_helper &helper) {
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(helper);
    ast::relation_ptr relation = relations_parser::parse_relation(helper);

    return std::make_shared<ast::agent_relation>(std::move(obs_group), std::move(relation));
}

ast::relation_ptr relations_parser::parse_relation(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::relation_ptr relation;

    if (tok->has_either_type<ast_token::identifier, ast_token::variable>())
        relation = relations_parser::parse_simple_relation(helper, false);
    else if (tok->has_type<connective_token::conjunction>())
        relation = relations_parser::parse_and_relation(helper, false);
    else if (tok->has_type<quantifier_token::forall>())
        relation = relations_parser::parse_forall_relation(helper, false);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected agent relations. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return relation;
}

ast::simple_relation_ptr relations_parser::parse_simple_relation(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    ast::term t1 = formulas_parser::parse_term(helper);
    ast::term t2 = formulas_parser::parse_term(helper);
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_shared<ast::simple_relation>(std::move(t1), std::move(t2));
}

ast::and_relation_ptr relations_parser::parse_and_relation(epddl::parser::parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    helper.check_next_token<connective_token::conjunction>();
    auto relation_list = helper.parse_list<ast::relation_ptr>([&]() { return relations_parser::parse_relation(helper); });
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_shared<ast::and_relation>(std::move(relation_list));
}

ast::forall_relation_ptr relations_parser::parse_forall_relation(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();

    helper.check_next_token<quantifier_token::forall>();
    helper.check_next_token<punctuation_token::lpar>();
    ast::list_comprehension_ptr params = formulas_parser::parse_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();

    auto relation = relations_parser::parse_relation(helper);
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_shared<ast::forall_relation>(std::move(params), std::move(relation));
}
