#ifndef EPDDL_ACTION_DECL_PARSER_H
#define EPDDL_ACTION_DECL_PARSER_H

#include "../../../ast/domains/actions/action_decl_ast.h"
#include "../../parser_helper.h"

namespace epddl::parser {
    class action_decl_parser {
    public:
        static ast::action_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_ACTION_DECL_PARSER_H
