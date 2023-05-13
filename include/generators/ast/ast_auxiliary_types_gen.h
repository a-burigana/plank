#ifndef EPDDL_AST_AUXILIARY_TYPES_GEN_H
#define EPDDL_AST_AUXILIARY_TYPES_GEN_H

#include "../../grammar/grammar.h"

namespace epddl::ast {
#define epddl_token_type(token_type) token_type
#define type_name(name) name
#define epddl_token(t_type, t_scope, t_name, t_lexeme) token_alias(t_type, t_name)
#define element_name(name) name
#define node(n) n
#define leaf(l) l
#define element_bnf(nodes...) nodes
#define epddl_variant_element(name, nodes) \
    using name = std::variant<nodes>; \
    using unique_ptr(name) = std::unique_ptr<name>;
    // Declaration of auxiliary types and auxiliary unique pointer types
    epddl_all_auxiliary_type_defs
#undef epddl_variant_element
#undef element_bnf
#undef leaf
#undef node
#undef element_name
#undef epddl_token
#undef type_name
#undef epddl_token_type
}

#endif //EPDDL_AST_AUXILIARY_TYPES_GEN_H
