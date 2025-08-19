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

#include "../../../../include/parser/domains/actions/action_signatures_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/domains/actions/expressions_parser.h"

using namespace epddl;using namespace epddl;
using namespace epddl::parser;

ast::action_signature_ptr action_signatures_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::act_type>();                // Eating ':action-type'
    helper.check_next_token<punctuation_token::lpar>();                // Eating '('
    ast::identifier_ptr act_type_name = tokens_parser::parse_token<ast::identifier>(helper);     // Eating action type name (identifier)

//    ast::expression_list assignments = helper.parse_list<ast::expression>([&] () { return expressions_parser::parse(helper); });
    helper.check_next_token<punctuation_token::rpar>();                // Eating ')'

    return std::make_shared<ast::action_signature>(std::move(act_type_name));   //, std::move(assignments)
}
