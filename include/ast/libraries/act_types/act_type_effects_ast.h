#ifndef EPDDL_ACT_TYPE_EFFECTS_AST_H
#define EPDDL_ACT_TYPE_EFFECTS_AST_H

#include "../../tokens/tokens_ast.h"
#include "../../common/postconditions_ast.h"
#include <list>

namespace epddl::ast {
    using event_postconditions = std::pair<identifier_ptr, postconditions>;
    using event_postconditions_list = std::list<event_postconditions>;
}

#endif //EPDDL_ACT_TYPE_EFFECTS_AST_H
