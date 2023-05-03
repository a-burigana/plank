#ifndef EPDDL_DOMAIN_MODALITIES_DEF_H
#define EPDDL_DOMAIN_MODALITIES_DEF_H

#include "../tokens/tokens_def.h"

#define epddl_domain_modalities domain_modalities

#define epddl_all_domain_modalities_element_defs \
    epddl_domain_modalities_def

#define epddl_all_domain_modalities_auxiliary_type_defs

#define epddl_domain_modalities_def \
    epddl_element(                                             \
        ast_class(                                             \
            class_name(epddl_domain_modalities),               \
            class_params(                                      \
                list_param(epddl_tok_modality, modalities)     \
            )                                                  \
        ),                                                     \
        parse_element(                                         \
            terminal(epddl_tok_lpar)                           \
            terminal(epddl_tok_modalities)                     \
            list_terminal(epddl_tok_modality)                  \
            terminal(epddl_tok_rpar)                           \
        )                                                      \
    )

#endif //EPDDL_DOMAIN_MODALITIES_DEF_H
