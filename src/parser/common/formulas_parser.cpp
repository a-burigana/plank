#include "../../../include/parser/common/formulas_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include "../../../include/parser/common/typed_elem_parser.h"
#include <memory>

using namespace epddl;

ast::formula_ptr formulas_parser::parse_formula(epddl::parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = parser.peek_next_token();
    ast::formula_ptr f;

    if (tok->has_type<pattern_token::identifier>())          f = formulas_parser::parse_predicate_formula(parser);
    else if (tok->has_type<punctuation_token::eq>())         f = formulas_parser::parse_eq_formula(parser);
    else if (tok->has_type<connective_token::negation>())    f = formulas_parser::parse_not_formula(parser);
    else if (tok->has_type<connective_token::conjunction>()) f = formulas_parser::parse_and_formula(parser);
    else if (tok->has_type<connective_token::disjunction>()) f = formulas_parser::parse_or_formula(parser);
    else if (tok->has_type<connective_token::implication>()) f = formulas_parser::parse_imply_formula(parser);
    else if (tok->has_type<punctuation_token::lbrack>())     f = formulas_parser::parse_box_formula(parser);
    else if (tok->has_type<punctuation_token::langle>())     f = formulas_parser::parse_diamond_formula(parser);
    else if (tok->has_type<quantifier_token::forall>())      f = formulas_parser::parse_forall_formula(parser);
    else if (tok->has_type<quantifier_token::exists>())      f = formulas_parser::parse_exists_formula(parser);
    else                                                     throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected formula. Found: " + tok->to_string());

    parser.check_next_token<punctuation_token::rpar>();
    return f;
}

ast::formula_ptr formulas_parser::parse_predicate_formula(parser_helper &parser) {
    return std::make_unique<ast::predicate_formula>(formulas_parser::parse_predicate(parser, false));
}

ast::formula_ptr formulas_parser::parse_eq_formula(parser_helper &parser) {
    parser.check_next_token<punctuation_token::eq>();
    ast::term t1 = formulas_parser::parse_term(parser);
    ast::term t2 = formulas_parser::parse_term(parser);

    return std::make_unique<ast::eq_formula>(std::move(t1), std::move(t2));
}

ast::formula_ptr formulas_parser::parse_not_formula(parser_helper &parser) {
    parser.check_next_token<connective_token::negation>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::not_formula>(std::move(f));
}

ast::formula_ptr formulas_parser::parse_and_formula(parser_helper &parser) {
    parser.check_next_token<connective_token::conjunction>();
    auto fs = parser.parse_list<ast::formula_ptr>([&] () { return formulas_parser::parse_formula(parser); });

    return std::make_unique<ast::and_formula>(std::move(fs));
}

ast::formula_ptr formulas_parser::parse_or_formula(parser_helper &parser) {
    parser.check_next_token<connective_token::disjunction>();
    auto fs = parser.parse_list<ast::formula_ptr>([&] () { return formulas_parser::parse_formula(parser); });

    return std::make_unique<ast::or_formula>(std::move(fs));
}

ast::formula_ptr formulas_parser::parse_imply_formula(parser_helper &parser) {
    parser.check_next_token<connective_token::implication>();
    ast::formula_ptr f1 = formulas_parser::parse_formula(parser);
    ast::formula_ptr f2 = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::imply_formula>(std::move(f1), std::move(f2));
}

ast::formula_ptr formulas_parser::parse_box_formula(parser_helper &parser) {
    parser.check_next_token<punctuation_token::lbrack>();
    ast::modality_ptr mod = formulas_parser::parse_modality(parser);
    parser.check_next_token<punctuation_token::rbrack>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::box_formula>(std::move(mod), std::move(f));
}

ast::formula_ptr formulas_parser::parse_diamond_formula(parser_helper &parser) {
    parser.check_next_token<punctuation_token::langle>();
    ast::modality_ptr mod = formulas_parser::parse_modality(parser);
    parser.check_next_token<punctuation_token::rangle>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::diamond_formula>(std::move(mod), std::move(f));
}

ast::formula_ptr formulas_parser::parse_forall_formula(parser_helper &parser) {
    parser.check_next_token<quantifier_token::forall>();
    parser.check_next_token<punctuation_token::lpar>();
    auto formal_params = parser.parse_list<ast::typed_elem_ptr<ast::variable>>([&] () { return typed_elem_parser::parse_typed_elem<ast::variable>(parser); });
    parser.check_next_token<punctuation_token::rpar>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::forall_formula>(std::move(formal_params), std::move(f));
}

ast::formula_ptr formulas_parser::parse_exists_formula(parser_helper &parser) {
    parser.check_next_token<quantifier_token::exists>();
    parser.check_next_token<punctuation_token::lpar>();
    auto formal_params = parser.parse_list<ast::typed_elem_ptr<ast::variable>>([&] () { return typed_elem_parser::parse_typed_elem<ast::variable>(parser); });
    parser.check_next_token<punctuation_token::rpar>();
    ast::formula_ptr f = formulas_parser::parse_formula(parser);

    return std::make_unique<ast::exists_formula>(std::move(formal_params), std::move(f));
}

ast::predicate_ptr formulas_parser::parse_predicate(parser_helper &parser, bool parse_outer_pars) {
    if (parse_outer_pars) parser.check_next_token<punctuation_token::lpar>();
    auto name = tokens_parser::parse_token<ast::identifier>(parser);
    auto terms = parser.parse_list<ast::term>([&]() { return formulas_parser::parse_term(parser); }, true);
    if (parse_outer_pars) parser.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::predicate>(std::move(name), std::move(terms));
}

ast::literal_ptr formulas_parser::parse_literal(epddl::parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = parser.peek_next_token();
    ast::predicate_ptr predicate;
    bool is_positive = false;

    if (tok->has_type<pattern_token::identifier>()) {
        auto name = tokens_parser::parse_token<ast::identifier>(parser);
        auto terms = parser.parse_list<ast::term>([&]() { return formulas_parser::parse_term(parser); }, true);
        parser.check_next_token<punctuation_token::rpar>();

        predicate = std::make_unique<ast::predicate>(std::move(name), std::move(terms));
        is_positive = true;
    } else if (tok->has_type<connective_token::negation>()) {
        parser.check_next_token<connective_token::negation>();
        predicate = std::move(formulas_parser::parse_predicate(parser));
    } else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected literal. Found: " + tok->to_string());

    return std::make_unique<ast::literal>(is_positive, std::move(predicate));
}

ast::term formulas_parser::parse_term(epddl::parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();
    ast::term term;

    if (tok->has_type<pattern_token::identifier>())    term = std::move(tokens_parser::parse_token<ast::identifier>(parser));
    else if (tok->has_type<pattern_token::variable>()) term = std::move(tokens_parser::parse_token<ast::variable>(parser));
    else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected term. Found: " + tok->to_string());

    return term;
}

ast::modality_ptr formulas_parser::parse_modality(epddl::parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();

    if (tok->has_type<pattern_token::identifier>())
        return tokens_parser::parse_token<ast::identifier>(parser);
    else if (tok->has_type<pattern_token::variable>())
        return tokens_parser::parse_token<ast::variable>(parser);
    else if (tok->has_type<punctuation_token::lpar>())
        return formulas_parser::parse_group_modality(parser);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected modality. Found: " + tok->to_string());
}

ast::group_modality_ptr formulas_parser::parse_group_modality(epddl::parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    auto mods = parser.parse_list<ast::single_modality_ptr>([&] () { return formulas_parser::parse_term(parser); });
    parser.check_next_token<punctuation_token::rpar>();

    return mods;
}
