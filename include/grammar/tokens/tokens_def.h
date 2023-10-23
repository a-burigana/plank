#ifndef EPDDL_TOKENS_DEF_H
#define EPDDL_TOKENS_DEF_H

#include "token_types_def.h"

#define scope_token     true
#define not_scope_token false

// Syntax:                          epddl_token(<token_type>,                    <is_scope_token>, <name>,            <lexeme>)
#define epddl_tok_eof               epddl_token(epddl_special_token_type,         not_scope_token, eof,               "eof")
#define epddl_tok_invalid           epddl_token(epddl_special_token_type,         not_scope_token, invalid,           "invalid")

#define epddl_tok_lpar              epddl_token(epddl_punctuation_token_type,     not_scope_token, lpar,              "(")
#define epddl_tok_rpar              epddl_token(epddl_punctuation_token_type,     not_scope_token, rpar,              ")")
#define epddl_tok_lbrack            epddl_token(epddl_punctuation_token_type,     not_scope_token, lbrack,            "[")
#define epddl_tok_rbrack            epddl_token(epddl_punctuation_token_type,     not_scope_token, rbrack,            "]")
#define epddl_tok_langle            epddl_token(epddl_punctuation_token_type,     not_scope_token, langle,            "<")
#define epddl_tok_rangle            epddl_token(epddl_punctuation_token_type,     not_scope_token, rangle,            ">")
#define epddl_tok_dash              epddl_token(epddl_punctuation_token_type,     not_scope_token, dash,              "-")
#define epddl_tok_eq                epddl_token(epddl_punctuation_token_type,     not_scope_token, eq,                "=")
#define epddl_tok_gets              epddl_token(epddl_punctuation_token_type,     not_scope_token, gets,              "<-")

#define epddl_tok_identifier        epddl_token(epddl_pattern_token_type,         not_scope_token, identifier,        "") /* [_a-zA-Z][_'a-zA-Z0-9]* */
#define epddl_tok_variable          epddl_token(epddl_pattern_token_type,         not_scope_token, variable,          "") /* \?[_a-zA-Z][_'a-zA-Z0-9]* */
//#define epddl_tok_modality          epddl_token(epddl_pattern_token_type,         not_scope_token, modality,          "") /* [a-z][_a-zA-Z0-9]*\. */
#define epddl_tok_requirement       epddl_token(epddl_pattern_token_type,         not_scope_token, requirement,       "") /* [a-zA-Z][\-a-zA-Z0-9]* */
#define epddl_tok_integer           epddl_token(epddl_pattern_token_type,         not_scope_token, integer,           "") /* [0-9]|[1-9][0-9]+ */

