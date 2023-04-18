#ifndef EPDDL_FORMULA_DEF_H
#define EPDDL_FORMULA_DEF_H

#include "propositional_formula_def.h"

#define epddl_formula formula

#define epddl_all_formula_element_defs \
    epddl_all_propositional_formula_element_defs

    #define epddl_all_formula_auxiliary_type_defs \
    epddl_formula_def                                   \
    epddl_all_propositional_formula_auxiliary_type_defs

#define epddl_formula_def \
    epddl_auxiliary_type(                 \
        type_name(epddl_formula),         \
        variant(                          \
            epddl_not_formula \
        )                                 \
    )

/*
            atomic_formula,      \
            atomic_eq_formula,   \
            not_formula,         \
            and_formula,         \
            or_formula,          \
            imply_formula,       \
            box_formula,         \
            dia_formula,         \
            forall_formula,      \
            exists_formula,      \
            true_formula,        \
            false_formula        \
 */

#endif //EPDDL_FORMULA_DEF_H
