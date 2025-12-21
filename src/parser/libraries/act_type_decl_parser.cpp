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

#include "../../../include/parser/libraries/act_type_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/relations_parser.h"
#include "../../../include/parser/libraries/event_conditions_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::action_type_ptr act_type_decl_parser::parse(parser_helper &helper) {
    // Action type
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<keyword_token::act_type>();
    ast::identifier_ptr action_type_name = tokens_parser::parse_identifier(helper, "action type name");
    const std::string what = "action type '" + action_type_name->get_token().get_lexeme() + "'";

    // Event variables
    ast::variable_list events_vars = act_type_decl_parser::parse_events(
            helper, action_type_name->get_token().get_lexeme());

    // Observability types
    ast::identifier_list obs_types = act_type_decl_parser::parse_obs_types(
            helper, action_type_name->get_token().get_lexeme());

    // Abstract relations
    auto relations = relations_parser::parse_model_relations<ast::variable_ptr>(
            helper, [&] () {
                return tokens_parser::parse_variable(helper, "relation");
            }, what);

    // Designated event variables
    ast::variable_list designated_vars = act_type_decl_parser::parse_designated(
            helper, action_type_name->get_token().get_lexeme());

    // Events conditions (optional)
    auto conditions = helper.parse_optional<ast::act_type_event_conditions_ptr, keyword_token::conditions>(
            [&]() {
                return event_conditions_parser::parse(helper, action_type_name->get_token().get_lexeme());
            });

    // End action type
    helper.check_right_par("declaration of " + what);

    if (designated_vars.size() > 1)
        info.add_requirement(":multi-pointed-models", "Declaration of multiple designated events requires ':multi-pointed-models'.");

    return std::make_shared<ast::action_type>(std::move(info), std::move(action_type_name), std::move(events_vars),
                                              std::move(obs_types), std::move(relations), std::move(designated_vars),
                                              std::move(conditions));
}

ast::variable_list act_type_decl_parser::parse_events(parser_helper &helper, const std::string &action_type_name) {
    // Action type events
    helper.check_next_token<keyword_token::events>();
    const std::string what = "event variables of action type '" + action_type_name + "'";

    helper.check_left_par(what);
    helper.push_error_info(what);

    auto event_names = helper.parse_list<ast::variable_ptr>([&] () {
        return tokens_parser::parse_variable(helper, "event variable");
    });

    // End action type events
    helper.pop_error_info();
    helper.check_right_par(what);

    return event_names;
}

ast::identifier_list act_type_decl_parser::parse_obs_types(parser_helper &helper, const std::string &action_type_name) {
    // Action type observability types
    helper.check_next_token<keyword_token::obs_types>();
    const std::string what = "observability types of action type '" + action_type_name + "'";

    helper.check_left_par(what);
    helper.push_error_info(what);

    auto obs_types = helper.parse_list<ast::identifier_ptr>([&] () {
        return tokens_parser::parse_identifier(helper, "observability type name");
    });

    // End action type observability types
    helper.pop_error_info();
    helper.check_right_par(what);

    return obs_types;
}

ast::variable_list act_type_decl_parser::parse_designated(parser_helper &helper, const std::string &action_type_name) {
    // Action type designated events
    helper.check_next_token<keyword_token::designated>();
    const std::string what = "designated event variables of action type '" + action_type_name + "'";

    helper.check_left_par(what);
    helper.push_error_info(what);

    auto event_names = helper.parse_list<ast::variable_ptr>([&] () {
        return tokens_parser::parse_variable(helper, "event variable");
    });

    // End action type designated events
    helper.pop_error_info();
    helper.check_right_par(what);

    return event_names;
}
