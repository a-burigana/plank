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

#include "../../../../include/parser/domains/actions/action_preconditions_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::event_precondition_list action_preconditions_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::precondition>();
    helper.check_next_token<punctuation_token::lpar>();
    auto pre = helper.parse_list<ast::event_precondition>([&] () { return action_preconditions_parser::parse_event_precondition(helper); }, true);
    helper.check_next_token<punctuation_token::rpar>();

    return pre;
}

ast::event_precondition action_preconditions_parser::parse_event_precondition(parser_helper &helper) {
    ast::identifier_ptr event = tokens_parser::parse_identifier(helper);
    ast::formula_ptr pre = formulas_parser::parse_formula(helper);

    return std::make_pair(std::move(event), std::move(pre));
}

//ast::formula_ptr action_preconditions_parser::parse(parser_helper &helper) {
//    helper.check_next_token<keyword_token::precondition>();
//    return formulas_parser::parse_formula(helper);
//}
