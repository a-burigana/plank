#ifndef EPDDL_ACTION_OBSERVABILITY_CONDITIONS_H
#define EPDDL_ACTION_OBSERVABILITY_CONDITIONS_H

#include "../common/agent_def.h"
#include "../tokens/tokens_def.h"

#define epddl_action_obs_conditions         action_obs_conditions
#define epddl_obs_condition                 obs_condition
#define epddl_conditional_obs               conditional_obs
#define epddl_conditional_obs_conjunction   conditional_obs_conjunction
#define epddl_static_obs_condition          static_obs_condition
#define epddl_if_obs_condition              if_obs_condition
#define epddl_else_if_or_else_obs_condition else_if_or_else_obs_condition
#define epddl_else_if_obs_condition         else_if_obs_condition
#define epddl_else_obs_condition            else_obs_condition
#define epddl_forall_obs_condition          forall_obs_condition

#define epddl_all_observability_conditions_element_defs \
    epddl_action_obs_conditions_def                     \
    epddl_conditional_obs_conjunction_def               \
    epddl_forall_obs_condition_def                      \
    epddl_if_obs_condition_def                          \
    epddl_else_if_obs_condition_def                     \
    epddl_else_obs_condition_def                        \
    epddl_static_obs_condition_def

#define epddl_all_observability_conditions_variant_element_defs \
    epddl_conditional_obs_def                                   \
    epddl_else_if_or_else_obs_condition_def                     \
    epddl_obs_condition_def

#define epddl_action_obs_conditions_def \
    epddl_element(                                 \
        element_name(epddl_action_obs_conditions), \
        is_terminal(0),                            \
        element_bnf(                               \
            terminal(epddl_tok_obs_conditions),    \
            node(epddl_obs_condition, conditions)  \
        )                                          \
    )

#define epddl_obs_condition_def  \
    epddl_variant_element(                           \
        element_name(epddl_obs_condition),           \
        element_bnf(                                 \
             node(epddl_conditional_obs),            \
             node(epddl_conditional_obs_conjunction) \
        )                                            \
    )

#define epddl_conditional_obs_def \
    epddl_variant_element(                     \
        element_name(epddl_conditional_obs),   \
        element_bnf(                           \
             node(epddl_forall_obs_condition), \
             node(epddl_if_obs_condition),     \
             node(epddl_static_obs_condition)  \
        )                                      \
    )

#define epddl_conditional_obs_conjunction_def \
    epddl_element(                                       \
        element_name(epddl_conditional_obs_conjunction), \
        is_terminal(0),                                  \
        element_bnf(                                     \
            terminal(epddl_tok_lpar),                    \
            terminal(epddl_tok_conjunction),             \
            list_node(epddl_conditional_obs, obs_conds), \
            terminal(epddl_tok_rpar)                     \
        )                                                \
    )

#define epddl_forall_obs_condition_def \
    epddl_element(                                   \
        element_name(epddl_forall_obs_condition),    \
        is_terminal(0),                              \
        element_bnf(                                 \
            terminal(epddl_tok_lpar),                \
            terminal(epddl_tok_forall),              \
            terminal(epddl_tok_lpar),                \
            list_node(epddl_typed_variable, params), \
            terminal(epddl_tok_rpar),                \
            node(epddl_obs_condition, obs_conds),    \
            terminal(epddl_tok_rpar)                 \
        )                                            \
    )

#define epddl_if_obs_condition_def \
    epddl_element(                                                   \
        element_name(epddl_if_obs_condition),                        \
        is_terminal(0),                                              \
        element_bnf(                                                 \
            terminal(epddl_tok_lpar),                                \
            terminal(epddl_tok_if_cond),                             \
            node(epddl_formula, cond),                               \
            node(epddl_agent, agent),                                \
            leaf(epddl_tok_identifier, group),                       \
            terminal(epddl_tok_rpar),                                \
            opt_node(epddl_else_if_or_else_obs_condition, else_cond) \
        )                                                            \
    )

#define epddl_else_if_or_else_obs_condition_def            \
    epddl_variant_element(                                 \
        element_name(epddl_else_if_or_else_obs_condition), \
        element_bnf(                                       \
             node(epddl_else_if_obs_condition),            \
             node(epddl_else_obs_condition)                \
        )                                                  \
    )

#define epddl_else_if_obs_condition_def \
    epddl_element(                                                   \
        element_name(epddl_else_if_obs_condition),                   \
        is_terminal(0),                                              \
        element_bnf(                                                 \
            terminal(epddl_tok_lpar),                                \
            terminal(epddl_tok_else_if_cond),                        \
            node(epddl_formula, cond),                               \
            node(epddl_agent, agent),                                \
            leaf(epddl_tok_identifier, group),                       \
            terminal(epddl_tok_rpar),                                \
            opt_node(epddl_else_if_or_else_obs_condition, else_cond) \
        )                                                            \
    )

#define epddl_else_obs_condition_def \
    epddl_element(                              \
        element_name(epddl_else_obs_condition), \
        is_terminal(0),                         \
        element_bnf(                            \
            terminal(epddl_tok_lpar),           \
            terminal(epddl_tok_else_cond),      \
            node(epddl_agent, agent),           \
            leaf(epddl_tok_identifier, group),  \
            terminal(epddl_tok_rpar)            \
        )                                       \
    )

#define epddl_static_obs_condition_def \
    epddl_element(                                \
        element_name(epddl_static_obs_condition), \
        is_terminal(0),                           \
        element_bnf(                              \
            terminal(epddl_tok_lpar),             \
            terminal(epddl_tok_always),           \
            node(epddl_agent, agent),             \
            leaf(epddl_tok_identifier, group),    \
            terminal(epddl_tok_rpar)              \
        )                                         \
    )

#endif //EPDDL_ACTION_OBSERVABILITY_CONDITIONS_H
