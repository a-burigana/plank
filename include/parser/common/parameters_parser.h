#ifndef EPDDL_PARAMETERS_PARSER_H
#define EPDDL_PARAMETERS_PARSER_H

#include "../../ast/common/parameters_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class parameters_parser {
    public:
        static ast::parameters_ptr parse(parser_helper &parser);
    };
}

#endif //EPDDL_PARAMETERS_PARSER_H
