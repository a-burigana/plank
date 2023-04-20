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
    epddl_element(                                          \
        ast_class(                                          \
            class_name(epddl_action_obs_conditions),        \
            class_params(                                   \
                list_param(epddl_obs_condition, conditions) \
            )                                               \
        ),                                                  \
        parse_element(                                      \
            terminal(epddl_tok_obs_conditions)              \
            list_node(epddl_obs_condition)                  \
        )                                                   \
    )

#define epddl_obs_condition_def \
    epddl_auxiliary_type(                           \
        type_name(epddl_obs_condition),             \
        variant(                                    \
             ast_class(epddl_simple_obs_condition), \
             ast_class(epddl_forall_obs_condition)  \
        )                                           \
    )

#define epddl_simple_obs_condition_def \
    epddl_auxiliary_type(                             \
        type_name(epddl_simple_obs_condition),        \
        variant(                                      \
             ast_class(epddl_static_obs_condition),   \
             ast_class(epddl_if_obs_condition),       \
             ast_class(epddl_otherwise_obs_condition) \
        )                                             \
    )

#define epddl_static_obs_condition_def \
    epddl_element(                                  \
        ast_class(                                  \
            class_name(epddl_static_obs_condition), \
            class_params(                           \
                param(epddl_agent, agent),          \
                param(epddl_tok_identifier, group)  \
            )                                       \
        ),                                          \
        parse_element(                              \
            terminal(epddl_tok_lpar)                \
            terminal(epddl_agent)                   \
            terminal(epddl_tok_identifier)          \
            terminal(epddl_tok_rpar)                \
        )                                           \
    )

#define epddl_if_obs_condition_def \
    epddl_element(                                 \
        ast_class(                                 \
            class_name(epddl_if_obs_condition),    \
            class_params(                          \
                param(epddl_formula, cond),        \
                param(epddl_agent, agent),         \
                param(epddl_tok_identifier, group) \
            )                                      \
        ),                                         \
        parse_element(                             \
            terminal(epddl_tok_lpar)               \
            terminal(epddl_tok_if_cond)            \
            node(epddl_formula)                    \
            terminal(epddl_agent)                  \
            terminal(epddl_tok_identifier)         \
            terminal(epddl_tok_rpar)               \
        )                                          \
    )

#define epddl_otherwise_obs_condition_def \
    epddl_element(                                     \
        ast_class(                                     \
            class_name(epddl_otherwise_obs_condition), \
            class_params(                              \
                param(epddl_agent, agent),             \
                param(epddl_tok_identifier, group)     \
            )                                          \
        ),                                             \
        parse_element(                                 \
            terminal(epddl_tok_lpar)                   \
            terminal(epddl_tok_otherwise)              \
            terminal(epddl_agent)                      \
            terminal(epddl_tok_identifier)             \
            terminal(epddl_tok_rpar)                   \
        )                                              \
    )

#define epddl_forall_obs_condition_def \
    epddl_element(                                                \
        ast_class(                                                \
            class_name(epddl_forall_obs_condition),               \
            class_params(                                         \
                list_param(epddl_typed_variable, params),         \
                list_param(epddl_simple_obs_condition, obs_conds) \
            )                                                     \
        ),                                                        \
        parse_element(                                            \
            terminal(epddl_tok_lpar)                              \
            terminal(epddl_tok_forall)                            \
            terminal(epddl_tok_lpar)                              \
            list_node(epddl_typed_variable)                       \
            terminal(epddl_tok_rpar)                              \
            list_node(epddl_simple_obs_condition)                 \
            terminal(epddl_tok_rpar)                              \
        )                                                         \
    )

#endif //EPDDL_ACTION_OBSERVABILITY_CONDITIONS_H
