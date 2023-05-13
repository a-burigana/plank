#ifndef EPDDL_PARSER_GEN_H
#define EPDDL_PARSER_GEN_H

#include "../../grammar/grammar.h"
#include "../ast/ast_gen.h"

namespace epddl {
#define function_name0(arg) parse_##arg
#define function_name(arg) function_name0(arg)

#define element_name(name) name
#define epddl_element(name, _, __) ast::unique_ptr(name) function_name(name)();
    // Prototypes of parsing functions
    epddl_all_element_defs

#undef epddl_element

#define epddl_element(name, _, __) \
    ast::unique_ptr(name) function_name(name)() { \
        return {};                                \
    }

    // Parsing functions
//    epddl_all_element_defs

#undef epddl_element
#undef element_name
}

#endif //EPDDL_PARSER_GEN_H
