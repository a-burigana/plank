#ifndef EPDDL_ATOMIC_FORMULA_DEF_H
#define EPDDL_ATOMIC_FORMULA_DEF_H

#define epddl_epddl_true_formula  epddl_true_formula
#define epddl_epddl_false_formula epddl_false_formula
#define epddl_atomic_formula      atomic_formula
#define epddl_term                term
#define epddl_predicate           predicate
#define epddl_negated_predicate   negated_predicate
#define epddl_literal             literal
#define epddl_formula_variable    formula_variable
#define epddl_eq_formula          eq_formula

#define epddl_all_atomic_formula_element_defs \
    epddl_true_formula_def                    \
    epddl_false_formula_def                   \
    epddl_predicate_def                       \
    epddl_negated_predicate_def               \
    epddl_formula_variable_def                \
    epddl_eq_formula_def

#define epddl_all_atomic_formula_auxiliary_type_defs \
    epddl_term_def                                   \
    epddl_atomic_formula_def                         \
    epddl_literal_def

#define epddl_true_formula_def \
    epddl_element(                                  \
        ast_class(                                  \
            class_name(epddl_true_formula),         \
            class_params()                          \
        ),                                          \
        parse_element(                              \
            terminal(epddl_tok_lpar)                \
            terminal(epddl_tok_top)                 \
            terminal(epddl_tok_rpar)                \
        )                                           \
    )

#define epddl_false_formula_def \
    epddl_element(                                  \
        ast_class(                                  \
            class_name(epddl_false_formula),        \
            class_params()                          \
        ),                                          \
        parse_element(                              \
            terminal(epddl_tok_lpar)                \
            terminal(epddl_tok_bot)                 \
            terminal(epddl_tok_rpar)                \
        )                                           \
    )

#define epddl_atomic_formula_def \
    epddl_auxiliary_type(                       \
        type_name(epddl_atomic_formula),        \
        variant(                                \
            ast_class(epddl_predicate),         \
            ast_class(epddl_formula_variable),  \
            ast_class(epddl_true_formula),      \
            ast_class(epddl_false_formula)      \
        )                                       \
    )

#define epddl_term_def \
    epddl_auxiliary_type(           \
        type_name(epddl_term),      \
        variant(                    \
            epddl_tok_identifier,   \
            epddl_tok_variable      \
        )                           \
    )

#define epddl_predicate_def \
    epddl_element(                                  \
        ast_class(                                  \
            class_name(epddl_predicate),            \
            class_params(                           \
                param(epddl_tok_identifier, name),  \
                list_param(epddl_term, terms)       \
            )                                       \
        ),                                          \
        parse_element(                              \
            terminal(epddl_tok_lpar)                \
            terminal(epddl_tok_identifier)          \
            list_node(epddl_term)                   \
            terminal(epddl_tok_rpar)                \
        )                                           \
    )

#define epddl_negated_predicate_def \
    epddl_element(                                  \
        ast_class(                                  \
            class_name(epddl_negated_predicate),    \
            class_params(                           \
                param(epddl_predicate, pred)        \
            )                                       \
        ),                                          \
        parse_element(                              \
            terminal(epddl_tok_lpar)                \
            terminal(epddl_tok_negation)            \
            node(epddl_predicate)                   \
            terminal(epddl_tok_rpar)                \
        )                                           \
    )

#define epddl_literal_def \
    epddl_auxiliary_type(           \
        type_name(epddl_literal),   \
        variant(                    \
            epddl_predicate,        \
            epddl_negated_predicate \
        )                           \
    )

#define epddl_formula_variable_def \
    epddl_element(                                  \
        ast_class(                                  \
            class_name(epddl_formula_variable),     \
            class_params(                           \
                param(epddl_tok_variable, var)      \
            )                                       \
        ),                                          \
        parse_element(                              \
            terminal(epddl_tok_lpar)                \
            terminal(epddl_tok_variable)            \
            terminal(epddl_tok_rpar)                \
        )                                           \
    )

#define epddl_eq_formula_def \
    epddl_element(                                  \
        ast_class(                                  \
            class_name(epddl_eq_formula),           \
            class_params(                           \
                param(epddl_term, t1),              \
                param(epddl_term, t2)               \
            )                                       \
        ),                                          \
        parse_element(                              \
            terminal(epddl_tok_lpar)                \
            terminal(epddl_tok_eq)                  \
            node(epddl_term)                        \
            node(epddl_term)                        \
            terminal(epddl_tok_rpar)                \
        )                                           \
    )

#endif //EPDDL_ATOMIC_FORMULA_DEF_H
