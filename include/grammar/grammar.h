#ifndef EPDDL_GRAMMAR_H
#define EPDDL_GRAMMAR_H

#include "token_types.h"

// Syntax:
//  1. NODE(<node_name>,  <is_optional>, <is_list>)
//  2. LEAF(<token_type>, <is_optional>)

#define VAL(token_type, scope, name, lexeme) token_type::name

#define NODE_LPAR \
    LEAF(LPAR, false)

#define NODE_DEFINE \
    LEAF(define, false)

#define NODE(name, is_optional, is_list) NODE(name, is_optional, is_list)
#define LEAF(token_type, is_optional) LEAF(token_type, is_optional)
#define DOMAIN \
    NODE_LPAR \
    NODE_DEFINE \
    NODE_LPAR \
    NODE(leaf, "domain", false, invalid,           "invalid")  \
#undef LEAF
#undef NODE

#undef VAL

#endif //EPDDL_GRAMMAR_H
