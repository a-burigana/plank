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
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::formula_ptr f;

    if (tok->has_type<atomic_formula_token::top>()) f = formulas_parser::parse_true_formula(helper, f_type, is_propositional);
    else if (tok->has_type<atomic_formula_token::bot>()) f = formulas_parser::parse_false_formula(helper, f_type, is_propositional);
    else if (tok->has_type<ast_token::identifier>()) f = formulas_parser::parse_predicate_formula(helper, is_propositional);
    else if (tok->has_type<punctuation_token::eq>()) f = formulas_parser::parse_eq_formula(helper, f_type, is_propositional);
    else if (tok->has_type<punctuation_token::neq>()) f = formulas_parser::parse_neq_formula(helper, f_type, is_propositional);
//    else if (tok->has_type<keyword_token::in>()) f = formulas_parser::parse_in_formula(helper, is_propositional);
    else if (tok->has_type<connective_token::negation>()) f = formulas_parser::parse_not_formula(helper, f_type, is_propositional);
    else if (tok->has_type<connective_token::conjunction>()) f = formulas_parser::parse_and_formula(helper, f_type, is_propositional);
    else if (tok->has_type<connective_token::disjunction>()) f = formulas_parser::parse_or_formula(helper, f_type, is_propositional);
    else if (tok->has_type<connective_token::implication>()) f = formulas_parser::parse_imply_formula(helper, f_type, is_propositional);
    else if (tok->has_type<punctuation_token::lbrack>()) f = formulas_parser::parse_box_formula(helper, f_type, is_propositional);
    else if (tok->has_type<punctuation_token::langle>()) f = formulas_parser::parse_diamond_formula(helper, f_type, is_propositional);
    else if (tok->has_type<quantifier_token::forall>()) f = formulas_parser::parse_forall_formula(helper, f_type, is_propositional);
    else if (tok->has_type<quantifier_token::exists>()) f = formulas_parser::parse_exists_formula(helper, f_type, is_propositional);
    else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected formula. Found: " + tok->to_string());

    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();
    return f;
}

ast::formula_ptr formulas_parser::parse_true_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type == formula_type::finitary_S5_formula)
        throw EPDDLException(info, "Atomic formula 'true' cannot be used in finitary S5 formulas.");

    helper.check_next_token<atomic_formula_token::top>();
    return std::make_shared<ast::true_formula>(std::move(info));
}

ast::formula_ptr formulas_parser::parse_false_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type == formula_type::finitary_S5_formula)
        throw EPDDLException(info, "Atomic formula 'false' cannot be used in finitary S5 formulas.");

    helper.check_next_token<atomic_formula_token::bot>();
    return std::make_shared<ast::false_formula>(std::move(info));
}

ast::formula_ptr formulas_parser::parse_predicate_formula(parser_helper &helper, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    return std::make_shared<ast::predicate_formula>(std::move(info), formulas_parser::parse_predicate(helper, false));
}

ast::formula_ptr formulas_parser::parse_eq_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type == formula_type::finitary_S5_formula)
        throw EPDDLException(info, "Equality cannot be used in finitary S5 formulas.");

    info.add_requirement(":equality", "Use of equality operators requires ':equality'.");

    helper.check_next_token<punctuation_token::eq>();
    ast::term t1 = formulas_parser::parse_term(helper);
    ast::term t2 = formulas_parser::parse_term(helper);

    return std::make_shared<ast::eq_formula>(std::move(info), std::move(t1), std::move(t2));
}

ast::formula_ptr formulas_parser::parse_neq_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    if (f_type == formula_type::finitary_S5_formula)
        throw EPDDLException(info, "Inequality cannot be used in finitary S5 formulas.");

    info.add_requirement(":equality", "Use of inequality operators requires ':equality'.");

    helper.check_next_token<punctuation_token::neq>();
    ast::term t1 = formulas_parser::parse_term(helper);
    ast::term t2 = formulas_parser::parse_term(helper);

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
                             "Use of negations requires ':negative-" + get_formula_type_str(f_type) + "'.");

    helper.check_next_token<connective_token::negation>();
    ast::formula_ptr f = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::not_formula>(std::move(info), std::move(f));
}

