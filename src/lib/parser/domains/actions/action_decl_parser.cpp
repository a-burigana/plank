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

#include "../../../../../include/lib/parser/domains/actions/action_decl_parser.h"
#include "../../../../../include/lib/parser/tokens/tokens_parser.h"
#include "../../../../../include/lib/parser/common/parameters_parser.h"
#include "../../../../../include/lib/parser/domains/actions/action_signatures_parser.h"
#include "../../../../../include/lib/parser/domains/actions/obs_conditions_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::action_ptr action_decl_parser::parse(parser_helper &helper) {
    // Domain action
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<keyword_token::action>();
    ast::identifier_ptr action_name = tokens_parser::parse_identifier(helper, error_manager::get_error_info(decl_type::action_name));

    // Action parameters
    ast::list_comprehension_ptr params = parameters_parser::parse_list_comprehension_params(
            helper, action_name->get_token().get_lexeme());

    // Action signature
    ast::action_signature_ptr sign = action_signatures_parser::parse(helper, action_name->get_token().get_lexeme());

    // Action observability conditions
    auto obs_conditions = helper.parse_optional<ast::list<ast::obs_cond>, keyword_token::obs_conditions>([&] () {
        return obs_conditions_parser::parse_action_obs_cond(helper, action_name->get_token().get_lexeme());
    });

    // End domain action
    helper.check_right_par(error_manager::get_error_info(decl_type::action_decl, action_name->get_token().get_lexeme()));

    if (obs_conditions.has_value())
        info.add_requirement(":partial-observability",
                             error_manager::get_requirement_warning(requirement_warning::obs_conditions));

    return std::make_shared<ast::action>(std::move(info), std::move(action_name), std::move(params),
                                         std::move(sign), std::move(obs_conditions));
}
