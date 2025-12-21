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

#include "../../../include/parser/libraries/event_conditions_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::act_type_event_conditions_ptr event_conditions_parser::parse(parser_helper &helper,
                                                                  const std::string &action_type_name) {
    // Action type events conditions
    ast::info info = helper.get_next_token_info();
    info.add_requirement(":events-conditions", "Declaration of events conditions requires ':events-conditions'.");

    helper.check_next_token<keyword_token::conditions>();
    const std::string what = "event variables of action type '" + action_type_name + "'";

    helper.check_left_par(what);
    helper.push_error_info(what);

    auto conditions = helper.parse_list<ast::event_conditions_ptr>(
            [&]() { return event_conditions_parser::parse_event_conditions(helper); });

    // End action type events conditions
    helper.pop_error_info();
    helper.check_right_par(what);

    return std::make_shared<ast::act_type_event_conditions>(std::move(info), std::move(conditions));
}

ast::event_conditions_ptr event_conditions_parser::parse_event_conditions(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    ast::variable_ptr event = tokens_parser::parse_variable(helper);

    helper.check_left_par("event conditions");
    auto event_conditions = helper.parse_list<ast::event_condition_ptr>(
            [&]() { return event_conditions_parser::parse_condition(helper); });

    helper.check_right_par("event conditions");
    return std::make_shared<ast::event_conditions>(std::move(info), std::move(event), std::move(event_conditions));
}

ast::event_condition_ptr event_conditions_parser::parse_condition(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();
    token_ptr cond = helper.get_ast_token<event_condition_token>();

    return std::make_shared<ast::event_condition>(std::move(info), std::move(cond));
}
