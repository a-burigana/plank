#ifndef EPDDL_AGENT_DEF_H
#define EPDDL_AGENT_DEF_H

#include "../tokens/tokens_def.h"

#define epddl_agent agent

#define epddl_all_agent_element_defs

#define epddl_all_agent_auxiliary_type_defs \
    epddl_agent_def

#define epddl_agent_def \
    epddl_auxiliary_type(           \
        type_name(epddl_agent),     \
        variant(                    \
            epddl_tok_identifier,   \
            epddl_tok_variable,     \
            epddl_tok_all           \
        )                           \
    )

#endif //EPDDL_AGENT_DEF_H
