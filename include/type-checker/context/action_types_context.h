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

namespace epddl::type_checker {
    class action_types_context {
    public:
        action_types_context() = default;

        [[nodiscard]] const signature_map &get_action_type_signatures() const { return m_action_type_signatures; }
        [[nodiscard]] const ast_node_map<ast::action_type_ptr> &get_action_types_map() const { return m_action_types_map; }
        [[nodiscard]] const ast_node_map<ast::identifier_list> &get_obs_types_map() const { return m_obs_types_map; }

        [[nodiscard]] const ast::action_type_ptr &get_action_type_decl(const ast::identifier_ptr &id) const {
            assert_declared_action_type(id);
            return m_action_types_map.at(id->get_token().get_lexeme());
        }

        [[nodiscard]] typed_var_list get_formal_param_types_action_type(const ast::identifier_ptr &id) const {
            assert_declared_action_type(id);
            return m_action_type_signatures.at(id->get_token().get_lexeme());
        }

        [[nodiscard]] const ast::identifier_list &get_obs_types(const ast::identifier_ptr &id) const {
            assert_declared_action_type(id);
            return m_obs_types_map.at(id->get_token().get_lexeme());
        }

        void assert_declared_action_type(const ast::identifier_ptr &id) const {
            if (context_utils::is_declared(id, m_action_type_signatures)) return;

            throw EPDDLException(id->get_info(), "Use of undeclared action type name '" + id->get_token().get_lexeme() + "'.");
        }

        void assert_not_declared_action_type(const ast::identifier_ptr &id) const {
            if (not context_utils::is_declared(id, m_action_type_signatures)) return;
            const ast::info &previous_info = m_action_types_map.at(id->get_token().get_lexeme())->get_info();

            throw EPDDLException(id->get_info(), "Redeclaration of action type '" + id->get_token().get_lexeme() +
                                                 "'. Previous declaration at (" + std::to_string(previous_info.m_row) + ":" +
                                                 std::to_string(previous_info.m_col) + ").");
        }

        void add_decl_action_type(entities_context &entities_context, const ast::action_type_ptr &action_type, const type_ptr &types_tree) {
            assert_not_declared_action_type(action_type->get_name());
            const type_ptr &event = type_utils::find(types_tree, "event");

            // Checking for duplicate variables in action type signature
            entities_context.push();
            entities_context.add_decl_list(action_type->get_events(), either_type{event}, types_tree);
            entities_context.pop();

            const std::string &name = action_type->get_name()->get_token().get_lexeme();
            typed_var_list typed_vars;

            for (const ast::variable_ptr &e : action_type->get_events())
                typed_vars.emplace_back(e->get_token().get_lexeme(), either_type{event});

            m_action_type_signatures[name] = std::move(typed_vars);
            m_obs_types_map[name] = action_type->get_obs_types();

            m_action_types_map[name] = action_type;
        }

        void add_decl_action_type(const std::string &action_type_name, const type_ptr &types_tree) {
            assert(action_type_name == "basic");

            const type_ptr &event = type_utils::find(types_tree, "event");
            m_action_type_signatures[action_type_name] = typed_var_list{{"?e", either_type{event}}};
        }

        void check_action_type_signature(const entities_context &entities_context, const ast::identifier_ptr &id, const ast::term_list &terms) const {
            assert_declared_action_type(id);
            entities_context.assert_declared(terms);
            context_utils::check_signature(m_action_type_signatures, id, terms, entities_context.get_scopes(), "action type");
        }

    private:
        signature_map m_action_type_signatures;
        ast_node_map<ast::action_type_ptr> m_action_types_map;
        ast_node_map<ast::identifier_list> m_obs_types_map;
    };
}

#endif //EPDDL_ACTION_TYPES_CONTEXT_H
