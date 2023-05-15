#ifndef EPDDL_DOMAIN_PREDICATES_DEF_H
#define EPDDL_DOMAIN_PREDICATES_DEF_H

#include "../tokens/tokens_def.h"

#define epddl_domain_predicates   domain_predicates
#define epddl_predicate_signature predicate_signature

#define epddl_all_domain_predicates_element_defs \
    epddl_domain_predicates_def                  \
    epddl_predicate_signature_def

#define epddl_all_domain_predicates_variant_element_defs

#define epddl_domain_predicates_def \
    epddl_element(                                            \
        element_name(epddl_domain_predicates),                \
        is_terminal(0),                                       \
        element_bnf(                                          \
            terminal(epddl_tok_lpar),                         \
            terminal(epddl_tok_predicates),                   \
            list_node(epddl_predicate_signature, signatures), \
            terminal(epddl_tok_rpar)                          \
        )                                                     \
    )

#define epddl_predicate_signature_def \
    epddl_element(                                       \
        element_name(epddl_predicate_signature),         \
        is_terminal(0),                                  \
        element_bnf(                                     \
            terminal(epddl_tok_lpar),                    \
            leaf(epddl_tok_identifier, name),            \
            opt_list_node(epddl_typed_variable, params), \
            terminal(epddl_tok_rpar)                     \
        )                                                \
    )

#endif //EPDDL_DOMAIN_PREDICATES_DEF_H
