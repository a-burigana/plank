#ifndef EPDDL_DOMAIN_REQUIREMENTS_DEF_H
#define EPDDL_DOMAIN_REQUIREMENTS_DEF_H

#include "../tokens/tokens_def.h"

#define epddl_domain_requirements domain_requirements
#define epddl_requirement         requirement
#define epddl_simple_requirement  simple_requirement
#define epddl_val_requirement     val_requirement

#define epddl_all_domain_requirements_element_defs \
    epddl_domain_requirements_def                  \
    epddl_simple_requirement_def                   \
    epddl_val_requirement_def

#define epddl_all_domain_requirements_variant_element_defs \
    epddl_requirement_def

#define epddl_domain_requirements_def \
    epddl_element(                               \
        element_name(epddl_domain_requirements), \
        is_terminal(0),                          \
        element_bnf(                             \
            terminal(epddl_tok_lpar),            \
            terminal(epddl_tok_requirements),    \
            list_node(epddl_requirement, reqs),  \
            terminal(epddl_tok_rpar)             \
        )                                        \
    )

#define epddl_requirement_def \
    epddl_variant_element(                  \
        element_name(epddl_requirement),    \
        element_bnf(                        \
            node(epddl_simple_requirement), \
            node(epddl_val_requirement)     \
        )                                   \
    )

#define epddl_simple_requirement_def \
    epddl_element(                              \
        element_name(epddl_simple_requirement), \
        is_terminal(0),                         \
        element_bnf(                            \
            leaf(epddl_tok_requirement, req)    \
        )                                       \
    )

#define epddl_val_requirement_def \
    epddl_element(                            \
        element_name(epddl_val_requirement),  \
        is_terminal(0),                       \
        element_bnf(                          \
            terminal(epddl_tok_lpar),         \
            leaf(epddl_tok_requirement, req), \
            leaf(epddl_tok_integer, val),     \
            terminal(epddl_tok_rpar)          \
        )                                     \
    )

#endif //EPDDL_DOMAIN_REQUIREMENTS_DEF_H
