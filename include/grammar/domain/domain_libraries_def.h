#ifndef EPDDL_DOMAIN_LIBRARIES_DEF_H
#define EPDDL_DOMAIN_LIBRARIES_DEF_H

#include "../tokens/tokens_def.h"

#define epddl_domain_libraries domain_libraries

#define epddl_all_domain_libraries_element_defs \
    epddl_domain_libraries_def

#define epddl_all_domain_libraries_auxiliary_type_defs

#define epddl_domain_libraries_def \
    epddl_element(                                        \
        ast_class(                                        \
            class_name(epddl_domain_libraries),           \
            class_params(                                 \
                list_param(epddl_tok_identifier, libs)    \
            )                                             \
        ),                                                \
        parse_element(                                    \
            terminal(epddl_tok_lpar)                      \
            terminal(epddl_tok_act_type_lib)              \
            list_terminal(epddl_tok_identifier)           \
            terminal(epddl_tok_rpar)                      \
        )                                                 \
    )


#endif //EPDDL_DOMAIN_LIBRARIES_DEF_H
