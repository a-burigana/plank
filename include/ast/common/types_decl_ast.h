#ifndef EPDDL_TYPES_DECL_AST_H
#define EPDDL_TYPES_DECL_AST_H

#include "../ast_node.h"
#include "typed_elem_ast.h"

namespace epddl::ast {
    class types_decl;
    using types_decl_ptr = std::unique_ptr<types_decl>;

    class types_decl : public ast_node {
    public:
        explicit types_decl(typed_identifier_list types) :
                m_types{std::move(types)} {}

    private:
        const typed_identifier_list m_types;
    };
}

#endif //EPDDL_TYPES_DECL_AST_H
