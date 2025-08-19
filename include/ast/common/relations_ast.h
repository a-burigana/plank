// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
    class simple_relation;
    class forall_relation;

    using edge_ptr   = std::shared_ptr<edge>;
    using edge_list  = std::list<edge_ptr>;
    using edge_label = std::variant<term, term_list>;
    
    using simple_relation_ptr = std::shared_ptr<simple_relation>;
    using forall_relation_ptr = std::shared_ptr<forall_relation>;

    using single_relation     = std::variant<simple_relation_ptr, forall_relation_ptr>;
    using relation_list       = std::list<single_relation>;

    using relations           = std::variant<single_relation, relation_list>;

    class edge : public ast_node {
    public:
        explicit edge(term node_1, term node_2) :
                m_node_1{std::move(node_1)},
                m_node_2{std::move(node_2)} {}

    private:
        const term m_node_1, m_node_2;
    };

    class simple_relation : public ast_node {
    public:
        explicit simple_relation(edge_label label, edge_list edges) :
                m_label{std::move(label)},
                m_edges{std::move(edges)} {}

    private:
        const edge_label m_label;
        const edge_list m_edges;
    };

    class forall_relation : public ast_node {
    public:
        explicit forall_relation(int_list_comprehension_ptr params, relations r) :
                m_params{std::move(params)},
                m_r{std::move(r)} {}

    private:
        const int_list_comprehension_ptr m_params;
        const relations m_r;
    };
}

#endif //EPDDL_RELATIONS_AST_H
