#ifndef EPDDL_MODALITIES_DECL_AST_H
#define EPDDL_MODALITIES_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class modalities_decl;
    using modalities_decl_ptr = std::unique_ptr<ast::modalities_decl>;
    using modality_name_list  = std::list<modality_name_ptr>;


    class modalities_decl : public ast_node {
    public:
        explicit modalities_decl(modality_name_list mods) :
                m_mods{std::move(mods)} {}

    private:
        const modality_name_list m_mods;
    };
}

#endif //EPDDL_MODALITIES_DECL_AST_H
