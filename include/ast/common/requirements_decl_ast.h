#ifndef EPDDL_REQUIREMENTS_DECL_AST_H
#define EPDDL_REQUIREMENTS_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class requirements_decl;
    using requirements_decl_ptr = std::unique_ptr<requirements_decl>;
    using requirement_list      = std::list<requirement_ptr>;


    class requirements_decl : public ast_node {
    public:
        explicit requirements_decl(requirement_list reqs) :
                m_reqs{std::move(reqs)} {}

    private:
        const requirement_list m_reqs;
    };
}

#endif //EPDDL_REQUIREMENTS_DECL_AST_H
