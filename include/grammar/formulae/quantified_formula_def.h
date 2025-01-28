#ifndef EPDDL_QUANTIFIED_FORMULA_DEF_H
#define EPDDL_QUANTIFIED_FORMULA_DEF_H

#include "formula_def.h"
#include "../common/typed_ident_var_def.h"
#include "../tokens/tokens_def.h"

#define epddl_quantified_formula quantified_formula_ptr
#define epddl_exists_formula     exists_formula
#define epddl_forall_formula     forall_formula

#define epddl_all_quantified_formula_element_defs \
    epddl_exists_formula_def                      \
    epddl_forall_formula_def

#define epddl_all_quantified_formula_variant_element_defs \
    epddl_quantified_formula_def

#define epddl_quantified_formula_def \
    epddl_variant_element(                      \
        element_name(epddl_quantified_formula), \
        element_bnf(                            \
            node(epddl_exists_formula),         \
            node(epddl_forall_formula)          \
        )                                       \
    )

#define epddl_exists_formula_def \
    epddl_element(                                   \
        element_name(epddl_exists_formula),          \
        is_terminal(0),                              \
        element_bnf(                                 \
            terminal(epddl_tok_lpar),                \
            terminal(epddl_tok_exists),              \
            terminal(epddl_tok_lpar),                \
            list_node(epddl_typed_variable, params), \
            terminal(epddl_tok_rpar),                \
            node(epddl_formula, f),                  \
            terminal(epddl_tok_rpar)                 \
        )                                            \
    )

#define epddl_forall_formula_def \
    epddl_element(                                   \
        element_name(epddl_forall_formula),          \
        is_terminal(0),                              \
        element_bnf(                                 \
            terminal(epddl_tok_lpar),                \
            terminal(epddl_tok_forall),              \
            terminal(epddl_tok_lpar),                \
            list_node(epddl_typed_variable, params), \
            terminal(epddl_tok_rpar),                \
            node(epddl_formula, f),                  \
            terminal(epddl_tok_rpar)                 \
        )                                            \
    )

#endif //EPDDL_QUANTIFIED_FORMULA_DEF_H
