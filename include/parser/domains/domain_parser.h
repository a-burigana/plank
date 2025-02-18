#ifndef EPDDL_DOMAIN_PARSER_H
#define EPDDL_DOMAIN_PARSER_H

#include "../../ast/domains/domain_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class domain_parser {
    public:
        static ast::domain_ptr parse(parser_helper &helper);
        static ast::domain_item parse_domain_item(parser_helper &helper);
    };
}

#endif //EPDDL_DOMAIN_PARSER_H
