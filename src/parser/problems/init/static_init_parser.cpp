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

#include "../../../../include/parser/problems/init/static_init_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::static_init_ptr static_init_parser::parse(epddl::parser::parser_helper &helper) {
    ast::info info = helper.get_next_token_info();
    info.add_requirement(":static-predicates", "Initialization of static predicates requires ':static-predicates'.");

    helper.check_next_token<keyword_token::static_init>();
    auto literals = formulas_parser::parse_list<ast::predicate_ptr, ast_token::identifier>(
            helper, [&] () { return formulas_parser::parse_predicate(helper, false); });

    return std::make_shared<ast::static_init>(std::move(info), std::move(literals));
}
