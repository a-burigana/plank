#ifndef EPDDL_POSTCONDITION_DEF_H
#define EPDDL_POSTCONDITION_DEF_H

#include "../formulae/formula_def.h"
#include "../formulae/atomic_formula_def.h"
#include "../tokens/tokens_def.h"

#define epddl_postcondition        postcondition
#define epddl_simple_postcondition simple_postcondition
#define epddl_iff_postcondition    iff_postcondition
#define epddl_when_postcondition   when_postcondition
#define epddl_always_postcondition always_postcondition
#define epddl_forall_postcondition forall_postcond

#define epddl_all_postconditions_element_defs \
    epddl_iff_postcondition_def               \
    epddl_when_postcondition_def              \
    epddl_always_postcondition_def            \
    epddl_forall_postcondition_def

#define epddl_all_postconditions_auxiliary_type_defs \
    epddl_simple_postcondition_def                   \
    epddl_postcondition_def

#define epddl_postcondition_def \
    epddl_variant_element(                     \
        element_name(epddl_postcondition),     \
        element_bnf(                           \
             node(epddl_simple_postcondition), \
             node(epddl_forall_postcondition)  \
        )                                      \
    )

#define epddl_simple_postcondition_def \
    epddl_variant_element(                        \
        element_name(epddl_simple_postcondition), \
        element_bnf(                              \
             node(epddl_iff_postcondition),       \
             node(epddl_when_postcondition),      \
             node(epddl_always_postcondition)     \
        )                                         \
    )

#define epddl_iff_postcondition_def \
    epddl_element(                             \
        element_name(epddl_iff_postcondition), \
        is_terminal(0),                        \
        element_bnf(                           \
            terminal(epddl_tok_lpar),          \
            terminal(epddl_tok_iff),           \
            node(epddl_formula, cond),         \
            node(epddl_literal, l),            \
            terminal(epddl_tok_rpar)           \
        )                                      \
    )

#define epddl_when_postcondition_def \
    epddl_element(                              \
        element_name(epddl_when_postcondition), \
        is_terminal(0),                         \
        element_bnf(                            \
            terminal(epddl_tok_lpar),           \
            terminal(epddl_tok_when),           \
            node(epddl_formula, cond),          \
            node(epddl_literal, l),             \
            terminal(epddl_tok_rpar)            \
        )                                       \
    )

#define epddl_always_postcondition_def \
    epddl_element(                                \
        element_name(epddl_always_postcondition), \
        is_terminal(0),                           \
        element_bnf(                              \
            terminal(epddl_tok_lpar),             \
            terminal(epddl_tok_always),           \
            node(epddl_literal, l),               \
            terminal(epddl_tok_rpar)              \
        )                                         \
    )

#define epddl_forall_postcondition_def \
    epddl_element(                                            \
        element_name(epddl_forall_postcondition),             \
        is_terminal(0),                                       \
        element_bnf(                                          \
            terminal(epddl_tok_lpar),                         \
            terminal(epddl_tok_forall),                       \
            terminal(epddl_tok_lpar),                         \
            list_node(epddl_typed_variable, params),          \
            terminal(epddl_tok_rpar),                         \
            list_node(epddl_simple_postcondition, postconds), \
            terminal(epddl_tok_rpar)                          \
        )                                                     \
    )

#endif //EPDDL_POSTCONDITION_DEF_H
