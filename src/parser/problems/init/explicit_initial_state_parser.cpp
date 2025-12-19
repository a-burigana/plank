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

#include "../../../../include/parser/problems/init/explicit_initial_state_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/parser/common/relations_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"

using namespace epddl;
using namespace epddl::parser;

ast::explicit_initial_state_ptr explicit_initial_state_parser::parse(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    // World names
    ast::identifier_list worlds_names = explicit_initial_state_parser::parse_worlds(helper);

    // Relations
    auto relations = relations_parser::parse_model_relations<ast::term>(
            helper, [&] () {
                return formulas_parser::parse_term(helper, "relation");
            }, "initial state");

    // World labels
    ast::world_label_list labels = explicit_initial_state_parser::parse_labels(helper);

    // Designated worlds names
    ast::identifier_list designated_names = explicit_initial_state_parser::parse_designated(helper);

    if (designated_names.size() > 1)
        info.add_requirement(":multi-pointed-models",
                             "Declaration of multiple designated worlds requires ':multi-pointed-models'.");

    return std::make_shared<ast::explicit_initial_state>(std::move(info), std::move(worlds_names), std::move(relations),
                                                         std::move(labels), std::move(designated_names));
}

ast::identifier_list explicit_initial_state_parser::parse_worlds(parser_helper &helper) {
    // Initial state worlds
    helper.check_next_token<keyword_token::worlds>();
    const std::string what = "world names declaration of initial state";

    helper.check_left_par(what);
    helper.push_info(helper.get_next_token_info(), what);

    auto worlds_names = helper.parse_list<ast::identifier_ptr>([&] () {
        return tokens_parser::parse_identifier(helper, "world name");
    });

    // End initial state worlds
    helper.pop_info();
    helper.check_right_par(what);

    return worlds_names;
}

ast::world_label_list explicit_initial_state_parser::parse_labels(parser_helper &helper) {
    // Initial state labels
    helper.check_next_token<keyword_token::labels>();
    const std::string what = "labels declaration of initial state";

    helper.check_left_par(what);

    auto labels = helper.parse_list<ast::world_label_ptr>([&] () {
        return explicit_initial_state_parser::parse_world_label(helper);
    });

    // End initial state labels
    helper.check_right_par(what);

    return labels;
}

ast::world_label_ptr explicit_initial_state_parser::parse_world_label(parser_helper &helper) {
    // World label
    ast::info info = helper.get_next_token_info();

    ast::identifier_ptr world_name = tokens_parser::parse_identifier(helper, "world name");
    const std::string what = "declaration labels for world '" + world_name->get_token().get_lexeme() + "'";
    helper.push_info(helper.get_next_token_info(), what);

    // Predicates
    auto predicates = formulas_parser::parse_list<ast::predicate_ptr, ast_token::identifier>(
            helper, what, [&] () {
                return formulas_parser::parse_predicate(helper, false);
            });

    // End world label
    helper.pop_info();

    return std::make_shared<ast::world_label>(std::move(info), std::move(world_name),
                                              std::move(predicates));
}

ast::identifier_list explicit_initial_state_parser::parse_designated(parser_helper &helper) {
    // Initial state designated worlds
    helper.check_next_token<keyword_token::designated>();
    const std::string what = "designated world names declaration of initial state";

    helper.check_left_par(what);
    helper.push_info(helper.get_next_token_info(), what);

    auto world_names = helper.parse_list<ast::identifier_ptr>([&] () {
        return tokens_parser::parse_identifier(helper, "world name");
    });

    // End initial state designated worlds
    helper.pop_info();
    helper.check_right_par(what);

    return world_names;
}
