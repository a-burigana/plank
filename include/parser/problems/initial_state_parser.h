#ifndef EPDDL_INITIAL_STATE_PARSER_H
#define EPDDL_INITIAL_STATE_PARSER_H

#include "../../ast/problems/initial_state_decl_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class initial_state_parser {
    public:
        static ast::initial_state_ptr parse(parser_helper &helper);

        static ast::ident_list parse_worlds(parser_helper &helper);
        static ast::ident_list parse_designated(parser_helper &helper);
    };
}

#endif //EPDDL_INITIAL_STATE_PARSER_H
