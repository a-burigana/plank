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

#include "../../../include/parser/libraries/act_type_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/relations_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::action_type_ptr act_type_decl_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::act_type>();
    ast::identifier_ptr action_type_name = tokens_parser::parse_identifier(helper);       // Eating action-type name (identifier)

    ast::identifier_list events_names = act_type_decl_parser::parse_events(helper);
    ast::relations relations = relations_parser::parse_model_relations(helper);
    ast::identifier_list designated_names = act_type_decl_parser::parse_designated(helper);

    return std::make_shared<ast::action_type>(std::move(action_type_name), std::move(events_names),
                                              std::move(relations), std::move(designated_names));
}

ast::identifier_list act_type_decl_parser::parse_events(parser_helper &helper) {
    helper.check_next_token<keyword_token::events>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}

ast::identifier_list act_type_decl_parser::parse_designated(parser_helper &helper) {
    helper.check_next_token<keyword_token::designated>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}
