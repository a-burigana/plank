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

#ifndef PLANK_TOKENS_PARSER_H
#define PLANK_TOKENS_PARSER_H

#include "../parser_helper.h"
#include "../../ast/tokens/tokens_ast.h"

namespace epddl::parser {
    class tokens_parser {
    public:
        template<typename ast_leaf_type>
        static std::shared_ptr<ast_leaf_type> parse_token(parser_helper &helper) {
            ast::info info = helper.get_next_token_info();

            return std::make_shared<ast_leaf_type>(std::move(info), helper.get_ast_token<typename ast_leaf_type::token_type>());
        }

        static ast::identifier_ptr parse_identifier(parser_helper &helper, const std::string &msg = "");
        static ast::variable_ptr parse_variable(parser_helper &helper, const std::string &msg = "");
        static ast::modality_name_ptr parse_modality_name(parser_helper &helper, const std::string &msg = "");
        static ast::requirement_ptr parse_requirement(parser_helper &helper, const std::string &msg = "");
        static ast::integer_ptr parse_integer(parser_helper &helper, const std::string &msg = "");
    };
}

#endif //PLANK_TOKENS_PARSER_H
