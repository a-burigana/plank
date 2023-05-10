#ifndef EPDDL_MODAL_FORMULA_DEF_H
#define EPDDL_MODAL_FORMULA_DEF_H

#include "formula_def.h"
#include "../common/agent_def.h"
#include "../tokens/tokens_def.h"

#define epddl_modal_formula   modal_formula
#define epddl_modality        modality
#define epddl_box_formula     box_formula
#define epddl_diamond_formula diamond_formula

#define epddl_all_modal_formula_element_defs \
    epddl_modality_def                       \
    epddl_box_formula_def                    \
    epddl_diamond_formula_def

#define epddl_all_modal_formula_auxiliary_type_defs \
    epddl_modal_formula_def

#define epddl_modal_formula_def \
    epddl_auxiliary_type(                    \
        type_name(epddl_modal_formula),      \
        variant(                             \
            ast_class(epddl_box_formula),    \
            ast_class(epddl_diamond_formula) \
        )                                    \
    )

#define epddl_modality_def \
    epddl_element(                                    \
        ast_class(                                    \
            class_name(epddl_modality),               \
            class_params(                             \
                opt_param(epddl_tok_modality, mod),   \
                list_param(epddl_agent, ags)          \
            )                                         \
        ),                                            \
        parse_element(                                \
            opt_terminal(epddl_tok_modality)          \
            list_terminal(epddl_agent)                \
        )                                             \
    )

#define epddl_box_formula_def \
    epddl_element(                          \
        ast_class(                          \
            class_name(epddl_box_formula),  \
            class_params(                   \
                param(epddl_modality, mod), \
                param(epddl_formula, f)     \
            )                               \
        ),                                  \
        parse_element(                      \
            terminal(epddl_tok_lbrack)      \
            terminal(epddl_modality)        \
            terminal(epddl_tok_rbrack)      \
            node(epddl_formula)             \
        )                                   \
    )

#define epddl_diamond_formula_def \
    epddl_element(                             \
        ast_class(                             \
            class_name(epddl_diamond_formula), \
            class_params(                      \
                param(epddl_modality, mod),    \
                param(epddl_formula, f)        \
            )                                  \
        ),                                     \
        parse_element(                         \
            terminal(epddl_tok_lt)             \
            terminal(epddl_modality)           \
            terminal(epddl_tok_gt)             \
            node(epddl_formula)                \
        )                                      \
    )

#endif //EPDDL_MODAL_FORMULA_DEF_H
