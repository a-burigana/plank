#ifndef EPDDL_TOKEN_TYPES_H
#define EPDDL_TOKEN_TYPES_H

#include "tokens.h"

#define SPECIAL \
    TOK_EOF \
    TOK_INVALID

#define PUNCTUATION \
    TOK_LPAR   \
    TOK_RPAR   \
    TOK_LBRACK \
    TOK_RBRACK \
    TOK_LT     \
    TOK_GT     \
    TOK_DASH   \
    TOK_EQ     \
    TOK_GETS

#define BASIC \
    TOK_IDENTIFIER  \
    TOK_VARIABLE    \
    TOK_MODALITY    \
    TOK_REQUIREMENT \
    TOK_INTEGER

#define KEYWORD \
    TOK_ACTION         \
    TOK_ACT_TYPE       \
    TOK_ACT_TYPE_LIB   \
    TOK_AGENTS         \
    TOK_AGENT_GROUPS   \
    TOK_DEFINE         \
    TOK_DESIGNATED     \
    TOK_DOMAIN         \
    TOK_EVENT          \
    TOK_EVENTS         \
    TOK_GOAL           \
    TOK_INIT           \
    TOK_LIBRARY        \
    TOK_MODALITIES     \
    TOK_OBJECTS        \
    TOK_OBS_CONDITIONS \
    TOK_OBS_GROUPS     \
    TOK_PARAMETERS     \
    TOK_POSTCONDITIONS \
    TOK_PRECONDITION   \
    TOK_PREDICATES     \
    TOK_PROBLEM        \
    TOK_PROB_DOMAIN    \
    TOK_RELATIONS      \
    TOK_REQUIREMENTS   \
    TOK_STATE          \
    TOK_STATE_NAME     \
    TOK_STATIC_PREDS   \
    TOK_TYPES          \
    TOK_VALUATION      \
    TOK_WHERE          \
    TOK_WORLDS

#define CONNECTIVE \
    TOK_CONJUNCTION \
    TOK_DISJUNCTION \
    TOK_IMPLICATION \
    TOK_NEGATION

#define QUANTIFIER \
    TOK_EXISTS \
    TOK_FORALL


#define ATOMIC_FORMULA \
    TOK_BOT \
    TOK_TOP


#define POSTCONDITION \
    TOK_IFF \
    TOK_WHEN


#define OBSERVABILITY \
    TOK_IF_COND \
    TOK_OTHERWISE


#define AGENT_GROUP \
    TOK_ALL

#define RESERVED_TYPE \
    TOK_AGENT         \
    TOK_FORMULA       \
    TOK_LITERAL       \
    TOK_OBJECT        \
    TOK_POSTCONDITION \
    TOK_PREDICATE     \
    TOK_PREDICATE_FORMULA

#define ALL_TOKENS \
    SPECIAL        \
    PUNCTUATION    \
    BASIC          \
    KEYWORD        \
    CONNECTIVE     \
    QUANTIFIER     \
    ATOMIC_FORMULA \
    POSTCONDITION  \
    OBSERVABILITY  \
    AGENT_GROUP    \
    RESERVED_TYPE

#define VALID_KEYWORDS \
    KEYWORD        \
    CONNECTIVE     \
    QUANTIFIER     \
    ATOMIC_FORMULA \
    POSTCONDITION  \
    OBSERVABILITY  \
    AGENT_GROUP    \
    RESERVED_TYPE

#undef ENUM_NAME

#endif //EPDDL_TOKEN_TYPES_H
