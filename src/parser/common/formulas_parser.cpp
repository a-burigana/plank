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

#include "../../../include/parser/common/formulas_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include "../../../include/parser/common/typed_elem_parser.h"
#include "../../../include/lexer/tokens/definitions/modalities_def.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::formula_ptr formulas_parser::parse_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::formula_ptr f;

    if (tok->has_type<atomic_formula_token::top>())          f = formulas_parser::parse_true_formula(helper);
    else if (tok->has_type<atomic_formula_token::bot>())     f = formulas_parser::parse_false_formula(helper);
    else if (tok->has_type<ast_token::identifier>())         f = formulas_parser::parse_predicate_formula(helper);
    else if (tok->has_type<punctuation_token::eq>())         f = formulas_parser::parse_eq_formula(helper);
    else if (tok->has_type<punctuation_token::neq>())        f = formulas_parser::parse_neq_formula(helper);
    else if (tok->has_type<keyword_token::in>())             f = formulas_parser::parse_in_formula(helper);
    else if (tok->has_type<connective_token::negation>())    f = formulas_parser::parse_not_formula(helper);
    else if (tok->has_type<connective_token::conjunction>()) f = formulas_parser::parse_and_formula(helper);
    else if (tok->has_type<connective_token::disjunction>()) f = formulas_parser::parse_or_formula(helper);
    else if (tok->has_type<connective_token::implication>()) f = formulas_parser::parse_imply_formula(helper);
    else if (tok->has_type<punctuation_token::lbrack>())     f = formulas_parser::parse_box_formula(helper);
    else if (tok->has_type<punctuation_token::langle>())     f = formulas_parser::parse_diamond_formula(helper);
    else if (tok->has_type<quantifier_token::forall>())      f = formulas_parser::parse_forall_formula(helper);
    else if (tok->has_type<quantifier_token::exists>())      f = formulas_parser::parse_exists_formula(helper);
    else                                                     throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected formula. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return f;
}

ast::formula_ptr formulas_parser::parse_true_formula(epddl::parser::parser_helper &helper) {
    helper.check_next_token<atomic_formula_token::top>();
    return std::make_shared<ast::true_formula>();
}

ast::formula_ptr formulas_parser::parse_false_formula(epddl::parser::parser_helper &helper) {
    helper.check_next_token<atomic_formula_token::bot>();
    return std::make_shared<ast::false_formula>();
}

ast::formula_ptr formulas_parser::parse_predicate_formula(parser_helper &helper) {
    return std::make_shared<ast::predicate_formula>(formulas_parser::parse_predicate(helper, false));
}

ast::formula_ptr formulas_parser::parse_eq_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::eq>();
    ast::term t1 = formulas_parser::parse_term(helper);
    ast::term t2 = formulas_parser::parse_term(helper);

    return std::make_shared<ast::eq_formula>(std::move(t1), std::move(t2));
}

ast::formula_ptr formulas_parser::parse_neq_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::neq>();
    ast::term t1 = formulas_parser::parse_term(helper);
    ast::term t2 = formulas_parser::parse_term(helper);

    return std::make_shared<ast::neq_formula>(std::move(t1), std::move(t2));
}

ast::formula_ptr formulas_parser::parse_in_formula(parser_helper &helper) {
    helper.check_next_token<keyword_token::in>();
    auto term = formulas_parser::parse_term(helper);
    helper.check_next_token<punctuation_token::lpar>();
    ast::list_comprehension_ptr list = formulas_parser::parse_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();

    return std::make_shared<ast::in_formula>(std::move(term), std::move(list));
}

ast::formula_ptr formulas_parser::parse_not_formula(parser_helper &helper) {
    helper.check_next_token<connective_token::negation>();
    ast::formula_ptr f = formulas_parser::parse_formula(helper);

    return std::make_shared<ast::not_formula>(std::move(f));
}

ast::formula_ptr formulas_parser::parse_and_formula(parser_helper &helper) {
    helper.check_next_token<connective_token::conjunction>();
    auto fs = helper.parse_list<ast::formula_ptr>([&] () { return formulas_parser::parse_formula(helper); });

    return std::make_shared<ast::and_formula>(std::move(fs));
}

ast::formula_ptr formulas_parser::parse_or_formula(parser_helper &helper) {
    helper.check_next_token<connective_token::disjunction>();
    auto fs = helper.parse_list<ast::formula_ptr>([&] () { return formulas_parser::parse_formula(helper); });

    return std::make_shared<ast::or_formula>(std::move(fs));
}

ast::formula_ptr formulas_parser::parse_imply_formula(parser_helper &helper) {
    helper.check_next_token<connective_token::implication>();
    ast::formula_ptr f1 = formulas_parser::parse_formula(helper);
    ast::formula_ptr f2 = formulas_parser::parse_formula(helper);

    return std::make_shared<ast::imply_formula>(std::move(f1), std::move(f2));
}

