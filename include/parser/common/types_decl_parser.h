#ifndef EPDDL_TYPES_DECL_PARSER_H
#define EPDDL_TYPES_DECL_PARSER_H

#include "../../ast/common/types_decl_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class types_decl_parser {
    public:
        static ast::types_decl_ptr parse(parser_helper &parser);
    };
}

#endif //EPDDL_TYPES_DECL_PARSER_H
