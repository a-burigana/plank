#ifndef EPDDL_ACT_TYPE_DECL_PARSER_H
#define EPDDL_ACT_TYPE_DECL_PARSER_H

#include "../../../ast/libraries/act_types/act_type_decl_ast.h"
#include "../../parser_helper.h"

namespace epddl {
    class act_type_decl_parser {
    public:
        static ast::action_type_ptr parse(parser_helper &helper);
    };
}

#endif //EPDDL_ACT_TYPE_DECL_PARSER_H
