#ifndef EPDDL_AST_ALIASES_GEN_H
#define EPDDL_AST_ALIASES_GEN_H

namespace epddl::ast {
#define epddl_token_type(token_type) token_type
#define ast_class(name, _) name
#define epddl_element(ast_class, _) ast_class
#define class_name(c_name) using unique_ptr(c_name) = std::unique_ptr<c_name>;
    // Declaration of unique pointers for AST classes
    epddl_all_element_defs
#undef class_name
#undef epddl_element
#undef ast_class
#undef epddl_token_type
}

#endif //EPDDL_AST_ALIASES_GEN_H
