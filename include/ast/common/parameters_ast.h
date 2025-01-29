#ifndef EPDDL_PARAMETERS_AST_H
#define EPDDL_PARAMETERS_AST_H

#include "../../ast/ast_node.h"
#include "typed_elem_ast.h"
#include <memory>

namespace epddl::ast {
    class parameters;
    using parameters_ptr = std::unique_ptr<ast::parameters>;

    class parameters : public ast_node {
    public:
        explicit parameters(formal_param_list params) :
                m_params{std::move(params)} {}

    private:
        const formal_param_list m_params;
    };
}

#endif //EPDDL_PARAMETERS_AST_H
