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

#ifndef EPDDL_ACTION_SIGNATURES_AST_H
#define EPDDL_ACTION_SIGNATURES_AST_H

#include "../../ast_node.h"
#include "../../tokens/tokens_ast.h"
#include "../../common/formulas_ast.h"
#include <memory>
#include <list>

namespace epddl::ast {
    class action_signature;
    class event_signature;

    using action_signature_ptr = std::shared_ptr<action_signature>;
    using event_signature_ptr  = std::shared_ptr<event_signature>;
    using event_signature_list = std::list<event_signature_ptr>;

    class action_signature : public ast_node {
    public:
        explicit action_signature(identifier_ptr name, event_signature_list events, bool is_basic) :
                m_name{std::move(name)},
                m_events{std::move(events)},
                m_is_basic{is_basic} {}

        [[nodiscard]] const identifier_ptr &get_name() const { return m_name; }
        [[nodiscard]] const event_signature_list &get_events() const { return m_events; }
        [[nodiscard]] bool is_basic() const { return m_is_basic; }

    private:
        const identifier_ptr m_name;
        const event_signature_list m_events;
        const bool m_is_basic;
    };

    class event_signature : public ast_node {
    public:
        explicit event_signature(identifier_ptr name, term_list params) :
                m_name{std::move(name)},
                m_params{std::move(params)} {}

        [[nodiscard]] const identifier_ptr &get_name() const { return m_name; }
        [[nodiscard]] const term_list &get_params() const { return m_params; }

    private:
        const identifier_ptr m_name;
        const term_list m_params;
    };
}

#endif //EPDDL_ACTION_SIGNATURES_AST_H
