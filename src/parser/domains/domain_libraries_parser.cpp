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

#include "../../../include/parser/domains/domain_libraries_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::domain_libraries_ptr act_type_libraries_parser::parse(parser_helper &helper) {
    // Domain action type libraries
    ast::info info = helper.get_next_token_info();
    const std::string what = "action type libraries declaration";

    helper.check_next_token<keyword_token::domain_libs>();
    helper.push_info(info, what);

    // Action type libraries names
    ast::identifier_list ids = helper.parse_list<ast::identifier_ptr>([&] () {
        return tokens_parser::parse_identifier(helper, "action type library name");
    });

    // End domain action type libraries
    helper.pop_info();
    helper.check_right_par(what);

    if (not ids.empty())
        info.add_requirement(":partial-observability",
                             "Inclusion of action type libraries requires ':partial-observability'.");

    return std::make_shared<ast::domain_libraries>(std::move(info), std::move(ids));
}
