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

#ifndef EPDDL_PROBLEM_AST_H
#define EPDDL_PROBLEM_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/requirements_decl_ast.h"
#include "agent_groups_decl_ast.h"
#include "agents_decl_ast.h"
#include "problem_domain_ast.h"
#include "goal_decl_ast.h"
#include "init/initial_state_decl_ast.h"
#include "objects_decl_ast.h"
#include "init/static_init_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class problem;
    using problem_ptr       = std::shared_ptr<ast::problem>;

    using problem_item      = std::variant<requirements_decl_ptr, objects_decl_ptr, agents_decl_ptr,
                                           agent_groups_decl_ptr, initial_state_ptr, static_init_ptr, goal_decl_ptr>;
    using problem_item_list = std::list<problem_item>;

    class problem : public ast_node {
    public:
        explicit problem(info info, identifier_ptr name, problem_domain_ptr domain, problem_item_list items) :
                ast_node{std::move(info)},
                m_name{std::move(name)},
                m_domain{std::move(domain)},
                m_items{std::move(items)} {
            add_children({m_name, m_domain});
            for (const problem_item &item : m_items)
                std::visit([&](auto &&arg) { add_child(arg); }, item);
        }

        [[nodiscard]] const identifier_ptr    &get_name()  const { return m_name;  }
        [[nodiscard]] const problem_item_list &get_items() const { return m_items; }

    private:
        const identifier_ptr m_name;
        const problem_domain_ptr m_domain;
        const problem_item_list m_items;
    };
}

#endif //EPDDL_PROBLEM_AST_H
