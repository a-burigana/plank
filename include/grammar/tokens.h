#ifndef EPDDL_TOKENS_H
#define EPDDL_TOKENS_H

#include "token_enums.h"

// Syntax: VAL(<enum_name>, <is_scope_token>, <name>, <lexeme>)
#define ENUM_NAME(name) name

#define TOK_EOF               VAL(SPECIAL_ENUM,        false, eof,               "eof")
#define TOK_INVALID           VAL(SPECIAL_ENUM,        false, invalid,           "invalid")

#define TOK_LPAR              VAL(PUNCTUATION_ENUM,    false, lpar,              "(")
#define TOK_RPAR              VAL(PUNCTUATION_ENUM,    false, rpar,              ")")
#define TOK_LBRACK            VAL(PUNCTUATION_ENUM,    false, lbrack,            "[")
#define TOK_RBRACK            VAL(PUNCTUATION_ENUM,    false, rbrack,            "]")
#define TOK_LT                VAL(PUNCTUATION_ENUM,    false, lt,                "<")
#define TOK_GT                VAL(PUNCTUATION_ENUM,    false, gt,                ">")
#define TOK_DASH              VAL(PUNCTUATION_ENUM,    false, dash,              "-")
#define TOK_EQ                VAL(PUNCTUATION_ENUM,    false, eq,                "=")
#define TOK_GETS              VAL(PUNCTUATION_ENUM,    false, gets,              "<-")

#define TOK_IDENTIFIER        VAL(BASIC_ENUM,          false, identifier,         "") /* [_a-zA-Z][_'a-zA-Z0-9]* */
#define TOK_VARIABLE          VAL(BASIC_ENUM,          false, variable,          "") /* \?[_a-zA-Z][_'a-zA-Z0-9]* */
#define TOK_MODALITY          VAL(BASIC_ENUM,          false, modality,          "") /* [a-z][_a-zA-Z0-9]*\. */
#define TOK_REQUIREMENT       VAL(BASIC_ENUM,          false, requirement,       "") /* [a-zA-Z][\-a-zA-Z0-9]* */
#define TOK_INTEGER           VAL(BASIC_ENUM,          false, integer,           "") /* [0-9]|[1-9][0-9]+ */

#define TOK_ACTION            VAL(KEYWORD_ENUM,        true,  action,            ":action")
#define TOK_ACT_TYPE          VAL(KEYWORD_ENUM,        true,  act_type,          ":action-type")
#define TOK_ACT_TYPE_LIB      VAL(KEYWORD_ENUM,        true,  act_type_lib,      ":action-type-libraries")
#define TOK_AGENTS            VAL(KEYWORD_ENUM,        true,  agents,            ":agents")
#define TOK_AGENT_GROUPS      VAL(KEYWORD_ENUM,        true,  agent_groups,      ":agent-groups")
#define TOK_DEFINE            VAL(KEYWORD_ENUM,        true,  define,             "define")
#define TOK_DESIGNATED        VAL(KEYWORD_ENUM,        true,  designated,        ":designated")
#define TOK_DOMAIN            VAL(KEYWORD_ENUM,        true,  domain,            "domain")
#define TOK_EVENT             VAL(KEYWORD_ENUM,        true,  event,             ":event")
#define TOK_EVENTS            VAL(KEYWORD_ENUM,        true,  events,            ":events")
#define TOK_GOAL              VAL(KEYWORD_ENUM,        true,  goal,              ":goal")
#define TOK_INIT              VAL(KEYWORD_ENUM,        true,  init,              ":init")
#define TOK_LIBRARY           VAL(KEYWORD_ENUM,        true,  library,           "library")
#define TOK_MODALITIES        VAL(KEYWORD_ENUM,        true,  modalities,        ":modalities")
#define TOK_OBJECTS           VAL(KEYWORD_ENUM,        true,  objects,           ":objects")
#define TOK_OBS_CONDITIONS    VAL(KEYWORD_ENUM,        true,  obs_conditions,    ":observability-conditions")
#define TOK_OBS_GROUPS        VAL(KEYWORD_ENUM,        true,  obs_groups,        ":observability-groups")
#define TOK_PARAMETERS        VAL(KEYWORD_ENUM,        true,  parameters,        ":parameters")
#define TOK_POSTCONDITIONS    VAL(KEYWORD_ENUM,        true,  postconditions,    ":postconditions")
#define TOK_PRECONDITION      VAL(KEYWORD_ENUM,        true,  precondition,      ":precondition")
#define TOK_PREDICATES        VAL(KEYWORD_ENUM,        true,  predicates,        ":predicates")
#define TOK_PROBLEM           VAL(KEYWORD_ENUM,        true,  problem,           "problem")
#define TOK_PROB_DOMAIN       VAL(KEYWORD_ENUM,        true,  prob_domain,       ":domain")
#define TOK_RELATIONS         VAL(KEYWORD_ENUM,        true,  relations,         ":relations")
#define TOK_REQUIREMENTS      VAL(KEYWORD_ENUM,        true,  requirements,      ":requirements")
#define TOK_STATE             VAL(KEYWORD_ENUM,        true,  state,             ":state")
#define TOK_STATE_NAME        VAL(KEYWORD_ENUM,        true,  state_name,        ":state-name")
#define TOK_STATIC_PREDS      VAL(KEYWORD_ENUM,        true,  static_preds,      ":static")
#define TOK_TYPES             VAL(KEYWORD_ENUM,        true,  types,             ":types")
#define TOK_VALUATION         VAL(KEYWORD_ENUM,        true,  valuation,         ":valuation")
#define TOK_WHERE             VAL(KEYWORD_ENUM,        true,  where,             ":where")
#define TOK_WORLDS            VAL(KEYWORD_ENUM,        true,  worlds,            ":worlds")

