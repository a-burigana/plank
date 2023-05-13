#ifndef EPDDL_AST_ALIASES_GEN_H
#define EPDDL_AST_ALIASES_GEN_H

#include "ast_classes_gen.h"

namespace epddl::ast {
#define epddl_token_type(token_type) token_type
#define element_name(c_name) using unique_ptr(c_name) = std::unique_ptr<c_name>;
#define epddl_element(element_name, _, __) element_name
    // Declaration of unique pointers for AST classes
    epddl_all_element_defs
#undef epddl_element
#undef element_name
#undef epddl_token_type
}

#endif //EPDDL_AST_ALIASES_GEN_H
