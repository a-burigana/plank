#ifndef EPDDL_ACT_TYPE_EFFECTS_PARSER_H
#define EPDDL_ACT_TYPE_EFFECTS_PARSER_H

#include "../../parser_helper.h"
#include "../../../ast/libraries/act_types/act_type_effects_ast.h"

namespace epddl {
    class act_type_effects_parser {
    public:
        static ast::event_postconditions_list parse(parser_helper &helper);
        static ast::event_postconditions parse_event_postcondition(parser_helper &helper);
    };
}

#endif //EPDDL_ACT_TYPE_EFFECTS_PARSER_H
