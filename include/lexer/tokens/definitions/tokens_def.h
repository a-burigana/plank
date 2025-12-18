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

#ifndef EPDDL_TOKENS_DEF_H
#define EPDDL_TOKENS_DEF_H

#include "token_types_def.h"

#define scope_token     true
#define not_scope_token false

// Syntax:                           epddl_token(<token_type>,                    <is_scope_token>, <name>,            <lexeme>)
#define epddl_tok_eof                epddl_token(epddl_special_token_type,         not_scope_token, eof,                "eof")
#define epddl_tok_invalid            epddl_token(epddl_special_token_type,         not_scope_token, invalid,            "invalid")

#define epddl_tok_lpar               epddl_token(epddl_punctuation_token_type,     not_scope_token, lpar,               "(")
#define epddl_tok_rpar               epddl_token(epddl_punctuation_token_type,     not_scope_token, rpar,               ")")
#define epddl_tok_lbrack             epddl_token(epddl_punctuation_token_type,     not_scope_token, lbrack,             "[")
#define epddl_tok_rbrack             epddl_token(epddl_punctuation_token_type,     not_scope_token, rbrack,             "]")
#define epddl_tok_langle             epddl_token(epddl_punctuation_token_type,     not_scope_token, langle,             "<")
#define epddl_tok_rangle             epddl_token(epddl_punctuation_token_type,     not_scope_token, rangle,             ">")
#define epddl_tok_dash               epddl_token(epddl_punctuation_token_type,     not_scope_token, dash,               "-")
#define epddl_tok_eq                 epddl_token(epddl_punctuation_token_type,     not_scope_token, eq,                 "=")
#define epddl_tok_neq                epddl_token(epddl_punctuation_token_type,     not_scope_token, neq,                "/=")
#define epddl_tok_such_that          epddl_token(epddl_punctuation_token_type,     scope_token,     such_that,          "|")

#define epddl_tok_identifier         epddl_token(epddl_ast_token_type,             not_scope_token, identifier,         "") /* [_a-zA-Z][_'a-zA-Z0-9]* */
#define epddl_tok_variable           epddl_token(epddl_ast_token_type,             not_scope_token, variable,           "") /* \?[_a-zA-Z][_'a-zA-Z0-9]* */
#define epddl_tok_requirement        epddl_token(epddl_ast_token_type,             not_scope_token, requirement,        "") /* [a-zA-Z][\-a-zA-Z0-9]* */
#define epddl_tok_integer            epddl_token(epddl_ast_token_type,             not_scope_token, integer,            "") /* [0-9]|[1-9][0-9]+ */

