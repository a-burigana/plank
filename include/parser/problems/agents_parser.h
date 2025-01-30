#ifndef EPDDL_AGENTS_PARSER_H
#define EPDDL_AGENTS_PARSER_H

#include "../../ast/problems/agents_decl_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class agents_parser {
    public:
        static ast::agents_decl_ptr parse(parser_helper &helper);
    };
}


#endif //EPDDL_AGENTS_PARSER_H
