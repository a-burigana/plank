#ifndef EPDDL_ACTION_OBSERVABILITY_CONDITIONS_H
#define EPDDL_ACTION_OBSERVABILITY_CONDITIONS_H

#include "../common/agent_def.h"
#include "../tokens/tokens_def.h"

#define epddl_action_obs_conditions   action_obs_conditions
#define epddl_obs_condition           obs_condition
#define epddl_simple_obs_condition    simple_obs_condition
#define epddl_static_obs_condition    static_obs_condition
#define epddl_if_obs_condition        if_obs_condition
#define epddl_otherwise_obs_condition otherwise_obs_condition
#define epddl_forall_obs_condition    forall_obs_condition

#define epddl_all_observability_conditions_element_defs \
    epddl_action_obs_conditions_def                     \
    epddl_static_obs_condition_def                      \
    epddl_if_obs_condition_def                          \
    epddl_otherwise_obs_condition_def                   \
    epddl_forall_obs_condition_def

#define epddl_all_observability_conditions_auxiliary_type_defs \
    epddl_simple_obs_condition_def                             \
    epddl_obs_condition_def

#define epddl_action_obs_conditions_def \
    epddl_element(                                     \
        element_name(epddl_action_obs_conditions),     \
        is_terminal(0),                                \
        element_bnf(                                   \
            terminal(epddl_tok_obs_conditions),        \
            list_node(epddl_obs_condition, conditions) \
        )                                              \
    )

#define epddl_obs_condition_def \
    epddl_variant_element(                     \
        element_name(epddl_obs_condition),     \
        element_bnf(                           \
             node(epddl_simple_obs_condition), \
             node(epddl_forall_obs_condition)  \
        )                                      \
    )

#define epddl_simple_obs_condition_def \
    epddl_variant_element(                        \
        element_name(epddl_simple_obs_condition), \
        element_bnf(                              \
             node(epddl_static_obs_condition),    \
             node(epddl_if_obs_condition),        \
             node(epddl_otherwise_obs_condition)  \
        )                                         \
    )

#define epddl_static_obs_condition_def \
    epddl_element(                                \
        element_name(epddl_static_obs_condition), \
        is_terminal(0),                           \
        element_bnf(                              \
            terminal(epddl_tok_lpar),             \
            node(epddl_agent, agent),             \
            leaf(epddl_tok_identifier, group),    \
            terminal(epddl_tok_rpar)              \
        )                                         \
    )

#define epddl_if_obs_condition_def \
    epddl_element(                             \
        element_name(epddl_if_obs_condition),  \
        is_terminal(0),                        \
        element_bnf(                           \
            terminal(epddl_tok_lpar),          \
            terminal(epddl_tok_if_cond),       \
            node(epddl_formula, cond),         \
            node(epddl_agent, agent),          \
            leaf(epddl_tok_identifier, group), \
            terminal(epddl_tok_rpar)           \
        )                                      \
    )

#define epddl_otherwise_obs_condition_def \
    epddl_element(                                   \
        element_name(epddl_otherwise_obs_condition), \
        is_terminal(0),                              \
        element_bnf(                                 \
            terminal(epddl_tok_lpar),                \
            terminal(epddl_tok_otherwise),           \
            node(epddl_agent, agent),                \
            leaf(epddl_tok_identifier, group),       \
            terminal(epddl_tok_rpar)                 \
        )                                            \
    )

#define epddl_forall_obs_condition_def \
    epddl_element(                                            \
        element_name(epddl_forall_obs_condition),             \
        is_terminal(0),                                       \
        element_bnf(                                          \
            terminal(epddl_tok_lpar),                         \
            terminal(epddl_tok_forall),                       \
            terminal(epddl_tok_lpar),                         \
            list_node(epddl_typed_variable, params),          \
            terminal(epddl_tok_rpar),                         \
            list_node(epddl_simple_obs_condition, obs_conds), \
            terminal(epddl_tok_rpar)                          \
        )                                                     \
    )

#endif //EPDDL_ACTION_OBSERVABILITY_CONDITIONS_H
