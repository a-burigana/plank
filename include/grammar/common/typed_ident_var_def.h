#ifndef EPDDL_TYPED_IDENT_VAR_DEF_H
#define EPDDL_TYPED_IDENT_VAR_DEF_H

#include "../tokens/tokens_def.h"

#define epddl_typed_identifier typed_ident
#define epddl_typed_variable   typed_var

#define epddl_all_typed_ident_var_element_defs \
    epddl_typed_identifier_def                 \
    epddl_typed_variable_def

#define epddl_all_typed_ident_var_auxiliary_element_defs


#define epddl_typed_identifier_def \
    epddl_element(                                           \
        ast_class(                                           \
            class_name(epddl_typed_identifier),              \
            class_params(                                    \
                param(epddl_tok_identifier, id),             \
                opt_param(epddl_tok_identifier, id_type)     \
            )                                                \
        ),                                                   \
        parse_element(                                       \
            terminal(epddl_tok_identifier)                   \
            opt_terminal_sequence(                           \
                terminal(epddl_tok_dash)                     \
                terminal(epddl_tok_identifier)               \
            )                                                \
        )                                                    \
    )

#define epddl_typed_variable_def \
    epddl_element(                                            \
        ast_class(                                            \
            class_name(epddl_typed_variable),                 \
            class_params(                                     \
                param(epddl_tok_variable, var),               \
                opt_param(epddl_tok_identifier, var_type)     \
            )                                                 \
        ),                                                    \
        parse_element(                                        \
            terminal(epddl_tok_variable)                      \
            opt_terminal_sequence(                            \
                terminal(epddl_tok_dash)                      \
                terminal(epddl_tok_identifier)                \
            )                                                 \
        )                                                     \
    )

#endif //EPDDL_TYPED_IDENT_VAR_DEF_H
