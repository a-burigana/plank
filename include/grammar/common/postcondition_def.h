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
    epddl_auxiliary_type(                           \
        type_name(epddl_postcondition),             \
        variant(                                    \
             ast_class(epddl_simple_postcondition), \
             ast_class(epddl_forall_postcondition)  \
        )                                           \
    )

#define epddl_simple_postcondition_def \
    epddl_auxiliary_type(                          \
        type_name(epddl_simple_postcondition),     \
        variant(                                   \
             ast_class(epddl_iff_postcondition),   \
             ast_class(epddl_when_postcondition),  \
             ast_class(epddl_always_postcondition) \
        )                                          \
    )

#define epddl_iff_postcondition_def \
    epddl_element(                                          \
        ast_class(                                          \
            class_name(epddl_iff_postcondition),            \
            class_params(                                   \
                param(epddl_formula, cond),                 \
                param(epddl_literal, l)                     \
            )                                               \
        ),                                                  \
        parse_element(                                      \
            terminal(epddl_tok_lpar)                        \
            terminal(epddl_tok_iff)                         \
            node(epddl_formula)                             \
            node(epddl_literal)                             \
            terminal(epddl_tok_rpar)                        \
        )                                                   \
    )

#define epddl_when_postcondition_def \
    epddl_element(                                          \
        ast_class(                                          \
            class_name(epddl_when_postcondition),           \
            class_params(                                   \
                param(epddl_formula, cond),                 \
                param(epddl_literal, l)                     \
            )                                               \
        ),                                                  \
        parse_element(                                      \
            terminal(epddl_tok_lpar)                        \
            terminal(epddl_tok_when)                        \
            node(epddl_formula)                             \
            node(epddl_literal)                             \
            terminal(epddl_tok_rpar)                        \
        )                                                   \
    )

#define epddl_always_postcondition_def \
    epddl_element(                                          \
        ast_class(                                          \
            class_name(epddl_always_postcondition),         \
            class_params(                                   \
                param(epddl_literal, l)                     \
            )                                               \
        ),                                                  \
        parse_element(                                      \
            terminal(epddl_tok_lpar)                        \
            terminal(epddl_tok_always)                      \
            node(epddl_literal)                             \
            terminal(epddl_tok_rpar)                        \
        )                                                   \
    )

#define epddl_forall_postcondition_def \
    epddl_element(                                                \
        ast_class(                                                \
            class_name(epddl_forall_postcondition),               \
            class_params(                                         \
                list_param(epddl_typed_variable, params),         \
                list_param(epddl_simple_postcondition, postconds) \
            )                                                     \
        ),                                                        \
        parse_element(                                            \
            terminal(epddl_tok_lpar)                              \
            terminal(epddl_tok_forall)                            \
            terminal(epddl_tok_lpar)                              \
            list_node(epddl_typed_variable)                       \
            terminal(epddl_tok_rpar)                              \
            list_node(epddl_simple_postcondition)                 \
            terminal(epddl_tok_rpar)                              \
        )                                                         \
    )

#endif //EPDDL_POSTCONDITION_DEF_H
