#ifndef EPDDL_EXPRESSIONS_PARSER_H
#define EPDDL_EXPRESSIONS_PARSER_H

#include "../../../ast/ast.h"
#include "../../parser_helper.h"

namespace epddl {
    class expressions_parser {
    public:
        static ast::expression parse(parser_helper &parser);

        static ast::expression parse_object_expr(parser_helper &parser);
        static ast::expression parse_agent_expr(parser_helper &parser);
        static ast::expression parse_agent_group_expr(parser_helper &parser);
        static ast::expression parse_predicate_expr(parser_helper &parser);
        static ast::expression parse_literal_expr(parser_helper &parser);
        static ast::expression parse_formula_expr(parser_helper &parser);
        static ast::expression parse_effects_expr(parser_helper &parser);
    };
}

#endif //EPDDL_EXPRESSIONS_PARSER_H
