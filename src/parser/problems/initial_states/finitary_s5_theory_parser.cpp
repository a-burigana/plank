#include "../../../../include/parser/problems/initial_states/finitary_s5_theory_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"
#include "../../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::finitary_s5_theory_ptr finitary_s5_theory_parser::parse(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    helper.check_next_token<connective_token::conjunction>();
    auto theory_fs = helper.parse_list<ast::theory_formula_ptr>([&]() { return finitary_s5_theory_parser::parse_theory_formula(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::finitary_s5_theory>(std::move(theory_fs));
}

ast::theory_formula_ptr finitary_s5_theory_parser::parse_theory_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::theory_formula_ptr f;

    if (tok->has_type<pattern_token::identifier>())          f = finitary_s5_theory_parser::parse_pred_atomic_formula(helper);
    else if (tok->has_type<connective_token::negation>())    f = finitary_s5_theory_parser::parse_not_atomic_formula(helper);
    else if (tok->has_type<connective_token::conjunction>()) f = finitary_s5_theory_parser::parse_and_atomic_formula(helper);
    else if (tok->has_type<connective_token::disjunction>()) f = finitary_s5_theory_parser::parse_or_atomic_formula(helper);
    else if (tok->has_type<connective_token::implication>()) f = finitary_s5_theory_parser::parse_imply_atomic_formula(helper);
    else if (tok->has_type<quantifier_token::forall>())      f = finitary_s5_theory_parser::parse_forall_atomic_formula(helper);
    else if (tok->has_type<quantifier_token::exists>())      f = finitary_s5_theory_parser::parse_exists_atomic_formula(helper);
    else if (tok->has_type<punctuation_token::lbrack>())     f = finitary_s5_theory_parser::parse_ck_formula(helper);
    else                                                     throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected finitary S5 theory formula. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return f;
}

ast::ck_formula_ptr finitary_s5_theory_parser::parse_ck_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lbrack>();
    helper.check_next_token<modality_token::ck>();
    helper.check_next_token<agent_group_token::all>();
    helper.check_next_token<punctuation_token::rbrack>();
    helper.check_next_token<punctuation_token::lpar>();

    const token_ptr &tok = helper.peek_next_token();
    ast::ck_formula_ptr f;

    if (tok->has_type<pattern_token::identifier>())          f = std::make_unique<ast::ck_atomic_formula>(finitary_s5_theory_parser::parse_pred_atomic_formula(helper));
    else if (tok->has_type<connective_token::negation>())    f = std::make_unique<ast::ck_atomic_formula>(finitary_s5_theory_parser::parse_not_atomic_formula(helper));
    else if (tok->has_type<connective_token::conjunction>()) f = std::make_unique<ast::ck_atomic_formula>(finitary_s5_theory_parser::parse_and_atomic_formula(helper));
    else if (tok->has_type<connective_token::disjunction>()) f = std::make_unique<ast::ck_atomic_formula>(finitary_s5_theory_parser::parse_or_atomic_formula(helper));
    else if (tok->has_type<connective_token::implication>()) f = std::make_unique<ast::ck_atomic_formula>(finitary_s5_theory_parser::parse_imply_atomic_formula(helper));
    else if (tok->has_type<quantifier_token::forall>())      f = std::make_unique<ast::ck_atomic_formula>(finitary_s5_theory_parser::parse_forall_atomic_formula(helper));
    else if (tok->has_type<quantifier_token::exists>())      f = std::make_unique<ast::ck_atomic_formula>(finitary_s5_theory_parser::parse_exists_atomic_formula(helper));
    else if (tok->has_type<punctuation_token::lbrack>())     f = finitary_s5_theory_parser::parse_K_or_Kw_formula(helper);
    else if (tok->has_type<punctuation_token::langle>())     f = finitary_s5_theory_parser::parse_not_Kw_formula(helper);
    else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected finitary S5 theory formula. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return f;
}

ast::atomic_formula_ptr finitary_s5_theory_parser::parse_atomic_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::atomic_formula_ptr f;

    if (tok->has_type<pattern_token::identifier>())          f = finitary_s5_theory_parser::parse_pred_atomic_formula(helper);
    else if (tok->has_type<connective_token::negation>())    f = finitary_s5_theory_parser::parse_not_atomic_formula(helper);
    else if (tok->has_type<connective_token::conjunction>()) f = finitary_s5_theory_parser::parse_and_atomic_formula(helper);
    else if (tok->has_type<connective_token::disjunction>()) f = finitary_s5_theory_parser::parse_or_atomic_formula(helper);
    else if (tok->has_type<connective_token::implication>()) f = finitary_s5_theory_parser::parse_imply_atomic_formula(helper);
    else if (tok->has_type<quantifier_token::forall>())      f = finitary_s5_theory_parser::parse_forall_atomic_formula(helper);
    else if (tok->has_type<quantifier_token::exists>())      f = finitary_s5_theory_parser::parse_exists_atomic_formula(helper);
    else                                                     throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected atomic formula. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return f;
}

