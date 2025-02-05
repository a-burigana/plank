#ifndef EPDDL_PROBLEM_AST_H
#define EPDDL_PROBLEM_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/requirements_decl_ast.h"
#include "../common/modalities_decl_ast.h"
#include "agent_groups_decl_ast.h"
#include "agents_decl_ast.h"
#include "problem_domain_ast.h"
#include "goal_decl_ast.h"
#include "initial_state_decl_ast.h"
#include "objects_decl_ast.h"
#include "static_predicates_decl_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class problem;
    using problem_ptr       = std::unique_ptr<ast::problem>;

    using problem_item      = std::variant<problem_domain_ptr, requirements_decl_ptr, objects_decl_ptr, agents_decl_ptr,
                                           agent_groups_decl_ptr, problem_predicates_ptr, modalities_decl_ptr,
                                           initial_state_ptr, goal_decl_ptr>;
    using problem_item_list = std::list<problem_item>;

    class problem : public ast_node {
    public:
        explicit problem(identifier_ptr name, problem_item_list items) :
                m_name{std::move(name)},
                m_items{std::move(items)} {}

    private:
        const identifier_ptr m_name;
        const problem_item_list m_items;
    };
}

#endif //EPDDL_PROBLEM_AST_H
