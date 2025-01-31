#ifndef EPDDL_RELATIONS_PARSER_H
#define EPDDL_RELATIONS_PARSER_H

#include "../parser_helper.h"
#include "../../ast/common/relations_ast.h"

namespace epddl {
    class relations_parser {
    public:
        static ast::edge_ptr parse_edge(parser_helper &helper);
        static ast::edge_label parse_edge_label(parser_helper &helper);

        static ast::simple_agent_relation_ptr parse_simple_agent_relation(parser_helper &helper, bool parse_outer_pars = true);
        static ast::forall_agent_relation_ptr parse_forall_agent_relation(parser_helper &helper, bool parse_outer_pars = true);

        static ast::agent_relation parse_agent_relation(parser_helper &helper);
        static ast::agent_relation_list parse_agent_relation_list(parser_helper &helper);

        static ast::set_comprehension_ptr parse_set_comprehension(parser_helper &helper);
    };
}

#endif //EPDDL_RELATIONS_PARSER_H
