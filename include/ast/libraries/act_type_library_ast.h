#ifndef EPDDL_ACT_TYPE_LIBRARY_AST_H
#define EPDDL_ACT_TYPE_LIBRARY_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/requirements_decl_ast.h"
#include "../common/modalities_decl_ast.h"
#include "observability_groups_decl_ast.h"
#include "act_types/act_type_decl_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class act_type_library;
    using act_type_library_ptr       = std::unique_ptr<ast::act_type_library>;
    using act_type_library_item      = std::variant<requirements_decl_ptr, modalities_decl_ptr, observability_groups_decl_ptr, action_type_ptr>;
    using act_type_library_item_list = std::list<act_type_library_item>;

    class act_type_library : public ast_node {
    public:
        explicit act_type_library(identifier_ptr name, act_type_library_item_list items) :
                m_name{std::move(name)},
                m_items{std::move(items)} {}

    private:
        const identifier_ptr m_name;
        const act_type_library_item_list m_items;
    };
}

#endif //EPDDL_ACT_TYPE_LIBRARY_AST_H
