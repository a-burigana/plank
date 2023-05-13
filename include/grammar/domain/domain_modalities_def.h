#ifndef EPDDL_DOMAIN_MODALITIES_DEF_H
#define EPDDL_DOMAIN_MODALITIES_DEF_H

#include "../tokens/tokens_def.h"

#define epddl_domain_modalities domain_modalities

#define epddl_all_domain_modalities_element_defs \
    epddl_domain_modalities_def

#define epddl_all_domain_modalities_auxiliary_type_defs

#define epddl_domain_modalities_def \
    epddl_element(                                     \
        element_name(epddl_domain_modalities),         \
        is_terminal(0),                                \
        element_bnf(                                   \
            terminal(epddl_tok_lpar),                  \
            terminal(epddl_tok_modalities),            \
            list_leaf(epddl_tok_modality, modalities), \
            terminal(epddl_tok_rpar)                   \
        )                                              \
    )

#endif //EPDDL_DOMAIN_MODALITIES_DEF_H
