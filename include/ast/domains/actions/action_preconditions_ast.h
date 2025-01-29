#ifndef EPDDL_ACTION_PRECONDITIONS_AST_H
#define EPDDL_ACTION_PRECONDITIONS_AST_H

#include "../../ast_node.h"

namespace epddl::ast {
    class precondition;
    using precondition_ptr = std::unique_ptr<ast::precondition>;
}

#endif //EPDDL_ACTION_PRECONDITIONS_AST_H
