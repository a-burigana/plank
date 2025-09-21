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

#include "../../../../include/parser/problems/initial_states/explicit_initial_state_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/parser/common/relations_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"

using namespace epddl;
using namespace epddl::parser;

ast::explicit_initial_state_ptr explicit_initial_state_parser::parse(parser_helper &helper) {
    ast::identifier_list worlds_names = explicit_initial_state_parser::parse_worlds(helper);
    ast::relations relations = relations_parser::parse_model_relations(helper);
    ast::world_label_list labels = explicit_initial_state_parser::parse_labels(helper);
    ast::identifier_list designated_names = explicit_initial_state_parser::parse_designated(helper);

    return std::make_shared<ast::explicit_initial_state>(std::move(worlds_names), std::move(relations),
                                                         std::move(labels), std::move(designated_names));
}

ast::identifier_list explicit_initial_state_parser::parse_worlds(parser_helper &helper) {
    helper.check_next_token<keyword_token::worlds>();
    helper.check_next_token<punctuation_token::lpar>();
    auto worlds_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return worlds_names;
}

ast::world_label_list explicit_initial_state_parser::parse_labels(parser_helper &helper) {
    helper.check_next_token<keyword_token::labels>();
    helper.check_next_token<punctuation_token::lpar>();
    auto labels = helper.parse_list<ast::world_label_ptr>([&] () { return explicit_initial_state_parser::parse_world_label(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return labels;
}

ast::world_label_ptr explicit_initial_state_parser::parse_world_label(parser_helper &helper) {
    ast::identifier_ptr world_name = tokens_parser::parse_identifier(helper);
    helper.check_next_token<punctuation_token::lpar>();

    ast::predicate_list predicates;
    const token_ptr &tok = helper.peek_next_token();

    if (tok->has_type<ast_token::identifier>())
        predicates.push_back(formulas_parser::parse_predicate(helper, false));
    else if (tok->has_type<connective_token::conjunction>()) {
        helper.check_next_token<connective_token::conjunction>();
        predicates = helper.parse_list<ast::predicate_ptr>([&]() { return formulas_parser::parse_predicate(helper); });
    } else
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(),
                             std::string{"Expected predicate list. Found: '" + tok->to_string() + "'."}};

    helper.check_next_token<punctuation_token::rpar>();

    return std::make_shared<ast::world_label>(std::move(world_name), std::move(predicates));
}

ast::identifier_list explicit_initial_state_parser::parse_designated(parser_helper &helper) {
    helper.check_next_token<keyword_token::designated>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}
