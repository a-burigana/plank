#ifndef EPDDL_SIGNATURE_DEF_H
#define EPDDL_SIGNATURE_DEF_H

#include "../formulae/formula_def.h"
#include "../common/postcondition_def.h"
#include "../tokens/tokens_def.h"

#define epddl_signature  signature
#define epddl_assignment assignment
#define epddl_expression expression

#define epddl_all_signature_element_defs \
    epddl_signature_def                  \
    epddl_assignment_def

#define epddl_all_signature_auxiliary_type_defs \
    epddl_expression_def

#define epddl_signature_def \
    epddl_element(                                          \
        ast_class(                                          \
            class_name(epddl_signature),                    \
            class_params(                                   \
                param(epddl_tok_identifier, name),          \
                list_param(epddl_assignment, assignments)   \
            )                                               \
        ),                                                  \
        parse_element(                                      \
            terminal(epddl_tok_act_type)                    \
            terminal(epddl_tok_lpar)                        \
            terminal(epddl_tok_identifier)                  \
            node_list(epddl_assignment)                     \
            terminal(epddl_tok_rpar)                        \
        )                                                   \
    )

#define epddl_assignment_def \
    epddl_element(                                \
        ast_class(                                \
            class_name(epddl_assignment),         \
            class_params(                         \
                param(epddl_tok_identifier, var), \
                param(epddl_expression, expr)     \
            )                                     \
        ),                                        \
        parse_element(                            \
            terminal(epddl_tok_lpar)              \
            terminal(epddl_tok_variable)          \
            terminal(epddl_tok_gets)              \
            node(epddl_expression)                \
            terminal(epddl_tok_rpar)              \
        )                                         \
    )

#define epddl_expression_def \
    epddl_auxiliary_type(                   \
        type_name(epddl_expression),        \
        variant(                            \
             ast_class(epddl_term),         \
             ast_class(epddl_formula),      \
             ast_class(epddl_postcondition) \
        )                                   \
    )

#endif //EPDDL_SIGNATURE_DEF_H
