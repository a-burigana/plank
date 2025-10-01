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

#ifndef EPDDL_AGENT_GROUPS_DECL_AST_H
#define EPDDL_AGENT_GROUPS_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/formulas_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class agent_group_decl;
    class agent_groups_decl;

    using agent_group_decl_ptr   = std::shared_ptr<agent_group_decl>;
    using agent_group_decl_list  = std::list<agent_group_decl_ptr>;
    using agent_groups_decl_ptr  = std::shared_ptr<agent_groups_decl>;

    class agent_groups_decl : public ast_node {
    public:
        explicit agent_groups_decl(info info, agent_group_decl_list agent_groups) :
                ast_node{std::move(info)},
                m_agent_groups{std::move(agent_groups)} {}

    private:
        const agent_group_decl_list m_agent_groups;
    };

    class agent_group_decl : public ast_node {
    public:
        explicit agent_group_decl(info info, identifier_ptr group_name, list_ptr agents) :
                ast_node{std::move(info)},
                m_group_name{std::move(group_name)},
                m_agents{std::move(agents)} {}

    private:
        const identifier_ptr m_group_name;
        const list_ptr m_agents;
    };
}

#endif //EPDDL_AGENT_GROUPS_DECL_AST_H