#define TOK_CONJUNCTION       VAL(CONNECTIVE_ENUM,     false, conjunction,       "and")
#define TOK_DISJUNCTION       VAL(CONNECTIVE_ENUM,     false, disjunction,       "or")
#define TOK_IMPLICATION       VAL(CONNECTIVE_ENUM,     false, implication,       "imply")
#define TOK_NEGATION          VAL(CONNECTIVE_ENUM,     false, negation,          "not")

#define TOK_EXISTS            VAL(QUANTIFIER_ENUM,     true,  exists,            "exists")
#define TOK_FORALL            VAL(QUANTIFIER_ENUM,     true,  forall,            "forall")

#define TOK_BOT               VAL(ATOMIC_FORMULA_ENUM, false, bot,               "false")
#define TOK_TOP               VAL(ATOMIC_FORMULA_ENUM, false, top,               "true")

#define TOK_IFF               VAL(POSTCONDITION_ENUM,  true,  iff,               "iff")
#define TOK_WHEN              VAL(POSTCONDITION_ENUM,  true,  when,              "when")

#define TOK_IF_COND           VAL(OBSERVABILITY_ENUM,  true,  if_cond,           "if")
#define TOK_OTHERWISE         VAL(OBSERVABILITY_ENUM,  true,  otherwise,         "otherwise")

#define TOK_ALL               VAL(AGENT_GROUP_ENUM,    false, all,               "All")

#define TOK_AGENT             VAL(RESERVED_TYPE_ENUM,  false, agent,             "agent")
#define TOK_FORMULA           VAL(RESERVED_TYPE_ENUM,  false, formula,           "formula")
#define TOK_LITERAL           VAL(RESERVED_TYPE_ENUM,  false, literal,           "literal")
#define TOK_OBJECT            VAL(RESERVED_TYPE_ENUM,  false, object,            "object")
#define TOK_POSTCONDITION     VAL(RESERVED_TYPE_ENUM,  false, postcondition,     "postcondition")
#define TOK_PREDICATE         VAL(RESERVED_TYPE_ENUM,  false, predicate,         "predicate")
#define TOK_PREDICATE_FORMULA VAL(RESERVED_TYPE_ENUM,  false, predicate_formula, "predicate_formula")

#undef ENUM_NAME
#endif //EPDDL_TOKENS_H
