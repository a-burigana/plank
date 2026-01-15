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

#include "../../../../include/lib/parser/common/formulas_parser.h"
#include "../../../../include/lib/parser/tokens/tokens_parser.h"
#include "../../../../include/lib/error-manager/epddl_exception.h"
#include "../../../../include/lib/parser/common/typed_elem_parser.h"
#include "../../../../include/lib/lexer/tokens/definitions/modalities_def.h"
#include <memory>
#include <variant>
#include <cassert>

using namespace epddl;
using namespace epddl::parser;

ast::formula_ptr formulas_parser::parse_formula(parser_helper &helper, const formula_type &f_type, bool parse_outer_pars) {
    return parse_formula_helper(helper, f_type, false, parse_outer_pars);
}

ast::formula_ptr formulas_parser::parse_propositional_formula(parser_helper &helper, const formula_type &f_type, bool parse_outer_pars) {
    return parse_formula_helper(helper, f_type, true, parse_outer_pars);
}

ast::formula_ptr formulas_parser::parse_formula_helper(parser_helper &helper, const formula_type &f_type, bool is_propositional, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_left_par(error_manager::get_error_info(decl_type::formula));
    const token_ptr &tok = helper.peek_next_token();
    ast::formula_ptr f;

    if (tok->has_type<atomic_formula_token::top>())
        f = formulas_parser::parse_true_formula(helper, f_type, is_propositional);
    else if (tok->has_type<atomic_formula_token::bot>())
        f = formulas_parser::parse_false_formula(helper, f_type, is_propositional);
    else if (tok->has_type<ast_token::identifier>())
        f = formulas_parser::parse_predicate_formula(helper, is_propositional);
    else if (tok->has_type<punctuation_token::eq>())
        f = formulas_parser::parse_eq_formula(helper, f_type, is_propositional);
    else if (tok->has_type<punctuation_token::neq>())
        f = formulas_parser::parse_neq_formula(helper, f_type, is_propositional);
//    else if (tok->has_type<keyword_token::in>())
//        f = formulas_parser::parse_in_formula(helper, is_propositional);
    else if (tok->has_type<connective_token::negation>())
        f = formulas_parser::parse_not_formula(helper, f_type, is_propositional);
    else if (tok->has_type<connective_token::conjunction>())
        f = formulas_parser::parse_and_formula(helper, f_type, is_propositional);
    else if (tok->has_type<connective_token::disjunction>())
        f = formulas_parser::parse_or_formula(helper, f_type, is_propositional);
    else if (tok->has_type<connective_token::implication>())
        f = formulas_parser::parse_imply_formula(helper, f_type, is_propositional);
    else if (tok->has_type<punctuation_token::lbrack>())
        f = formulas_parser::parse_box_formula(helper, f_type, is_propositional);
    else if (tok->has_type<punctuation_token::langle>())
        f = formulas_parser::parse_diamond_formula(helper, f_type, is_propositional);
    else if (tok->has_type<quantifier_token::forall>())
        f = formulas_parser::parse_forall_formula(helper, f_type, is_propositional);
    else if (tok->has_type<quantifier_token::exists>())
        f = formulas_parser::parse_exists_formula(helper, f_type, is_propositional);
    else
        helper.throw_error(error_type::token_mismatch, tok, error_manager::get_error_info(decl_type::formula));

    if (parse_outer_pars) helper.check_right_par(error_manager::get_error_info(decl_type::formula));
    return f;
}

ast::formula_ptr formulas_parser::parse_true_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type == formula_type::finitary_S5_formula)
        helper.throw_error(error_type::inadmissible_formula_in_theory, info,
                           "Atomic formula 'true'");

    helper.check_next_token<atomic_formula_token::top>();
    return std::make_shared<ast::true_formula>(std::move(info));
}

ast::formula_ptr formulas_parser::parse_false_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type == formula_type::finitary_S5_formula)
        helper.throw_error(error_type::inadmissible_formula_in_theory, info,
                           "Atomic formula 'false'");

    helper.check_next_token<atomic_formula_token::bot>();
    return std::make_shared<ast::false_formula>(std::move(info));
}

ast::formula_ptr formulas_parser::parse_predicate_formula(parser_helper &helper, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    return std::make_shared<ast::predicate_formula>(std::move(info),
                                                    formulas_parser::parse_predicate(helper, false));
}

