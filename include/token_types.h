#ifndef EPDDL_TOKEN_TYPES_H
#define EPDDL_TOKEN_TYPES_H


#define SPECIAL_ENUM \
    ENUM(special_value)

#define PUNCTUATION_ENUM \
    ENUM(punctuation_value)

#define BASIC_ENUM \
    ENUM(basic_value)

#define KEYWORD_ENUM \
    ENUM(keyword_value)

#define CONNECTIVE_ENUM \
    ENUM(connective_value)

#define QUANTIFIER_ENUM \
    ENUM(quantifier_value)

#define ATOMIC_FORMULA_ENUM \
    ENUM(atomic_formula_value)

#define POSTCONDITION_ENUM \
    ENUM(postcondition_value)

#define OBSERVABILITY_ENUM \
    ENUM(observability_value)

#define AGENT_GROUP_ENUM \
    ENUM(agent_group_value)

#define RESERVED_TYPE_ENUM \
    ENUM(reserved_type_value)

#define REQUIREMENT_ENUM \
    ENUM(requirement_value)

#define VAL_REQUIREMENT_ENUM \
    ENUM(val_requirement_value)


#define ALL_ENUMS \
    SPECIAL_ENUM \
    PUNCTUATION_ENUM \
    BASIC_ENUM \
    KEYWORD_ENUM \
    CONNECTIVE_ENUM \
    QUANTIFIER_ENUM \
    ATOMIC_FORMULA_ENUM \
    POSTCONDITION_ENUM \
    OBSERVABILITY_ENUM \
    AGENT_GROUP_ENUM \
    RESERVED_TYPE_ENUM \
    REQUIREMENT_ENUM \
    VAL_REQUIREMENT_ENUM

//#define KEYWORD_ENUMS \
//    KEYWORD_ENUM \
//    CONNECTIVE_ENUM \
//    QUANTIFIER_ENUM \
//    ATOMIC_FORMULA_ENUM \
//    POSTCONDITION_ENUM \
//    OBSERVABILITY_ENUM \
//    AGENT_GROUP_ENUM \
//    RESERVED_TYPE_ENUM \
//    REQUIREMENT_ENUM \
//    VAL_REQUIREMENT_ENUM


// Syntax: VAL(<enum_name>, <is_scope_token>, <name>, <lexeme>)

#define SPECIAL \
    VAL(special_value,         false, eof,               "eof") \
    VAL(special_value,         false, invalid,           "invalid")

#define PUNCTUATION \
    VAL(punctuation_value,     false, lpar,              "(") \
    VAL(punctuation_value,     false, rpar,              ")") \
    VAL(punctuation_value,     false, lbrack,            "[") \
    VAL(punctuation_value,     false, rbrack,            "]") \
    VAL(punctuation_value,     false, lt,                "<") \
    VAL(punctuation_value,     false, gt,                ">") \
    VAL(punctuation_value,     false, dash,              "-") \
    VAL(punctuation_value,     false, eq,                "=") \
    VAL(punctuation_value,     false, gets,              "<-")

#define BASIC \
    VAL(basic_value,           false, ident,             "") /* [_a-zA-Z][_'a-zA-Z0-9]* */   \
    VAL(basic_value,           false, variable,          "") /* \?[_a-zA-Z][_'a-zA-Z0-9]* */ \
    VAL(basic_value,           false, modality,          "") /* [a-z][_a-zA-Z0-9]*\. */      \
    VAL(basic_value,           false, requirement,       "")                                 \
    VAL(basic_value,           false, integer,           "") /* [0-9]|[1-9][0-9]+ */

// todo: how to handle requirements??

