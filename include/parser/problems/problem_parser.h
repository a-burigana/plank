#ifndef EPDDL_PROBLEM_PARSER_H
#define EPDDL_PROBLEM_PARSER_H

#include "../../ast/problems/problem_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class problem_parser {
    public:
        static ast::problem_ptr parse(parser_helper &helper);
        static ast::problem_item parse_problem_item(parser_helper &helper);
    };
}

#endif //EPDDL_PROBLEM_PARSER_H
