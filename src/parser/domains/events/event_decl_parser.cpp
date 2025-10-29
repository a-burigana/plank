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

#include "../../../../include/parser/domains/events/event_decl_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/parameters_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/parser/domains/events/event_postconditions_parser.h"
#include <optional>

using namespace epddl;
using namespace epddl::parser;

ast::event_ptr event_decl_parser::parse(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<keyword_token::event>();
    ast::identifier_ptr event_name = tokens_parser::parse_identifier(helper);       // Eating event name (identifier)

    auto params = helper.parse_optional<ast::list_comprehension_ptr , keyword_token::parameters>([&]() { return parameters_parser::parse(helper); });
    auto pre = helper.parse_optional<ast::formula_ptr, keyword_token::precondition>([&]() { return event_decl_parser::parse_precondition(helper); });

    std::optional<list<postcondition>> post = std::nullopt;
    if (helper.peek_next_token()->has_type<keyword_token::effects>())
        post = event_decl_parser::parse_effects(helper);

    if (post.has_value())
        info.add_requirement(":ontic-actions", "Definition of effects requires ':ontic-actions'.");

    return std::make_shared<ast::event>(std::move(info), std::move(event_name), std::move(params), std::move(pre), std::move(post));
}

ast::formula_ptr event_decl_parser::parse_precondition(parser_helper &helper) {
    helper.check_next_token<keyword_token::precondition>();
    return formulas_parser::parse_formula(helper, formula_type::precondition);
}

std::optional<ast::list<ast::postcondition>> event_decl_parser::parse_effects(parser_helper &helper) {
    helper.check_next_token<keyword_token::effects>();
    helper.check_next_token<punctuation_token::lpar>();

    std::optional<ast::list<ast::postcondition>> effects = std::nullopt;

    if (not helper.peek_next_token()->has_type<punctuation_token::rpar>())
        effects = event_postconditions_parser::parse(helper);

    helper.check_next_token<punctuation_token::rpar>();

    return effects;
}
