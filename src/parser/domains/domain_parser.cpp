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
#include "../../../include/parser/domains/domain_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include "../../../include/parser/domains/domain_libraries_parser.h"
#include "../../../include/parser/domains/requirements_parser.h"
#include "../../../include/parser/domains/types_decl_parser.h"
#include "../../../include/parser/domains/predicates_decl_parser.h"
#include "../../../include/parser/domains/actions/action_decl_parser.h"
#include "../../../include/parser/domains/constants_decl_parser.h"
#include "../../../include/parser/domains/events/event_decl_parser.h"
#include "../../../include/error-manager/error_manager.h"

using namespace epddl;
using namespace epddl::parser;

ast::domain_ptr domain_parser::parse(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    // Domain
    helper.check_left_par("domain declaration");
    helper.check_next_token<keyword_token::define>();

    // Domain name
    helper.check_left_par("domain name declaration");
    helper.check_next_token<keyword_token::domain>();
    ast::identifier_ptr domain_name = tokens_parser::parse_identifier(helper, "domain name");
    const std::string what = "domain '" + domain_name->get_token().get_lexeme() + "'";

    // End domain name
    helper.check_right_par("declaration of " + what);
    helper.push_info(info, what);

    // Domain items
    ast::domain_item_list domain_items = helper.parse_list<ast::domain_item>([&] () {
        return domain_parser::parse_domain_item(helper);
    });

    // End domain
    helper.pop_info();
    helper.check_right_par("declaration of " + what);
    helper.check_eof("declaration of " + what);

    return std::make_shared<ast::domain>(std::move(info), std::move(domain_name), std::move(domain_items));
}

ast::domain_item domain_parser::parse_domain_item(parser_helper &helper) {
    // Domain item
    const std::string what = "domain item";
    helper.check_left_par(what);
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
        helper.throw_error(tok, what, error_type::token_mismatch);

    return item;
}
