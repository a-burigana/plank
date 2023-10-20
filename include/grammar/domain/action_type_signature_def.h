#ifndef EPDDL_ACTION_TYPE_SIGNATURE_DEF_H
#define EPDDL_ACTION_TYPE_SIGNATURE_DEF_H

#include "../common/signature_def.h"

#define epddl_action_type_signature action_type_signature

#define epddl_all_action_type_signature_element_defs \
    epddl_action_type_signature_def

#define epddl_all_action_type_signature_variant_element_defs

#define epddl_action_type_signature_def \
    epddl_element(                                 \
        element_name(epddl_action_type_signature), \
        is_terminal(0),                            \
        element_bnf(                               \
            terminal(epddl_tok_act_type),          \
            terminal(epddl_tok_lpar),              \
            node(epddl_signature, signature),      \
            terminal(epddl_tok_rpar)               \
        )                                          \
    )

#endif //EPDDL_ACTION_TYPE_SIGNATURE_DEF_H
