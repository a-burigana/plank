#ifndef EPDDL_LABELS_AST_H
#define EPDDL_LABELS_AST_H

#include "../tokens/tokens_ast.h"
#include "../common/formulas_ast.h"
#include <list>
#include <memory>
#include <utility>

namespace epddl::ast {
    class world_label;
    using world_label_ptr  = std::unique_ptr<world_label>;
    using world_label_list = std::list<world_label_ptr>;

    class world_label : public ast_node {
    public:
        explicit world_label(identifier_ptr world_name, predicate_list predicates) :
            m_world_name{std::move(world_name)},
            m_predicates{std::move(predicates)} {}

    private:
        const identifier_ptr m_world_name;
        const predicate_list m_predicates;
    };
}

#endif //EPDDL_LABELS_AST_H
