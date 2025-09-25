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

#ifndef EPDDL_TYPED_ELEM_PARSER_H
#define EPDDL_TYPED_ELEM_PARSER_H

#include "../../ast/common/typed_elem_ast.h"
#include "../parser_helper.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include <memory>

namespace epddl::parser {
    class typed_elem_parser {
    public:
        static ast::typed_identifier_ptr parse_typed_identifier(parser_helper &helper);
        static ast::typed_variable_ptr parse_typed_variable(parser_helper &helper);

    private:
        static ast::type parse_type(parser_helper &helper);
        static ast::either_type_ptr parse_either_type(parser_helper &helper);

        // ast_leaf_type: the type of the token (ast::identifier or ast::variable) being declared
        // ast_type_node: the EPDDL type of the token (primitive if ast_type_node = ast::identifier, or general if
        //                ast_type_node = ast::type)
        template<typename ast_leaf_type, typename ast_type_node>
        static std::shared_ptr<ast::typed_elem<ast_leaf_type>> parse_typed_elem(parser_helper &helper) {
            static_assert(std::is_same_v<ast_type_node, ast::identifier> or std::is_same_v<ast_type_node, ast::type>);

            std::shared_ptr<ast_leaf_type> elem = tokens_parser::parse_token<ast_leaf_type>(helper);
            std::optional<ast::type> type = std::nullopt;

            const token_ptr &tok = helper.peek_next_token();            // Peeking either '-' or another ast_leaf_type token

            if (tok->has_type<punctuation_token::dash>()) {
                helper.check_next_token<punctuation_token::dash>();     // Actually eating '-'

                if constexpr (std::is_same_v<ast_type_node, ast::identifier>)
                    type = tokens_parser::parse_identifier(helper);
                else if constexpr (std::is_same_v<ast_type_node, ast::type>)
                    type = typed_elem_parser::parse_type(helper);
            }
            return std::make_shared<ast::typed_elem<ast_leaf_type>>(std::move(elem), std::move(type));
        }
    };
}

#endif //EPDDL_TYPED_ELEM_PARSER_H
