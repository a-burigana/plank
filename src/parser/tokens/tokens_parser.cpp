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

#include "../../../include/parser/tokens/tokens_parser.h"
#include <type_traits>

#define epddl_token_type(token_type) token_type

using namespace epddl;
using namespace epddl::parser;

//template<typename ast_leaf_type>
//std::shared_ptr<ast_leaf_type> tokens_parser::parse_token(epddl::parser &helper) {
//    return std::make_shared<ast_leaf_type>(helper.get_ast_token<ast_leaf_type::token_type>());
//}

ast::identifier_ptr tokens_parser::parse_identifier(parser_helper &helper) {
    return std::make_shared<ast::identifier>(helper.get_ast_token<epddl_ast_token_type::identifier>());
}

ast::variable_ptr tokens_parser::parse_variable(parser_helper &helper) {
    return std::make_shared<ast::variable>(helper.get_ast_token<epddl_ast_token_type::variable>());
}

ast::modality_name_ptr tokens_parser::parse_modality_name(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    return std::visit([&](auto &&arg) {
        using tok_type = std::remove_reference_t<decltype(arg)>;
        return std::make_shared<ast::modality_name>(helper.get_ast_token<tok_type>());
    }, tok->get_type());

//    if (tok->has_type<modality_token::ck>())
//        return std::make_shared<ast::modality_name>(helper.get_ast_token<epddl_modality_token_type::ck>());
//    else if (tok->has_type<modality_token::kw>())
//        return std::make_shared<ast::modality_name>(helper.get_ast_token<epddl_modality_token_type::kw>());
//    else if (tok->has_type<modality_token::modality>())
//        return std::make_shared<ast::modality_name>(helper.get_ast_token<epddl_modality_token_type::modality>());
}

ast::requirement_ptr tokens_parser::parse_requirement(parser_helper &helper) {
    return std::make_shared<ast::requirement>(helper.get_ast_token<epddl_ast_token_type::requirement>());
}

ast::integer_ptr tokens_parser::parse_integer(parser_helper &helper) {
    return std::make_shared<ast::integer>(helper.get_ast_token<epddl_ast_token_type::integer>());
}

#undef epddl_token_type