ast::atomic_formula_ptr finitary_s5_theory_parser::parse_pred_atomic_formula(parser_helper &helper) {
    return std::make_unique<ast::pred_atomic_formula>(formulas_parser::parse_predicate(helper, false));
}

ast::atomic_formula_ptr finitary_s5_theory_parser::parse_not_atomic_formula(parser_helper &helper) {
    helper.check_next_token<connective_token::negation>();
    ast::atomic_formula_ptr f = finitary_s5_theory_parser::parse_atomic_formula(helper);

    return std::make_unique<ast::not_atomic_formula>(std::move(f));
}

ast::atomic_formula_ptr finitary_s5_theory_parser::parse_and_atomic_formula(parser_helper &helper) {
    helper.check_next_token<connective_token::conjunction>();
    auto fs = helper.parse_list<ast::atomic_formula_ptr>([&] () { return finitary_s5_theory_parser::parse_atomic_formula(helper); });

    return std::make_unique<ast::and_atomic_formula>(std::move(fs));
}

ast::atomic_formula_ptr finitary_s5_theory_parser::parse_or_atomic_formula(parser_helper &helper) {
    helper.check_next_token<connective_token::disjunction>();
    auto fs = helper.parse_list<ast::atomic_formula_ptr>([&] () { return finitary_s5_theory_parser::parse_atomic_formula(helper); });

    return std::make_unique<ast::or_atomic_formula>(std::move(fs));
}

ast::atomic_formula_ptr finitary_s5_theory_parser::parse_imply_atomic_formula(parser_helper &helper) {
    helper.check_next_token<connective_token::implication>();
    ast::atomic_formula_ptr f1 = finitary_s5_theory_parser::parse_atomic_formula(helper);
    ast::atomic_formula_ptr f2 = finitary_s5_theory_parser::parse_atomic_formula(helper);

    return std::make_unique<ast::imply_atomic_formula>(std::move(f1), std::move(f2));
}

ast::atomic_formula_ptr finitary_s5_theory_parser::parse_forall_atomic_formula(parser_helper &helper) {
    helper.check_next_token<quantifier_token::forall>();
    helper.check_next_token<punctuation_token::lpar>();
    auto params = helper.parse_list<ast::formal_param>([&]() { return typed_elem_parser::parse_typed_variable(helper); });
    helper.check_next_token<punctuation_token::rpar>();
    ast::atomic_formula_ptr f = finitary_s5_theory_parser::parse_atomic_formula(helper);

    return std::make_unique<ast::forall_atomic_formula>(std::move(params), std::move(f));
}

ast::atomic_formula_ptr finitary_s5_theory_parser::parse_exists_atomic_formula(parser_helper &helper) {
    helper.check_next_token<quantifier_token::exists>();
    helper.check_next_token<punctuation_token::lpar>();
    auto params = helper.parse_list<ast::formal_param>([&]() { return typed_elem_parser::parse_typed_variable(helper); });
    helper.check_next_token<punctuation_token::rpar>();
    ast::atomic_formula_ptr f = finitary_s5_theory_parser::parse_atomic_formula(helper);

    return std::make_unique<ast::exists_atomic_formula>(std::move(params), std::move(f));
}

ast::ck_formula_ptr finitary_s5_theory_parser::parse_K_or_Kw_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lbrack>();
    const token_ptr &tok = helper.peek_next_token();
    bool is_kw_formula = false;

    if (tok->has_type<modality_token::kw>()) {
        helper.check_next_token<modality_token::kw>();
        is_kw_formula = true;
    }

    ast::modality_index_ptr mod = formulas_parser::parse_modality_index(helper);
    helper.check_next_token<punctuation_token::rbrack>();
    ast::atomic_formula_ptr af = finitary_s5_theory_parser::parse_atomic_formula(helper);

    ast::ck_formula_ptr f;
    if (is_kw_formula) f = std::make_unique<ast::ck_Kw_formula>(std::move(mod), std::move(af));
    else f = std::make_unique<ast::ck_K_formula>(std::move(mod), std::move(af));

    return f;
}

ast::ck_not_Kw_formula_ptr finitary_s5_theory_parser::parse_not_Kw_formula(parser_helper &helper) {
    helper.check_next_token<punctuation_token::langle>();
    helper.check_next_token<modality_token::kw>();
    ast::modality_index_ptr mod = formulas_parser::parse_modality_index(helper);
    helper.check_next_token<punctuation_token::rangle>();
    ast::atomic_formula_ptr f = finitary_s5_theory_parser::parse_atomic_formula(helper);

    return std::make_unique<ast::ck_not_Kw_formula>(std::move(mod), std::move(f));
}
