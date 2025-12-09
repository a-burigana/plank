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

#ifndef EPDDL_ACTIONS_CONTEXT_H
#define EPDDL_ACTIONS_CONTEXT_H

#include "context_types.h"
#include "entities_context.h"
#include "context_utils.h"
#include <string>
#include <unordered_map>

namespace epddl::type_checker {
    class actions_context {
    public:
        actions_context() = default;

        [[nodiscard]] const name_vector &get_action_names() const { return m_actions_names; }
        [[nodiscard]] const signature_map &get_actions_signatures() const { return m_actions_signatures; }
        [[nodiscard]] const ast::action_ptr &get_action_decl(const std::string &name) const { return m_actions_map.at(name); }

        [[nodiscard]] typed_var_list get_formal_param_types_action(const ast::identifier_ptr &id) const {
            assert_declared_action(id);
            return m_actions_signatures.at(id->get_token().get_lexeme());
        }

        void assert_declared_action(const ast::identifier_ptr &id) const {
            if (context_utils::is_declared(id, m_actions_signatures)) return;

            throw EPDDLException(id->get_info(), "Use of undeclared action name '" + id->get_token().get_lexeme() + "'.");
        }

        void assert_not_declared_action(const ast::identifier_ptr &id) const {
            if (not context_utils::is_declared(id, m_actions_signatures)) return;
            const ast::info &previous_info = m_actions_map.at(id->get_token().get_lexeme())->get_info();

            throw EPDDLException(id->get_info(), "Redeclaration of action '" + id->get_token().get_lexeme() +
                                                 "'. Previous declaration at (" + std::to_string(previous_info.m_row) + ":" +
                                                 std::to_string(previous_info.m_col) + ").");
        }

        void add_decl_action(const types_context &types_context, entities_context &entities_context,
                             const ast::action_ptr &action) {
            assert_not_declared_action(action->get_name());
            const type_ptr
                    &entity = types_context.get_type("entity"),
                    &object = types_context.get_type("object");

            // Checking for duplicate variables in action signature
            entities_context.push();
            entities_context.add_decl_list(types_context, action->get_params()->get_formal_params(), entity);
            entities_context.pop();

            const std::string &name = action->get_name()->get_token().get_lexeme();

            m_actions_signatures[name] =
                    types_context.build_typed_var_list(action->get_params()->get_formal_params(),
                                                       either_type{types_context.get_type_id(object)});
            m_actions_names.emplace_back(name);
            m_actions_map[name] = action;
        }

        void check_action_signature(const types_context &types_context, const entities_context &entities_context,
                                    const ast::identifier_ptr &id,  const ast::term_list &terms) const {
            assert_declared_action(id);
            entities_context.assert_declared(terms);
            context_utils::check_signature(types_context, m_actions_signatures, id, terms,
                                           entities_context.get_scopes(), "action");
        }

        void set_default_obs_type(const std::string &action_name, const std::string &default_t) {
            m_default_obs_types[action_name] = default_t;
        }

        const std::string &get_default_obs_type(const std::string &action_name) const {
            return m_default_obs_types.at(action_name);
        }

    private:
        name_vector m_actions_names;
        signature_map m_actions_signatures;
        ast_node_map<ast::action_ptr> m_actions_map;
        string_string_map m_default_obs_types;
    };
}

#endif //EPDDL_ACTIONS_CONTEXT_H
