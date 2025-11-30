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

#ifndef EPDDL_EVENTS_CONTEXT_H
#define EPDDL_EVENTS_CONTEXT_H

#include "context_types.h"
#include "entities_context.h"
#include "context_utils.h"

namespace epddl::type_checker {
    class events_context {
    public:
        events_context() = default;

        [[nodiscard]] const signature_map &get_event_signatures() const { return m_event_signatures; }
        [[nodiscard]] const ast_node_map<ast::event_ptr> &get_events_map() const { return m_events_map; }

        [[nodiscard]] const ast::event_ptr &get_event_decl(const ast::identifier_ptr &id) const {
            assert_declared_event(id);
            return m_events_map.at(id->get_token().get_lexeme());
        }

        [[nodiscard]] typed_var_list get_formal_param_types_event(const ast::identifier_ptr &id) const {
            assert_declared_event(id);
            return m_event_signatures.at(id->get_token().get_lexeme());
        }

        void assert_declared_event(const ast::identifier_ptr &id) const {
            if (context_utils::is_declared(id, m_event_signatures)) return;

            throw EPDDLException(id->get_info(), "Use of undeclared event name '" + id->get_token().get_lexeme() + "'.");
        }

        void assert_not_declared_event(const ast::identifier_ptr &id) const {
            if (not context_utils::is_declared(id, m_event_signatures)) return;
            const ast::info &previous_info = m_events_map.at(id->get_token().get_lexeme())->get_info();

            throw EPDDLException(id->get_info(), "Redeclaration of event '" + id->get_token().get_lexeme() +
                                                 "'. Previous declaration at (" + std::to_string(previous_info.m_row) + ":" +
                                                 std::to_string(previous_info.m_col) + ").");
        }

        void add_decl_event(entities_context &entities_context, const ast::event_ptr &event, const type_ptr &types_tree) {
            assert_not_declared_event(event->get_name());

            // Checking for duplicate variables in event signature
            if (event->get_params().has_value()) {
                entities_context.push();
                entities_context.add_decl_list(*event->get_params(), type_utils::find(types_tree, "entity"), types_tree);
                entities_context.pop();
            }

            const type_ptr &object = type_utils::find(types_tree, "object");
            const std::string &name = event->get_name()->get_token().get_lexeme();

            m_event_signatures[name] = event->get_params().has_value()
                                       ? types_context::build_typed_var_list((*event->get_params()), types_tree, either_type{object})
                                       : m_event_signatures[name] = typed_var_list{};

            m_events_map[name] = event;
        }

        void check_event_signature(const entities_context &entities_context, const ast::event_signature_ptr &e) const {
            assert_declared_event(e->get_name());

            entities_context.assert_declared(e->get_params());
            context_utils::check_signature(m_event_signatures, e->get_name(), e->get_params(), entities_context.get_scopes(), "event");
        }

    private:
        signature_map m_event_signatures;
        ast_node_map<ast::event_ptr> m_events_map;
    };
}

#endif //EPDDL_EVENTS_CONTEXT_H
