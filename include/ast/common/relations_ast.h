#ifndef EPDDL_RELATIONS_AST_H
#define EPDDL_RELATIONS_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "formulas_ast.h"
#include <list>
#include <memory>
#include <optional>
#include <variant>

namespace epddl::ast {
    class edge;
//    class int_list_comprehension;
    class simple_agent_relation;
    class forall_agent_relation;

    using edge_ptr   = std::unique_ptr<edge>;
    using edge_list  = std::list<edge_ptr>;
    using edge_label = std::variant<term, term_list>;

//    using int_list_comprehension_ptr     = std::unique_ptr<int_list_comprehension>;
//    using int_list_comprehension_list    = std::list<int_list_comprehension_ptr>;

    using simple_agent_relation_ptr = std::unique_ptr<simple_agent_relation>;
    using forall_agent_relation_ptr = std::unique_ptr<forall_agent_relation>;
    using agent_relation            = std::variant<simple_agent_relation_ptr, forall_agent_relation_ptr>;
    using agent_relation_list       = std::list<agent_relation>;

    class edge : public ast_node {
    public:
        explicit edge(term node_1, term node_2) :
                m_node_1{std::move(node_1)},
                m_node_2{std::move(node_2)} {}

    private:
        const term m_node_1, m_node_2;
    };

//    class int_list_comprehension : public ast_node {
//    public:
//        explicit int_list_comprehension(variable_ptr var, std::optional<ident_list> list) :
//            m_var{std::move(var)},
//            m_list{std::move(list)} {}
//
//    private:
//        const variable_ptr m_var;
//        const std::optional<ident_list> m_list;
//    };

    class simple_agent_relation : public ast_node {
    public:
        explicit simple_agent_relation(edge_label label, edge_list edges) :
                m_label{std::move(label)},
                m_edges{std::move(edges)} {}

    private:
        const edge_label m_label;
        const edge_list m_edges;
    };

    class forall_agent_relation : public ast_node {
    public:
        explicit forall_agent_relation(int_list_comprehension_ptr params, simple_agent_relation_ptr relation) :
                m_params{std::move(params)},
                m_relation{std::move(relation)} {}

    private:
        const int_list_comprehension_ptr m_params;
        const simple_agent_relation_ptr m_relation;
    };
}

#endif //EPDDL_RELATIONS_AST_H
