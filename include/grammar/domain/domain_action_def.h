#ifndef EPDDL_DOMAIN_ACTION_DEF_H
#define EPDDL_DOMAIN_ACTION_DEF_H

#include "action_observability_conditions.h"
#include "../common/parameters_def.h"
#include "../common/signature_def.h"
#include "../formulae/formula_def.h"
#include "../tokens/tokens_def.h"

#define epddl_domain_action domain_action
#define epddl_parameters parameters

#define epddl_all_domain_actions_element_defs \
    epddl_domain_action_def                         \
    epddl_all_observability_conditions_element_defs

#define epddl_all_domain_actions_auxiliary_type_defs \
    epddl_all_observability_conditions_auxiliary_type_defs

#define epddl_domain_action_def \
    epddl_element(                                                               \
        ast_class(                                                               \
            class_name(epddl_domain_action),                                     \
            class_params(                                                        \
                param(epddl_tok_identifier, name),                               \
                param(epddl_parameters, parameters),                             \
                param(epddl_signature, signature),                               \
                param(epddl_formula, precondition),                              \
                opt_list_param(epddl_action_obs_conditions, obs_conditions)      \
            )                                                                    \
        ),                                                                       \
        parse_element(                                                           \
            terminal(epddl_tok_lpar)                                             \
            terminal(epddl_tok_action)                                           \
            terminal(epddl_tok_identifier)                                       \
            node(epddl_parameters)                                               \
            node(epddl_signature)                                                \
            node(epddl_formula)                                                  \
            opt_node(epddl_action_obs_conditions)                                \
            terminal(epddl_tok_rpar)                                             \
        )                                                                        \
    )

//  todo:          node(action_condition)                                               \

#endif //EPDDL_DOMAIN_ACTION_DEF_H
