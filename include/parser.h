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

    parser(lexer& lex);
    ~parser();

//    token get_current_token();

private:
    lexer& m_lex;
    std::optional<Token> m_current_tok, m_next_tok;
    std::stack<std::pair<unsigned long,token_type>> m_scopes;
    unsigned long m_lpar_count;

    void get_next_token();
    void peek_next_token();

    bool is_next_token(token_type type);

    void check_current_token(const token_type &expected_type);
    void check_next_token(const token_type& expected_type);
    void check_token_list(const std::list<token_type>& to_check);

    template<class T>
    std::unique_ptr<T> get_node_from_next_token(const token_type& expected_type);

    template<class T>
    std::unique_ptr<T> get_last_node_from_token_list(const std::list<token_type>& to_check);

    template<class T>
    std::list<T> parse_list(std::function<T()> parse_elem);
    void parse_end_list();

    template<class T>
    std::unique_ptr<T> parse_basic(basic_value type);

    template<class T>
    std::unique_ptr<T> parse_basic_or_rpar(basic_value type);

    identifier parse_ident();
    variable parse_variable();
    integer parse_integer();
    type parse_type();
    modality parse_modality();
    requirement parse_requirement();
    valued_requirement parse_valued_requirement();
    term parse_term();
    formula parse_formula();
    quantified_formula parse_quantified_formula();
    modal_formula parse_modal_formula();

    predicate parse_predicate();

    eq_formula parse_eq_formula();

    expression parse_expression();
    assignment parse_assignment();
    parameters parse_parameters();

    actual_parameter parse_actual_parameter();
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

    action_type parse_action_type();
    literal parse_literal();
    simple_post parse_simple_postcondition();
    forall_post parse_forall_postcondition();
    event parse_event();
    library parse_library();
    agent_group parse_agent_group();
    epistemic_state parse_epistemic_state();
    init parse_init();
    problem parse_problem();
    planning_task parse_epddl_planning_task();
};

#endif //EPDDL_PARSER_H
