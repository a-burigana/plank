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
    ast::info info = helper.get_next_token_info();

    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(helper);
    auto relation = formulas_parser::parse_list<ast::simple_relation_ptr, ast_token::identifier, ast_token::variable>(
            helper, [&]() { return relations_parser::parse_simple_relation(helper); });

    return std::make_shared<ast::agent_relation>(std::move(info), std::move(obs_group), std::move(relation));
}

ast::simple_relation_ptr relations_parser::parse_simple_relation(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    ast::term t1 = formulas_parser::parse_term(helper);
    ast::term t2 = formulas_parser::parse_term(helper);

    return std::make_shared<ast::simple_relation>(std::move(info), std::move(t1), std::move(t2));
}
