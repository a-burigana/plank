#ifndef EPDDL_SIGNATURE_DEF_H
#define EPDDL_SIGNATURE_DEF_H

#include "../formulae/formula_def.h"
#include "../common/effects_def.h"
#include "../tokens/tokens_def.h"

#define epddl_signature                  signature
#define epddl_typed_expression           typed_expression
#define epddl_object_typed_expression    object_typed_expression
#define epddl_agent_typed_expression     agent_typed_expression
#define epddl_predicate_typed_expression predicate_typed_expression
#define epddl_literal_typed_expression   literal_typed_expression
#define epddl_formula_typed_expression   formula_typed_expression
#define epddl_effects_typed_expression   effects_typed_expression

#define epddl_all_signature_element_defs \
    epddl_signature_def                  \
    epddl_object_typed_expression_def    \
    epddl_agent_typed_expression_def     \
    epddl_predicate_typed_expression_def \
    epddl_literal_typed_expression_def   \
    epddl_formula_typed_expression_def   \
    epddl_effects_typed_expression_def

#define epddl_all_signature_variant_element_defs \
    epddl_typed_expression_def

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
    epddl_variant_element(                          \
        element_name(epddl_typed_expression),       \
        element_bnf(                                \
            node(epddl_object_typed_expression),    \
            node(epddl_agent_typed_expression),     \
            node(epddl_predicate_typed_expression), \
            node(epddl_literal_typed_expression),   \
            node(epddl_formula_typed_expression),   \
            node(epddl_effects_typed_expression)    \
        )                                           \
    )

#define epddl_object_typed_expression_def \
    epddl_element(                                   \
        element_name(epddl_object_typed_expression), \
        is_terminal(0),                              \
        element_bnf(                                 \
            terminal(epddl_tok_lpar),                \
            terminal(epddl_tok_et_object),           \
            node(epddl_term, object),                \
            terminal(epddl_tok_rpar)                 \
        )                                            \
    )
// todo: how do I disambiguate from object and agent?
#define epddl_agent_typed_expression_def \
    epddl_element(                                  \
        element_name(epddl_agent_typed_expression), \
        is_terminal(0),                             \
        element_bnf(                                \
            terminal(epddl_tok_lpar),               \
            terminal(epddl_tok_et_agent),           \
            node(epddl_term, agent),                \
            terminal(epddl_tok_rpar)                \
        )                                           \
    )

#define epddl_predicate_typed_expression_def \
    epddl_element(                                      \
        element_name(epddl_predicate_typed_expression), \
        is_terminal(0),                                 \
        element_bnf(                                    \
            terminal(epddl_tok_lpar),                   \
            terminal(epddl_tok_et_predicate),           \
            node(epddl_predicate, pred),                \
            terminal(epddl_tok_rpar)                    \
        )                                               \
    )

#define epddl_literal_typed_expression_def \
    epddl_element(                                    \
        element_name(epddl_literal_typed_expression), \
        is_terminal(0),                               \
        element_bnf(                                  \
            terminal(epddl_tok_lpar),                 \
            terminal(epddl_tok_et_literal),           \
            node(epddl_literal, lit),                 \
            terminal(epddl_tok_rpar)                  \
        )                                             \
    )

#define epddl_formula_typed_expression_def \
    epddl_element(                                    \
        element_name(epddl_formula_typed_expression), \
        is_terminal(0),                               \
        element_bnf(                                  \
            terminal(epddl_tok_lpar),                 \
            terminal(epddl_tok_et_formula),           \
            node(epddl_formula, formula),             \
            terminal(epddl_tok_rpar)                  \
        )                                             \
    )

#define epddl_effects_typed_expression_def \
    epddl_element(                                    \
        element_name(epddl_effects_typed_expression), \
        is_terminal(0),                               \
        element_bnf(                                  \
            terminal(epddl_tok_lpar),                 \
            terminal(epddl_tok_et_effects),           \
            node(epddl_effect, effect),               \
            terminal(epddl_tok_rpar)                  \
        )                                             \
    )

#endif //EPDDL_SIGNATURE_DEF_H
