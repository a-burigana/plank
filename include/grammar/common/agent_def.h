#ifndef EPDDL_AGENT_DEF_H
#define EPDDL_AGENT_DEF_H

#include "../tokens/tokens_def.h"

#define epddl_agent agent

#define epddl_all_agent_element_defs

#define epddl_all_agent_variant_element_defs \
    epddl_agent_def

#define epddl_agent_def \
    epddl_variant_element(              \
        element_name(epddl_agent),      \
        element_bnf(                    \
            leaf(epddl_tok_all),        \
            leaf(epddl_tok_identifier), \
            leaf(epddl_tok_variable)    \
        )                               \
    )

#endif //EPDDL_AGENT_DEF_H
