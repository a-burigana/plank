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

#include "parser/domains/domain_libraries_parser.h"
#include "parser/tokens/tokens_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::domain_libraries_ptr act_type_libraries_parser::parse(parser_helper &helper) {
    // Domain action type libraries
    ast::info info = helper.get_next_token_info();
    const std::string err_info = error_manager::get_error_info(decl_type::action_type_libraries_decl);

    helper.check_next_token<keyword_token::domain_libs>();
    helper.push_error_info(err_info);

    // Action type libraries names
    ast::identifier_list ids = helper.parse_non_empty_sequence<ast::identifier_ptr>([&] () {
        return tokens_parser::parse_identifier(helper, error_manager::get_error_info(decl_type::library_name));
    }, "action type library names");

    // End domain action type libraries
    helper.pop_error_info();
    helper.check_right_par(err_info);

    if (not ids.empty())
        info.add_requirement(":partial-observability",
                             error_manager::get_requirement_warning(requirement_warning::action_types_incl));

    return std::make_shared<ast::domain_libraries>(std::move(info), std::move(ids));
}
