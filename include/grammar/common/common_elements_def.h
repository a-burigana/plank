#ifndef EPDDL_COMMON_ELEMENTS_DEF_H
#define EPDDL_COMMON_ELEMENTS_DEF_H

#include "agent_def.h"
#include "parameters_def.h"
#include "postcondition_def.h"
#include "signature_def.h"
#include "typed_ident_var_def.h"

#define epddl_all_common_element_defs \
    epddl_all_agent_element_defs           \
    epddl_all_parameters_element_defs      \
    epddl_all_postconditions_element_defs  \
    epddl_all_signature_element_defs       \
    epddl_all_typed_ident_var_element_defs

#define epddl_all_common_auxiliary_type_defs \
    epddl_all_agent_auxiliary_type_defs              \
    epddl_all_parameters_auxiliary_defs              \
    epddl_all_postconditions_auxiliary_type_defs     \
    epddl_all_signature_auxiliary_type_defs          \
    epddl_all_typed_ident_var_auxiliary_element_defs

#endif //EPDDL_COMMON_ELEMENTS_DEF_H
