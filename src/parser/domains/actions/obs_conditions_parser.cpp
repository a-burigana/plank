#include "../../../../include/parser/domains/actions/obs_conditions_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;

ast::obs_cond obs_conditions_parser::parse_action_obs_cond(parser_helper &parser) {
    parser.check_next_token<keyword_token::obs_conditions>();
    return obs_conditions_parser::parse_obs_cond(parser);
}

ast::obs_cond obs_conditions_parser::parse_obs_cond(parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = parser.peek_next_token();
    ast::obs_cond obs_cond;

    if (tok->has_type<observability_token::always>()  or
        tok->has_type<observability_token::if_cond>() or
        tok->has_type<quantifier_token::forall>()     or
        tok->has_type<observability_token::default_cond>())
        obs_cond = obs_conditions_parser::parse_single_obs_cond(parser, false);
    else if (tok->has_type<connective_token::conjunction>())
        obs_cond = obs_conditions_parser::parse_obs_cond_list(parser);
    else if (tok->has_type<observability_token::else_if_cond>()) throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Ill formed observability condition: 'else-if' must be preceded by 'if'.");
    else if (tok->has_type<observability_token::else_cond>())    throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Ill formed observability condition: 'else' must be preceded by 'if'.");
    else                                                         throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected observability condition. Found: " + tok->to_string());

    parser.check_next_token<punctuation_token::rpar>();
    return obs_cond;
}

ast::single_obs_cond obs_conditions_parser::parse_single_obs_cond(epddl::parser_helper &parser, bool parse_outer_pars) {
    if (parse_outer_pars) parser.check_next_token<punctuation_token::lpar>();
    const token_ptr &tok = parser.peek_next_token();
    ast::single_obs_cond obs_cond;

    if (tok->has_type<observability_token::always>())            obs_cond = obs_conditions_parser::parse_always_obs_cond(parser, false);
    else if (tok->has_type<observability_token::if_cond>())      obs_cond = obs_conditions_parser::parse_if_then_else_obs_cond(parser, false);
    else if (tok->has_type<quantifier_token::forall>())          obs_cond = obs_conditions_parser::parse_forall_obs_cond(parser, false);
    else if (tok->has_type<observability_token::default_cond>()) obs_cond = obs_conditions_parser::parse_default_obs_cond(parser, false);
    else if (tok->has_type<connective_token::conjunction>())     throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected single observability condition.");
    else if (tok->has_type<observability_token::else_if_cond>()) throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Ill formed observability condition: 'else-if' must be preceded by 'if'.");
    else if (tok->has_type<observability_token::else_cond>())    throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Ill formed observability condition: 'else' must be preceded by 'if'.");
    else                                                         throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected observability condition. Found: " + tok->to_string());

    if (parse_outer_pars) parser.check_next_token<punctuation_token::rpar>();
    return obs_cond;
}

//ast::simple_obs_cond obs_conditions_parser::parse_simple_obs_cond(epddl::parser_helper &parser) {
//    parser.check_next_token<punctuation_token::lpar>();
//    const token_ptr &tok = parser.peek_next_token();
//    ast::simple_obs_cond obs_cond;
//
//    if (tok->has_type<observability_token::always>())            obs_cond = obs_conditions_parser::parse_always_obs_cond(parser, false);
//    else if (tok->has_type<observability_token::if_cond>())      obs_cond = obs_conditions_parser::parse_if_then_else_obs_cond(parser, false);
//    else if (tok->has_type<quantifier_token::forall>() or
//             tok->has_type<observability_token::default_cond>() or
//             tok->has_type<connective_token::conjunction>())     throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected 'always' or 'if-then-else' observability condition.");
//    else if (tok->has_type<observability_token::else_if_cond>()) throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Ill formed observability condition: 'else-if' must be preceded by 'if'.");
//    else if (tok->has_type<observability_token::else_cond>())    throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Ill formed observability condition: 'else' must be preceded by 'if'.");
//    else                                                         throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected observability condition. Found: " + tok->to_string());
//
//    parser.check_next_token<punctuation_token::rpar>();
//    return obs_cond;
//}

ast::obs_cond_list obs_conditions_parser::parse_obs_cond_list(epddl::parser_helper &parser) {
    parser.check_next_token<connective_token::conjunction>();
    auto obs_conds = parser.parse_list<ast::single_obs_cond>([&] () { return obs_conditions_parser::parse_single_obs_cond(parser); });

    return obs_conds;
}