ast::formula_ptr formulas_parser::parse_and_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();

    helper.check_next_token<connective_token::conjunction>();
    auto fs = helper.parse_list<ast::formula_ptr>(
            [&]() { return formulas_parser::parse_formula_helper(helper, f_type, is_propositional); });

    return std::make_shared<ast::and_formula>(std::move(info), std::move(fs));
}

ast::formula_ptr formulas_parser::parse_or_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();
    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":disjunctive-" + get_formula_type_str(f_type),
                             "Use of disjunctions requires ':disjunctive-" + get_formula_type_str(f_type) + "'.");

    helper.check_next_token<connective_token::disjunction>();
    auto fs = helper.parse_list<ast::formula_ptr>(
            [&]() { return formulas_parser::parse_formula_helper(helper, f_type, is_propositional); });

    return std::make_shared<ast::or_formula>(std::move(info), std::move(fs));
}

ast::formula_ptr formulas_parser::parse_imply_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();
    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":negative-" + get_formula_type_str(f_type),
                             "Use of implications requires ':negative-" + get_formula_type_str(f_type) + "'.");

    helper.check_next_token<connective_token::implication>();
    ast::formula_ptr f1 = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);
    ast::formula_ptr f2 = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::imply_formula>(std::move(info), std::move(f1), std::move(f2));
}

ast::formula_ptr formulas_parser::parse_box_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();
    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":modal-" + get_formula_type_str(f_type),
                             "Use of modalities requires ':modal-" + get_formula_type_str(f_type) + "'.");

    const token_ptr &tok = helper.peek_next_token();
    assert(f_type != formula_type::list_formula or f_type != formula_type::finitary_S5_formula);

    if (is_propositional and tok->has_type<punctuation_token::lbrack>())
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(),
                             std::string{"Unexpected modality in "} +
                             std::string{(f_type == formula_type::list_formula
                                          ? "list comprehension."
                                          : "finitary S5 formula.")}};

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
                             "Use of modalities requires ':modal-" + get_formula_type_str(f_type) + "'.");

    const token_ptr &tok = helper.peek_next_token();
    assert(f_type != formula_type::list_formula or f_type != formula_type::finitary_S5_formula);

    if (is_propositional and tok->has_type<punctuation_token::langle>())
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(),
                             std::string{"Unexpected modality in "} +
                             std::string{(f_type == formula_type::list_formula
                                ? "list comprehension."
                                : "finitary S5 formula.")}};

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
                             "Use of universal quantifiers requires ':universal-" + get_formula_type_str(f_type) + "'.");

    helper.check_next_token<quantifier_token::forall>();
    helper.check_next_token<punctuation_token::lpar>();
    ast::list_comprehension_ptr params = formulas_parser::parse_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();
    ast::formula_ptr f = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::forall_formula>(std::move(info), std::move(params), std::move(f));
}

ast::formula_ptr formulas_parser::parse_exists_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional) {
    ast::info info = helper.get_next_token_info();
    if (f_type != formula_type::finitary_S5_formula)
        info.add_requirement(":existential-" + get_formula_type_str(f_type),
                             "Use of existential quantifiers requires ':existential-" + get_formula_type_str(f_type) + "'.");

    helper.check_next_token<quantifier_token::exists>();
    helper.check_next_token<punctuation_token::lpar>();
    ast::list_comprehension_ptr params = formulas_parser::parse_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();
    ast::formula_ptr f = formulas_parser::parse_formula_helper(helper, f_type, is_propositional);

    return std::make_shared<ast::exists_formula>(std::move(info), std::move(params), std::move(f));
}

