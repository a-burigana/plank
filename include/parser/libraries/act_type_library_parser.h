#ifndef EPDDL_ACT_TYPE_LIBRARY_PARSER_H
#define EPDDL_ACT_TYPE_LIBRARY_PARSER_H

#include "../../ast/libraries/act_type_library_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class act_type_library_parser {
    public:
        static ast::act_type_library_ptr parse(parser_helper &parser);
        static ast::act_type_library_item parse_act_type_library_item(parser_helper &parser);
    };
}

#endif //EPDDL_ACT_TYPE_LIBRARY_PARSER_H
