#ifndef EPDDL_AGENT_GROUPS_DECL_AST_H
#define EPDDL_AGENT_GROUPS_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class agent_groups_decl;
    using agent_groups_decl_ptr  = std::unique_ptr<agent_groups_decl>;

    class agent_groups_decl : public ast_node {
    public:
        explicit agent_groups_decl(ident_list agent_groups) :
                m_agent_groups{std::move(agent_groups)} {}

    private:
        const ident_list m_agent_groups;
    };
}

#endif //EPDDL_AGENT_GROUPS_DECL_AST_H
