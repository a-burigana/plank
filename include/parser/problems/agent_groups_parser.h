#ifndef EPDDL_AGENT_GROUPS_PARSER_H
#define EPDDL_AGENT_GROUPS_PARSER_H

#include "../../ast/problems/agent_groups_decl_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class agent_groups_parser {
    public:
        static ast::agent_groups_decl_ptr parse(parser_helper &helper);
        static ast::agent_group_decl_ptr parse_agent_group_decl(parser_helper &helper);

        static ast::agent_group parse_agent_group(parser_helper &helper);

        static ast::single_agent_group parse_single_agent_group(parser_helper &helper);
        static ast::agent_group_list parse_agent_group_list(parser_helper &helper, bool parse_outer_pars = true);

        static ast::simple_agent_group_ptr parse_simple_agent_group(parser_helper &helper);
        static ast::forall_agent_group_ptr parse_forall_agent_group(parser_helper &helper, bool parse_outer_pars = true);
    };
}

#endif //EPDDL_AGENT_GROUPS_PARSER_H
