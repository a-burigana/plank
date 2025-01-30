#ifndef EPDDL_AGENTS_DECL_AST_H
#define EPDDL_AGENTS_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class agents_decl;
    using agents_decl_ptr  = std::unique_ptr<agents_decl>;

    class agents_decl : public ast_node {
    public:
        explicit agents_decl(ident_list agents) :
                m_agents{std::move(agents)} {}

    private:
        const ident_list m_agents;
    };
}

#endif //EPDDL_AGENTS_DECL_AST_H
