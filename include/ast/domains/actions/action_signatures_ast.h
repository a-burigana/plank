#ifndef EPDDL_ACTION_SIGNATURES_AST_H
#define EPDDL_ACTION_SIGNATURES_AST_H

#include "../../ast_node.h"
#include "../../tokens/tokens_ast.h"
#include "expressions_ast.h"

namespace epddl::ast {
    class action_signature;
    using action_signature_ptr      = std::unique_ptr<ast::action_signature>;

    class action_signature : public ast_node {
    public:
        explicit action_signature(identifier_ptr name, expression_list assign_list) :
                m_name{std::move(name)},
                m_assign_list{std::move(assign_list)} {}

    private:
        const identifier_ptr m_name;
        const expression_list m_assign_list;
    };
}

#endif //EPDDL_ACTION_SIGNATURES_AST_H
