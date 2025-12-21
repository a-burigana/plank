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

#include "../../../../include/parser/problems/init/initial_state_parser.h"
#include "../../../../include/parser/problems/init/finitary_s5_theory_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"
#include "../../../../include/parser/problems/init/explicit_initial_state_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::initial_state_ptr initial_state_parser::parse(parser_helper &helper) {
    // Problem initial state
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<keyword_token::init>();
    const token_ptr &tok = helper.peek_next_token();
    const std::string what = "initial state declaration";

    ast::initial_state_repr init;

    if (tok->has_type<keyword_token::worlds>())
        init = explicit_initial_state_parser::parse(helper);
    else if (tok->has_type<punctuation_token::lpar>()) {
        info.add_requirement(":finitary-S5-theories",
                             "Non-explicit initial state declaration requires ':finitary-S5-theories'.");

        const std::string what_ = "finitary S5-theory declaration";
        helper.push_error_info(what_);
        init = finitary_s5_theory_parser::parse(helper);
        helper.pop_error_info();
    } else
        helper.throw_error(error_type::token_mismatch, tok, what);

    // End problem initial state
    helper.check_right_par("declaration of " + what);

    return std::make_shared<ast::initial_state>(std::move(info), std::move(init));
}
