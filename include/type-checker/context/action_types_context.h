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

#ifndef EPDDL_ACTION_TYPES_CONTEXT_H
#define EPDDL_ACTION_TYPES_CONTEXT_H

#include "context_types.h"

#include "context_types.h"
#include "entities_context.h"
#include "context_utils.h"
#include "types_context.h"

namespace epddl::type_checker {
    class action_types_context {
    public:
        action_types_context() = default;

        [[nodiscard]] const signature_map &get_action_type_signatures() const { return m_action_type_signatures; }
        [[nodiscard]] const ast_node_map<ast::action_type_ptr> &get_action_types_map() const { return m_action_types_map; }
        [[nodiscard]] const ast_node_map<ast::identifier_list> &get_obs_types_map() const { return m_obs_types_map; }

        [[nodiscard]] const ast::action_type_ptr &get_action_type_decl(const std::string &name) const {
            return m_action_types_map.at(name);
        }

        [[nodiscard]] const ast::action_type_ptr &get_action_type_decl(error_manager_ptr &err_manager,
                                                                       const ast::identifier_ptr &id) const {
            assert_declared_action_type(err_manager, id);
            return m_action_types_map.at(id->get_token().get_lexeme());
        }

        [[nodiscard]] typed_var_list get_formal_param_types_action_type(const std::string &name) const {
            return m_action_type_signatures.at(name);
        }

        [[nodiscard]] typed_var_list get_formal_param_types_action_type(error_manager_ptr &err_manager,
                                                                        const ast::identifier_ptr &id) const {
            assert_declared_action_type(err_manager, id);
            return m_action_type_signatures.at(id->get_token().get_lexeme());
        }

        [[nodiscard]] const ast::identifier_list &get_obs_types(const std::string &name) const {
            return m_obs_types_map.at(name);
        }

        [[nodiscard]] const ast::identifier_list &get_obs_types(error_manager_ptr &err_manager,
                                                                const ast::identifier_ptr &id) const {
            assert_declared_action_type(err_manager, id);
            return m_obs_types_map.at(id->get_token().get_lexeme());
        }

        void assert_declared_action_type(error_manager_ptr &err_manager, const ast::identifier_ptr &id) const {
            if (context_utils::is_declared(id, m_action_type_signatures)) return;

            err_manager->throw_error(error_type::undeclared_element, id->get_token_ptr(),
                                     {error_manager::get_error_info(decl_type::type_name)});
        }

        void assert_not_declared_action_type(error_manager_ptr &err_manager, const ast::identifier_ptr &id) const {
            if (not context_utils::is_declared(id, m_action_type_signatures)) return;
            const ast::info &previous_info = m_action_types_map.at(id->get_token().get_lexeme())->get_info();

            err_manager->throw_error(error_type::element_redeclaration, id->get_token_ptr(),
                                     {error_manager::get_error_info(decl_type::action_type),
                                      std::to_string(previous_info.m_row), std::to_string(previous_info.m_col)});
        }

        void add_decl_action_type(const types_context &types_context, entities_context &entities_context,
                                  error_manager_ptr &err_manager, const ast::action_type_ptr &action_type) {
            assert_not_declared_action_type(err_manager, action_type->get_name());
            const type_ptr &event = types_context.get_type("event");

            // Checking for duplicate variables in action type signature
            entities_context.push();
            entities_context.add_decl_list(err_manager, action_type->get_events(),
                                           either_type{types_context.get_type_id(event)}, true);
            entities_context.pop();

            const std::string &name = action_type->get_name()->get_token().get_lexeme();
            typed_var_list typed_vars;

            for (const ast::variable_ptr &e : action_type->get_events())
                typed_vars.emplace_back(e->get_token().get_lexeme(), either_type{types_context.get_type_id(event)});

            m_action_type_signatures[name] = std::move(typed_vars);
            m_obs_types_map[name] = action_type->get_obs_types();

            m_action_types_map[name] = action_type;
        }

        void add_decl_action_type(const types_context &types_context, const std::string &action_type_name) {
            assert(action_type_name == "basic");

            const type_ptr &event = types_context.get_type("event");
            m_action_type_signatures[action_type_name] = typed_var_list{{"?e", either_type{types_context.get_type_id(event)}}};
        }

        void check_action_type_signature(const types_context &types_context, const entities_context &entities_context,
                                         error_manager_ptr &err_manager, const ast::identifier_ptr &id,
                                         const ast::term_list &terms) {
            assert_declared_action_type(err_manager, id);
            entities_context.assert_declared(err_manager, terms);
            context_utils::check_signature(types_context, entities_context, err_manager,
                                           m_action_type_signatures, id, terms, "action type");
        }

    private:
        signature_map m_action_type_signatures;
        ast_node_map<ast::action_type_ptr> m_action_types_map;
        ast_node_map<ast::identifier_list> m_obs_types_map;
    };
}

#endif //EPDDL_ACTION_TYPES_CONTEXT_H
