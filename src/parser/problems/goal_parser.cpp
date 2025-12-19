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

#include "../../../include/parser/problems/goal_parser.h"
#include "../../../include/parser/common/formulas_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::goal_decl_ptr goal_parser::parse(parser_helper &helper) {
    // Problem goal
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<keyword_token::goal>();
    const std::string what = "goal declaration";
    helper.push_info(info, what);

    // Goal
    auto goal = formulas_parser::parse_formula(helper, formula_type::goal);

    // End problem goal
    helper.pop_info();
    helper.check_right_par(what);

    return std::make_shared<ast::goal_decl>(std::move(info), std::move(goal));
}
