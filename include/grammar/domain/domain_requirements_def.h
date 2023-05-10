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

#define epddl_all_domain_requirements_auxiliary_type_defs \
    epddl_requirement_def

#define epddl_domain_requirements_def \
    epddl_element(                                      \
        ast_class(                                      \
            class_name(epddl_domain_requirements),      \
            class_params(                               \
                list_param(epddl_requirement, reqs)     \
            )                                           \
        ),                                              \
        parse_element(                                  \
            terminal(epddl_tok_lpar)                    \
            terminal(epddl_tok_requirements)            \
            list_node(epddl_requirement)                \
            terminal(epddl_tok_rpar)                    \
        )                                               \
    )

#define epddl_requirement_def \
    epddl_auxiliary_type(                         \
        type_name(epddl_requirement),             \
        variant(                                  \
            ast_class(epddl_simple_requirement),  \
            ast_class(epddl_val_requirement)      \
        )                                         \
    )

#define epddl_simple_requirement_def \
    epddl_element(                                    \
        ast_class(                                    \
            class_name(epddl_simple_requirement),     \
            class_params(                             \
                param(epddl_tok_requirement, req)     \
            )                                         \
        ),                                            \
        parse_element(                                \
            terminal(epddl_tok_requirement)           \
        )                                             \
    )

#define epddl_val_requirement_def \
    epddl_element(                                    \
        ast_class(                                    \
            class_name(epddl_val_requirement),        \
            class_params(                             \
                param(epddl_tok_requirement, req),    \
                param(epddl_tok_integer, val)         \
            )                                         \
        ),                                            \
        parse_element(                                \
            terminal(epddl_tok_lpar)                  \
            terminal(epddl_tok_requirement)           \
            terminal(epddl_tok_integer)               \
            terminal(epddl_tok_rpar)                  \
        )                                             \
    )

#endif //EPDDL_DOMAIN_REQUIREMENTS_DEF_H
