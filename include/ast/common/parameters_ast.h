#ifndef EPDDL_PARAMETERS_AST_H
#define EPDDL_PARAMETERS_AST_H

#include "../../ast/ast_node.h"
#include "formulas_ast.h"
#include <memory>

namespace epddl::ast {
    class parameters;
    using parameters_ptr = std::unique_ptr<ast::parameters>;

    class parameters : public ast_node {
    public:
        explicit parameters(int_list_comprehension_ptr params) :
                m_params{std::move(params)} {}

    private:
        const int_list_comprehension_ptr m_params;
    };
}

#endif //EPDDL_PARAMETERS_AST_H
