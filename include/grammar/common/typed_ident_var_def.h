#ifndef EPDDL_TYPED_IDENT_VAR_DEF_H
#define EPDDL_TYPED_IDENT_VAR_DEF_H

#include "../tokens/tokens_def.h"

// todo: is 'type' okay for a C++ identifier?
#define epddl_type             type
#define epddl_typed_identifier typed_ident
#define epddl_typed_variable   typed_var

#define epddl_all_typed_ident_var_element_defs \
    epddl_type_def                             \
    epddl_typed_identifier_def                 \
    epddl_typed_variable_def

#define epddl_all_typed_ident_var_auxiliary_element_defs


#define epddl_type_def \
    epddl_element(                                \
        element_name(epddl_type),                 \
        is_terminal(0),                           \
        element_bnf(                              \
            terminal(epddl_tok_dash),             \
            leaf(epddl_tok_identifier, elem_type) \
        )                                         \
    )

#define epddl_typed_identifier_def \
    epddl_element(                            \
        element_name(epddl_typed_identifier), \
        is_terminal(0),                       \
        element_bnf(                          \
            leaf(epddl_tok_identifier, id),   \
            opt_node(epddl_type, id_type)     \
        )                                     \
    )

#define epddl_typed_variable_def \
    epddl_element(                          \
        element_name(epddl_typed_variable), \
        is_terminal(0),                     \
        element_bnf(                        \
            leaf(epddl_tok_variable, var),  \
            opt_node(epddl_type, var_type)  \
        )                                   \
    )

#endif //EPDDL_TYPED_IDENT_VAR_DEF_H