#define epddl_tok_action             epddl_token(epddl_keyword_token_type,         scope_token,     action,             ":action")
#define epddl_tok_act_type           epddl_token(epddl_keyword_token_type,         scope_token,     act_type,           ":action-type")
#define epddl_tok_agents             epddl_token(epddl_keyword_token_type,         scope_token,     agents,             ":agents")
#define epddl_tok_agent_groups       epddl_token(epddl_keyword_token_type,         scope_token,     agent_groups,       ":agent-groups")
#define epddl_tok_conditions         epddl_token(epddl_keyword_token_type,         scope_token,     conditions,         ":conditions")
#define epddl_tok_constants          epddl_token(epddl_keyword_token_type,         scope_token,     constants,          ":constants")
#define epddl_tok_define             epddl_token(epddl_keyword_token_type,         scope_token,     define,             "define")
#define epddl_tok_designated         epddl_token(epddl_keyword_token_type,         scope_token,     designated,         ":designated")
#define epddl_tok_domain             epddl_token(epddl_keyword_token_type,         scope_token,     domain,             "domain")
#define epddl_tok_domain_libs        epddl_token(epddl_keyword_token_type,         scope_token,     domain_libs,        ":action-type-libraries")
#define epddl_tok_effects            epddl_token(epddl_keyword_token_type,         scope_token,     effects,            ":effects")
#define epddl_tok_either             epddl_token(epddl_keyword_token_type,         scope_token,     either,             "either")
#define epddl_tok_event              epddl_token(epddl_keyword_token_type,         scope_token,     event,              ":event")
#define epddl_tok_events             epddl_token(epddl_keyword_token_type,         scope_token,     events,             ":events")
#define epddl_tok_fact               epddl_token(epddl_keyword_token_type,         not_scope_token, fact,               ":fact")
#define epddl_tok_facts_init         epddl_token(epddl_keyword_token_type,         scope_token,     facts_init,         ":facts")
#define epddl_tok_goal               epddl_token(epddl_keyword_token_type,         scope_token,     goal,               ":goal")
//#define epddl_tok_in                 epddl_token(epddl_keyword_token_type,         not_scope_token, in,                 "in")
#define epddl_tok_init               epddl_token(epddl_keyword_token_type,         scope_token,     init,               ":init")
#define epddl_tok_labels             epddl_token(epddl_keyword_token_type,         scope_token,     labels,             ":labels")
#define epddl_tok_library            epddl_token(epddl_keyword_token_type,         scope_token,     library,            "action-type-library")
#define epddl_tok_list_and           epddl_token(epddl_keyword_token_type,         not_scope_token, list_and,           ":and")
#define epddl_tok_list_forall        epddl_token(epddl_keyword_token_type,         not_scope_token, list_forall,        ":forall")
//#define epddl_tok_modalities         epddl_token(epddl_keyword_token_type,         scope_token,     modalities,         ":modalities")
#define epddl_tok_objects            epddl_token(epddl_keyword_token_type,         scope_token,     objects,            ":objects")
#define epddl_tok_obs_conditions     epddl_token(epddl_keyword_token_type,         scope_token,     obs_conditions,     ":observability-conditions")
#define epddl_tok_obs_types          epddl_token(epddl_keyword_token_type,         scope_token,     obs_types,          ":observability-types")
#define epddl_tok_parameters         epddl_token(epddl_keyword_token_type,         scope_token,     parameters,         ":parameters")
#define epddl_tok_precondition       epddl_token(epddl_keyword_token_type,         scope_token,     precondition,       ":precondition")
#define epddl_tok_predicates         epddl_token(epddl_keyword_token_type,         scope_token,     predicates,         ":predicates")
#define epddl_tok_problem            epddl_token(epddl_keyword_token_type,         scope_token,     problem,            "problem")
#define epddl_tok_prob_domain        epddl_token(epddl_keyword_token_type,         scope_token,     prob_domain,        ":domain")
#define epddl_tok_relations          epddl_token(epddl_keyword_token_type,         scope_token,     relations,          ":relations")
#define epddl_tok_requirements       epddl_token(epddl_keyword_token_type,         scope_token,     requirements,       ":requirements")
#define epddl_tok_state              epddl_token(epddl_keyword_token_type,         scope_token,     state,              ":state")
#define epddl_tok_state_name         epddl_token(epddl_keyword_token_type,         scope_token,     state_name,         ":state-name")
#define epddl_tok_types              epddl_token(epddl_keyword_token_type,         scope_token,     types,              ":types")
#define epddl_tok_worlds             epddl_token(epddl_keyword_token_type,         scope_token,     worlds,             ":worlds")

#define epddl_tok_conjunction        epddl_token(epddl_connective_token_type,      not_scope_token, conjunction,        "and")
#define epddl_tok_disjunction        epddl_token(epddl_connective_token_type,      not_scope_token, disjunction,        "or")
#define epddl_tok_implication        epddl_token(epddl_connective_token_type,      not_scope_token, implication,        "imply")
#define epddl_tok_negation           epddl_token(epddl_connective_token_type,      not_scope_token, negation,           "not")

#define epddl_tok_exists             epddl_token(epddl_quantifier_token_type,      scope_token,     exists,             "exists")
#define epddl_tok_forall             epddl_token(epddl_quantifier_token_type,      scope_token,     forall,             "forall")

#define epddl_tok_ck                 epddl_token(epddl_modality_token_type,        not_scope_token, ck,                 "C.")
#define epddl_tok_kw                 epddl_token(epddl_modality_token_type,        not_scope_token, kw,                 "Kw.")

#define epddl_tok_bot                epddl_token(epddl_atomic_formula_token_type,  not_scope_token, bot,                "false")
#define epddl_tok_top                epddl_token(epddl_atomic_formula_token_type,  not_scope_token, top,                "true")

#define epddl_tok_iff                epddl_token(epddl_post_connective_token_type, scope_token,     iff,                "iff")
#define epddl_tok_when               epddl_token(epddl_post_connective_token_type, scope_token,     when,               "when")

#define epddl_tok_else_cond          epddl_token(epddl_observability_token_type,   scope_token,     else_cond,          "else")
#define epddl_tok_else_if_cond       epddl_token(epddl_observability_token_type,   scope_token,     else_if_cond,       "else-if")
#define epddl_tok_if_cond            epddl_token(epddl_observability_token_type,   scope_token,     if_cond,            "if")
#define epddl_tok_default            epddl_token(epddl_observability_token_type,   scope_token,     default_cond,       "default")

