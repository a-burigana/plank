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

#ifndef EPDDL_EVENT_CONDITIONS_AST_H
#define EPDDL_EVENT_CONDITIONS_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/relations_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class event_condition;
    class event_conditions;

    using event_condition_ptr   = std::shared_ptr<event_condition>;
    using event_conditions_ptr  = std::shared_ptr<event_conditions>;
    using event_condition_list  = std::list<event_condition_ptr>;
    using event_conditions_list = std::list<event_conditions_ptr>;

    class event_condition : public ast_node {
    public:
        explicit event_condition(info info, token_ptr cond) :
                ast_node{std::move(info)},
                m_cond{std::move(cond)} {}

        [[nodiscard]] const token_ptr &get_cond() const { return m_cond; }

    private:
        const token_ptr m_cond;
    };

    class event_conditions : public ast_node {
    public:
        explicit event_conditions(info info, variable_ptr event, event_condition_list conditions) :
                ast_node{std::move(info)},
                m_event{std::move(event)},
                m_conditions{std::move(conditions)} {
            add_child(m_event);
            for (const event_condition_ptr &cond : m_conditions) add_child(cond);
        }

        [[nodiscard]] const variable_ptr &get_event() const { return m_event; }
        [[nodiscard]] const event_condition_list &get_conditions() const { return m_conditions; }

    private:
        const variable_ptr m_event;
        const event_condition_list m_conditions;
    };
}
#endif //EPDDL_EVENT_CONDITIONS_AST_H
