#ifndef EPDDL_OBJECTS_DECL_AST_H
#define EPDDL_OBJECTS_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class objects_decl;
    using objects_decl_ptr  = std::unique_ptr<objects_decl>;

    class objects_decl : public ast_node {
    public:
        explicit objects_decl(ident_list objects) :
                m_objects{std::move(objects)} {}

    private:
        const ident_list m_objects;
    };
}

#endif //EPDDL_OBJECTS_DECL_AST_H
