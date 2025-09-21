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
    class agent_relation;
    class simple_relation;
    class and_relation;
    class forall_relation;

    using agent_relation_ptr  = std::shared_ptr<agent_relation>;
    using agent_relation_list = std::list<agent_relation_ptr>;

    using simple_relation_ptr = std::shared_ptr<simple_relation>;
    using and_relation_ptr    = std::shared_ptr<and_relation>;
    using forall_relation_ptr = std::shared_ptr<forall_relation>;

    using relation_ptr        = std::variant<simple_relation_ptr, and_relation_ptr, forall_relation_ptr>;
    using relation_list       = std::list<relation_ptr>;

    class agent_relation : public ast_node {
    public:
        explicit agent_relation(identifier_ptr obs_group, relation_ptr edges) :
                m_obs_group{std::move(obs_group)},
                m_edges{std::move(edges)} {}

    private:
        const identifier_ptr m_obs_group;
        const relation_ptr m_edges;
    };

    class simple_relation : public ast_node {
    public:
        explicit simple_relation(term node_1, term node_2) :
                m_node_1{std::move(node_1)},
                m_node_2{std::move(node_2)} {}

    private:
        const term m_node_1, m_node_2;
    };

    class and_relation : public ast_node {
    public:
        explicit and_relation(relation_list edges) :
                m_edges{std::move(edges)} {}

    private:
        const relation_list m_edges;
    };

    class forall_relation : public ast_node {
    public:
        explicit forall_relation(list_comprehension_ptr params, relation_ptr r) :
                m_params{std::move(params)},
                m_r{std::move(r)} {}

    private:
        const list_comprehension_ptr m_params;
        const relation_ptr m_r;
    };
}

#endif //EPDDL_RELATIONS_AST_H
