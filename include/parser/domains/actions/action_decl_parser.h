#ifndef EPDDL_ACTION_DECL_PARSER_H
#define EPDDL_ACTION_DECL_PARSER_H

#include "../../../ast/ast_types.h"
#include "../../parser_helper.h"

namespace epddl {
    class action_decl_parser {
    public:
        static ast::action_ptr parse(parser_helper &parser);
    };
}

#endif //EPDDL_ACTION_DECL_PARSER_H
