#ifndef EPDDL_OBSERVABILITY_GROUPS_DECL_AST_H
#define EPDDL_OBSERVABILITY_GROUPS_DECL_AST_H

#include "../ast_node.h"
#include "../common/typed_elem_ast.h"
#include <memory>

namespace epddl::ast {
    class observability_groups_decl;
    using observability_groups_decl_ptr = std::unique_ptr<observability_groups_decl>;

    class observability_groups_decl : public ast_node {
    public:
        explicit observability_groups_decl(identifier_list obs_groups_names) :
                m_obs_groups_names{std::move(obs_groups_names)} {}

    private:
        const identifier_list m_obs_groups_names;
    };
}

#endif //EPDDL_OBSERVABILITY_GROUPS_DECL_AST_H
