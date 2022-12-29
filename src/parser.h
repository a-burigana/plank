#ifndef EPDDL_PARSER_H
#define EPDDL_PARSER_H

#include "ast.h"
#include "lex.h"
#include <stack>
#include "../include/lexer_utils.h"


using namespace epddl::lexer;
using namespace epddl::ast;

class parser {
public:
    using error_handler = std::function<void(token&, std::string)>;

    parser(lexer lex, error_handler error);
    ~parser();

    token get_current_token();
    token & get_next_token();

private:
    lexer m_lex;
    token m_current_tok;
    std::stack<scope> m_scopes;
    error_handler m_error;
    bool m_good;

    [[nodiscard]] bool good() const;

    void check_next_token(epddl_token::type expected_type, const std::string &error);

    ASTNode parse_ast_node();
    ident parse_ident();
    variable parse_variable();
    integer parse_integer();
    type parse_type();
    modality parse_modality();
    requirement parse_requirement();
    ASTNode parse_valued_requirement();
    ASTNode parse_term();
    ASTNode parse_formula();
    ASTNode parse_quantified_formula();
    ASTNode parse_modal_formula();
    ASTNode parse_predicate();
    ASTNode parse_eq_formula();
    ASTNode parse_actual_parameter();
    ASTNode parse_signature();
    ASTNode parse_simple_obs_condition();
    ASTNode parse_if_obs_condition();
    ASTNode parse_forall_obs_condition();
    ASTNode parse_action();
    domain_item parse_domain_item();
    domain parse_domain();
    ASTNode parse_action_type();
    ASTNode parse_literal();
    ASTNode parse_simple_postcondition();
    ASTNode parse_forall_postcondition();
    ASTNode parse_event();
    ASTNode parse_library();
    ASTNode parse_agent_group();
    ASTNode parse_epistemic_state();
    ASTNode parse_init();
    ASTNode parse_problem();
    ASTNode parse_epddl_planning_task();
};

#endif //EPDDL_PARSER_H