ast::always_obs_cond_ptr obs_conditions_parser::parse_always_obs_cond(parser_helper &parser, bool parse_outer_pars) {
    if (parse_outer_pars) parser.check_next_token<punctuation_token::lpar>();
    parser.check_next_token<observability_token::always>();
    ast::observing_agent ag = obs_conditions_parser::parse_observing_agent(parser);
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(parser);
    if (parse_outer_pars) parser.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::always_obs_condition>(std::move(ag), std::move(obs_group));
}

ast::if_then_else_obs_cond_ptr obs_conditions_parser::parse_if_then_else_obs_cond(parser_helper &parser, bool parse_outer_pars) {
    if (parse_outer_pars) parser.check_next_token<punctuation_token::lpar>();
    ast::if_obs_cond_ptr if_cond = obs_conditions_parser::parse_if_obs_cond(parser);
    auto else_if_conds = parser.parse_list<ast::else_if_obs_cond_ptr, observability_token::else_cond>([&]() { return obs_conditions_parser::parse_else_if_obs_cond(parser); }, true);
    auto else_cond = parser.parse_optional<ast::else_obs_cond_ptr, observability_token::else_cond>([&] () { return obs_conditions_parser::parse_else_obs_cond(parser); });
    if (parse_outer_pars) parser.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::if_then_else_obs_condition>(std::move(if_cond), std::move(else_if_conds), std::move(else_cond));
}

ast::if_obs_cond_ptr obs_conditions_parser::parse_if_obs_cond(parser_helper &parser) {
    parser.check_next_token<observability_token::if_cond>();
    ast::formula_ptr cond = formulas_parser::parse_formula(parser);
    ast::observing_agent ag = obs_conditions_parser::parse_observing_agent(parser);
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(parser);

    return std::make_unique<ast::if_obs_condition>(std::move(cond), std::move(ag), std::move(obs_group));
}

ast::else_if_obs_cond_ptr obs_conditions_parser::parse_else_if_obs_cond(parser_helper &parser) {
    parser.check_next_token<observability_token::else_if_cond>();
    ast::formula_ptr cond = formulas_parser::parse_formula(parser);
    ast::observing_agent ag = obs_conditions_parser::parse_observing_agent(parser);
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(parser);

    return std::make_unique<ast::else_if_obs_condition>(std::move(cond), std::move(ag), std::move(obs_group));
}

ast::else_obs_cond_ptr obs_conditions_parser::parse_else_obs_cond(parser_helper &parser) {
    parser.check_next_token<observability_token::else_cond>();
    ast::observing_agent ag = obs_conditions_parser::parse_observing_agent(parser);
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(parser);

    return std::make_unique<ast::else_obs_condition>(std::move(ag), std::move(obs_group));
}

ast::forall_obs_cond_ptr obs_conditions_parser::parse_forall_obs_cond(parser_helper &parser, bool parse_outer_pars) {
    if (parse_outer_pars) parser.check_next_token<punctuation_token::lpar>();
    parser.check_next_token<quantifier_token::forall>();
    parser.check_next_token<punctuation_token::lpar>();
    auto list_comprehension = formulas_parser::parse_int_list_comprehension(parser);
    parser.check_next_token<punctuation_token::rpar>();
    ast::obs_cond obs_cond = obs_conditions_parser::parse_obs_cond(parser);
    if (parse_outer_pars) parser.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::forall_obs_condition>(std::move(list_comprehension), std::move(obs_cond));
}

ast::default_obs_cond_ptr obs_conditions_parser::parse_default_obs_cond(parser_helper &parser, bool parse_outer_pars) {
    if (parse_outer_pars) parser.check_next_token<punctuation_token::lpar>();
    parser.check_next_token<observability_token::default_cond>();
    ast::identifier_ptr obs_group = tokens_parser::parse_identifier(parser);
    if (parse_outer_pars) parser.check_next_token<punctuation_token::rpar>();

    return std::make_unique<ast::default_obs_condition>(std::move(obs_group));
}

ast::observing_agent obs_conditions_parser::parse_observing_agent(epddl::parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();
    ast::observing_agent ag;

    if (tok->has_type<pattern_token::identifier>())    ag = std::move(tokens_parser::parse_token<ast::identifier>(parser));
    else if (tok->has_type<pattern_token::variable>()) ag = std::move(tokens_parser::parse_token<ast::variable>(parser));
    else if (tok->has_type<agent_group_token::all>()) {
        parser.check_next_token<agent_group_token::all>();
        ag = agent_group_token::all{};
    } else throw EPDDLParserException("", tok->get_row(), tok->get_col(), "Expected variable or agent identifier. Found: " + tok->to_string());

    return ag;
}
