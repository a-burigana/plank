#ifndef EPDDL_PARSER_GEN_H
#define EPDDL_PARSER_GEN_H

#include "../../grammar/grammar.h"
#include "../ast/ast_gen.h"

namespace epddl {
#define class_name(c_name) c_name
#define function_name(arg) parse_##arg
#define ast_class(name, params) ast::unique_ptr(name) function_name(name)();
#define epddl_element(ast_class, _) ast_class
    // Prototypes of parsing functions
    epddl_all_element_defs

#undef epddl_element
#undef ast_class
#undef function_name
#undef class_name

#define class_name(c_name) c_name
#define function_name(arg) parse_##arg
#define ast_class(name, params) \
    ast::unique_ptr(name) function_name(name)() { \
        return {};                                \
    }

#define epddl_element(ast_class, _) ast_class
    // Prototypes of parsing functions
    epddl_all_element_defs

#undef epddl_element
#undef ast_class
#undef function_name
#undef class_name
}

#endif //EPDDL_PARSER_GEN_H
