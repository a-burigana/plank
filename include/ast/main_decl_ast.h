#ifndef EPDDL_MAIN_DECL_AST_H
#define EPDDL_MAIN_DECL_AST_H

#include "domains/domain_ast.h"
#include "libraries/act_type_library_ast.h"
#include "problems/problem_ast.h"
#include <memory>
#include <variant>

namespace epddl::ast {
    using main_decl = std::variant<domain_ptr, act_type_library_ptr, problem_ptr>;
}

#endif //EPDDL_MAIN_DECL_AST_H
