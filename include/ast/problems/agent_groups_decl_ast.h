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
    class simple_agent_group;
    class forall_agent_group;
    class agent_group_decl;
    class agent_groups_decl;

    using simple_agent_group_ptr = std::shared_ptr<simple_agent_group>;
    using forall_agent_group_ptr = std::shared_ptr<forall_agent_group>;
    using single_agent_group     = std::variant<simple_agent_group_ptr, forall_agent_group_ptr>;

    using agent_group_list       = std::list<single_agent_group>;
    using agent_group            = std::variant<single_agent_group, agent_group_list>;

    using agent_group_decl_ptr   = std::shared_ptr<agent_group_decl>;
    using agent_group_decl_list  = std::list<agent_group_decl_ptr>;

    using agent_groups_decl_ptr  = std::shared_ptr<agent_groups_decl>;

    class simple_agent_group : public ast_node {
    public:
        explicit simple_agent_group(term_list agents) :
            m_agents{std::move(agents)} {}

    private:
        const term_list m_agents;
    };

    class forall_agent_group : public ast_node {
    public:
        explicit forall_agent_group(list_comprehension_ptr params, agent_group agents) :
                m_params{std::move(params)},
                m_agents{std::move(agents)} {}

    private:
        const list_comprehension_ptr m_params;
        const agent_group m_agents;
    };

    class agent_group_decl : public ast_node {
    public:
        explicit agent_group_decl(identifier_ptr group_name, agent_group agents) :
                m_group_name{std::move(group_name)},
                m_agents{std::move(agents)} {}

    private:
        const identifier_ptr m_group_name;
        const agent_group m_agents;
    };

    class agent_groups_decl : public ast_node {
    public:
        explicit agent_groups_decl(agent_group_decl_list agent_groups) :
            m_agent_groups{std::move(agent_groups)} {}

    private:
        const agent_group_decl_list m_agent_groups;
    };
}

#endif //EPDDL_AGENT_GROUPS_DECL_AST_H
