#ifndef EPDDL_PARSER_H
#define EPDDL_PARSER_H

#include <stack>
#include "lex.h"
#include "ast.h"
#include "lex_utils.h"


using namespace epddl;
//using namespace epddl::ast;

class parser {
public:
//    using error_handler = std::function<void(Token&, std::string)>;

    parser(lexer lex);
    ~parser();

//    token get_current_token();

private:
    lexer m_lex;
    std::optional<Token> m_current_tok, m_next_tok;
    std::stack<scope> m_scopes;
//    error_handler m_error;
//    bool m_good;

//    [[nodiscard]] bool good() const;

    void get_next_token();
    void peek_next_token();

    bool is_next_token(utils::token::type type);

    void check_current_token(utils::token::type expected_type, const std::string& error);
    void check_next_token(utils::token::type expected_type, const std::string& error);
    void check_token_list(const std::list<std::pair<utils::token::type, std::string>>& to_check);

    template<class T>
    std::unique_ptr<T> get_node_from_token(utils::token::type expected_type, const std::string& error);

    template<class T>
    std::unique_ptr<T> get_node_from_token_list(const std::list<std::pair<utils::token::type, std::string>>& to_check);

    template<class T>
    std::list<T> parse_list(std::function<T()> parse_elem);

    ident parse_ident();
    variable parse_variable();
    integer parse_integer();
    type parse_type();
    modality parse_modality();
    requirement parse_requirement();
    valued_requirement parse_valued_requirement();
    ast::ASTNode parse_term();
    formula parse_formula();
    ast::ASTNode parse_quantified_formula();
    ast::ASTNode parse_modal_formula();

    predicate parse_predicate();

    ast::ASTNode parse_eq_formula();

    assignment parse_assignment();
    parameters parse_parameters();

    ast::ASTNode parse_actual_parameter();
    signature parse_signature();

    simple_obs_cond parse_simple_obs_condition();
    if_obs_cond parse_if_obs_condition();
    forall_obs_cond parse_forall_obs_condition();

    obs_cond parse_obs_condition();
    std::optional<obs_cond_list> parse_obs_condition_list();

    domain_libraries parse_domain_act_type_libs();
    domain_requirements parse_domain_requirements();
    domain_types parse_domain_types();

    formal_param parse_formal_param();
    formal_param_list parse_formal_param_list();
    predicate_def parse_predicate_def();
    domain_predicates parse_domain_predicates();
    domain_modalities parse_domain_modalities();
    action parse_action();
    domain_item parse_domain_item();
    domain parse_domain();

    ast::ASTNode parse_action_type();
    ast::ASTNode parse_literal();
    ast::ASTNode parse_simple_postcondition();
    ast::ASTNode parse_forall_postcondition();
    ast::ASTNode parse_event();
    ast::ASTNode parse_library();
    ast::ASTNode parse_agent_group();
    ast::ASTNode parse_epistemic_state();
    ast::ASTNode parse_init();
    ast::ASTNode parse_problem();
    ast::ASTNode parse_epddl_planning_task();
};

#endif //EPDDL_PARSER_H
