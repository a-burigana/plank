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

// todo: isn't action signature different from event signature? (epddl_tok_act_type vs epddl_tok_event)

#define epddl_signature_def \
    epddl_element(                                    \
        element_name(epddl_signature),                \
        is_terminal(0),                               \
        element_bnf(                                  \
            terminal(epddl_tok_act_type),             \
            terminal(epddl_tok_lpar),                 \
            leaf(epddl_tok_identifier, name),         \
            list_node(epddl_assignment, assignments), \
            terminal(epddl_tok_rpar)                  \
        )                                             \
    )

#define epddl_assignment_def \
    epddl_element(                         \
        element_name(epddl_assignment),    \
        is_terminal(0),                    \
        element_bnf(                       \
            terminal(epddl_tok_lpar),      \
            leaf(epddl_tok_variable, var), \
            terminal(epddl_tok_gets),      \
            node(epddl_expression, expr),  \
            terminal(epddl_tok_rpar)       \
        )                                  \
    )

#define epddl_expression_def \
    epddl_variant_element(              \
        element_name(epddl_expression), \
        element_bnf(                    \
             node(epddl_term),          \
             node(epddl_formula),       \
             node(epddl_postcondition)  \
        )                               \
    )

#endif //EPDDL_SIGNATURE_DEF_H
