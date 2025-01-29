#ifndef EPDDL_EXPRESSIONS_AST_H
#define EPDDL_EXPRESSIONS_AST_H

#include "../../ast_node.h"
#include "../../common/formulas_ast.h"
#include "../../common/postconditions_ast.h"
#include <list>
#include <variant>

namespace epddl::ast {
    using expression      = std::variant<identifier_ptr, variable_ptr, predicate_ptr, literal_ptr, formula_ptr, postconditions>;
    using expression_list = std::list<expression>;
}

#endif //EPDDL_EXPRESSIONS_AST_H
