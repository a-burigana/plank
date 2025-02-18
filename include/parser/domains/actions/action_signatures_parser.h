#ifndef EPDDL_ACTION_SIGNATURES_PARSER_H
#define EPDDL_ACTION_SIGNATURES_PARSER_H

#include "../../../ast/domains/actions/action_signatures_ast.h"
#include "../../parser_helper.h"

namespace epddl::parser {
    class action_signatures_parser {
    public:
        static ast::action_signature_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_ACTION_SIGNATURES_PARSER_H
