#ifndef EPDDL_FORMULA_DEF_H
#define EPDDL_FORMULA_DEF_H

#include "propositional_formula_def.h"
#include "modal_formula_def.h"
#include "quantified_formula_def.h"

#define epddl_formula formula

#define epddl_all_formula_element_defs \
    epddl_all_propositional_formula_element_defs \
    epddl_all_modal_formula_element_defs         \
    epddl_all_quantified_formula_element_defs

#define epddl_all_formula_variant_element_defs \
    epddl_all_propositional_formula_variant_element_defs \
    epddl_all_modal_formula_variant_element_defs         \
    epddl_all_quantified_formula_variant_element_defs    \
    epddl_formula_def

#define epddl_formula_def \
    epddl_variant_element(                     \
        element_name(epddl_formula),           \
        element_bnf(                           \
            node(epddl_propositional_formula), \
            node(epddl_modal_formula),         \
            node(epddl_quantified_formula)     \
        )                                      \
    )

//#define epddl_formula_def \
//    epddl_variant_element(                     \
//        element_name(epddl_formula),           \
//        element_bnf(                           \
//            node(epddl_non_modal_formula),     \
//            node(epddl_modal_formula)          \
//        )                                      \
//    )
//
//#define epddl_non_modal_formula_def \
//    epddl_variant_element(                     \
//        element_name(epddl_non_modal_formula), \
//        element_bnf(                           \
//            node(epddl_propositional_formula), \
//            node(epddl_quantified_formula)     \
//        )                                      \
//    )

#endif //EPDDL_FORMULA_DEF_H
