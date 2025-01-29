#ifndef EPDDL_ACT_TYPE_PRECONDITIONS_PARSER_H
#define EPDDL_ACT_TYPE_PRECONDITIONS_PARSER_H

#include "../../parser_helper.h"
#include "../../../ast/libraries/act_types/act_type_preconditions_ast.h"

namespace epddl {
    class act_type_preconditions_parser {
    public:
        static ast::event_precondition_list parse(parser_helper &helper);
        static ast::event_precondition parse_event_precondition(parser_helper &helper);
    };
}

#endif //EPDDL_ACT_TYPE_PRECONDITIONS_PARSER_H