ast::formula_ptr formulas_parser::parse_box_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lbrack>();
    ast::modality_ptr mod = formulas_parser::parse_modality(helper);
    helper.check_next_token<punctuation_token::rbrack>();
    ast::formula_ptr f = formulas_parser::parse_formula(helper);

    return std::make_shared<ast::box_formula>(std::move(mod), std::move(f));
}

ast::formula_ptr formulas_parser::parse_diamond_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::langle>();
    ast::modality_ptr mod = formulas_parser::parse_modality(helper);
    helper.check_next_token<punctuation_token::rangle>();
    ast::formula_ptr f = formulas_parser::parse_formula(helper);

    return std::make_shared<ast::diamond_formula>(std::move(mod), std::move(f));
}

ast::formula_ptr formulas_parser::parse_such_that(parser_helper &helper) {
    helper.check_next_token<punctuation_token::such_that>();
    return formulas_parser::parse_formula(helper);
}

ast::ext_list_comprehension_ptr formulas_parser::parse_ext_list_comprehension(parser_helper &helper, ast::variable_list &&prefix) {
    ast::term_list terms;
    for (ast::variable_ptr &v : prefix) terms.emplace_back(std::move(v));

    ast::term_list terms_ = helper.parse_list<ast::term>([&]() { return formulas_parser::parse_term(helper); });
    for (ast::term &t : terms_) terms.emplace_back(std::move(t));

    return std::make_shared<ast::ext_list_comprehension>(std::move(terms));
}

ast::int_list_comprehension_ptr formulas_parser::parse_int_list_comprehension(parser_helper &helper, bool allow_empty_params) {
    auto params = helper.parse_list<ast::typed_variable_ptr, punctuation_token::such_that>([&] () { return typed_elem_parser::parse_typed_variable(helper); }, allow_empty_params);
    auto f = helper.parse_optional<ast::formula_ptr, punctuation_token::such_that>([&] () { return formulas_parser::parse_such_that(helper); });

    return std::make_shared<ast::int_list_comprehension>(std::move(params), std::move(f));
}

ast::list_comprehension_ptr formulas_parser::parse_list_comprehension(parser_helper &helper) {
    ast::list_comprehension_ptr set_compr;
    ast::variable_list prefix;
    bool go = true;

    // We first parse a (possibly empty) prefix of consecutive variables
    while (go)
        if (const token_ptr &tok = helper.peek_next_token(); (go = tok->has_type<ast_token::variable>()))
            prefix.emplace_back(tokens_parser::parse_variable(helper));

    const token_ptr &tok = helper.peek_next_token();

    // Once we read the prefix, we have three options for the next token:
    if (tok->has_type<ast_token::identifier>())         // 1. Identifier: we are in an extensional list comprehension
        set_compr = formulas_parser::parse_ext_list_comprehension(helper, std::move(prefix));
    else if (tok->has_type<punctuation_token::rpar>()) {    // 2. Right parenthesis: we are in an extensional list comprehension
        if (prefix.empty())
            throw EPDDLParserException("", tok->get_row(), tok->get_col(), "List comprehension can not declare empty lists.");

        set_compr = formulas_parser::parse_ext_list_comprehension(helper);
    } else if (tok->has_type<punctuation_token::dash>()) {  // Dash: we are in an intensional list comprehension
        if (prefix.empty())
            throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Missing variable before type specification.");

        // We read the type of the last scanned variable and we create the relative formal parameter
        helper.check_next_token<punctuation_token::dash>();
        ast::identifier_ptr last_var_type = tokens_parser::parse_identifier(helper);
        ast::formal_param last_fp = std::make_shared<ast::typed_variable>(std::move(prefix.back()), std::move(last_var_type));
        prefix.pop_back();

        // We convert variables into formal parameters
        ast::formal_param_list params;
        for (ast::variable_ptr &v : prefix) params.push_back(std::make_shared<ast::typed_variable>(std::move(v)));
        params.push_back(std::move(last_fp));
        // We finish scanning the remaining formal parameters (if any)
        auto params_ = helper.parse_list<ast::formal_param, punctuation_token::such_that>([&]() { return typed_elem_parser::parse_typed_variable(helper); });
        for (ast::formal_param &fp : params_) params.push_back(std::move(fp));

        auto f = helper.parse_optional<ast::formula_ptr, punctuation_token::such_that>([&] () { return formulas_parser::parse_such_that(helper); });
        set_compr = std::make_shared<ast::int_list_comprehension>(std::move(params), std::move(f));
/*        ast::term_list terms = helper.parse_list<ast::term, punctuation_token::dash>([&]() { return formulas_parser::parse_term(helper); });
        const token_ptr &tok_ = helper.peek_next_token();

        if (tok_->has_type<punctuation_token::rpar>())
            set_compr = std::make_shared<ast::ext_list_comprehension>(std::move(terms));
        else if (tok_->has_type<punctuation_token::dash>()) {
            ast::formal_param_list params;

            for (ast::term &t : terms) {
                std::visit([&](auto&& t_) {
                    using term_type = std::decay_t<decltype(t_)>;

                    if constexpr (std::is_same_v<term_type, ast::variable_ptr>)
                        params.push_back(std::make_shared<ast::typed_variable>(std::forward<ast::variable_ptr>(t_)));
                    else if constexpr (std::is_same_v<term_type, ast::identifier_ptr>)
                        throw EPDDLParserException("", tok_->get_row(), tok_->get_col(), "Unexpected type specification in extensional set declaration.");
                }, t);
            }

            helper.check_next_token<punctuation_token::dash>();
            ast::identifier_ptr last_var_type = tokens_parser::parse_identifier(helper);
            auto params_ = helper.parse_list<ast::formal_param>([&]() { return typed_elem_parser::parse_typed_variable(helper); });

            for (ast::formal_param &param : params_)
                params.push_back(std::move(param));
        } else
            throw EPDDLParserException("", tok_->get_row(), tok_->get_col(), "Expected term or type specification. Found: " + tok_->to_string());*/
    } else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected term. Found: " + tok->to_string());

    return set_compr;
}

