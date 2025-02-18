#ifndef EPDDL_EXPLICIT_INITIAL_STATE_PARSER_H
#define EPDDL_EXPLICIT_INITIAL_STATE_PARSER_H

#include "../../../ast/problems/initial_states/explicit_inititial_state_ast.h"
#include "../../../ast/tokens/tokens_ast.h"
#include "../../../ast/problems/labels_ast.h"
#include "../../parser_helper.h"

namespace epddl::parser {
    class explicit_initial_state_parser {
    public:
        static ast::explicit_initial_state_ptr parse(parser_helper &helper);

        static ast::identifier_list parse_worlds(parser_helper &helper);
        static ast::world_label_ptr parse_world_label(parser_helper &helper);
        static ast::world_label_list parse_labels(parser_helper &helper);
        static ast::identifier_list parse_designated(parser_helper &helper);
    };
}

#endif //EPDDL_EXPLICIT_INITIAL_STATE_PARSER_H
