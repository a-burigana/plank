#ifndef EPDDL_STATIC_PREDICATES_DECL_PARSER_H
#define EPDDL_STATIC_PREDICATES_DECL_PARSER_H

#include "../parser_helper.h"
#include "../../ast/problems/static_predicates_decl_ast.h"

namespace epddl {
    class static_predicates_decl_parser {
    public:
        static ast::problem_predicates_ptr parse(parser_helper &parser);
        static ast::static_predicate_decl_ptr parse_static_predicate_decl(parser_helper &parser);
    };
}

#endif //EPDDL_STATIC_PREDICATES_DECL_PARSER_H