//ast::agent_group_ptr formulas_parser::parse_agent_group(parser_helper &helper) {
//    ast::agent_group_ptr list;
//
////    if (tok->has_compatible_type<ast_token::identifier>()) list = formulas_parser::parse_list_name(helper);
////    else if (not tok->has_compatible_type<punctuation_token::lpar>())
////        throw EPDDLParserException("", tok->get_row(), tok->get_col(),
////                                   "Expected list definition. Found: " + tok->to_string());
//
//    helper.check_next_token<punctuation_token::lpar>();
//    const token_ptr &tok = helper.peek_next_token();
//
//    if (tok->has_either_type<ast_token::identifier, ast_token::variable>())
//        list = formulas_parser::parse_simple_agent_group(helper);
//    else if (tok->has_type<keyword_token::list_and>())
//        list = formulas_parser::parse_and_agent_group(helper);
//    else if (tok->has_type<keyword_token::list_forall>())
//        list = formulas_parser::parse_forall_agent_group(helper);
//    else
//        throw EPDDLParserException("", tok->get_row(), tok->get_col(),
//                                   "Expected list definition. Found: " + tok->to_string());
//
//    helper.check_next_token<punctuation_token::rpar>();
//
//    return list;
//}

//ast::list_ptr formulas_parser::parse_list_name(parser_helper &helper) {
//    ast::info info = helper.get_next_token_info();
//    info.add_requirement(":lists", "List declarations require ':lists'.");
//
//    auto name = tokens_parser::parse_identifier(helper);
//    return std::make_shared<ast::list_name>(std::move(info), std::move(name));
//}

ast::simple_agent_group_ptr formulas_parser::parse_simple_agent_group(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();
    info.add_requirement(":lists", "List declarations require ':lists'.");

    auto terms = helper.parse_list<ast::term>([&]() { return formulas_parser::parse_term(helper); });
    return std::make_shared<ast::simple_agent_group>(std::move(info), std::move(terms));
}

//ast::agent_group_ptr formulas_parser::parse_and_agent_group(parser_helper &helper) {
//    ast::info info = helper.get_next_token_info();
//    info.add_requirement(":lists", "List declarations require ':lists'.");
//
//    helper.check_next_token<keyword_token::list_and>();
//    auto lists = helper.parse_list<ast::agent_group_ptr>([&]() { return formulas_parser::parse_agent_group(helper); });
//    return std::make_shared<ast::and_agent_group>(std::move(info), std::move(lists));
//}
//
//ast::agent_group_ptr formulas_parser::parse_forall_agent_group(parser_helper &helper) {
//    ast::info info = helper.get_next_token_info();
//    info.add_requirement(":lists", "List declarations require ':lists'.");
//
//    helper.check_next_token<keyword_token::list_forall>();
//    helper.check_next_token<punctuation_token::lpar>();
//    ast::list_comprehension_ptr params = formulas_parser::parse_list_comprehension(helper);
//    helper.check_next_token<punctuation_token::rpar>();
//    auto group = formulas_parser::parse_agent_group(helper);
//
//    return std::make_shared<ast::forall_agent_group>(std::move(info), std::move(params), std::move(group));
//}

ast::list_comprehension_ptr formulas_parser::parse_list_comprehension(parser_helper &helper, bool allow_empty_params) {
    ast::info info = helper.get_next_token_info();

    auto params = helper.parse_list<ast::typed_variable_ptr, punctuation_token::such_that>(
            [&]() { return typed_elem_parser::parse_typed_variable(helper); }, allow_empty_params);
    auto f = helper.parse_optional<ast::formula_ptr, punctuation_token::such_that>(
            [&]() { return formulas_parser::parse_such_that(helper); });

    if (f.has_value())
        info.add_requirement(":list-comprehensions", "Use of list comprehensions requires ':list-comprehensions'.");

    return std::make_shared<ast::list_comprehension>(std::move(info), std::move(params), std::move(f));
}

