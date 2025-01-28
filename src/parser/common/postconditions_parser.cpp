#include "../../../include/parser/common/postconditions_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include "../../../include/parser/common/formulas_parser.h"
#include "../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;

ast::postconditions postconditions_parser::parse(parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = parser.peek_next_token();
    ast::postconditions post;

    if (tok->has_type<pattern_token::identifier>() or tok->has_type<connective_token::negation>())
        post = postconditions_parser::parse_literal_postcondition(parser);
    else if (tok->has_type<post_connective_token::iff>())
        post = postconditions_parser::parse_iff_postcondition(parser);
    else if (tok->has_type<post_connective_token::when>())
        post = postconditions_parser::parse_when_postcondition(parser);
    else if (tok->has_type<quantifier_token::forall>())
        post = postconditions_parser::parse_forall_postcondition(parser);
    else if (tok->has_type<connective_token::conjunction>())
        post = postconditions_parser::parse_postcondition_list(parser);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected postconditions. Found: " + tok->to_string());

    parser.check_next_token<punctuation_token::rpar>();
    return post;
}

ast::single_postcondition postconditions_parser::parse_single_postcondition(parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();
    ast::single_postcondition post;

    if (tok->has_type<pattern_token::identifier>() or
        tok->has_type<connective_token::negation>())       post = postconditions_parser::parse_literal_postcondition(parser);
    else if (tok->has_type<post_connective_token::iff>())  post = postconditions_parser::parse_iff_postcondition(parser);
    else if (tok->has_type<post_connective_token::when>()) post = postconditions_parser::parse_when_postcondition(parser);
    else if (tok->has_type<quantifier_token::forall>())    post = postconditions_parser::parse_forall_postcondition(parser);
    else                                                   throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected postcondition. Found: " + tok->to_string());

    return post;
}

ast::simple_postcondition postconditions_parser::parse_simple_postcondition(parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();
    ast::simple_postcondition post;

    if (tok->has_type<pattern_token::identifier>())        post = postconditions_parser::parse_literal_postcondition(parser);
    else if (tok->has_type<post_connective_token::iff>())  post = postconditions_parser::parse_iff_postcondition(parser);
    else if (tok->has_type<post_connective_token::when>()) post = postconditions_parser::parse_when_postcondition(parser);
    else if (tok->has_type<quantifier_token::forall>())    throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected literal, 'iff' or 'when' postcondition.");
    else                                                   throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected postcondition. Found: " + tok->to_string());

    return post;
}

ast::postcondition_list_ptr postconditions_parser::parse_postcondition_list(parser_helper &parser) {
    parser.check_next_token<connective_token::conjunction>();
    auto post_list = parser.parse_list<ast::single_postcondition>([&]() { return postconditions_parser::parse_single_postcondition(parser); });

    return std::make_unique<ast::postcondition_list>(std::move(post_list));
}

ast::literal_postcondition_ptr postconditions_parser::parse_literal_postcondition(parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();
    ast::predicate_ptr predicate;
    bool is_positive = false;

    if (tok->has_type<pattern_token::identifier>()) {
        auto name = tokens_parser::parse_token<ast::identifier>(parser);
        auto terms = parser.parse_list<ast::term>([&]() { return formulas_parser::parse_term(parser); }, true);

        predicate = std::make_unique<ast::predicate>(std::move(name), std::move(terms));
        is_positive = true;
    } else if (tok->has_type<connective_token::negation>()) {
        parser.check_next_token<connective_token::negation>();
        predicate = std::move(formulas_parser::parse_predicate(parser));
    } else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected literal. Found: " + tok->to_string());

    ast::literal_ptr literal = std::make_unique<ast::literal>(is_positive, std::move(predicate));
    return std::make_unique<ast::literal_postcondition>(std::move(literal));
}

ast::iff_postcondition_ptr postconditions_parser::parse_iff_postcondition(parser_helper &parser) {
    parser.check_next_token<post_connective_token::iff>();
    ast::formula_ptr cond = formulas_parser::parse_formula(parser);
    ast::literal_ptr literal = formulas_parser::parse_literal(parser);

    return std::make_unique<ast::iff_postcondition>(std::move(cond), std::move(literal));
}

ast::when_postcondition_ptr postconditions_parser::parse_when_postcondition(parser_helper &parser) {
    parser.check_next_token<post_connective_token::when>();
    ast::formula_ptr cond = formulas_parser::parse_formula(parser);
    ast::literal_ptr literal = formulas_parser::parse_literal(parser);

    return std::make_unique<ast::when_postcondition>(std::move(cond), std::move(literal));
}

ast::forall_postcondition_ptr postconditions_parser::parse_forall_postcondition(parser_helper &parser) {
    parser.check_next_token<quantifier_token::forall>();
    parser.check_next_token<punctuation_token::lpar>();
    auto params = parser.parse_list<ast::typed_elem_ptr<ast::variable>>([&] () { return typed_elem_parser::parse_typed_elem<ast::variable>(parser); });
    parser.check_next_token<punctuation_token::rpar>();
    auto post_list = parser.parse_list<ast::simple_postcondition>([&]() { return postconditions_parser::parse_simple_postcondition(parser); });

    return std::make_unique<ast::forall_postcondition>(std::move(params), std::move(post_list));
}
