#ifndef EPDDL_PARAMETERS_DEF_H
#define EPDDL_PARAMETERS_DEF_H

#include "../tokens/tokens_def.h"
#include "typed_ident_var_def.h"

#define epddl_all_parameters_element_defs \
    epddl_parameters_def

#define epddl_all_parameters_auxiliary_defs

#define epddl_parameters_def \
    epddl_element(                                           \
        ast_class(                                           \
            class_name(epddl_parameters),                    \
            class_params(                                    \
                opt_list_param(epddl_typed_variable, params) \
            )                                                \
        ),                                                   \
        parse_element(                                       \
            terminal(epddl_tok_parameters)                   \
            terminal(epddl_tok_lpar)                         \
            opt_list_node(epddl_typed_variable)              \
            terminal(epddl_tok_rpar)                         \
        )                                                    \
    )

#endif //EPDDL_PARAMETERS_DEF_H
