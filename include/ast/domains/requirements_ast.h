#ifndef EPDDL_REQUIREMENTS_AST_H
#define EPDDL_REQUIREMENTS_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class domain_requirements;
    using domain_requirements_ptr = std::unique_ptr<domain_requirements>;
    using requirement_list        = std::list<requirement_ptr>;


    class domain_requirements : public ast_node {
    public:
        explicit domain_requirements(requirement_list reqs) :
                m_reqs{std::move(reqs)} {}

    private:
        const requirement_list m_reqs;
    };
}

#endif //EPDDL_REQUIREMENTS_AST_H
