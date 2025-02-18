#ifndef EPDDL_OBSERVABILITY_GROUPS_DECL_PARSER_H
#define EPDDL_OBSERVABILITY_GROUPS_DECL_PARSER_H

#include "../../ast/libraries/observability_groups_decl_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class observability_groups_decl_parser {
    public:
        static ast::observability_groups_decl_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_OBSERVABILITY_GROUPS_DECL_PARSER_H
