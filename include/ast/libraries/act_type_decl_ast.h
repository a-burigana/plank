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

#ifndef EPDDL_ACT_TYPE_DECL_AST_H
#define EPDDL_ACT_TYPE_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/relations_ast.h"
#include "event_conditions_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class action_type;
    using action_type_ptr = std::shared_ptr<action_type>;

    class action_type : public ast_node {
    public:
        explicit action_type(info info, identifier_ptr name, variable_list events, identifier_list obs_groups,
                             agent_relation_list<variable_ptr> relations, variable_list designated,
                             std::optional<act_type_event_conditions_ptr> conditions) :
                ast_node{std::move(info)},
                m_name{std::move(name)},
                m_events{std::move(events)},
                m_obs_groups{std::move(obs_groups)},
                m_relations{std::move(relations)},
                m_designated{std::move(designated)},
                m_conditions{std::move(conditions)} {
            add_child(m_name);
            for (const variable_ptr &var : m_events) add_child(var);
            for (const identifier_ptr &id : m_obs_groups) add_child(id);
            for (const agent_relation_ptr<variable_ptr> &q_i : m_relations) add_child(q_i);
            for (const variable_ptr &var : m_designated) add_child(var);
            if (m_conditions.has_value()) add_child(*m_conditions);
        }

        [[nodiscard]] const identifier_ptr &get_name() const { return m_name; }
        [[nodiscard]] const variable_list &get_events() const { return m_events; }
        [[nodiscard]] const identifier_list &get_obs_groups() const { return m_obs_groups; }
        [[nodiscard]] const agent_relation_list<variable_ptr> &get_relations() const { return m_relations; }
        [[nodiscard]] const variable_list &get_designated() const { return m_designated; }
        [[nodiscard]] const std::optional<act_type_event_conditions_ptr> &get_conditions() const { return m_conditions; }

    private:
        const identifier_ptr m_name;
        const variable_list m_events;
        const identifier_list m_obs_groups;
        const agent_relation_list<variable_ptr> m_relations;
        const variable_list m_designated;
        const std::optional<act_type_event_conditions_ptr> m_conditions;
    };
}

#endif //EPDDL_ACT_TYPE_DECL_AST_H
