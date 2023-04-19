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
    epddl_element(                                       \
        ast_class(                                       \
            class_name(epddl_domain),                    \
            class_params(                                \
                param(epddl_tok_identifier, name),       \
                list_param(epddl_domain_item, items)     \
            )                                            \
        ),                                               \
        parse_element(                                   \
            terminal(epddl_tok_lpar)                     \
            terminal(epddl_tok_define)                   \
            terminal(epddl_tok_lpar)                     \
            terminal(epddl_tok_domain)                   \
            terminal(epddl_tok_identifier)               \
            terminal(epddl_tok_rpar)                     \
            list_node(epddl_domain_item)                 \
            terminal(epddl_tok_rpar)                     \
        )                                                \
    )

#define epddl_domain_item_def \
    epddl_auxiliary_type(                          \
        type_name(epddl_domain_item),              \
        variant(                                   \
            ast_class(epddl_domain_requirements),  \
            ast_class(epddl_domain_libraries),     \
            ast_class(epddl_domain_types),         \
            ast_class(epddl_domain_predicates),    \
            ast_class(epddl_domain_modalities),    \
            ast_class(epddl_domain_action)         \
        )                                          \
    )

#endif //EPDDL_DOMAIN_DEF_H
