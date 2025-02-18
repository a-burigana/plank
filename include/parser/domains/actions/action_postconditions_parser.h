#ifndef EPDDL_ACTION_POSTCONDITIONS_PARSER_H
#define EPDDL_ACTION_POSTCONDITIONS_PARSER_H

#include "../../parser_helper.h"
#include "../../../ast/domains/actions/action_postconditions_ast.h"

namespace epddl::parser {
    class action_postconditions_parser {
    public:
        static ast::event_postconditions_list parse(parser_helper &helper);
        static ast::event_postconditions parse_event_postcondition(parser_helper &helper);

        static ast::postconditions parse_postcondition(parser_helper &helper);

        static ast::single_postcondition parse_single_postcondition(parser_helper &helper);
        static ast::postcondition_list parse_postcondition_list(parser_helper &helper);

        static ast::literal_postcondition_ptr parse_literal_postcondition(parser_helper &helper);
        static ast::iff_postcondition_ptr parse_iff_postcondition(parser_helper &helper);
        static ast::when_postcondition_ptr parse_when_postcondition(parser_helper &helper);
        static ast::forall_postcondition_ptr parse_forall_postcondition(parser_helper &helper);
    };
}

#endif //EPDDL_ACTION_POSTCONDITIONS_PARSER_H
