#ifndef EPDDL_AST_FORWARD_DECL_GEN_H
#define EPDDL_AST_FORWARD_DECL_GEN_H

#include "../../grammar/grammar.h"

namespace epddl::ast {
#define epddl_token_type(token_type) token_type
#define element_name(name) \
    class name;            \
    using unique_ptr(name) = std::unique_ptr<name>;

#define epddl_element(element_name, _, __) element_name
    // Forward declaration of AST classes
    epddl_all_element_defs

#undef epddl_element
#undef element_name
#undef epddl_token_type
}

#endif //EPDDL_AST_FORWARD_DECL_GEN_H
