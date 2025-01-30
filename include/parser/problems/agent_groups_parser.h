#ifndef EPDDL_AGENT_GROUPS_PARSER_H
#define EPDDL_AGENT_GROUPS_PARSER_H

#include "../../ast/problems/agent_groups_decl_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class agent_groups_parser {
    public:
        static ast::agent_groups_decl_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_AGENT_GROUPS_PARSER_H
