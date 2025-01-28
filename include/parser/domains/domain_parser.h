#ifndef EPDDL_DOMAIN_PARSER_H
#define EPDDL_DOMAIN_PARSER_H

#include "../../ast/ast_types.h"
#include "../parser_helper.h"

namespace epddl {
    class domain_parser {
    public:
        static ast::domain_ptr parse(parser_helper &parser);
        static ast::domain_item parse_domain_item(parser_helper &parser);
    };
}

#endif //EPDDL_DOMAIN_PARSER_H
