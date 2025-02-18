#ifndef EPDDL_MAIN_DECL_PARSER_H
#define EPDDL_MAIN_DECL_PARSER_H

#include "../ast/main_decl_ast.h"
#include "parser_helper.h"

namespace epddl::parser {
    class main_decl_parser {
    public:
        static ast::main_decl parse(parser_helper &helper);
    };
}

#endif //EPDDL_MAIN_DECL_PARSER_H
