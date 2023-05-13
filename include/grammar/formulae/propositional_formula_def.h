#ifndef EPDDL_PROPOSITIONAL_FORMULA_DEF_H
#define EPDDL_PROPOSITIONAL_FORMULA_DEF_H

#include "formula_def.h"
#include "atomic_formula_def.h"
#include "../tokens/tokens_def.h"

#define epddl_propositional_formula propositional_formula
#define epddl_not_formula           not_formula
#define epddl_and_formula           and_formula
#define epddl_or_formula            or_formula
#define epddl_imply_formula         imply_formula

#define epddl_all_propositional_formula_element_defs \
    epddl_all_atomic_formula_element_defs            \
    epddl_not_formula_def                            \
    epddl_and_formula_def                            \
    epddl_or_formula_def                             \
    epddl_imply_formula_def

#define epddl_all_propositional_formula_auxiliary_type_defs \
    epddl_all_atomic_formula_auxiliary_type_defs            \
    epddl_propositional_formula_def

#define epddl_propositional_formula_def \
    epddl_variant_element(                         \
        element_name(epddl_propositional_formula), \
        element_bnf(                               \
            node(epddl_atomic_formula),            \
            node(epddl_eq_formula),                \
            node(epddl_not_formula),               \
            node(epddl_and_formula),               \
            node(epddl_or_formula),                \
            node(epddl_imply_formula)              \
        )                                          \
    )

#define epddl_not_formula_def \
    epddl_element(                        \
        element_name(epddl_not_formula),  \
        is_terminal(0),                   \
        element_bnf(                      \
            terminal(epddl_tok_lpar),     \
            terminal(epddl_tok_negation), \
            node(epddl_formula, f),       \
            terminal(epddl_tok_rpar)      \
        )                                 \
    )

#define epddl_and_formula_def \
    epddl_element(                           \
        element_name(epddl_and_formula),     \
        is_terminal(0),                      \
        element_bnf(                         \
            terminal(epddl_tok_lpar),        \
            terminal(epddl_tok_conjunction), \
            list_node(epddl_formula, fs),    \
            terminal(epddl_tok_rpar)         \
        )                                    \
    )

#define epddl_or_formula_def \
    epddl_element(                           \
        element_name(epddl_or_formula),      \
        is_terminal(0),                      \
        element_bnf(                         \
            terminal(epddl_tok_lpar),        \
            terminal(epddl_tok_disjunction), \
            list_node(epddl_formula, fs),    \
            terminal(epddl_tok_rpar)         \
        )                                    \
    )

#define epddl_imply_formula_def \
    epddl_element(                           \
        element_name(epddl_imply_formula),   \
        is_terminal(0),                      \
        element_bnf(                         \
            terminal(epddl_tok_lpar),        \
            terminal(epddl_tok_disjunction), \
            node(epddl_formula, f1),         \
            node(epddl_formula, f2),         \
            terminal(epddl_tok_rpar)         \
        )                                    \
    )

#endif //EPDDL_PROPOSITIONAL_FORMULA_DEF_H
