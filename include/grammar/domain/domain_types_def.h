#ifndef EPDDL_DOMAIN_TYPES_DEF_H
#define EPDDL_DOMAIN_TYPES_DEF_H

#include "../tokens/tokens_def.h"
#include "../common/typed_ident_var_def.h"

#define epddl_domain_types domain_types

#define epddl_all_domain_types_element_defs \
    epddl_domain_types_def

#define epddl_all_domain_types_auxiliary_type_defs

#define epddl_domain_types_def \
    epddl_element(                                    \
        element_name(epddl_domain_types),             \
        is_terminal(0),                               \
        element_bnf(                                  \
            terminal(epddl_tok_lpar),                 \
            terminal(epddl_tok_types),                \
            list_node(epddl_typed_identifier, types), \
            terminal(epddl_tok_rpar)                  \
        )                                             \
    )

// todo: fix definition. Replace epddl_typed_identifier with epddl_type_def to allow definition of super types

#endif //EPDDL_DOMAIN_TYPES_DEF_H
