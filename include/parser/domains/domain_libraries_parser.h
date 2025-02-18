#ifndef EPDDL_DOMAIN_LIBRARIES_PARSER_H
#define EPDDL_DOMAIN_LIBRARIES_PARSER_H

#include "../../ast/domains/domain_libraries_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class act_type_libraries_parser {
    public:
        static ast::domain_libraries_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_DOMAIN_LIBRARIES_PARSER_H
