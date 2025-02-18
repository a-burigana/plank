#ifndef EPDDL_GOAL_PARSER_H
#define EPDDL_GOAL_PARSER_H

#include "../../ast/problems/goal_decl_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class goal_parser {
    public:
        static ast::goal_decl_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_GOAL_PARSER_H
