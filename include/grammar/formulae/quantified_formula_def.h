#ifndef EPDDL_QUANTIFIED_FORMULA_DEF_H
#define EPDDL_QUANTIFIED_FORMULA_DEF_H

#include "formula_def.h"
#include "../common/typed_ident_var_def.h"
#include "../tokens/tokens_def.h"

#define epddl_quantified_formula quantified_formula
#define epddl_exists_formula     exists_formula
#define epddl_forall_formula     forall_formula

#define epddl_all_quantified_formula_element_defs \
    epddl_exists_formula_def                      \
    epddl_forall_formula_def

#define epddl_all_quantified_formula_auxiliary_type_defs \
    epddl_quantified_formula_def

#define epddl_quantified_formula_def \
    epddl_auxiliary_type(                    \
        type_name(epddl_quantified_formula), \
        variant(                             \
            ast_class(epddl_exists_formula), \
            ast_class(epddl_forall_formula)  \
        )                                    \
    )

#define epddl_exists_formula_def \
    epddl_element(                                          \
        ast_class(                                          \
            class_name(epddl_exists_formula),               \
            class_params(                                   \
                list_param(epddl_typed_variable, params),   \
                param(epddl_formula, f)                     \
            )                                               \
        ),                                                  \
        parse_element(                                      \
            terminal(epddl_tok_lpar)                        \
            terminal(epddl_tok_exists)                      \
            terminal(epddl_tok_lpar)                        \
            list_node(epddl_typed_variable)                 \
            terminal(epddl_tok_rpar)                        \
            node(epddl_formula)                             \
            terminal(epddl_tok_rpar)                        \
        )                                                   \
    )

#define epddl_forall_formula_def \
    epddl_element(                                          \
        ast_class(                                          \
            class_name(epddl_forall_formula),               \
            class_params(                                   \
                list_param(epddl_typed_variable, params),   \
                param(epddl_formula, f)                     \
            )                                               \
        ),                                                  \
        parse_element(                                      \
            terminal(epddl_tok_lpar)                        \
            terminal(epddl_tok_forall)                      \
            terminal(epddl_tok_lpar)                        \
            list_node(epddl_typed_variable)                 \
            terminal(epddl_tok_rpar)                        \
            node(epddl_formula)                             \
            terminal(epddl_tok_rpar)                        \
        )                                                   \
    )

#endif //EPDDL_QUANTIFIED_FORMULA_DEF_H
