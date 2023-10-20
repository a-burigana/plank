#ifndef EPDDL_EFFECTS_DEF_H
#define EPDDL_EFFECTS_DEF_H

#include "../formulae/formula_def.h"
#include "../formulae/atomic_formula_def.h"
#include "../tokens/tokens_def.h"

#define epddl_effect                         effect
#define epddl_conditional_effect             cond_effect
#define epddl_conditional_effect_conjunction cond_effect_conjunction
#define epddl_forall_effect                  forall_effect
#define epddl_when_effect                    when_effect
#define epddl_iff_effect                     iff_effect
#define epddl_effect_condition               effect_condition
#define epddl_literal_conjunction            literal_conjunction

#define epddl_all_postconditions_element_defs \
    epddl_conditional_effect_conjunction_def \
    epddl_forall_effect_def                  \
    epddl_when_effect_def                    \
    epddl_iff_effect_def                     \
    epddl_literal_conjunction_def

#define epddl_all_postconditions_variant_element_defs \
    epddl_conditional_effect_def \
    epddl_effect_def             \
    epddl_effect_condition_def

#define epddl_effect_def  \
    epddl_variant_element(                              \
        element_name(epddl_effect),                     \
        element_bnf(                                    \
             node(epddl_conditional_effect),            \
             node(epddl_conditional_effect_conjunction) \
        )                                               \
    )

#define epddl_conditional_effect_def \
    epddl_variant_element(                      \
        element_name(epddl_conditional_effect), \
        element_bnf(                            \
             node(epddl_forall_effect),         \
             node(epddl_when_effect),           \
             node(epddl_iff_effect),            \
             node(epddl_literal)                \
        )                                       \
    )

#define epddl_conditional_effect_conjunction_def            \
    epddl_element(                                          \
        element_name(epddl_conditional_effect_conjunction), \
        is_terminal(0),                                     \
        element_bnf(                                        \
            terminal(epddl_tok_lpar),                       \
            terminal(epddl_tok_conjunction),                \
            list_node(epddl_conditional_effect, effects),   \
            terminal(epddl_tok_rpar)                        \
        )                                                   \
    )

#define epddl_forall_effect_def \
    epddl_element(                                   \
        element_name(epddl_forall_effect),           \
        is_terminal(0),                              \
        element_bnf(                                 \
            terminal(epddl_tok_lpar),                \
            terminal(epddl_tok_forall),              \
            terminal(epddl_tok_lpar),                \
            list_node(epddl_typed_variable, params), \
            terminal(epddl_tok_rpar),                \
            node(epddl_effect, effect),              \
            terminal(epddl_tok_rpar)                 \
        )                                            \
    )

#define epddl_when_effect_def \
    epddl_element(                                \
        element_name(epddl_when_effect),          \
        is_terminal(0),                           \
        element_bnf(                              \
            terminal(epddl_tok_lpar),             \
            terminal(epddl_tok_when),             \
            node(epddl_formula, cond),            \
            node(epddl_effect_condition, effect), \
            terminal(epddl_tok_rpar)              \
        )                                         \
    )

#define epddl_iff_effect_def \
    epddl_element(                                \
        element_name(epddl_iff_effect),           \
        is_terminal(0),                           \
        element_bnf(                              \
            terminal(epddl_tok_lpar),             \
            terminal(epddl_tok_iff),              \
            node(epddl_formula, cond),            \
            node(epddl_effect_condition, effect), \
            terminal(epddl_tok_rpar)              \
        )                                         \
    )

#define epddl_effect_condition_def \
    epddl_variant_element(                      \
        element_name(epddl_effect_condition),   \
        element_bnf(                            \
             node(epddl_literal),               \
             node(epddl_literal_conjunction)    \
        )                                       \
    )

#define epddl_literal_conjunction_def \
    epddl_element(                               \
        element_name(epddl_literal_conjunction), \
        is_terminal(0),                          \
        element_bnf(                             \
            terminal(epddl_tok_lpar),            \
            terminal(epddl_tok_conjunction),     \
            list_node(epddl_literal, literals),  \
            terminal(epddl_tok_rpar)             \
        )                                        \
    )

#endif //EPDDL_EFFECTS_DEF_H
