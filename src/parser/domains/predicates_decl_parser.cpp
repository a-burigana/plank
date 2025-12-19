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

#include "../../../include/parser/domains/predicates_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::domain_predicates_ptr predicates_decl_parser::parse(parser_helper &helper) {
    // Domain predicates
    ast::info info = helper.get_next_token_info();
    const std::string what = "predicates declaration";

    helper.check_next_token<keyword_token::predicates>();
    auto preds = helper.parse_list<ast::predicate_decl_ptr>([&] () {
        return predicates_decl_parser::parse_predicate_decl(helper);
    });

    // End domain predicates
    helper.check_right_par(what);

    return std::make_shared<ast::domain_predicates>(std::move(info), std::move(preds));
}

ast::predicate_decl_ptr predicates_decl_parser::parse_predicate_decl(parser_helper &helper) {
    // Predicate declaration
    ast::info info = helper.get_next_token_info();
    helper.check_left_par("predicate declaration");

    // Is fact
    const token_ptr &tok = helper.peek_next_token();
    bool is_fact = tok->has_type<keyword_token::fact>();

    if (is_fact) {
        info.add_requirement(":facts", "Fact declaration requires ':facts'.");
        helper.check_next_token<keyword_token::fact>();
    }

    // Predicate name
    ast::identifier_ptr pred_name = tokens_parser::parse_identifier(helper, "predicate name");
    const std::string what = "declaration of predicate '" + pred_name->get_token().get_lexeme() + "'";
    helper.push_info(info, what);

    // Predicate arguments
    auto formal_params = helper.parse_list<ast::typed_variable_ptr>([&] () {
        return typed_elem_parser::parse_typed_variable(helper);
    }, true);

    // End predicate declaration
    helper.pop_info();
    helper.check_right_par(what);

    return std::make_shared<ast::predicate_decl>(std::move(info), std::move(pred_name),
                                                 std::move(formal_params), is_fact);
}
