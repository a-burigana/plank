#ifndef EPDDL_PROBLEM_DOMAIN_PARSER_H
#define EPDDL_PROBLEM_DOMAIN_PARSER_H

#include "../../ast/problems/problem_domain_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class problem_domain_parser {
    public:
        static ast::problem_domain_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_PROBLEM_DOMAIN_PARSER_H
