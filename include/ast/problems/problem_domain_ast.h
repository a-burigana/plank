#ifndef EPDDL_PROBLEM_DOMAIN_AST_H
#define EPDDL_PROBLEM_DOMAIN_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class problem_domain;
    using problem_domain_ptr = std::unique_ptr<problem_domain>;

    class problem_domain : public ast_node {
    public:
        explicit problem_domain(identifier_ptr domain_name) :
                m_domain_name{std::move(domain_name)} {}

    private:
        const identifier_ptr m_domain_name;
    };
}
#endif //EPDDL_PROBLEM_DOMAIN_AST_H