ast::formula_ptr formulas_parser::parse_eq_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type == formula_type::finitary_S5_formula)
        helper.throw_error(error_type::inadmissible_formula_in_theory, info, "Equality");

    info.add_requirement(":equality", error_manager::get_requirement_warning(requirement_warning::equality));

    helper.check_next_token<punctuation_token::eq>();
    ast::term t1 = formulas_parser::parse_term(helper, error_manager::get_error_info(decl_type::term));
    ast::term t2 = formulas_parser::parse_term(helper, error_manager::get_error_info(decl_type::term));

    return std::make_shared<ast::eq_formula>(std::move(info), std::move(t1), std::move(t2));
}

ast::formula_ptr formulas_parser::parse_neq_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type == formula_type::finitary_S5_formula)
        helper.throw_error(error_type::inadmissible_formula_in_theory, info, "Inequality");

    info.add_requirement(":equality", error_manager::get_requirement_warning(requirement_warning::inequality));

    helper.check_next_token<punctuation_token::neq>();
    ast::term t1 = formulas_parser::parse_term(helper, error_manager::get_error_info(decl_type::term));
    ast::term t2 = formulas_parser::parse_term(helper, error_manager::get_error_info(decl_type::term));

    return std::make_shared<ast::neq_formula>(std::move(info), std::move(t1), std::move(t2));
}

//ast::formula_ptr formulas_parser::parse_in_formula(parser_helper &helper, bool is_propositional) {
//    ast::info info = helper.get_next_token_info();
//    info.add_requirement(":lists", "Use of membership operators requires ':lists'.");
//
//    helper.check_next_token<keyword_token::in>();
//    auto term = formulas_parser::parse_term(helper);
//    helper.check_next_token<punctuation_token::lpar>();
//    ast::list_ptr list = formulas_parser::parse_list(helper);
//    helper.check_next_token<punctuation_token::rpar>();
//
//    return std::make_shared<ast::in_formula>(std::move(info), std::move(term), std::move(list));
//}

ast::formula_ptr formulas_parser::parse_not_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":negative-" + get_formula_type_str(f_type),
                             error_manager::get_requirement_warning(requirement_warning::negative_formulas,
                                                                         get_formula_type_str(f_type)));

    helper.check_next_token<connective_token::negation>();
    ast::formula_ptr f = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::not_formula>(std::move(info), std::move(f));
}

ast::formula_ptr formulas_parser::parse_and_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<connective_token::conjunction>();
    auto fs = helper.parse_list<ast::formula_ptr>(
            [&]() {
                return formulas_parser::parse_formula_helper(helper, f_type, is_propositional);
            });

    return std::make_shared<ast::and_formula>(std::move(info), std::move(fs));
}

ast::formula_ptr formulas_parser::parse_or_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":disjunctive-" + get_formula_type_str(f_type),
                             error_manager::get_requirement_warning(requirement_warning::disjunctive_formulas,
                                                                         get_formula_type_str(f_type)));

    helper.check_next_token<connective_token::disjunction>();
    auto fs = helper.parse_list<ast::formula_ptr>(
            [&]() {
                return formulas_parser::parse_formula_helper(helper, f_type, is_propositional);
            });

    return std::make_shared<ast::or_formula>(std::move(info), std::move(fs));
}

ast::formula_ptr formulas_parser::parse_imply_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":negative-" + get_formula_type_str(f_type),
                             error_manager::get_requirement_warning(requirement_warning::implication_formulas,
                                                                         get_formula_type_str(f_type)));

    helper.check_next_token<connective_token::implication>();
    ast::formula_ptr f1 = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);
    ast::formula_ptr f2 = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::imply_formula>(std::move(info), std::move(f1), std::move(f2));
}

ast::formula_ptr formulas_parser::parse_box_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":modal-" + get_formula_type_str(f_type),
                             error_manager::get_requirement_warning(requirement_warning::modal_formulas,
                                                                         get_formula_type_str(f_type)));

    const token_ptr &tok = helper.peek_next_token();
    assert(f_type != formula_type::list_formula or f_type != formula_type::finitary_S5_formula);

    if (is_propositional and tok->has_type<punctuation_token::lbrack>()) {
        const std::string what =
                f_type == formula_type::list_formula ? "list comprehension." : "finitary S5 formula.";
        helper.throw_error(error_type::unexpected_token, tok, "modality in " + what);
    }

    helper.check_next_token<punctuation_token::lbrack>();
    ast::modality_ptr mod = formulas_parser::parse_modality(helper);
    helper.check_next_token<punctuation_token::rbrack>();
    ast::formula_ptr f = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::box_formula>(std::move(info), std::move(mod), std::move(f));
}

