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
#include "../../../../include/error-manager/epddl_exception.h"
#include "../../../../include/parser/problems/init/explicit_initial_state_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::initial_state_ptr initial_state_parser::parse(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<keyword_token::init>();
    const token_ptr &tok = helper.peek_next_token();
    ast::initial_state_repr init;

    if (tok->has_type<keyword_token::worlds>())
        init = explicit_initial_state_parser::parse(helper);
    else if (tok->has_type<punctuation_token::lpar>()) {
        info.add_requirement(":finitary-S5-theory", "Non-explicit initial state declaration requires ':finitary-S5-theory'.");
        init = formulas_parser::parse_formula(helper, formula_type::init);
    } else
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(),
                             std::string{"Expected initial state declaration. Found: "} + tok->to_string()};

    return std::make_shared<ast::initial_state>(std::move(info), std::move(init));
}
