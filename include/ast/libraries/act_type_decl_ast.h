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
#include <list>
#include <memory>

namespace epddl::ast {
    class action_type;
    using action_type_ptr = std::shared_ptr<action_type>;

    class action_type : public ast_node {
    public:
        explicit action_type(identifier_ptr name, identifier_list obs_groups, variable_list events, agent_relation_list relations, variable_list designated) :
                m_name{std::move(name)},
                m_obs_groups{std::move(obs_groups)},
                m_events{std::move(events)},
                m_relations{std::move(relations)},
                m_designated{std::move(designated)} {}

    private:
        const identifier_ptr m_name;
        const identifier_list m_obs_groups;
        const variable_list m_events;
        const agent_relation_list m_relations;
        const variable_list m_designated;
    };
}

#endif //EPDDL_ACT_TYPE_DECL_AST_H
