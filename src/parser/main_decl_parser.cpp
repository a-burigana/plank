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

#include "../../include/parser/main_decl_parser.h"
#include "../../include/parser/domains/domain_parser.h"
#include "../../include/parser/libraries/act_type_library_parser.h"
#include "../../include/parser/problems/problem_parser.h"
#include "../../include/error-manager/epddl_exception.h"

using namespace epddl;
using namespace epddl::parser;

ast::main_decl main_decl_parser::parse(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();         // Eating '('
    helper.check_next_token<keyword_token::define>();           // Eating 'define'
    helper.check_next_token<punctuation_token::lpar>();         // Eating '('

    const token_ptr &tok = helper.peek_next_token();

    ast::main_decl decl;

    if (tok->has_type<keyword_token::domain>())
        decl = domain_parser::parse(helper);
    else if (tok->has_type<keyword_token::library>())
        decl = act_type_library_parser::parse(helper);
    else if (tok->has_type<keyword_token::problem>())
        decl = problem_parser::parse(helper);
    else
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(),
                             std::string{"Expected 'domain', 'action-type-library' or 'problem'. Found : '" + tok->get_lexeme() + "'."}};

    helper.check_next_token<punctuation_token::rpar>();         // Eating ')'

    return decl;
}
