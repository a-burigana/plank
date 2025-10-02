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
        explicit agent_relation(info info, identifier_ptr obs_group, relation_ptr relation);

        [[nodiscard]] const identifier_ptr &get_obs_group() const { return m_obs_group; }
        [[nodiscard]] const relation_ptr &get_relation() const { return m_relation; }

    private:
        const identifier_ptr m_obs_group;
        const relation_ptr m_relation;
    };

    class simple_relation : public ast_node {
    public:
        explicit simple_relation(info info, term node_1, term node_2) :
                ast_node{std::move(info)},
                m_node_1{std::move(node_1)},
                m_node_2{std::move(node_2)} {
            std::visit([&](auto &&arg) { add_child(arg); }, m_node_1);
            std::visit([&](auto &&arg) { add_child(arg); }, m_node_2);
        }

        [[nodiscard]] const term &get_first_term() const { return m_node_1; }
        [[nodiscard]] const term &get_second_term() const { return m_node_2; }

    private:
        const term m_node_1, m_node_2;
    };

    class and_relation : public ast_node {
    public:
        explicit and_relation(info info, relation_list relation_list);

        [[nodiscard]] const relation_list &get_relation_list() const { return m_relation_list; }

    private:
        const relation_list m_relation_list;
    };

    class forall_relation : public ast_node {
    public:
        explicit forall_relation(info info, list_comprehension_ptr params, relation_ptr r);

        [[nodiscard]] const list_comprehension_ptr &get_params() const { return m_params; }
        [[nodiscard]] const relation_ptr &get_relation() const { return m_r; }
    private:
        const list_comprehension_ptr m_params;
        const relation_ptr m_r;
    };
}

#endif //EPDDL_RELATIONS_AST_H
