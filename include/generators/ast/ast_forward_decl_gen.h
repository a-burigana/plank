#ifndef EPDDL_AST_FORWARD_DECL_GEN_H
#define EPDDL_AST_FORWARD_DECL_GEN_H

#include "../../grammar/grammar.h"

namespace epddl::ast {
#define epddl_token_type(token_type) token_type
#define class_name(c_name) class c_name;
#define ast_class(name, _) name
#define epddl_element(ast_class, _) ast_class
    // Forward declaration of AST classes
    epddl_all_element_defs

#undef epddl_element
#undef ast_class
#undef class_name
#undef epddl_token_type
}

#endif //EPDDL_AST_FORWARD_DECL_GEN_H