ast::formula_ptr formulas_parser::parse_such_that(parser_helper &helper) {
    helper.check_next_token<punctuation_token::such_that>();
    return formulas_parser::parse_propositional_formula(helper, formula_type::list_formula);
}

ast::predicate_ptr formulas_parser::parse_predicate(parser_helper &helper, bool parse_outer_pars) {
    ast::info info = helper.get_next_token_info();

    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    auto name = tokens_parser::parse_token<ast::identifier>(helper);
    auto terms = helper.parse_list<ast::term>([&]() { return formulas_parser::parse_term(helper); }, true);
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_shared<ast::predicate>(std::move(info), std::move(name), std::move(terms));
}

ast::literal_ptr formulas_parser::parse_literal(parser_helper &helper, bool parse_outer_pars) {
    ast::info info = helper.get_next_token_info();

    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    bool is_positive = tok->has_type<ast_token::identifier>();

    if (not tok->has_type<ast_token::identifier>() and not tok->has_type<connective_token::negation>())
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected literal. Found: " + tok->to_string());

    if (tok->has_type<connective_token::negation>())
        helper.check_next_token<connective_token::negation>();

    // If we are parsing a positive literal, then 'parse_predicate' should not parse the outer parentheses of the predicate
    auto predicate = formulas_parser::parse_predicate(helper, not is_positive);
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_shared<ast::literal>(std::move(info), is_positive, std::move(predicate));
}

ast::term formulas_parser::parse_term(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    ast::term term;

    if (tok->has_type<ast_token::identifier>()) term = std::move(tokens_parser::parse_token<ast::identifier>(helper));
    else if (tok->has_type<ast_token::variable>()) term = std::move(tokens_parser::parse_token<ast::variable>(helper));
    else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected term. Found: " + tok->to_string());

    return term;
}

ast::modality_ptr formulas_parser::parse_modality(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();

    auto modality_name = helper.parse_optional<ast::modality_name_ptr, modality_token::kw, modality_token::ck>([&]() {
        return tokens_parser::parse_modality_name(helper);
    });

    ast::modality_index_ptr modality_index = formulas_parser::parse_modality_index(helper);

    if (std::holds_alternative<ast::list<ast::simple_agent_group_ptr>>(modality_index) or
        std::holds_alternative<ast::all_group_modality_ptr>(modality_index))
        info.add_requirement(":group-modalities", "Use of group modalities requires ':group-modalities'.");

    return std::make_shared<ast::modality>(std::move(info), std::move(modality_name), std::move(modality_index));
}

ast::modality_index_ptr formulas_parser::parse_modality_index(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    ast::modality_index_ptr modality_index;

    if (tok->has_either_type<ast_token::identifier, ast_token::variable>())
        modality_index = formulas_parser::parse_term(helper);
    else if (tok->has_type<punctuation_token::lpar>())
        modality_index = formulas_parser::parse_list<ast::simple_agent_group_ptr, ast_token::identifier, ast_token::variable>(
                helper, [&]() { return formulas_parser::parse_simple_agent_group(helper); });
    else if (tok->has_type<agent_group_token::all>())
        modality_index = formulas_parser::parse_all_group_modality(helper);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected modality index. Found: " + tok->to_string());

    return modality_index;
}

ast::all_group_modality_ptr formulas_parser::parse_all_group_modality(parser_helper &helper) {
    ast::info info = helper.get_next_token_info();
    info.add_requirement(":group-modalities", "Use of group modalities requires ':group-modalities'.");

    helper.check_next_token<agent_group_token::all>();
    return std::make_shared<ast::all_group_modality>(info);
}

ast::term_list formulas_parser::parse_group_modality(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    auto mods = helper.parse_list<ast::term>([&] () { return formulas_parser::parse_term(helper); });
    helper.check_next_token<punctuation_token::rpar>();

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
            return "";
    }
}
