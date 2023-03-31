#ifndef EPDDL_TOKEN_ENUMS_H
#define EPDDL_TOKEN_ENUMS_H

#define SPECIAL_ENUM         ENUM_NAME(special_value)
#define PUNCTUATION_ENUM     ENUM_NAME(punctuation_value)
#define BASIC_ENUM           ENUM_NAME(basic_value)
#define KEYWORD_ENUM         ENUM_NAME(keyword_value)
#define CONNECTIVE_ENUM      ENUM_NAME(connective_value)
#define QUANTIFIER_ENUM      ENUM_NAME(quantifier_value)
#define ATOMIC_FORMULA_ENUM  ENUM_NAME(atomic_formula_value)
#define POSTCONDITION_ENUM   ENUM_NAME(postcondition_value)
#define OBSERVABILITY_ENUM   ENUM_NAME(observability_value)
#define AGENT_GROUP_ENUM     ENUM_NAME(agent_group_value)
#define RESERVED_TYPE_ENUM   ENUM_NAME(reserved_type_value)
//#define REQUIREMENT_ENUM     ENUM_NAME(requirement_value)
//#define VAL_REQUIREMENT_ENUM ENUM_NAME(val_requirement_value)

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
//    REQUIREMENT_ENUM \
//    VAL_REQUIREMENT_ENUM

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

#endif //EPDDL_TOKEN_ENUMS_H
