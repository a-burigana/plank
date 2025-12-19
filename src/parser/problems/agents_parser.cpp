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

#include "../../../include/parser/problems/agents_parser.h"
#include "../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::agents_decl_ptr agents_parser::parse(parser_helper &helper) {
    // Problem agents
    ast::info info = helper.get_next_token_info();
    const std::string what = "agents declaration";

    helper.check_next_token<keyword_token::agents>();
    helper.push_info(info, what);

    auto agents = helper.parse_list<ast::typed_identifier_ptr>([&] () {
        return typed_elem_parser::parse_typed_identifier(helper, "agent");
    });

    // End problem agents
    helper.pop_info();
    helper.check_right_par(what);

    return std::make_shared<ast::agents_decl>(std::move(info), std::move(agents));
}
