#ifndef EPDDL_DOMAIN_LIBRARIES_AST_H
#define EPDDL_DOMAIN_LIBRARIES_AST_H

#include "../ast_node.h"
#include "../common/typed_elem_ast.h"
#include <memory>

namespace epddl::ast {
    class domain_libraries;
    using domain_libraries_ptr = std::unique_ptr<ast::domain_libraries>;

    class domain_libraries : public ast_node {
    public:
        explicit domain_libraries(identifier_list libs) :
                m_libs{std::move(libs)} {}

    private:
        const identifier_list m_libs;
    };
}

#endif //EPDDL_DOMAIN_LIBRARIES_AST_H
