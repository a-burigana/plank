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
#include <string>

using namespace epddl;
using namespace epddl::parser;

ast::event_ptr event_decl_parser::parse(parser_helper &helper) {
    // Domain event
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<keyword_token::event>();
    ast::identifier_ptr event_name = tokens_parser::parse_identifier(helper, error_manager::get_error_info(decl_type::event_name));

    // Event parameters (optional)
    auto params = helper.parse_optional<ast::formal_param_list, keyword_token::parameters>([&]() {
        return parameters_parser::parse_variable_list_params( helper, event_name->get_token().get_lexeme());
    });

    // Event precondition (optional)
    auto pre = helper.parse_optional<ast::formula_ptr, keyword_token::precondition>([&]() {
        return event_decl_parser::parse_precondition(helper, event_name->get_token().get_lexeme());
    });

    // Event effects (optional)
    std::optional<list<postcondition>> post = std::nullopt;
    if (helper.peek_next_token()->has_type<keyword_token::effects>())
        post = event_decl_parser::parse_effects(helper, event_name->get_token().get_lexeme());

    // End domain event
    helper.check_right_par(error_manager::get_error_info(decl_type::event_decl, event_name->get_token().get_lexeme()));

    if (post.has_value())
        info.add_requirement(":ontic-actions", error_manager::get_requirement_warning(requirement_warning::effects));

    return std::make_shared<ast::event>(std::move(info), std::move(event_name), std::move(params),
                                        std::move(pre), std::move(post));
}

ast::formula_ptr event_decl_parser::parse_precondition(parser_helper &helper, const std::string &event_name) {
    // Event precondition
    helper.check_next_token<keyword_token::precondition>();
    const std::string err_info = error_manager::get_error_info(decl_type::event_pre_decl, event_name);

    helper.check_left_par(err_info);
    helper.push_error_info(err_info);

    ast::formula_ptr precondition = formulas_parser::parse_formula(helper, formula_type::precondition, false);

    // End event precondition
    helper.pop_error_info();
    helper.check_right_par(err_info);

    return precondition;
}

std::optional<ast::list<ast::postcondition>> event_decl_parser::parse_effects(parser_helper &helper,
                                                                              const std::string &event_name) {
    // Event effects
    helper.check_next_token<keyword_token::effects>();
    const std::string err_info = error_manager::get_error_info(decl_type::event_effects_decl, event_name);

    helper.check_left_par(err_info);
    helper.push_error_info(err_info);

    std::optional<ast::list<ast::postcondition>> effects = std::nullopt;

    if (not helper.peek_next_token()->has_type<punctuation_token::rpar>())
        effects = event_postconditions_parser::parse(helper);

    // End event effects
    helper.pop_error_info();
    helper.check_right_par(err_info);

    return effects;
}
