#ifndef EPDDL_INITIAL_STATE_DECL_AST_H
#define EPDDL_INITIAL_STATE_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/relations_ast.h"
#include "labels_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class initial_state;
    using initial_state_ptr = std::unique_ptr<initial_state>;

    class initial_state : public ast_node {
    public:
        explicit initial_state(identifier_list worlds, agent_relation_list relations, world_label_list labels,
                               identifier_list designated) :
            m_worlds{std::move(worlds)},
            m_relations{std::move(relations)},
            m_labels{std::move(labels)},
            m_designated{std::move(designated)} {}

    private:
        const identifier_list m_worlds;
        const agent_relation_list m_relations;
        const world_label_list m_labels;
        const identifier_list m_designated;
    };
}

#endif //EPDDL_INITIAL_STATE_DECL_AST_H