ast::formula_ptr formulas_parser::parse_forall_formula(parser_helper &helper) {
    helper.check_next_token<quantifier_token::forall>();
    helper.check_next_token<punctuation_token::lpar>();
    ast::int_list_comprehension_ptr params = formulas_parser::parse_int_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();
    ast::formula_ptr f = formulas_parser::parse_formula(helper);

    return std::make_shared<ast::forall_formula>(std::move(params), std::move(f));
}

ast::formula_ptr formulas_parser::parse_exists_formula(parser_helper &helper) {
    helper.check_next_token<quantifier_token::exists>();
    helper.check_next_token<punctuation_token::lpar>();
    ast::int_list_comprehension_ptr params = formulas_parser::parse_int_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();
    ast::formula_ptr f = formulas_parser::parse_formula(helper);

    return std::make_shared<ast::exists_formula>(std::move(params), std::move(f));
}

ast::predicate_ptr formulas_parser::parse_predicate(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    auto name = tokens_parser::parse_token<ast::identifier>(helper);
    auto terms = helper.parse_list<ast::term>([&]() { return formulas_parser::parse_term(helper); }, true);
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_shared<ast::predicate>(std::move(name), std::move(terms));
}

ast::literal_ptr formulas_parser::parse_literal(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    bool is_positive = tok->has_type<ast_token::identifier>();

    if (not tok->has_type<ast_token::identifier>() and not tok->has_type<connective_token::negation>())
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected literal. Found: " + tok->to_string());

    if (tok->has_type<connective_token::negation>())
        helper.check_next_token<connective_token::negation>();

    // If we are parsing a positive literal, then 'parse_predicate' should not parse the outer parentheses of the predicate
    auto predicate = formulas_parser::parse_predicate(helper, not is_positive);
    helper.check_next_token<punctuation_token::rpar>();

    return std::make_shared<ast::literal>(is_positive, std::move(predicate));
}

ast::term formulas_parser::parse_term(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    ast::term term;

    if (tok->has_type<ast_token::identifier>())    term = std::move(tokens_parser::parse_token<ast::identifier>(helper));
    else if (tok->has_type<ast_token::variable>()) term = std::move(tokens_parser::parse_token<ast::variable>(helper));
    else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected term. Found: " + tok->to_string());

    return term;
}

ast::modality_ptr formulas_parser::parse_modality(parser_helper &helper) {
    auto modality_name = helper.parse_optional<ast::modality_name_ptr, modality_token::kw, modality_token::ck>([&]() {
        return tokens_parser::parse_modality_name(helper);
    });

    ast::modality_index_ptr modality_index = formulas_parser::parse_modality_index(helper);
    return std::make_shared<ast::modality>(std::move(modality_name), std::move(modality_index));
}

ast::modality_index_ptr formulas_parser::parse_modality_index(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    ast::modality_index_ptr modality_index;

    if (tok->has_type<ast_token::identifier>() or tok->has_type<ast_token::variable>())
        modality_index = formulas_parser::parse_term(helper);
    else if (tok->has_type<agent_group_token::all>()) {
        helper.check_next_token<agent_group_token::all>();
        modality_index = agent_group_token::all{};
    } else if (tok->has_type<punctuation_token::lpar>())
        modality_index = formulas_parser::parse_group_modality(helper);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected modality. Found: " + tok->to_string());

    return modality_index;
}

ast::term_list formulas_parser::parse_group_modality(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    auto mods = helper.parse_list<ast::term>([&] () { return formulas_parser::parse_term(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return mods;
}
