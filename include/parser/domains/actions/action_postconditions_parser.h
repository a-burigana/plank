#ifndef EPDDL_ACTION_POSTCONDITIONS_PARSER_H
#define EPDDL_ACTION_POSTCONDITIONS_PARSER_H

#include "../../parser_helper.h"
#include "../../../ast/domains/actions/action_postconditions_ast.h"

namespace epddl {
    class action_postconditions_parser {
    public:
        static ast::event_postconditions_list parse(parser_helper &helper);
        static ast::event_postconditions parse_event_postcondition(parser_helper &helper);
    };
}

#endif //EPDDL_ACTION_POSTCONDITIONS_PARSER_H
