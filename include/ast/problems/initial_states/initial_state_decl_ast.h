#ifndef EPDDL_INITIAL_STATE_DECL_AST_H
#define EPDDL_INITIAL_STATE_DECL_AST_H

#include "explicit_inititial_state_ast.h"
#include "finitary_s5_theory_ast.h"
#include <variant>

namespace epddl::ast {
    using initial_state = std::variant<explicit_initial_state_ptr, finitary_s5_theory_ptr>;
}

#endif //EPDDL_INITIAL_STATE_DECL_AST_H