#define epddl_tok_action            epddl_token(epddl_keyword_token_type,         scope_token,     action,            ":action")
#define epddl_tok_act_type          epddl_token(epddl_keyword_token_type,         scope_token,     act_type,          ":action-type")
#define epddl_tok_act_type_lib      epddl_token(epddl_keyword_token_type,         scope_token,     act_type_lib,      ":action-type-libraries")
#define epddl_tok_agents            epddl_token(epddl_keyword_token_type,         scope_token,     agents,            ":agents")
#define epddl_tok_agent_groups      epddl_token(epddl_keyword_token_type,         scope_token,     agent_groups,      ":agent-groups")
#define epddl_tok_define            epddl_token(epddl_keyword_token_type,         scope_token,     define,            "define")
#define epddl_tok_designated        epddl_token(epddl_keyword_token_type,         scope_token,     designated,        ":designated")
#define epddl_tok_domain            epddl_token(epddl_keyword_token_type,         scope_token,     domain,            "domain")
#define epddl_tok_effects           epddl_token(epddl_keyword_token_type,         scope_token,     effects,           ":effects")
#define epddl_tok_event             epddl_token(epddl_keyword_token_type,         scope_token,     event,             ":event")
#define epddl_tok_events            epddl_token(epddl_keyword_token_type,         scope_token,     events,            ":events")
#define epddl_tok_goal              epddl_token(epddl_keyword_token_type,         scope_token,     goal,              ":goal")
#define epddl_tok_init              epddl_token(epddl_keyword_token_type,         scope_token,     init,              ":init")
#define epddl_tok_library           epddl_token(epddl_keyword_token_type,         scope_token,     library,           "library")
#define epddl_tok_modalities        epddl_token(epddl_keyword_token_type,         scope_token,     modalities,        ":modalities")
#define epddl_tok_objects           epddl_token(epddl_keyword_token_type,         scope_token,     objects,           ":objects")
#define epddl_tok_obs_conditions    epddl_token(epddl_keyword_token_type,         scope_token,     obs_conditions,    ":observability-conditions")
#define epddl_tok_obs_groups        epddl_token(epddl_keyword_token_type,         scope_token,     obs_groups,        ":observability-groups")
#define epddl_tok_parameters        epddl_token(epddl_keyword_token_type,         scope_token,     parameters,        ":parameters")
#define epddl_tok_precondition      epddl_token(epddl_keyword_token_type,         scope_token,     precondition,      ":precondition")
#define epddl_tok_predicates        epddl_token(epddl_keyword_token_type,         scope_token,     predicates,        ":predicates")
#define epddl_tok_problem           epddl_token(epddl_keyword_token_type,         scope_token,     problem,           "problem")
#define epddl_tok_prob_domain       epddl_token(epddl_keyword_token_type,         scope_token,     prob_domain,       ":domain")
#define epddl_tok_relations         epddl_token(epddl_keyword_token_type,         scope_token,     relations,         ":relations")
#define epddl_tok_requirements      epddl_token(epddl_keyword_token_type,         scope_token,     requirements,      ":requirements")
#define epddl_tok_state             epddl_token(epddl_keyword_token_type,         scope_token,     state,             ":state")
#define epddl_tok_state_name        epddl_token(epddl_keyword_token_type,         scope_token,     state_name,        ":state-name")
#define epddl_tok_static_preds      epddl_token(epddl_keyword_token_type,         scope_token,     static_preds,      ":static")
#define epddl_tok_types             epddl_token(epddl_keyword_token_type,         scope_token,     types,             ":types")
#define epddl_tok_valuation         epddl_token(epddl_keyword_token_type,         scope_token,     valuation,         ":valuation")
#define epddl_tok_where             epddl_token(epddl_keyword_token_type,         scope_token,     where,             ":where")
#define epddl_tok_worlds            epddl_token(epddl_keyword_token_type,         scope_token,     worlds,            ":worlds")

#define epddl_tok_conjunction       epddl_token(epddl_connective_token_type,      not_scope_token, conjunction,       "and")
#define epddl_tok_disjunction       epddl_token(epddl_connective_token_type,      not_scope_token, disjunction,       "or")
#define epddl_tok_implication       epddl_token(epddl_connective_token_type,      not_scope_token, implication,       "imply")
#define epddl_tok_negation          epddl_token(epddl_connective_token_type,      not_scope_token, negation,          "not")

#define epddl_tok_exists            epddl_token(epddl_quantifier_token_type,      scope_token,     exists,            "exists")
#define epddl_tok_forall            epddl_token(epddl_quantifier_token_type,      scope_token,     forall,            "forall")

#define epddl_tok_bot               epddl_token(epddl_atomic_formula_token_type,  not_scope_token, bot,               "false")
#define epddl_tok_top               epddl_token(epddl_atomic_formula_token_type,  not_scope_token, top,               "true")

#define epddl_tok_iff               epddl_token(epddl_post_connective_token_type, scope_token,     iff,               "iff")
#define epddl_tok_when              epddl_token(epddl_post_connective_token_type, scope_token,     when,              "when")

#define epddl_tok_always            epddl_token(epddl_observability_token_type,   scope_token,     always,            "always")
#define epddl_tok_else_cond         epddl_token(epddl_observability_token_type,   scope_token,     else_cond,         "else")
#define epddl_tok_if_cond           epddl_token(epddl_observability_token_type,   scope_token,     if_cond,           "if")

#define epddl_tok_all               epddl_token(epddl_agent_group_token_type,     not_scope_token, all,               "All")

#define epddl_tok_et_object         epddl_token(epddl_expr_type_token_type,       not_scope_token, object_type,       "~object")
#define epddl_tok_et_agent          epddl_token(epddl_expr_type_token_type,       not_scope_token, agent_type,        "~agent")
#define epddl_tok_et_predicate      epddl_token(epddl_expr_type_token_type,       not_scope_token, predicate_type,    "~predicate")
#define epddl_tok_et_literal        epddl_token(epddl_expr_type_token_type,       not_scope_token, literal_type,      "~literal")
#define epddl_tok_et_formula        epddl_token(epddl_expr_type_token_type,       not_scope_token, formula_type,      "~formula")
#define epddl_tok_et_effects        epddl_token(epddl_expr_type_token_type,       not_scope_token, effects_type,      "~effects")

