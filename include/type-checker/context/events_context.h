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

#ifndef PLANK_EVENTS_CONTEXT_H
#define PLANK_EVENTS_CONTEXT_H

#include "context_types.h"
#include "entities_context.h"
#include "context_utils.h"
#include "types_context.h"

namespace epddl::type_checker {
    class events_context {
    public:
        explicit events_context(error_manager_ptr domain_err_manager) :
                m_domain_err_manager{std::move(domain_err_manager)} {}

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

        [[nodiscard]] bool is_ontic(const std::string &name) const {
            return m_ontic_events.at(name);
        }

        void assert_declared_event(const ast::identifier_ptr &id) const {
            if (context_utils::is_declared(id, m_event_signatures)) return;

            m_domain_err_manager->throw_error(error_type::undeclared_element, id->get_token_ptr(),
                                              {error_manager::get_error_info(decl_type::event_name)});
        }

        void assert_not_declared_event(const ast::identifier_ptr &id) const {
            if (not context_utils::is_declared(id, m_event_signatures)) return;
            const ast::info &previous_info = m_events_map.at(id->get_token().get_lexeme())->get_info();

            m_domain_err_manager->throw_error(error_type::element_redeclaration, id->get_token_ptr(),
                                              {error_manager::get_error_info(decl_type::event_name),
                                               std::to_string(previous_info.m_row),
                                               std::to_string(previous_info.m_col)});
        }

        void add_decl_event(const types_context &types_context, entities_context &entities_context,
                            const ast::event_ptr &event) {
            assert_not_declared_event(event->get_name());
            const type_ptr
                    &entity = types_context.get_type("entity"),
                    &object = types_context.get_type("object");

            // Checking for duplicate variables in event signature
            if (event->get_params().has_value()) {
                entities_context.push();
                entities_context.add_decl_list(types_context, m_domain_err_manager, *event->get_params(), entity);
                entities_context.pop();
            }

            const std::string &name = event->get_name()->get_token().get_lexeme();

            m_event_signatures[name] = event->get_params().has_value()
                    ? types_context.build_typed_var_list(m_domain_err_manager, (*event->get_params()),
                                                         either_type{types_context.get_type_id(object)})
                    : m_event_signatures[name] = typed_var_list{};

            m_events_map[name] = event;
            m_ontic_events[name] = event->get_postconditions().has_value();
        }

        void check_event_signature(const types_context &types_context, const entities_context &entities_context,
                                   const ast::event_signature_ptr &e) {
            assert_declared_event(e->get_name());

            entities_context.assert_declared(m_domain_err_manager, e->get_params());
            context_utils::check_signature(types_context, entities_context, m_domain_err_manager,
                                           m_event_signatures, e->get_name(), e->get_params(), "event");
        }

    private:
        error_manager_ptr m_domain_err_manager;
        signature_map m_event_signatures;
        string_bool_map m_ontic_events;
        ast_node_map<ast::event_ptr> m_events_map;
    };
}

#endif //PLANK_EVENTS_CONTEXT_H
