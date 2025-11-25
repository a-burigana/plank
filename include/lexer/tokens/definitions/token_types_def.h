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
#define epddl_event_condition_token_type epddl_token_type(event_condition_token)


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
            epddl_tok_event_conditions  \
            epddl_tok_events            \
            epddl_tok_goal              \
            epddl_tok_init              \
            epddl_tok_library           \
            epddl_tok_list_and          \
            epddl_tok_list_forall       \
            epddl_tok_objects           \
            epddl_tok_obs_conditions    \
            epddl_tok_obs_types         \
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
// epddl_tok_in                \

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


#define epddl_event_condition_tokens_def  \
    epddl_tokens(                         \
        epddl_event_condition_token_type, \
        tokens(                           \
            epddl_tok_prop_pre            \
            epddl_tok_prop_post           \
            epddl_tok_prop_event          \
            epddl_tok_trivial_pre         \
            epddl_tok_trivial_post        \
            epddl_tok_trivial_event       \
        )                                 \
    )


#define epddl_all_token_types_def    \
    epddl_special_tokens_def         \
    epddl_punctuation_tokens_def     \
    epddl_ast_tokens_def             \
    epddl_keyword_tokens_def         \
    epddl_connective_tokens_def      \
    epddl_quantifier_tokens_def      \
    epddl_modality_tokens_def        \
    epddl_atomic_formula_tokens_def  \
    epddl_post_connective_tokens_def \
    epddl_observability_tokens_def   \
    epddl_agent_group_tokens_def     \
    epddl_event_condition_tokens_def

#define epddl_valid_keywords_def     \
    epddl_keyword_tokens_def         \
    epddl_connective_tokens_def      \
    epddl_quantifier_tokens_def      \
    epddl_atomic_formula_tokens_def  \
    epddl_post_connective_tokens_def \
    epddl_observability_tokens_def   \
    epddl_agent_group_tokens_def     \
    epddl_event_condition_tokens_def

#define epddl_all_token_super_types       \
    all_token_super_types(                \
        epddl_special_token_type,         \
        epddl_punctuation_token_type,     \
        epddl_ast_token_type,             \
        epddl_keyword_token_type,         \
        epddl_connective_token_type,      \
        epddl_quantifier_token_type,      \
        epddl_modality_token_type,        \
        epddl_atomic_formula_token_type,  \
        epddl_post_connective_token_type, \
        epddl_observability_token_type,   \
        epddl_agent_group_token_type,     \
        epddl_event_condition_token_type  \
    )

#endif //EPDDL_TOKEN_TYPES_DEF_H
