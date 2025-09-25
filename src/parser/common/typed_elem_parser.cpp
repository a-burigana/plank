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

#include "../../../include/parser/common/typed_elem_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::type typed_elem_parser::parse_type(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    ast::type type;

    if (tok->has_type<ast_token::identifier>()) type = tokens_parser::parse_identifier(helper);
    else if (tok->has_type<punctuation_token::lpar>()) type = typed_elem_parser::parse_either_type(helper);
    else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected type. Found: " + tok->to_string());

    return type;
}

ast::either_type_ptr typed_elem_parser::parse_either_type(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    helper.check_next_token<keyword_token::either>();
    ast::identifier_list types = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    // Sorting the list ensures that we can check whether two either-types are the same by direct comparison
    types.sort([](const ast::identifier_ptr &x, const ast::identifier_ptr &y) -> bool {
        return x->get_token().get_lexeme() < y->get_token().get_lexeme();
    });

    return std::make_shared<ast::either_type>(std::move(types));
}

ast::typed_identifier_ptr typed_elem_parser::parse_typed_identifier(parser_helper &helper) {
    ast::identifier_ptr id = tokens_parser::parse_identifier(helper);
    std::optional<ast::identifier_ptr> type = std::nullopt;

    const token_ptr &tok = helper.peek_next_token();            // Peeking either '-' or another ast_leaf_type token

    if (tok->has_type<punctuation_token::dash>()) {
        helper.check_next_token<punctuation_token::dash>();     // Actually eating '-'
        type = tokens_parser::parse_identifier(helper);
    }
    return std::make_shared<ast::typed_identifier>(std::move(id), std::move(type));
}

ast::typed_variable_ptr typed_elem_parser::parse_typed_variable(parser_helper &helper) {
    ast::variable_ptr var = tokens_parser::parse_variable(helper);
    std::optional<ast::type> type = std::nullopt;

    const token_ptr &tok = helper.peek_next_token();            // Peeking either '-' or another ast_leaf_type token

    if (tok->has_type<punctuation_token::dash>()) {
        helper.check_next_token<punctuation_token::dash>();     // Actually eating '-'
        type = typed_elem_parser::parse_type(helper);
    }
    return std::make_shared<ast::typed_variable>(std::move(var), std::move(type));
}
