#ifndef EPDDL_DOMAIN_AST_H
#define EPDDL_DOMAIN_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "act_type_libraries_ast.h"
#include "../common/requirements_decl_ast.h"
#include "types_decl_ast.h"
#include "predicates_decl_ast.h"
#include "../common/modalities_decl_ast.h"
#include "actions/action_decl_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class domain;
    using domain_ptr       = std::unique_ptr<ast::domain>;
    using domain_item      = std::variant<domain_libraries_ptr, requirements_decl_ptr, domain_types_ptr,
                                          domain_predicates_ptr, modalities_decl_ptr, action_ptr>;
    using domain_item_list = std::list<domain_item>;

    class domain : public ast_node {
    public:
        explicit domain(identifier_ptr name, domain_item_list items) :
                m_name{std::move(name)},
                m_items{std::move(items)} {}

    private:
        const identifier_ptr m_name;
        const domain_item_list m_items;
    };
}

#endif //EPDDL_DOMAIN_AST_H
