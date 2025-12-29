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

#include "../../../include/parser/libraries/act_type_library_parser.h"
#include "../../../include/parser/libraries/act_type_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include "../../../include/parser/domains/requirements_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::act_type_library_ptr act_type_library_parser::parse(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    // Action type library
    helper.check_left_par(error_manager::get_error_info(decl_type::library_decl));
    helper.check_next_token<keyword_token::define>();

    // Action type library name
    helper.check_left_par(error_manager::get_error_info(decl_type::library_name));
    helper.check_next_token<keyword_token::library>();
    ast::identifier_ptr library_name = tokens_parser::parse_identifier(helper, error_manager::get_error_info(decl_type::library_name));
    const std::string err_info = error_manager::get_error_info(decl_type::library_decl, library_name->get_token().get_lexeme());

    // End action type library name
    helper.check_right_par(err_info);
    helper.push_error_info(err_info);

    // Action type library items
    auto library_items = helper.parse_list<ast::act_type_library_item>([&] () {
        return act_type_library_parser::parse_act_type_library_item(helper);
    }, true);

    // End action type library
    helper.pop_error_info();
    helper.check_right_par(err_info);
    helper.check_eof(err_info);

    return std::make_shared<ast::act_type_library>(std::move(info), std::move(library_name), std::move(library_items));
}

ast::act_type_library_item act_type_library_parser::parse_act_type_library_item(parser_helper &helper) {
    // Action type library item
    const std::string err_info = error_manager::get_error_info(decl_type::library_item_decl);
    helper.check_left_par(err_info);
    const token_ptr &tok = helper.peek_next_token();       // Eating keyword

    ast::act_type_library_item item;

    if (tok->has_type<keyword_token::requirements>())
        item = requirements_parser::parse(helper);
    else if (tok->has_type<keyword_token::act_type>())
        item = act_type_decl_parser::parse(helper);
    else
        helper.throw_error(error_type::token_mismatch, tok, err_info);

    return item;
}
