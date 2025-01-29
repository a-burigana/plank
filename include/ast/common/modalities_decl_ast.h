#ifndef EPDDL_MODALITIES_DECL_AST_H
#define EPDDL_MODALITIES_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include <memory>
#include <list>

namespace epddl::ast {
    class domain_modalities;
    using domain_modalities_ptr     = std::unique_ptr<ast::domain_modalities>;
    using modality_name_list        = std::list<modality_name_ptr>;


    class domain_modalities : public ast_node {
    public:
        explicit domain_modalities(modality_name_list mods) :
                m_mods{std::move(mods)} {}

    private:
        const modality_name_list m_mods;
    };
}

#endif //EPDDL_MODALITIES_DECL_AST_H
