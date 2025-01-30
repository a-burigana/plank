#ifndef EPDDL_ACTION_PRECONDITIONS_AST_H
#define EPDDL_ACTION_PRECONDITIONS_AST_H

#include "../../ast_node.h"
#include "../../tokens/tokens_ast.h"
#include "../../common/formulas_ast.h"

namespace epddl::ast {
    class precondition;
    using precondition_ptr = std::unique_ptr<ast::precondition>;

    using event_precondition      = std::pair<identifier_ptr, formula_ptr>;
    using event_precondition_list = std::list<event_precondition>;
}

#endif //EPDDL_ACTION_PRECONDITIONS_AST_H
