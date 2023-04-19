#ifndef EPDDL_AST_AUXILIARY_TYPES_GEN_H
#define EPDDL_AST_AUXILIARY_TYPES_GEN_H

#include "../../grammar/grammar.h"

namespace epddl::ast {
#define unique_ptr0(type) type##_ptr
#define unique_ptr(type) unique_ptr0(type)

#define epddl_token_type(token_type) token_type
#define type_name(name) name
#define epddl_token(t_type, t_scope, t_name, t_lexeme) token_alias(t_type, t_name)
#define ast_class(class_name) class_name
#define variant(types...) types
#define epddl_auxiliary_type(name, types) \
    using name = std::variant<types>; \
    using unique_ptr(name) = std::unique_ptr<name>;
    // Declaration of auxiliary types and auxiliary unique pointer types
    epddl_all_auxiliary_type_defs
#undef epddl_auxiliary_type
#undef variant
#undef ast_class
#undef epddl_token
#undef type_name
#undef epddl_token_type

#undef unique_ptr
#undef unique_ptr0
}

#endif //EPDDL_AST_AUXILIARY_TYPES_GEN_H
