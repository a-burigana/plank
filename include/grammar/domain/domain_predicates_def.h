#ifndef EPDDL_DOMAIN_PREDICATES_DEF_H
#define EPDDL_DOMAIN_PREDICATES_DEF_H

#include "../../tokens/tokens.h"

#define epddl_domain_predicates   domain_predicates
#define epddl_predicate_signature predicate_signature

#define epddl_all_domain_predicates_element_defs \
    epddl_domain_predicates_def                  \
    epddl_predicate_signature_def

#define epddl_all_domain_predicates_auxiliary_type_defs

#define epddl_domain_predicates_def \
    epddl_element(                                                    \
        ast_class(                                                    \
            class_name(epddl_domain_predicates),                      \
            class_params(                                             \
                list_param(epddl_predicate_signature, signatures)     \
            )                                                         \
        ),                                                            \
        parse_element(                                                \
            terminal(epddl_tok_lpar)                                  \
            terminal(epddl_tok_predicates)                            \
            list_node(epddl_predicate_signature)                      \
            terminal(epddl_tok_rpar)                                  \
        )                                                             \
    )

#define epddl_predicate_signature_def \
    epddl_element(                                               \
        ast_class(                                               \
            class_name(epddl_predicate_signature),               \
            class_params(                                        \
                param(epddl_tok_identifier, name),               \
                opt_list_param(epddl_typed_variable, params)     \
            )                                                    \
        ),                                                       \
        parse_element(                                           \
            terminal(epddl_tok_lpar)                             \
            terminal(epddl_tok_identifier)                       \
            list_node(epddl_typed_variable)                      \
            terminal(epddl_tok_rpar)                             \
        )                                                        \
    )

#endif //EPDDL_DOMAIN_PREDICATES_DEF_H