ast::formula_ptr formulas_parser::parse_diamond_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":modal-" + get_formula_type_str(f_type),
                             error_manager::get_requirement_warning(requirement_warning::modal_formulas,
                                                                         get_formula_type_str(f_type)));

    const token_ptr &tok = helper.peek_next_token();
    assert(f_type != formula_type::list_formula or f_type != formula_type::finitary_S5_formula);

    if (is_propositional and tok->has_type<punctuation_token::langle>()) {
        const std::string what =
                f_type == formula_type::list_formula ? "list comprehension." : "finitary S5 formula.";
        helper.throw_error(error_type::unexpected_token, tok, "modality in " + what);
    }

    helper.check_next_token<punctuation_token::langle>();
    ast::modality_ptr mod = formulas_parser::parse_modality(helper);
    helper.check_next_token<punctuation_token::rangle>();
    ast::formula_ptr f = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::diamond_formula>(std::move(info), std::move(mod), std::move(f));
}

ast::formula_ptr formulas_parser::parse_forall_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":universal-" + get_formula_type_str(f_type),
                             error_manager::get_requirement_warning(requirement_warning::universal_formulas,
                                                                         get_formula_type_str(f_type)));

    helper.check_next_token<quantifier_token::forall>();
    helper.check_left_par(error_manager::get_error_info(decl_type::quantified_params));
    ast::list_comprehension_ptr params = formulas_parser::parse_list_comprehension(helper);
    helper.check_right_par(error_manager::get_error_info(decl_type::quantified_params));

    ast::formula_ptr f = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::forall_formula>(std::move(info), std::move(params), std::move(f));
}

ast::formula_ptr formulas_parser::parse_exists_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":existential-" + get_formula_type_str(f_type),
                             error_manager::get_requirement_warning(requirement_warning::existential_formulas,
                                                                         get_formula_type_str(f_type)));

    helper.check_next_token<quantifier_token::exists>();
    helper.check_left_par(error_manager::get_error_info(decl_type::quantified_params));
    ast::list_comprehension_ptr params = formulas_parser::parse_list_comprehension(helper);
    helper.check_right_par(error_manager::get_error_info(decl_type::quantified_params));

    ast::formula_ptr f = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::exists_formula>(std::move(info), std::move(params), std::move(f));
}

ast::simple_agent_group_ptr formulas_parser::parse_simple_agent_group(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();
    info.add_requirement(":lists", error_manager::get_requirement_warning(requirement_warning::lists));

    auto terms = helper.parse_list<ast::term>([&]() {
        return formulas_parser::parse_term(helper, error_manager::get_error_info(decl_type::agent_term));
    });

    return std::make_shared<ast::simple_agent_group>(std::move(info), std::move(terms));
}

ast::list_comprehension_ptr formulas_parser::parse_list_comprehension(parser_helper &helper, bool allow_empty_params) {
    ast::info info = helper.get_next_token_info();

    auto params = helper.parse_list<ast::typed_variable_ptr, punctuation_token::such_that>(
            [&]() {
                return typed_elem_parser::parse_typed_variable(helper);
            }, allow_empty_params);

    auto f = helper.parse_optional<ast::formula_ptr, punctuation_token::such_that>(
            [&]() {
                return formulas_parser::parse_such_that(helper);
            });

    if (f.has_value())
        info.add_requirement(":list-comprehensions",
                             error_manager::get_requirement_warning(requirement_warning::list_comprehensions));

    return std::make_shared<ast::list_comprehension>(std::move(info), std::move(params), std::move(f));
}

ast::formula_ptr formulas_parser::parse_such_that(parser_helper &helper) {
    helper.check_next_token<punctuation_token::such_that>();
    return formulas_parser::parse_propositional_formula(helper, formula_type::list_formula);
}

ast::predicate_ptr formulas_parser::parse_predicate(parser_helper &helper, bool parse_outer_pars) {
    ast::info info = helper.get_next_token_info();

    if (parse_outer_pars) helper.check_left_par(error_manager::get_error_info(decl_type::predicate));

    auto name = tokens_parser::parse_token<ast::identifier>(helper);
    auto terms = helper.parse_list<ast::term>([&]() {
        return formulas_parser::parse_term(helper, error_manager::get_error_info(decl_type::term));
    }, true);

    if (parse_outer_pars) helper.check_right_par(error_manager::get_error_info(decl_type::predicate));

    return std::make_shared<ast::predicate>(std::move(info), std::move(name), std::move(terms));
}

