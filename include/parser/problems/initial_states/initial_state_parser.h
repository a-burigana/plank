#ifndef EPDDL_INITIAL_STATE_PARSER_H
#define EPDDL_INITIAL_STATE_PARSER_H

#include "../../../ast/problems/initial_states/initial_state_decl_ast.h"
#include "../../parser_helper.h"

namespace epddl::parser {
    class initial_state_parser {
    public:
        static ast::initial_state parse(parser_helper &helper);
    };
}

#endif //EPDDL_INITIAL_STATE_PARSER_H
