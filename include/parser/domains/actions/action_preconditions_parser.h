#ifndef EPDDL_ACTION_PRECONDITIONS_PARSER_H
#define EPDDL_ACTION_PRECONDITIONS_PARSER_H

#include "../../../ast/domains/actions/action_preconditions_ast.h"
#include "../../parser_helper.h"

namespace epddl::parser {
    class action_preconditions_parser {
    public:
        static ast::event_precondition_list parse(parser_helper &helper);
        static ast::event_precondition parse_event_precondition(parser_helper &helper);

//        static ast::formula_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_ACTION_PRECONDITIONS_PARSER_H
