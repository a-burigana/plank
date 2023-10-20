#ifndef EPDDL_PRECONDITION_DEF_H
#define EPDDL_PRECONDITION_DEF_H

#define epddl_precondition precondition

#define epddl_all_precondition_element_defs \
    epddl_precondition_def

#define epddl_all_precondition_variant_element_defs

#define epddl_precondition_def \
    epddl_element(                            \
        element_name(epddl_precondition),     \
        is_terminal(0),                       \
        element_bnf(                          \
            terminal(epddl_tok_precondition), \
            node(epddl_formula, precondition) \
        )                                     \
    )

#endif //EPDDL_PRECONDITION_DEF_H
