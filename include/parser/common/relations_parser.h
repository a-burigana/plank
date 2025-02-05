#ifndef EPDDL_RELATIONS_PARSER_H
#define EPDDL_RELATIONS_PARSER_H

#include "../parser_helper.h"
#include "../../ast/common/relations_ast.h"

namespace epddl {
    class relations_parser {
    public:
        static ast::relations parse_model_relations(parser_helper &helper);
        static ast::relations parse_relation(parser_helper &helper);

        static ast::single_relation parse_single_relation(parser_helper &helper);
        static ast::relation_list parse_relation_list(parser_helper &helper, bool parse_outer_pars = true);

        static ast::simple_relation_ptr parse_simple_relation(parser_helper &helper, bool parse_outer_pars = true);
        static ast::forall_relation_ptr parse_forall_relation(parser_helper &helper, bool parse_outer_pars = true);

        static ast::edge_ptr parse_edge(parser_helper &helper);
        static ast::edge_label parse_edge_label(parser_helper &helper);
    };
}

#endif //EPDDL_RELATIONS_PARSER_H
