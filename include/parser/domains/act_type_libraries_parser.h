#ifndef EPDDL_ACT_TYPE_LIBRARIES_PARSER_H
#define EPDDL_ACT_TYPE_LIBRARIES_PARSER_H

#include "../../ast/ast.h"
#include "../parser_helper.h"

namespace epddl {
    class act_type_libraries_parser {
    public:
        static ast::domain_libraries_ptr parse(parser_helper &parser);
    };
}

#endif //EPDDL_ACT_TYPE_LIBRARIES_PARSER_H
