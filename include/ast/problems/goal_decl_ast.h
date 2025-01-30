#ifndef EPDDL_GOAL_DECL_AST_H
#define EPDDL_GOAL_DECL_AST_H

#include "../ast_node.h"
#include "../common/formulas_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class goal_decl;
    using goal_decl_ptr  = std::unique_ptr<goal_decl>;

    class goal_decl : public ast_node {
    public:
        explicit goal_decl(formula_ptr goal) :
                m_goal{std::move(goal)} {}

    private:
        const formula_ptr m_goal;
    };
}

#endif //EPDDL_GOAL_DECL_AST_H
