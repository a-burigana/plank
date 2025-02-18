#ifndef EPDDL_REQUIREMENTS_PARSER_H
#define EPDDL_REQUIREMENTS_PARSER_H

#include "../../ast/common/requirements_decl_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class requirements_parser {
    public:
        static ast::requirements_decl_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_REQUIREMENTS_PARSER_H
