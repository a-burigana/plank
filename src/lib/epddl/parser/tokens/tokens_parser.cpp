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

#include "parser/tokens/tokens_parser.h"
#include <type_traits>

#define epddl_token_type(token_type) token_type

using namespace epddl;
using namespace epddl::parser;

//template<typename ast_leaf_type>
//std::shared_ptr<ast_leaf_type> tokens_parser::parse_token(epddl::parser &helper) {
//    return std::make_shared<ast_leaf_type>(helper.gstd::move(location ,et_ast_token<ast_leaf_type::token_type>());
//}

ast::identifier_ptr tokens_parser::parse_identifier(parser_helper &helper, const std::string &msg) {
    ast::info info = helper.get_next_token_info();

    return std::make_shared<ast::identifier>(std::move(info),
                                             helper.get_ast_token<epddl_ast_token_type::identifier>(msg));
}

ast::variable_ptr tokens_parser::parse_variable(parser_helper &helper, const std::string &msg) {
    ast::info info = helper.get_next_token_info();

    return std::make_shared<ast::variable>(std::move(info),
                                           helper.get_ast_token<epddl_ast_token_type::variable>(msg));
}

ast::modality_name_ptr tokens_parser::parse_modality_name(parser_helper &helper, const std::string &msg) {
    ast::info info = helper.get_next_token_info();
    const token_ptr &tok = helper.peek_next_token();

    if (tok->has_type<modality_token::kw>()) {
        info.add_requirement(":knowing-whether", error_manager::get_requirement_warning(requirement_warning::knowing_whether));
        return std::make_shared<ast::modality_name>(std::move(info),
                                                    helper.get_ast_token<modality_token::kw>(msg));
    } else if (tok->has_type<modality_token::ck>()) {
        // We add the requirements at type-checking time: we first need to know whether the formula is static or not
        // and we can't do this at parsing time
        return std::make_shared<ast::modality_name>(std::move(info),
                                                    helper.get_ast_token<modality_token::ck>(msg));
    } else
        helper.throw_error(error_type::token_mismatch, tok, error_manager::get_error_info(decl_type::modality_name));

    return nullptr;
}

ast::requirement_ptr tokens_parser::parse_requirement(parser_helper &helper, const std::string &msg) {
    ast::info info = helper.get_next_token_info();

    return std::make_shared<ast::requirement>(std::move(info),
                                              helper.get_ast_token<epddl_ast_token_type::requirement>(msg));
}

ast::integer_ptr tokens_parser::parse_integer(parser_helper &helper, const std::string &msg) {
    ast::info info = helper.get_next_token_info();

    return std::make_shared<ast::integer>(std::move(info),
                                          helper.get_ast_token<epddl_ast_token_type::integer>(msg));
}

#undef epddl_token_type
