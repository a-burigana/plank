#ifndef EPDDL_OBJECTS_PARSER_H
#define EPDDL_OBJECTS_PARSER_H

#include "../../ast/problems/objects_decl_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class objects_parser {
    public:
        static ast::objects_decl_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_OBJECTS_PARSER_H
