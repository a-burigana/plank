#ifndef EPDDL_POSTCONDITIONS_PARSER_H
#define EPDDL_POSTCONDITIONS_PARSER_H

#include "../../ast/ast.h"
#include "../parser_helper.h"

namespace epddl {
    class postconditions_parser {
    public:
        static ast::postconditions parse(parser_helper &parser);

        static ast::single_postcondition parse_single_postcondition(parser_helper &parser);
        static ast::simple_postcondition parse_simple_postcondition(parser_helper &parser);
        static ast::postcondition_list_ptr parse_postcondition_list(parser_helper &parser);

        static ast::literal_postcondition_ptr parse_literal_postcondition(parser_helper &parser);
        static ast::iff_postcondition_ptr parse_iff_postcondition(parser_helper &parser);
        static ast::when_postcondition_ptr parse_when_postcondition(parser_helper &parser);
        static ast::forall_postcondition_ptr parse_forall_postcondition(parser_helper &parser);
    };
}

#endif //EPDDL_POSTCONDITIONS_PARSER_H
