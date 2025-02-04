#include "../../../../include/parser/domains/actions/action_postconditions_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;

ast::event_postconditions_list action_postconditions_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::effects>();
    helper.check_next_token<punctuation_token::lpar>();
    auto post = helper.parse_list<ast::event_postconditions>([&] () { return action_postconditions_parser::parse_event_postcondition(helper); }, true);
    helper.check_next_token<punctuation_token::rpar>();

    return post;
}

ast::event_postconditions action_postconditions_parser::parse_event_postcondition(epddl::parser_helper &helper) {
    ast::identifier_ptr event = tokens_parser::parse_identifier(helper);
    ast::postconditions post = action_postconditions_parser::parse_postcondition(helper);

    return std::make_pair(std::move(event), std::move(post));
}

ast::postconditions action_postconditions_parser::parse_postcondition(parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = parser.peek_next_token();
    ast::postconditions post;

    if (tok->has_type<pattern_token::identifier>() or tok->has_type<connective_token::negation>())
        post = action_postconditions_parser::parse_literal_postcondition(parser);
    else if (tok->has_type<post_connective_token::iff>())
        post = action_postconditions_parser::parse_iff_postcondition(parser);
    else if (tok->has_type<post_connective_token::when>())
        post = action_postconditions_parser::parse_when_postcondition(parser);
    else if (tok->has_type<quantifier_token::forall>())
        post = action_postconditions_parser::parse_forall_postcondition(parser);
    else if (tok->has_type<connective_token::conjunction>())
        post = action_postconditions_parser::parse_postcondition_list(parser);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected postconditions. Found: " + tok->to_string());

    parser.check_next_token<punctuation_token::rpar>();
    return post;
}

ast::single_postcondition action_postconditions_parser::parse_single_postcondition(parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = parser.peek_next_token();
    ast::single_postcondition post;

    if (tok->has_type<pattern_token::identifier>() or
        tok->has_type<connective_token::negation>())       post = action_postconditions_parser::parse_literal_postcondition(parser);
    else if (tok->has_type<post_connective_token::iff>())  post = action_postconditions_parser::parse_iff_postcondition(parser);
    else if (tok->has_type<post_connective_token::when>()) post = action_postconditions_parser::parse_when_postcondition(parser);
    else if (tok->has_type<quantifier_token::forall>())    post = action_postconditions_parser::parse_forall_postcondition(parser);
    else                                                   throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected postcondition. Found: " + tok->to_string());

    parser.check_next_token<punctuation_token::rpar>();
    return post;
}

//ast::simple_postcondition action_postconditions_parser::parse_simple_postcondition(parser_helper &parser) {
//    parser.check_next_token<punctuation_token::lpar>();
//    const token_ptr &tok = parser.peek_next_token();
//    ast::simple_postcondition post;
//
//    if (tok->has_type<pattern_token::identifier>())        post = action_postconditions_parser::parse_literal_postcondition(parser);
//    else if (tok->has_type<post_connective_token::iff>())  post = action_postconditions_parser::parse_iff_postcondition(parser);
//    else if (tok->has_type<post_connective_token::when>()) post = action_postconditions_parser::parse_when_postcondition(parser);
//    else if (tok->has_type<quantifier_token::forall>())    throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected literal, 'iff' or 'when' postcondition.");
//    else                                                   throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected postcondition. Found: " + tok->to_string());
//
//    parser.check_next_token<punctuation_token::rpar>();
//    return post;
//}

ast::postcondition_list action_postconditions_parser::parse_postcondition_list(parser_helper &parser) {
    parser.check_next_token<connective_token::conjunction>();
    auto post_list = parser.parse_list<ast::single_postcondition>([&]() { return action_postconditions_parser::parse_single_postcondition(parser); });

    return post_list;
}

ast::literal_postcondition_ptr action_postconditions_parser::parse_literal_postcondition(parser_helper &parser) {
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

ast::iff_postcondition_ptr action_postconditions_parser::parse_iff_postcondition(parser_helper &parser) {
    parser.check_next_token<post_connective_token::iff>();
    ast::formula_ptr cond = formulas_parser::parse_formula(parser);
    ast::literal_ptr literal = formulas_parser::parse_literal(parser);

    return std::make_unique<ast::iff_postcondition>(std::move(cond), std::move(literal));
}

ast::when_postcondition_ptr action_postconditions_parser::parse_when_postcondition(parser_helper &parser) {
    parser.check_next_token<post_connective_token::when>();
    ast::formula_ptr cond = formulas_parser::parse_formula(parser);
    ast::literal_ptr literal = formulas_parser::parse_literal(parser);

    return std::make_unique<ast::when_postcondition>(std::move(cond), std::move(literal));
}

ast::forall_postcondition_ptr action_postconditions_parser::parse_forall_postcondition(parser_helper &parser) {
    parser.check_next_token<quantifier_token::forall>();
    parser.check_next_token<punctuation_token::lpar>();
    auto list_comprehension = formulas_parser::parse_int_list_comprehension(parser);
    parser.check_next_token<punctuation_token::rpar>();
    auto post = action_postconditions_parser::parse_postcondition(parser);

    return std::make_unique<ast::forall_postcondition>(std::move(list_comprehension), std::move(post));
}
