#ifndef EPDDL_PREDICATES_DECL_PARSER_H
#define EPDDL_PREDICATES_DECL_PARSER_H

#include "../../ast/domains/predicates_decl_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class predicates_decl_parser {
    public:
        static ast::domain_predicates_ptr parse(parser_helper &parser);
        static ast::predicate_decl_ptr parse_predicate_decl(parser_helper &parser);
    };
}

#endif //EPDDL_PREDICATES_DECL_PARSER_H