#define epddl_tok_all                epddl_token(epddl_agent_group_token_type,     not_scope_token, all,                "All")

#define epddl_tok_non_trivial_pre    epddl_token(epddl_event_condition_token_type, not_scope_token, non_trivial_pre,    ":non-trivial-precondition")
#define epddl_tok_non_trivial_post   epddl_token(epddl_event_condition_token_type, not_scope_token, non_trivial_post,   ":non-trivial-postconditions")
#define epddl_tok_non_trivial_event  epddl_token(epddl_event_condition_token_type, not_scope_token, non_trivial_event,  ":non-trivial-event")
#define epddl_tok_prop_pre           epddl_token(epddl_event_condition_token_type, not_scope_token, prop_pre,           ":propositional-precondition")
#define epddl_tok_prop_post          epddl_token(epddl_event_condition_token_type, not_scope_token, prop_post,          ":propositional-postconditions")
#define epddl_tok_prop_event         epddl_token(epddl_event_condition_token_type, not_scope_token, prop_event,         ":propositional-event")
#define epddl_tok_trivial_pre        epddl_token(epddl_event_condition_token_type, not_scope_token, trivial_pre,        ":trivial-precondition")
#define epddl_tok_trivial_post       epddl_token(epddl_event_condition_token_type, not_scope_token, trivial_post,       ":trivial-postconditions")
#define epddl_tok_trivial_event      epddl_token(epddl_event_condition_token_type, not_scope_token, trivial_event,      ":trivial-event")


#define epddl_all_tokens              \
    all_tokens(                       \
        epddl_tok_eof,                \
        epddl_tok_invalid,            \
        epddl_tok_lpar,               \
        epddl_tok_rpar,               \
        epddl_tok_lbrack,             \
        epddl_tok_rbrack,             \
        epddl_tok_langle,             \
        epddl_tok_rangle,             \
        epddl_tok_dash,               \
        epddl_tok_eq,                 \
        epddl_tok_neq,                \
        epddl_tok_identifier,         \
        epddl_tok_variable,           \
        epddl_tok_requirement,        \
        epddl_tok_integer,            \
        epddl_tok_action,             \
        epddl_tok_act_type,           \
        epddl_tok_agents,             \
        epddl_tok_agent_groups,       \
        epddl_tok_conditions,         \
        epddl_tok_constants,          \
        epddl_tok_define,             \
        epddl_tok_designated,         \
        epddl_tok_domain,             \
        epddl_tok_domain_libs,        \
        epddl_tok_effects,            \
        epddl_tok_either,             \
        epddl_tok_event,              \
        epddl_tok_events,             \
        epddl_tok_fact,               \
        epddl_tok_facts_init,         \
        epddl_tok_goal,               \
        epddl_tok_init,               \
        epddl_tok_labels,             \
        epddl_tok_library,            \
        epddl_tok_list_and,           \
        epddl_tok_list_forall,        \
        epddl_tok_objects,            \
        epddl_tok_obs_conditions,     \
        epddl_tok_obs_types,          \
        epddl_tok_parameters,         \
        epddl_tok_precondition,       \
        epddl_tok_predicates,         \
        epddl_tok_problem,            \
        epddl_tok_prob_domain,        \
        epddl_tok_relations,          \
        epddl_tok_requirements,       \
        epddl_tok_state,              \
        epddl_tok_state_name,         \
        epddl_tok_such_that,          \
        epddl_tok_types,              \
        epddl_tok_worlds,             \
        epddl_tok_conjunction,        \
        epddl_tok_disjunction,        \
        epddl_tok_implication,        \
        epddl_tok_negation,           \
        epddl_tok_exists,             \
        epddl_tok_forall,             \
        epddl_tok_ck,                 \
        epddl_tok_kw,                 \
        epddl_tok_bot,                \
        epddl_tok_top,                \
        epddl_tok_iff,                \
        epddl_tok_when,               \
        epddl_tok_else_cond,          \
        epddl_tok_else_if_cond,       \
        epddl_tok_if_cond,            \
        epddl_tok_default,            \
        epddl_tok_all,                \
        epddl_tok_non_trivial_pre,    \
        epddl_tok_non_trivial_post,   \
        epddl_tok_non_trivial_event,  \
        epddl_tok_prop_pre,           \
        epddl_tok_prop_post,          \
        epddl_tok_prop_event,         \
        epddl_tok_trivial_pre,        \
        epddl_tok_trivial_post,       \
        epddl_tok_trivial_event       \
)
// epddl_tok_in,                \

#endif //EPDDL_TOKENS_DEF_H
