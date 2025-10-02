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
    using explicit_initial_state_ptr = std::shared_ptr<explicit_initial_state>;

    class explicit_initial_state : public ast_node {
    public:
        explicit explicit_initial_state(info info, identifier_list worlds, agent_relation_list relations, world_label_list labels,
                                        identifier_list designated) :
                ast_node{std::move(info)},
                m_worlds{std::move(worlds)},
                m_relations{std::move(relations)},
                m_labels{std::move(labels)},
                m_designated{std::move(designated)} {
            for (const identifier_ptr &id : m_worlds) add_child(id);
            for (const agent_relation_ptr &r_i : m_relations) add_child(r_i);
            for (const world_label_ptr &l : m_labels) add_child(l);
            for (const identifier_ptr &id : m_designated) add_child(id);
        }

        [[nodiscard]] const identifier_list &get_worlds() const { return m_worlds; }
        [[nodiscard]] const agent_relation_list &get_relations() const { return m_relations; }
        [[nodiscard]] const world_label_list &get_labels() const { return m_labels; }
        [[nodiscard]] const identifier_list &get_designated() const { return m_designated; }

    private:
        const identifier_list m_worlds;
        const agent_relation_list m_relations;
        const world_label_list m_labels;
        const identifier_list m_designated;
    };
}
#endif //EPDDL_EXPLICIT_INITITIAL_STATE_AST_H
