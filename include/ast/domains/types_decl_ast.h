#ifndef EPDDL_TYPES_DECL_AST_H
#define EPDDL_TYPES_DECL_AST_H

#include "../ast_node.h"
#include "../common/typed_elem_ast.h"

namespace epddl::ast {
    class domain_types;
    using domain_types_ptr = std::unique_ptr<domain_types>;

    class domain_types : public ast_node {
    public:
        explicit domain_types(typed_identifier_list types) :
                m_types{std::move(types)} {}

    private:
        const typed_identifier_list m_types;
    };
}

#endif //EPDDL_TYPES_DECL_AST_H
