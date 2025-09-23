// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef EPDDL_TOKEN_TYPES_DEF_H
#define EPDDL_TOKEN_TYPES_DEF_H

#define epddl_special_token_type         epddl_token_type(special_token)
#define epddl_punctuation_token_type     epddl_token_type(punctuation_token)
#define epddl_ast_token_type             epddl_token_type(ast_token)
#define epddl_keyword_token_type         epddl_token_type(keyword_token)
#define epddl_connective_token_type      epddl_token_type(connective_token)
#define epddl_quantifier_token_type      epddl_token_type(quantifier_token)
#define epddl_modality_token_type        epddl_token_type(modality_token)
#define epddl_atomic_formula_token_type  epddl_token_type(atomic_formula_token)
#define epddl_post_connective_token_type epddl_token_type(post_connective_token)
#define epddl_observability_token_type   epddl_token_type(observability_token)
#define epddl_agent_group_token_type     epddl_token_type(agent_group_token)
//#define epddl_expr_type_token_type       epddl_token_type(expr_type_token)
//#define epddl_reserved_type_token_type   epddl_token_type(reserved_type_token)

#define epddl_special_tokens_def \
    epddl_tokens(                 \
        epddl_special_token_type, \
        tokens(                   \
            epddl_tok_eof         \
            epddl_tok_invalid     \
        )                         \
    )

#define epddl_punctuation_tokens_def \
    epddl_tokens(                     \
        epddl_punctuation_token_type, \
        tokens(                       \
            epddl_tok_lpar            \
            epddl_tok_rpar            \
            epddl_tok_lbrack          \
            epddl_tok_rbrack          \
            epddl_tok_langle          \
            epddl_tok_rangle          \
            epddl_tok_dash            \
            epddl_tok_eq              \
            epddl_tok_neq             \
            epddl_tok_such_that       \
        )                             \
    )

#define epddl_ast_tokens_def  \
    epddl_tokens(                 \
        epddl_ast_token_type,     \
        tokens(                   \
            epddl_tok_identifier  \
            epddl_tok_variable    \
            epddl_tok_requirement \
            epddl_tok_integer     \
        )                         \
    )
// epddl_tok_modality    \

#define epddl_keyword_tokens_def        \
    epddl_tokens(                       \
        epddl_keyword_token_type,       \
        tokens(                         \
            epddl_tok_action            \
            epddl_tok_act_type          \
            epddl_tok_domain_libs       \
            epddl_tok_agents            \
            epddl_tok_agent_groups      \
            epddl_tok_constants         \
            epddl_tok_define            \
            epddl_tok_designated        \
            epddl_tok_domain            \
            epddl_tok_event             \
            epddl_tok_events            \
            epddl_tok_goal              \
            epddl_tok_in                \
            epddl_tok_init              \
            epddl_tok_library           \
            epddl_tok_objects           \
            epddl_tok_obs_conditions    \
            epddl_tok_obs_types        \
            epddl_tok_parameters        \
            epddl_tok_effects           \
            epddl_tok_either            \
            epddl_tok_precondition      \
            epddl_tok_predicates        \
            epddl_tok_problem           \
            epddl_tok_prob_domain       \
            epddl_tok_relations         \
            epddl_tok_requirements      \
            epddl_tok_state             \
            epddl_tok_state_name        \
            epddl_tok_static            \
            epddl_tok_static_init       \
            epddl_tok_types             \
            epddl_tok_labels            \
            epddl_tok_worlds            \
        )                               \
    )
//            epddl_tok_et_object         \
//            epddl_tok_et_agent          \
//            epddl_tok_et_agent_group    \
//            epddl_tok_et_predicate      \
//            epddl_tok_et_literal        \
//            epddl_tok_et_formula        \

#define epddl_connective_tokens_def \
    epddl_tokens(                    \
        epddl_connective_token_type, \
        tokens(                      \
            epddl_tok_conjunction    \
            epddl_tok_disjunction    \
            epddl_tok_implication    \
            epddl_tok_negation       \
        )                            \
    )

#define epddl_quantifier_tokens_def \
    epddl_tokens(                    \
        epddl_quantifier_token_type, \
        tokens(                      \
            epddl_tok_exists         \
            epddl_tok_forall         \
        )                            \
    )

#define epddl_modality_tokens_def  \
    epddl_tokens(                  \
        epddl_modality_token_type, \
        tokens(                    \
            epddl_tok_ck           \
            epddl_tok_kw           \
        )                          \
    )

#define epddl_atomic_formula_tokens_def \
    epddl_tokens(                        \
        epddl_atomic_formula_token_type, \
        tokens(                          \
            epddl_tok_bot                \
            epddl_tok_top                \
        )                                \
    )

#define epddl_post_connective_tokens_def \
    epddl_tokens(                         \
        epddl_post_connective_token_type, \
        tokens(                           \
            epddl_tok_iff                 \
            epddl_tok_when                \
        )                                 \
    )

#define epddl_observability_tokens_def \
    epddl_tokens(                       \
        epddl_observability_token_type, \
        tokens(                         \
            epddl_tok_else_cond         \
            epddl_tok_else_if_cond      \
            epddl_tok_if_cond           \
            epddl_tok_default           \
        )                               \
    )

#define epddl_agent_group_tokens_def \
    epddl_tokens(                     \
        epddl_agent_group_token_type, \
        tokens(                       \
            epddl_tok_all             \
        )                             \
    )

//#define epddl_expr_type_tokens_def \
//    epddl_tokens(                    \
//        epddl_expr_type_token_type,  \
//        tokens(                      \
//            epddl_tok_et_object      \
//            epddl_tok_et_agent       \
//            epddl_tok_et_agent_group \
//            epddl_tok_et_predicate   \
//            epddl_tok_et_literal     \
//            epddl_tok_et_formula     \
//            epddl_tok_et_effects     \
//        )                            \
//    )

// todo: implement reserved types during type checking
// #define epddl_reserved_type_tokens_def \
//    epddl_tokens(                       \
//        epddl_reserved_type_token_type, \
//        tokens(                         \
//            epddl_tok_agent             \
//            epddl_tok_formula           \
//            epddl_tok_literal           \
//            epddl_tok_object            \
//            epddl_tok_postcondition     \
//            epddl_tok_predicate         \
//            epddl_tok_predicate_formula \
//        )                               \
//    )


#define epddl_all_token_types_def    \
    epddl_special_tokens_def         \
    epddl_punctuation_tokens_def     \
    epddl_ast_tokens_def         \
    epddl_keyword_tokens_def         \
    epddl_connective_tokens_def      \
    epddl_quantifier_tokens_def      \
    epddl_modality_tokens_def        \
    epddl_atomic_formula_tokens_def  \
    epddl_post_connective_tokens_def \
    epddl_observability_tokens_def   \
    epddl_agent_group_tokens_def
//    epddl_expr_type_tokens_def
//    epddl_reserved_type_tokens_def

#define epddl_valid_keywords_def     \
    epddl_keyword_tokens_def         \
    epddl_connective_tokens_def      \
    epddl_quantifier_tokens_def      \
    epddl_atomic_formula_tokens_def  \
    epddl_post_connective_tokens_def \
    epddl_observability_tokens_def   \
    epddl_agent_group_tokens_def
//    epddl_expr_type_tokens_def
//    epddl_reserved_type_tokens_def

#endif //EPDDL_TOKEN_TYPES_DEF_H
