#include "../../../include/parser/common/relations_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/formulas_parser.h"
#include "../../../include/error-manager/epddl_exception.h"

using namespace epddl;

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

ast::set_comprehension_ptr relations_parser::parse_set_comprehension(epddl::parser_helper &helper) {
    ast::variable_ptr var = tokens_parser::parse_variable(helper);
    std::optional<ast::ident_list> list = std::nullopt;

    const token_ptr &tok = helper.peek_next_token();            // Peeking either 'in' or another variable

    if (tok->has_type<keyword_token::in>()) {
        helper.check_next_token<keyword_token::in>();           // Actually eating 'in'
        helper.check_next_token<punctuation_token::lpar>();
        list = helper.parse_list<ast::identifier_ptr>([&]() { return tokens_parser::parse_identifier(helper); });
        helper.check_next_token<punctuation_token::rpar>();
    }

    return std::make_unique<ast::set_comprehension>(std::move(var), std::move(list));
}

ast::simple_agent_relation_ptr relations_parser::parse_simple_agent_relation(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();
    ast::edge_label label = relations_parser::parse_edge_label(helper);
    auto edge_list = helper.parse_list<ast::edge_ptr>([&]() { return relations_parser::parse_edge(helper); });
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::simple_agent_relation>(std::move(label), std::move(edge_list));
}

ast::forall_agent_relation_ptr relations_parser::parse_forall_agent_relation(parser_helper &helper, bool parse_outer_pars) {
    if (parse_outer_pars) helper.check_next_token<punctuation_token::lpar>();

    helper.check_next_token<quantifier_token::forall>();
    helper.check_next_token<punctuation_token::lpar>();
    auto vars = helper.parse_list<ast::set_comprehension_ptr>([&] () { return relations_parser::parse_set_comprehension(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    auto agent_relation = relations_parser::parse_simple_agent_relation(helper);
    if (parse_outer_pars) helper.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::forall_agent_relation>(std::move(vars), std::move(agent_relation));
}

ast::agent_relation relations_parser::parse_agent_relation(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = helper.peek_next_token();
    ast::agent_relation relation;

    if (tok->has_type<pattern_token::identifier>() or tok->has_type<pattern_token::variable>() or tok->has_type<punctuation_token::lpar>())
        relation = relations_parser::parse_simple_agent_relation(helper, false);
    else if (tok->has_type<quantifier_token::forall>())
        relation = relations_parser::parse_forall_agent_relation(helper, false);
    else
        throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected agent relation. Found: " + tok->to_string());

    helper.check_next_token<punctuation_token::rpar>();
    return relation;
}

ast::agent_relation_list relations_parser::parse_agent_relation_list(parser_helper &helper) {
    helper.check_next_token<keyword_token::relations>();

    helper.check_next_token<punctuation_token::lpar>();
    helper.check_next_token<connective_token::conjunction>();
    auto relation_list = helper.parse_list<ast::agent_relation>([&]() { return relations_parser::parse_agent_relation(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return relation_list;
}
