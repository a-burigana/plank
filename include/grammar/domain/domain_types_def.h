#ifndef EPDDL_DOMAIN_TYPES_DEF_H
#define EPDDL_DOMAIN_TYPES_DEF_H

#include "../../tokens/tokens.h"
#include "../common-elements/typed_ident_var_def.h"

#define epddl_domain_types domain_types

#define epddl_all_domain_types_element_defs \
    epddl_domain_types_def

#define epddl_all_domain_types_auxiliary_type_defs

#define epddl_domain_types_def \
    epddl_element(                                            \
        ast_class(                                            \
            class_name(epddl_domain_types),                   \
            class_params(                                     \
                list_param(epddl_typed_identifier, types)     \
            )                                                 \
        ),                                                    \
        parse_element(                                        \
            terminal(epddl_tok_lpar)                          \
            terminal(epddl_tok_types)                         \
            list_node(epddl_typed_identifier)                 \
            terminal(epddl_tok_rpar)                          \
        )                                                     \
    )

#endif //EPDDL_DOMAIN_TYPES_DEF_H
