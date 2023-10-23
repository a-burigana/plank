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
    epddl_box_formula_def                    \
    epddl_diamond_formula_def
//    epddl_modality_def                       \

#define epddl_all_modal_formula_variant_element_defs \
    epddl_modal_formula_def

#define epddl_modal_formula_def \
    epddl_variant_element(                 \
        element_name(epddl_modal_formula), \
        element_bnf(                       \
            node(epddl_box_formula),       \
            node(epddl_diamond_formula)    \
        )                                  \
    )

//#define epddl_modality_def \
//    epddl_element(                             \
//        element_name(epddl_modality),          \
//        is_terminal(0),                        \
//        element_bnf(                           \
//            opt_leaf(epddl_tok_modality, mod), \
//            list_node(epddl_agent, ags)        \
//        )                                      \
//    )

#define epddl_box_formula_def \
    epddl_element(                       \
        element_name(epddl_box_formula), \
        is_terminal(0),                  \
        element_bnf(                     \
            terminal(epddl_tok_lbrack),  \
            list_node(epddl_agent, ags), \
            terminal(epddl_tok_rbrack),  \
            node(epddl_formula, f)       \
        )                                \
    )

#define epddl_diamond_formula_def \
    epddl_element(                           \
        element_name(epddl_diamond_formula), \
        is_terminal(0),                      \
        element_bnf(                         \
            terminal(epddl_tok_langle),      \
            list_node(epddl_agent, ags),     \
            terminal(epddl_tok_rangle),      \
            node(epddl_formula, f)           \
        )                                    \
    )

#endif //EPDDL_MODAL_FORMULA_DEF_H
