#ifndef EPDDL_ACT_TYPE_DESIGNATED_PARSER_H
#define EPDDL_ACT_TYPE_DESIGNATED_PARSER_H

#include "../../parser_helper.h"
#include "../../../ast/tokens/tokens_ast.h"

namespace epddl {
    class act_type_designated_parser {
    public:
        static ast::ident_list parse(parser_helper &helper);
    };
}

#endif //EPDDL_ACT_TYPE_DESIGNATED_PARSER_H
