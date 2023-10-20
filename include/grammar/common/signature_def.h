#ifndef EPDDL_SIGNATURE_DEF_H
#define EPDDL_SIGNATURE_DEF_H

#include "../formulae/formula_def.h"
#include "../common/effects_def.h"
#include "../tokens/tokens_def.h"

#define epddl_signature        signature
#define epddl_typed_expression typed_expression
#define epddl_expression       expression

#define epddl_all_signature_element_defs \
    epddl_signature_def                  \
    epddl_typed_expression_def

#define epddl_all_signature_variant_element_defs \
    epddl_expression_def

#define epddl_signature_def \
    epddl_element(                                   \
        element_name(epddl_signature),               \
        is_terminal(0),                              \
        element_bnf(                                 \
            terminal(epddl_tok_lpar),                \
            leaf(epddl_tok_identifier, name),        \
            list_node(epddl_typed_expression, expr), \
            terminal(epddl_tok_rpar)                 \
        )                                            \
    )

#define epddl_typed_expression_def \
    epddl_element(                             \
        element_name(epddl_typed_expression),  \
        is_terminal(0),                        \
        element_bnf(                           \
            terminal(epddl_tok_lpar),          \
            leaf(epddl_tok_expr_type, type),   \
            node(epddl_expression, expr),      \
            terminal(epddl_tok_rpar)           \
        )                                      \
    )

#define epddl_expression_def \
    epddl_variant_element(              \
        element_name(epddl_expression), \
        element_bnf(                    \
             node(epddl_term),          \
             node(epddl_formula),       \
             node(epddl_effect)         \
        )                               \
    )

#endif //EPDDL_SIGNATURE_DEF_H
