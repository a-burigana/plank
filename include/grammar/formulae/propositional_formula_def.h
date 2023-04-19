#ifndef EPDDL_PROPOSITIONAL_FORMULA_DEF_H
#define EPDDL_PROPOSITIONAL_FORMULA_DEF_H

#include "formula_def.h"
#include "../tokens/tokens_def.h"

#define epddl_not_formula   not_formula
#define epddl_and_formula   and_formula
#define epddl_or_formula    or_formula
#define epddl_imply_formula imply_formula

#define epddl_all_propositional_formula_element_defs \
    epddl_not_formula_def                            \
    epddl_and_formula_def                            \
    epddl_or_formula_def                             \
    epddl_imply_formula_def

#define epddl_all_propositional_formula_auxiliary_type_defs

#define epddl_not_formula_def \
    epddl_element(                         \
        ast_class(                         \
            class_name(epddl_not_formula), \
            class_params(                  \
                param(epddl_formula, f)    \
            )                              \
        ),                                 \
        parse_element(                     \
            terminal(epddl_tok_lpar)       \
            terminal(epddl_tok_negation)   \
            node(epddl_formula)            \
            terminal(epddl_tok_rpar)       \
        )                                  \
    )

#define epddl_and_formula_def \
    epddl_element(                            \
        ast_class(                            \
            class_name(epddl_and_formula),    \
            class_params(                     \
                list_param(epddl_formula, fs) \
            )                                 \
        ),                                    \
        parse_element(                        \
            terminal(epddl_tok_lpar)          \
            terminal(epddl_tok_conjunction)   \
            list_node(epddl_formula)          \
            terminal(epddl_tok_rpar)          \
        )                                     \
    )

#define epddl_or_formula_def \
    epddl_element(                            \
        ast_class(                            \
            class_name(epddl_or_formula),     \
            class_params(                     \
                list_param(epddl_formula, fs) \
            )                                 \
        ),                                    \
        parse_element(                        \
            terminal(epddl_tok_lpar)          \
            terminal(epddl_tok_disjunction)   \
            list_node(epddl_formula)          \
            terminal(epddl_tok_rpar)          \
        )                                     \
    )

#define epddl_imply_formula_def \
    epddl_element(                           \
        ast_class(                           \
            class_name(epddl_imply_formula), \
            class_params(                    \
                param(epddl_formula, f1),    \
                param(epddl_formula, f2)     \
            )                                \
        ),                                   \
        parse_element(                       \
            terminal(epddl_tok_lpar)         \
            terminal(epddl_tok_disjunction)  \
            node(epddl_formula)              \
            node(epddl_formula)              \
            terminal(epddl_tok_rpar)         \
        )                                    \
    )

#endif //EPDDL_PROPOSITIONAL_FORMULA_DEF_H
