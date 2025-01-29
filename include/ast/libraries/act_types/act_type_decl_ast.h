#ifndef EPDDL_ACT_TYPE_DECL_AST_H
#define EPDDL_ACT_TYPE_DECL_AST_H

#include "../../ast_node.h"
#include "../../tokens/tokens_ast.h"
#include "../../common/parameters_ast.h"
#include "../../common/typed_elem_ast.h"
#include "act_type_preconditions_ast.h"
#include "act_type_effects_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class action_type;
    using action_type_ptr = std::unique_ptr<action_type>;

    class action_type : public ast_node {
    public:
        explicit action_type(identifier_ptr name, parameters_ptr params, ident_list events,
//                             relations relations,
                             ident_list designated, event_precondition_list preconditions,
                             event_postconditions_list postconditions) :
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_events{std::move(events)},
//                m_relations{std::move(relations)},
                m_designated{std::move(designated)},
                m_preconditions{std::move(preconditions)},
                m_postconditions{std::move(postconditions)} {}

    private:
        const identifier_ptr m_name;
        const parameters_ptr m_params;
        const ident_list m_events;
//        const relations m_relations;
        const ident_list m_designated;
        const event_precondition_list m_preconditions;
        const event_postconditions_list m_postconditions;
    };
}

#endif //EPDDL_ACT_TYPE_DECL_AST_H