// todo: implement reserved types during type checking
//#define epddl_tok_agent             epddl_token(epddl_reserved_type_token_type,   not_scope_token, agent,             "agent")
//#define epddl_tok_formula           epddl_token(epddl_reserved_type_token_type,   not_scope_token, formula,           "formula")
//#define epddl_tok_literal           epddl_token(epddl_reserved_type_token_type,   not_scope_token, literal,           "literal")
//#define epddl_tok_object            epddl_token(epddl_reserved_type_token_type,   not_scope_token, object,            "object")
//#define epddl_tok_postcondition     epddl_token(epddl_reserved_type_token_type,   not_scope_token, postcondition,     "postcondition")
//#define epddl_tok_predicate         epddl_token(epddl_reserved_type_token_type,   not_scope_token, predicate,         "predicate")
//#define epddl_tok_predicate_formula epddl_token(epddl_reserved_type_token_type,   not_scope_token, predicate_formula, "predicate_formula")


#define epddl_all_tokens            \
    all_tokens(                     \
        epddl_tok_eof,              \
        epddl_tok_invalid,          \
        epddl_tok_lpar,             \
        epddl_tok_rpar,             \
        epddl_tok_lbrack,           \
        epddl_tok_rbrack,           \
        epddl_tok_langle,           \
        epddl_tok_rangle,           \
        epddl_tok_dash,             \
        epddl_tok_eq,               \
        epddl_tok_gets,             \
        epddl_tok_identifier,       \
        epddl_tok_variable,         \
        epddl_tok_requirement,      \
        epddl_tok_integer,          \
        epddl_tok_action,           \
        epddl_tok_act_type,         \
        epddl_tok_act_type_lib,     \
        epddl_tok_agents,           \
        epddl_tok_agent_groups,     \
        epddl_tok_define,           \
        epddl_tok_designated,       \
        epddl_tok_domain,           \
        epddl_tok_effects,          \
        epddl_tok_event,            \
        epddl_tok_events,           \
        epddl_tok_goal,             \
        epddl_tok_init,             \
        epddl_tok_library,          \
        epddl_tok_modalities,       \
        epddl_tok_objects,          \
        epddl_tok_obs_conditions,   \
        epddl_tok_obs_groups,       \
        epddl_tok_parameters,       \
        epddl_tok_precondition,     \
        epddl_tok_predicates,       \
        epddl_tok_problem,          \
        epddl_tok_prob_domain,      \
        epddl_tok_relations,        \
        epddl_tok_requirements,     \
        epddl_tok_state,            \
        epddl_tok_state_name,       \
        epddl_tok_static_preds,     \
        epddl_tok_types,            \
        epddl_tok_valuation,        \
        epddl_tok_where,            \
        epddl_tok_worlds,           \
        epddl_tok_conjunction,      \
        epddl_tok_disjunction,      \
        epddl_tok_implication,      \
        epddl_tok_negation,         \
        epddl_tok_exists,           \
        epddl_tok_forall,           \
        epddl_tok_bot,              \
        epddl_tok_top,              \
        epddl_tok_iff,              \
        epddl_tok_when,             \
        epddl_tok_always,           \
        epddl_tok_else_cond,        \
        epddl_tok_if_cond,          \
        epddl_tok_all,              \
        epddl_tok_et_object,        \
        epddl_tok_et_agent,         \
        epddl_tok_et_predicate,     \
        epddl_tok_et_literal,       \
        epddl_tok_et_formula,       \
        epddl_tok_et_effects        \
)
// epddl_tok_modality,         \

// todo: implement reserved types during type checking
//        epddl_tok_agent,            \
//        epddl_tok_formula,          \
//        epddl_tok_literal,          \
//        epddl_tok_object,           \
//        epddl_tok_postcondition,    \
//        epddl_tok_predicate,        \
//        epddl_tok_predicate_formula \

#endif //EPDDL_TOKENS_DEF_H
