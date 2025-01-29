#ifndef EPDDL_REQUIREMENTS_PARSER_H
#define EPDDL_REQUIREMENTS_PARSER_H

#include "../../ast/domains/requirements_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class requirements_parser {
    public:
        static ast::domain_requirements_ptr parse(parser_helper &parser);
    };
}

#endif //EPDDL_REQUIREMENTS_PARSER_H
