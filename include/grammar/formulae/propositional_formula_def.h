#ifndef EPDDL_PROPOSITIONAL_FORMULA_DEF_H
#define EPDDL_PROPOSITIONAL_FORMULA_DEF_H

#include "formula_def.h"
#include "../../tokens/tokens.h"

#define epddl_not_formula not_formula

#define epddl_all_propositional_formula_element_defs \
    epddl_not_formula_def

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

#endif //EPDDL_PROPOSITIONAL_FORMULA_DEF_H
