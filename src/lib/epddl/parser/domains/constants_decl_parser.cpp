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

#include "parser/domains/constants_decl_parser.h"
#include "parser/common/typed_elem_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::constants_decl_ptr constants_decl_parser::parse(parser_helper &helper) {
    // Domain constants
    ast::info info = helper.get_next_token_info();
    const std::string err_info = error_manager::get_error_info(decl_type::constants_decl);

    helper.check_next_token<keyword_token::constants>();
    helper.push_error_info(err_info);

    // Constants declaration
    auto types_decl = helper.parse_sequence<ast::typed_identifier_ptr>([&] () {
        return typed_elem_parser::parse_typed_identifier(helper, error_manager::get_error_info(decl_type::entity_name));
    });

    // End domain constants
    helper.pop_error_info();
    helper.check_right_par(err_info);

    return std::make_shared<ast::constants_decl>(std::move(info), std::move(types_decl));
}
