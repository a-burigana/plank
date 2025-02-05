#include "../../../include/parser/common/relations_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/formulas_parser.h"
#include "../../../include/error-manager/epddl_exception.h"

using namespace epddl;

ast::relations relations_parser::parse_model_relations(parser_helper &helper) {
    helper.check_next_token<keyword_token::relations>();
    return relations_parser::parse_relation(helper);
}

ast::relations relations_parser::parse_relation(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::relations relation;

    if (tok->has_type<pattern_token::identifier>() or tok->has_type<pattern_token::variable>() or tok->has_type<punctuation_token::lpar>())
        relation = relations_parser::parse_simple_relation(helper, false);
    else if (tok->has_type<quantifier_token::forall>())
        relation = relations_parser::parse_forall_relation(helper, false);
    else if (tok->has_type<connective_token::conjunction>())
        relation = relations_parser::parse_relation_list(helper, false);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected agent relations. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return relation;
}

ast::single_relation relations_parser::parse_single_relation(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::single_relation relation;

    if (tok->has_type<pattern_token::identifier>() or tok->has_type<pattern_token::variable>() or tok->has_type<punctuation_token::lpar>())
        relation = relations_parser::parse_simple_relation(helper, false);
    else if (tok->has_type<quantifier_token::forall>())
        relation = relations_parser::parse_forall_relation(helper, false);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected agent relations. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return relation;
}

ast::relation_list relations_parser::parse_relation_list(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    helper.check_next_token<connective_token::conjunction>();
    auto relation_list = helper.parse_list<ast::single_relation>([&]() { return relations_parser::parse_single_relation(helper); });
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return relation_list;
}

ast::simple_relation_ptr relations_parser::parse_simple_relation(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    ast::edge_label label = relations_parser::parse_edge_label(helper);
    auto edge_list = helper.parse_list<ast::edge_ptr>([&]() { return relations_parser::parse_edge(helper); });
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::simple_relation>(std::move(label), std::move(edge_list));
}

ast::forall_relation_ptr relations_parser::parse_forall_relation(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();

    helper.check_next_token<quantifier_token::forall>();
    helper.check_next_token<punctuation_token::lpar>();
    ast::int_list_comprehension_ptr params = formulas_parser::parse_int_list_comprehension(helper);
    helper.check_next_token<punctuation_token::rpar>();

    auto relation = relations_parser::parse_relation(helper);
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::forall_relation>(std::move(params), std::move(relation));
}

ast::edge_ptr relations_parser::parse_edge(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    ast::term t1 = formulas_parser::parse_term(helper);
    ast::term t2 = formulas_parser::parse_term(helper);
    helper.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::edge>(std::move(t1), std::move(t2));
}

ast::edge_label relations_parser::parse_edge_label(parser_helper &helper) {
    const token_ptr &tok = helper.peek_next_token();
    ast::edge_label label;

    if (tok->has_type<pattern_token::identifier>() or tok->has_type<pattern_token::variable>())
        label = formulas_parser::parse_term(helper);
    else if (tok->has_type<punctuation_token::lpar>()) {
        helper.check_next_token<punctuation_token::lpar>();
        label = helper.parse_list<ast::term>([&]() { return formulas_parser::parse_term(helper); });
        helper.check_next_token<punctuation_token::rpar>();
    } else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected term or term list. Found: " + tok->to_string());

    return label;
}