#define KEYWORD \
    VAL(keyword_value,         true,  define,             "define") \
    VAL(keyword_value,         true,  domain,            "domain") \
    VAL(keyword_value,         true,  library,           "library") \
    VAL(keyword_value,         true,  problem,           "problem") \
    VAL(keyword_value,         true,  action,            ":action") \
    VAL(keyword_value,         true,  act_type,          ":action-type") \
    VAL(keyword_value,         true,  act_type_lib,      ":action-type-libraries") \
    VAL(keyword_value,         true,  agents,            ":agents") \
    VAL(keyword_value,         true,  agent_groups,      ":agent-groups") \
    VAL(keyword_value,         true,  designated,        ":designated") \
    VAL(keyword_value,         true,  prob_domain,       ":domain") \
    VAL(keyword_value,         true,  event,             ":event") \
    VAL(keyword_value,         true,  events,            ":events") \
    VAL(keyword_value,         true,  goal,              ":goal") \
    VAL(keyword_value,         true,  init,              ":init") \
    VAL(keyword_value,         true,  objects,           ":objects") \
    VAL(keyword_value,         true,  obs_conditions,    ":observability-conditions") \
    VAL(keyword_value,         true,  obs_groups,        ":observability-groups") \
    VAL(keyword_value,         true,  modalities,        ":modalities") \
    VAL(keyword_value,         true,  parameters,        ":parameters") \
    VAL(keyword_value,         true,  postconditions,    ":postconditions") \
    VAL(keyword_value,         true,  precondition,      ":precondition") \
    VAL(keyword_value,         true,  predicates,        ":predicates") \
    VAL(keyword_value,         true,  relations,         ":relations") \
    VAL(keyword_value,         true,  requirements,      ":requirements") \
    VAL(keyword_value,         true,  state,             ":state") \
    VAL(keyword_value,         true,  state_name,        ":state-name") \
    VAL(keyword_value,         true,  static_preds,      ":static") \
    VAL(keyword_value,         true,  types,             ":types") \
    VAL(keyword_value,         true,  valuation,         ":valuation") \
    VAL(keyword_value,         true,  where,             ":where") \
    VAL(keyword_value,         true,  worlds,            ":worlds")

#define CONNECTIVE \
    VAL(connective_value,      false, negation,          "not") \
    VAL(connective_value,      false, implication,       "imply") \
    VAL(connective_value,      false, conjunction,       "and") \
    VAL(connective_value,      false, disjunction,       "or")

#define QUANTIFIER \
    VAL(quantifier_value,       true,  exists,            "exists") \
    VAL(quantifier_value,       true,  forall,            "forall")

#define ATOMIC_FORMULA \
    VAL(atomic_formula_value,  false, bot,               "false") \
    VAL(atomic_formula_value,  false, top,               "true")

#define POSTCONDITION \
    VAL(postcondition_value,   true,  iff,               "iff") \
    VAL(postcondition_value,   true,  when,              "when")

#define OBSERVABILITY \
    VAL(observability_value,   true,  if_cond,           "if") \
    VAL(observability_value,   true,  otherwise,         "otherwise")

#define AGENT_GROUP \
    VAL(agent_group_value,     false, all,               "All")

#define RESERVED_TYPE \
    VAL(reserved_type_value,   false, agent,             "agent") \
    VAL(reserved_type_value,   false, formula,           "formula") \
    VAL(reserved_type_value,   false, literal,           "literal") \
    VAL(reserved_type_value,   false, object,            "object") \
    VAL(reserved_type_value,   false, postcondition,     "postcondition") \
    VAL(reserved_type_value,   false, predicate,         "predicate") \
    VAL(reserved_type_value,   false, predicate_formula, "predicate_formula")

#define REQUIREMENT \
    VAL(requirement_value,     false, ck,                ":common-knowledge") \
    VAL(requirement_value,     false, del,               ":del") \
    VAL(requirement_value,     false, dyn_ck,            ":dynamic-common-knowledge") \
    VAL(requirement_value,     false, eq,                ":equality") \
    VAL(requirement_value,     false, exist_form,        ":existential-formulae") \
    VAL(requirement_value,     false, fin_s5_th,          ":finitary-S5-theory") \
    VAL(requirement_value,     false, mod_post,          ":modal-postconditions") \
    VAL(requirement_value,     false, mod_pre,           ":modal-preconditions") \
    VAL(requirement_value,     false, ontic,             ":ontic-change") \
    VAL(requirement_value,     false, typing,            ":typing") \
    VAL(requirement_value,     false, univ_form,         ":universal-formulae") \
    VAL(requirement_value,     false, univ_post,         ":universal-postconditions")

#define VAL_REQUIREMENT \
    VAL(val_requirement_value, true,  max_depth,         ":maximum-modal-depth") \
    VAL(val_requirement_value, true,  max_pre_depth,     ":maximum-postconditions-depth") \
    VAL(val_requirement_value, true,  max_post_depth,    ":maximum-preconditions-depth")


#define ALL_TOKENS \
    SPECIAL \
    PUNCTUATION \
    BASIC \
    KEYWORD \
    CONNECTIVE \
    QUANTIFIER \
    ATOMIC_FORMULA \
    POSTCONDITION \
    OBSERVABILITY \
    AGENT_GROUP \
    RESERVED_TYPE \
    REQUIREMENT \
    VAL_REQUIREMENT

#define VALID_KEYWORDS \
    KEYWORD \
    CONNECTIVE \
    QUANTIFIER \
    ATOMIC_FORMULA \
    POSTCONDITION \
    OBSERVABILITY \
    AGENT_GROUP \
    RESERVED_TYPE \
    REQUIREMENT \
    VAL_REQUIREMENT

#endif //EPDDL_TOKEN_TYPES_H
