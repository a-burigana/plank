#ifndef EPDDL_ACTION_PRECONDITIONS_PARSER_H
#define EPDDL_ACTION_PRECONDITIONS_PARSER_H

#include "../../../ast/domains/actions/action_preconditions_ast.h"
#include "../../parser_helper.h"

namespace epddl {
    class action_preconditions_parser {
    public:
        static ast::formula_ptr parse(parser_helper &parser);
    };
}

#endif //EPDDL_ACTION_PRECONDITIONS_PARSER_H
