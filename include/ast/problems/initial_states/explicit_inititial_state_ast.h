#ifndef EPDDL_EXPLICIT_INITITIAL_STATE_AST_H
#define EPDDL_EXPLICIT_INITITIAL_STATE_AST_H

#include "../../ast_node.h"
#include "../../tokens/tokens_ast.h"
#include "../../common/relations_ast.h"
#include "../labels_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class explicit_initial_state;
    using explicit_initial_state_ptr = std::unique_ptr<explicit_initial_state>;

    class explicit_initial_state : public ast_node {
    public:
        explicit explicit_initial_state(identifier_list worlds, relations relations, world_label_list labels,
                                        identifier_list designated) :
                m_worlds{std::move(worlds)},
                m_relations{std::move(relations)},
                m_labels{std::move(labels)},
                m_designated{std::move(designated)} {}

    private:
        const identifier_list m_worlds;
        const relations m_relations;
        const world_label_list m_labels;
        const identifier_list m_designated;
    };
}
#endif //EPDDL_EXPLICIT_INITITIAL_STATE_AST_H
