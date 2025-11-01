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

#include "../../../../include/parser/problems/init/finitary_s5_theory_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

#define base_case_tokens \
    ast_token::identifier, \
    connective_token::negation, \
    connective_token::conjunction, \
    connective_token::disjunction, \
    connective_token::implication, \
    quantifier_token::forall, \
    quantifier_token::exists, \
    punctuation_token::lbrack, \
    punctuation_token::langle

ast::finitary_S5_theory finitary_s5_theory_parser::parse(parser_helper &helper) {
    return formulas_parser::parse_list<ast::finitary_S5_formula, base_case_tokens>(
            helper, [&] () { return finitary_s5_theory_parser::parse_formula(helper); });
}

#undef base_case_tokens

ast::finitary_S5_formula finitary_s5_theory_parser::parse_formula(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    ast::finitary_S5_formula formula;

    if (tok->has_type<punctuation_token::lbrack>()) {
        helper.check_next_token<punctuation_token::lbrack>();
        helper.check_next_token<modality_token::ck>();
        helper.check_next_token<agent_group_token::all>();
        helper.check_next_token<punctuation_token::rbrack>();

        helper.check_next_token<punctuation_token::lpar>();
        const token_ptr &tok_2 = helper.peek_next_token();

        if (tok_2->has_type<punctuation_token::lbrack>()) {
            helper.check_next_token<punctuation_token::lbrack>();
            const token_ptr &tok_3 = helper.peek_next_token();

            if (tok_3->has_type<modality_token::kw>())
                formula = finitary_s5_theory_parser::parse_ck_kw_formula(helper);
            else if (tok_3->has_either_type<ast_token::identifier, ast_token::variable>())
                formula = finitary_s5_theory_parser::parse_ck_k_formula(helper);
            else
                throw EPDDLParserException("", tok_3->get_row(), tok_3->get_col(),
                                           "Expected finitary S5 formula. Found: " + tok_3->to_string());

        } else if (tok_2->has_type<punctuation_token::langle>())
            formula = finitary_s5_theory_parser::parse_ck_not_kw_formula(helper);
        else
            formula = finitary_s5_theory_parser::parse_ck_formula(helper);

        helper.check_next_token<punctuation_token::rpar>();
    } else
        formula = finitary_s5_theory_parser::parse_prop_formula(helper);

    return formula;
}

ast::prop_formula_ptr finitary_s5_theory_parser::parse_prop_formula(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();
    ast::formula_ptr f = formulas_parser::parse_propositional_formula(helper, formula_type::finitary_S5_formula, false);

    return std::make_shared<ast::prop_formula>(std::move(info), std::move(f));
}

ast::ck_formula_ptr finitary_s5_theory_parser::parse_ck_formula(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();
    ast::formula_ptr f = formulas_parser::parse_propositional_formula(helper, formula_type::finitary_S5_formula, false);

    return std::make_shared<ast::ck_formula>(std::move(info), std::move(f));
}

ast::ck_k_formula_ptr finitary_s5_theory_parser::parse_ck_k_formula(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    ast::term term = formulas_parser::parse_term(helper);
    helper.check_next_token<punctuation_token::rbrack>();
    ast::formula_ptr f = formulas_parser::parse_propositional_formula(helper, formula_type::finitary_S5_formula);

    return std::make_shared<ast::ck_k_formula>(std::move(info), std::move(term), std::move(f));
}

ast::ck_kw_formula_ptr finitary_s5_theory_parser::parse_ck_kw_formula(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<modality_token::kw>();
    ast::term term = formulas_parser::parse_term(helper);
    helper.check_next_token<punctuation_token::rbrack>();
    ast::formula_ptr f = formulas_parser::parse_propositional_formula(helper, formula_type::finitary_S5_formula);

    return std::make_shared<ast::ck_kw_formula>(std::move(info), std::move(term), std::move(f));
}

ast::ck_not_kw_formula_ptr finitary_s5_theory_parser::parse_ck_not_kw_formula(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<punctuation_token::langle>();
    helper.check_next_token<modality_token::kw>();
    ast::term term = formulas_parser::parse_term(helper);
    helper.check_next_token<punctuation_token::rangle>();
    ast::formula_ptr f = formulas_parser::parse_propositional_formula(helper, formula_type::finitary_S5_formula);

    return std::make_shared<ast::ck_not_kw_formula>(std::move(info), std::move(term), std::move(f));
}
