#ifndef EPDDL_DOMAIN_DEF_H
#define EPDDL_DOMAIN_DEF_H

#include "domain_requirements_def.h"
#include "domain_libraries_def.h"
#include "domain_types_def.h"
#include "domain_predicates_def.h"
#include "domain_modalities_def.h"
#include "domain_action_def.h"
#include "../tokens/tokens_def.h"

#define epddl_domain      domain
#define epddl_domain_item domain_item

#define epddl_all_domain_element_defs \
    epddl_domain_def                           \
    epddl_all_domain_requirements_element_defs \
    epddl_all_domain_libraries_element_defs    \
    epddl_all_domain_types_element_defs        \
    epddl_all_domain_predicates_element_defs   \
    epddl_all_domain_modalities_element_defs   \
    epddl_all_domain_actions_element_defs

#define epddl_all_domain_auxiliary_type_defs \
    epddl_domain_item_def                             \
    epddl_all_domain_requirements_auxiliary_type_defs \
    epddl_all_domain_libraries_auxiliary_type_defs    \
    epddl_all_domain_types_auxiliary_type_defs        \
    epddl_all_domain_predicates_auxiliary_type_defs   \
    epddl_all_domain_modalities_auxiliary_type_defs   \
    epddl_all_domain_actions_auxiliary_type_defs

#define epddl_domain_def \
    epddl_element(                               \
        element_name(epddl_domain),              \
        is_terminal(0),                          \
        element_bnf(                             \
            terminal(epddl_tok_lpar),            \
            terminal(epddl_tok_define),          \
            terminal(epddl_tok_lpar),            \
            terminal(epddl_tok_domain),          \
            leaf(epddl_tok_identifier, name),    \
            terminal(epddl_tok_rpar),            \
            list_node(epddl_domain_item, items), \
            terminal(epddl_tok_rpar)             \
        )                                        \
    )

#define epddl_domain_item_def \
    epddl_variant_element(                   \
        element_name(epddl_domain_item),     \
        element_bnf(                         \
            node(epddl_domain_requirements), \
            node(epddl_domain_libraries),    \
            node(epddl_domain_types),        \
            node(epddl_domain_predicates),   \
            node(epddl_domain_modalities),   \
            node(epddl_domain_action)        \
        )                                    \
    )

#endif //EPDDL_DOMAIN_DEF_H
