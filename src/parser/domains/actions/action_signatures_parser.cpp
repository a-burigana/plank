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
#include "../../../../include/parser/common/formulas_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::action_signature_ptr action_signatures_parser::parse(parser_helper &helper, const std::string &action_name) {
    // Action signature
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<keyword_token::act_type>();
    const std::string what = "signature of action '" + action_name + "'";

    helper.push_error_info(what);
    helper.check_left_par(what);

    ast::identifier_ptr act_type_name = tokens_parser::parse_identifier(helper, "action type name");
    bool is_basic = act_type_name->get_token().get_lexeme() == "basic";

    if (not is_basic)
        info.add_requirement(":partial-observability",
                             "Use of user-defined action types requires ':partial-observability'.");

    auto signatures = helper.parse_list<ast::event_signature_ptr>([&]() {
        return action_signatures_parser::parse_event_signature(helper);
    });

    // End action signature
    helper.pop_error_info();
    helper.check_right_par(what);

    return std::make_shared<ast::action_signature>(std::move(info), std::move(act_type_name),
                                                   std::move(signatures), is_basic);
}

ast::event_signature_ptr action_signatures_parser::parse_event_signature(parser_helper &helper) {
    // Event signature
    ast::info info = helper.get_next_token_info();
    const std::string what = "event signature";

    helper.check_left_par(what);
    ast::identifier_ptr name = tokens_parser::parse_identifier(helper, "event name");

    // Actual parameters
    auto params = helper.parse_list<ast::term>([&]() {
        return formulas_parser::parse_term(helper, "term");
    }, true);

    // End event signature
    helper.check_right_par(what);

    return std::make_shared<ast::event_signature>(std::move(info), std::move(name), std::move(params));
}
