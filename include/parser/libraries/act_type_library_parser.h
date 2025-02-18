#ifndef EPDDL_ACT_TYPE_LIBRARY_PARSER_H
#define EPDDL_ACT_TYPE_LIBRARY_PARSER_H

#include "../../ast/libraries/act_type_library_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class act_type_library_parser {
    public:
        static ast::act_type_library_ptr parse(parser_helper &helper);
        static ast::act_type_library_item parse_act_type_library_item(parser_helper &helper);
    };
}

#endif //EPDDL_ACT_TYPE_LIBRARY_PARSER_H
