#ifndef EPDDL_DOMAIN_ACTION_DEF_H
#define EPDDL_DOMAIN_ACTION_DEF_H

#include "action_observability_conditions.h"
#include "../common/parameters_def.h"
#include "../common/signature_def.h"
#include "../formulae/formula_def.h"
#include "../tokens/tokens_def.h"

#define epddl_domain_action domain_action

#define epddl_all_domain_actions_element_defs \
    epddl_domain_action_def                         \
    epddl_all_observability_conditions_element_defs

#define epddl_all_domain_actions_variant_element_defs \
    epddl_all_observability_conditions_variant_element_defs

#define epddl_domain_action_def \
    epddl_element(                                                 \
        element_name(epddl_domain_action),                         \
        is_terminal(0),                                            \
        element_bnf(                                               \
            terminal(epddl_tok_lpar),                              \
            terminal(epddl_tok_action),                            \
            leaf(epddl_tok_identifier, name),                      \
            node(epddl_parameters, parameters),                    \
            node(epddl_signature, signature),                      \
            node(epddl_formula, precondition),                     \
            opt_node(epddl_action_obs_conditions, obs_conditions), \
            terminal(epddl_tok_rpar)                               \
        )                                                          \
    )

//  todo:          node(action_condition)                                               \

#endif //EPDDL_DOMAIN_ACTION_DEF_H
