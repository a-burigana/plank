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

#define epddl_all_formula_auxiliary_type_defs \
    epddl_all_propositional_formula_auxiliary_type_defs \
    epddl_all_modal_formula_auxiliary_type_defs         \
    epddl_all_quantified_formula_auxiliary_type_defs    \
    epddl_formula_def

#define epddl_formula_def \
    epddl_auxiliary_type(                           \
        type_name(epddl_formula),                   \
        variant(                                    \
            ast_class(epddl_propositional_formula), \
            ast_class(epddl_modal_formula),         \
            ast_class(epddl_quantified_formula)     \
        )                                           \
    )

#endif //EPDDL_FORMULA_DEF_H
