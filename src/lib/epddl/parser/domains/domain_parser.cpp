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

#include <memory>
#include "parser/domains/domain_parser.h"
#include "parser/tokens/tokens_parser.h"
#include "error-manager/epddl_exception.h"
#include "parser/domains/domain_libraries_parser.h"
#include "parser/domains/requirements_parser.h"
#include "parser/domains/types_decl_parser.h"
#include "parser/domains/predicates_decl_parser.h"
#include "parser/domains/actions/action_decl_parser.h"
#include "parser/domains/constants_decl_parser.h"
#include "parser/domains/events/event_decl_parser.h"
#include "error-manager/error_manager.h"

using namespace epddl;
using namespace epddl::parser;

ast::domain_ptr domain_parser::parse(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    // Domain
    helper.check_left_par(error_manager::get_error_info(decl_type::anon_domain_decl));
    helper.check_next_token<keyword_token::define>();

    // Domain name
    helper.check_left_par(error_manager::get_error_info(decl_type::domain_name));
    helper.check_next_token<keyword_token::domain>();
    ast::identifier_ptr domain_name = tokens_parser::parse_identifier(helper, error_manager::get_error_info(decl_type::domain_name));
    const std::string err_info = error_manager::get_error_info(decl_type::domain_decl, domain_name->get_token().get_lexeme());

    // End domain name
    helper.check_right_par(err_info);
    helper.push_error_info(err_info);

    // Domain items
    ast::domain_item_list domain_items = helper.parse_list<ast::domain_item>([&] () {
        return domain_parser::parse_domain_item(helper);
    });

    // End domain
    helper.pop_error_info();
    helper.check_right_par(err_info);
    helper.check_eof(err_info);

    return std::make_shared<ast::domain>(std::move(info), std::move(domain_name), std::move(domain_items));
}

ast::domain_item domain_parser::parse_domain_item(parser_helper &helper) {
    // Domain item
    const std::string err_info = error_manager::get_error_info(decl_type::domain_item_decl);
    helper.check_left_par(err_info);
    const token_ptr &tok = helper.peek_next_token();

    ast::domain_item item;

    if (tok->has_type<keyword_token::domain_libs>())
        item = act_type_libraries_parser::parse(helper);
    else if (tok->has_type<keyword_token::requirements>())
        item = requirements_parser::parse(helper);
    else if (tok->has_type<keyword_token::types>())
        item = types_decl_parser::parse(helper);
    else if (tok->has_type<keyword_token::predicates>())
        item = predicates_decl_parser::parse(helper);
    else if (tok->has_type<keyword_token::constants>())
        item = constants_decl_parser::parse(helper);
    else if (tok->has_type<keyword_token::event>())
        item = event_decl_parser::parse(helper);
    else if (tok->has_type<keyword_token::action>())
        item = action_decl_parser::parse(helper);
    else
        helper.throw_error(error_type::token_mismatch, tok, err_info);

    return item;
}