ast::literal_ptr formulas_parser::parse_literal(parser_helper &helper, bool parse_outer_pars) {
    ast::info info = helper.get_next_token_info();

    if (parse_outer_pars) helper.check_left_par(error_manager::get_error_info(decl_type::literal));
    const token_ptr &tok = helper.peek_next_token();
    bool is_positive = tok->has_type<ast_token::identifier>();

    if (not tok->has_type<ast_token::identifier>() and not tok->has_type<connective_token::negation>())
        helper.throw_error(error_type::token_mismatch, tok, error_manager::get_error_info(decl_type::literal));

    if (tok->has_type<connective_token::negation>())
        helper.check_next_token<connective_token::negation>();

    // If we are parsing a positive literal, then 'parse_predicate' should not clipp::parse the outer parentheses of the predicate
    auto predicate = formulas_parser::parse_predicate(helper, not is_positive);
    if (parse_outer_pars) helper.check_right_par(error_manager::get_error_info(decl_type::literal));

    return std::make_shared<ast::literal>(std::move(info), is_positive, std::move(predicate));
}

ast::term formulas_parser::parse_term(parser_helper &helper, const std::string &msg) {
    // Term
    const token_ptr &tok = helper.peek_next_token();
    ast::term term;

    if (tok->has_type<ast_token::identifier>())
        term = std::move(tokens_parser::parse_identifier(helper, msg));
    else if (tok->has_type<ast_token::variable>())
        term = std::move(tokens_parser::parse_variable(helper, msg));
    else
        helper.throw_error(error_type::token_mismatch, tok, error_manager::get_error_info(decl_type::term));

    return term;
}

ast::modality_ptr formulas_parser::parse_modality(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    auto modality_name = helper.parse_optional<ast::modality_name_ptr,
        modality_token::kw, modality_token::ck>([&]() {
        return tokens_parser::parse_modality_name(helper);
    });

    ast::modality_index_ptr modality_index = formulas_parser::parse_modality_index(helper);

    if (std::holds_alternative<ast::list<ast::simple_agent_group_ptr>>(modality_index) or
        std::holds_alternative<ast::all_group_modality_ptr>(modality_index))
        info.add_requirement(":group-modalities", error_manager::get_requirement_warning(requirement_warning::group_modalities));

    return std::make_shared<ast::modality>(std::move(info), std::move(modality_name),
                                           std::move(modality_index));
}

ast::modality_index_ptr formulas_parser::parse_modality_index(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    ast::modality_index_ptr modality_index;

    if (tok->has_either_type<ast_token::identifier, ast_token::variable>())
        modality_index = formulas_parser::parse_term(helper, error_manager::get_error_info(decl_type::modality_index_term));
    else if (tok->has_type<punctuation_token::lpar>())
        modality_index = formulas_parser::parse_list<ast::simple_agent_group_ptr,
            ast_token::identifier, ast_token::variable>(helper, error_manager::get_error_info(decl_type::modality_group), [&]() {
                    return formulas_parser::parse_simple_agent_group(helper);
                });
    else if (tok->has_type<agent_group_token::all>())
        modality_index = formulas_parser::parse_all_group_modality(helper);
    else
        helper.throw_error(error_type::token_mismatch, tok, error_manager::get_error_info(decl_type::modality_index));

    return modality_index;
}

ast::all_group_modality_ptr formulas_parser::parse_all_group_modality(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();
    info.add_requirement(":group-modalities", error_manager::get_requirement_warning(requirement_warning::group_modalities));

    helper.check_next_token<agent_group_token::all>();
    return std::make_shared<ast::all_group_modality>(info);
}

ast::term_list formulas_parser::parse_group_modality(parser_helper &helper) {
    helper.check_left_par(error_manager::get_error_info(decl_type::modality_group));
    auto mods = helper.parse_list<ast::term>([&] () {
        return formulas_parser::parse_term(helper, error_manager::get_error_info(decl_type::agent_term));
    });
    helper.check_right_par(error_manager::get_error_info(decl_type::modality_group));

    return mods;
}

std::string formulas_parser::get_formula_type_str(const formula_type &f_type) {
    switch (f_type) {
        case formula_type::precondition:
            return "preconditions";
        case formula_type::postcondition:
            return "postconditions";
        case formula_type::obs_condition:
            return "obs-conditions";
        case formula_type::goal:
            return "goals";
        case formula_type::list_formula:
            return "list-formulas";
        case formula_type::finitary_S5_formula:
        case formula_type::cli_user_formula:
            return "";
    }
    return "";
}
