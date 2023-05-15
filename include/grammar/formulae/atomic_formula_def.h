#ifndef EPDDL_ATOMIC_FORMULA_DEF_H
#define EPDDL_ATOMIC_FORMULA_DEF_H

#define epddl_true_formula      epddl_true_formula
#define epddl_false_formula     epddl_false_formula
#define epddl_atomic_formula    atomic_formula
#define epddl_term              term
#define epddl_predicate         predicate
#define epddl_negated_predicate negated_predicate
#define epddl_literal           literal
#define epddl_formula_variable  formula_variable
#define epddl_eq_formula        eq_formula

#define epddl_all_atomic_formula_element_defs \
    epddl_true_formula_def                    \
    epddl_false_formula_def                   \
    epddl_predicate_def                       \
    epddl_negated_predicate_def               \
    epddl_formula_variable_def                \
    epddl_eq_formula_def

#define epddl_all_atomic_formula_variant_element_defs \
    epddl_term_def                                   \
    epddl_atomic_formula_def                         \
    epddl_literal_def

#define epddl_true_formula_def \
    epddl_element(                        \
        element_name(epddl_true_formula), \
        is_terminal(1),                   \
        element_bnf(                      \
            terminal(epddl_tok_lpar),     \
            terminal(epddl_tok_top),      \
            terminal(epddl_tok_rpar)      \
        )                                 \
    )

#define epddl_false_formula_def \
    epddl_element(                         \
        element_name(epddl_false_formula), \
        is_terminal(1),                    \
        element_bnf(                       \
            terminal(epddl_tok_lpar),      \
            terminal(epddl_tok_bot),       \
            terminal(epddl_tok_rpar)       \
        )                                  \
    )

#define epddl_atomic_formula_def \
    epddl_variant_element(                  \
        element_name(epddl_atomic_formula), \
        element_bnf(                        \
            node(epddl_predicate),          \
            node(epddl_formula_variable),   \
            node(epddl_true_formula),       \
            node(epddl_false_formula)       \
        )                                   \
    )

#define epddl_term_def \
    epddl_variant_element(              \
        element_name(epddl_term),       \
        element_bnf(                    \
            leaf(epddl_tok_identifier), \
            leaf(epddl_tok_variable)    \
        )                               \
    )

#define epddl_predicate_def \
    epddl_element(                            \
        element_name(epddl_predicate),        \
        is_terminal(0),                       \
        element_bnf(                          \
            terminal(epddl_tok_lpar),         \
            leaf(epddl_tok_identifier, name), \
            list_node(epddl_term, terms),     \
            terminal(epddl_tok_rpar)          \
        )                                     \
    )

#define epddl_negated_predicate_def \
    epddl_element(                             \
        element_name(epddl_negated_predicate), \
        is_terminal(0),                        \
        element_bnf(                           \
            terminal(epddl_tok_lpar),          \
            terminal(epddl_tok_negation),      \
            node(epddl_predicate, pred),       \
            terminal(epddl_tok_rpar)           \
        )                                      \
    )

#define epddl_literal_def \
    epddl_variant_element(                \
        element_name(epddl_literal),      \
        element_bnf(                      \
            node(epddl_predicate),        \
            node(epddl_negated_predicate) \
        )                                 \
    )

#define epddl_formula_variable_def \
    epddl_element(                            \
        element_name(epddl_formula_variable), \
        is_terminal(0),                       \
        element_bnf(                          \
            terminal(epddl_tok_lpar),         \
            leaf(epddl_tok_variable, var),    \
            terminal(epddl_tok_rpar)          \
        )                                     \
    )

#define epddl_eq_formula_def \
    epddl_element(                      \
        element_name(epddl_eq_formula), \
        is_terminal(0),                 \
        element_bnf(                    \
            terminal(epddl_tok_lpar),   \
            terminal(epddl_tok_eq),     \
            node(epddl_term, t1),       \
            node(epddl_term, t2),       \
            terminal(epddl_tok_rpar)    \
        )                               \
    )

#endif //EPDDL_ATOMIC_FORMULA_DEF_H
