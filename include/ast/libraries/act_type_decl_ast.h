#ifndef EPDDL_ACT_TYPE_DECL_AST_H
#define EPDDL_ACT_TYPE_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/relations_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class action_type;
    using action_type_ptr = std::unique_ptr<action_type>;

    class action_type : public ast_node {
    public:
        explicit action_type(identifier_ptr name, identifier_list events, relations relations, identifier_list designated) :
                m_name{std::move(name)},
                m_events{std::move(events)},
                m_relations{std::move(relations)},
                m_designated{std::move(designated)} {}

    private:
        const identifier_ptr m_name;
        const identifier_list m_events;
        const relations m_relations;
        const identifier_list m_designated;
    };
}

#endif //EPDDL_ACT_TYPE_DECL_AST_H
