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
#include "lists_ast.h"
#include <list>
#include <memory>
#include <optional>
#include <variant>

namespace epddl::ast {
    template<typename node_type> class agent_relation;
    template<typename node_type> class simple_relation;

    template<typename node_type>
    using agent_relation_ptr  = std::shared_ptr<agent_relation<node_type>>;
    template<typename node_type>
    using agent_relation_list = std::list<agent_relation_ptr<node_type>>;

    template<typename node_type>
    using simple_relation_ptr = std::shared_ptr<simple_relation<node_type>>;

    template<typename node_type>
    class agent_relation : public ast_node {
    public:
        explicit agent_relation(info info, identifier_ptr obs_type, list<simple_relation_ptr<node_type>> relation) :
                ast_node{std::move(info)},
                m_obs_type{std::move(obs_type)},
                m_relation{std::move(relation)} {
            add_child(m_obs_type);
            std::visit([&](auto &&arg) { add_child(arg); }, m_relation);
        }

        [[nodiscard]] const identifier_ptr &get_obs_type() const { return m_obs_type; }
        [[nodiscard]] const list<simple_relation_ptr<node_type>> &get_relation() const { return m_relation; }

    private:
        const identifier_ptr m_obs_type;
        const list<simple_relation_ptr<node_type>> m_relation;
    };

    template<typename node_type>
    class simple_relation : public ast_node {
    public:
        explicit simple_relation(info info, node_type node_1, node_type node_2) :
                ast_node{std::move(info)},
                m_node_1{std::move(node_1)},
                m_node_2{std::move(node_2)} {
            if constexpr (is_specialization<node_type, std::variant>::value) {
                std::visit([&](auto &&arg) { add_child(arg); }, m_node_1);
                std::visit([&](auto &&arg) { add_child(arg); }, m_node_2);
            } else {
                add_child(m_node_1);
                add_child(m_node_2);
            }
        }

        [[nodiscard]] const node_type &get_first_node() const { return m_node_1; }
        [[nodiscard]] const node_type &get_second_node() const { return m_node_2; }

    private:
        const node_type m_node_1, m_node_2;
    };
}

#endif //EPDDL_RELATIONS_AST_H
