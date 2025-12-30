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
#include <algorithm>
#include <any>

namespace epddl::type_checker {
    class action_types_context {
    public:
        action_types_context() = default;

        [[nodiscard]] const ast::action_type_ptr &get_action_type_decl(const std::string &name) const {
            for (const auto &[lib_name, action_types_map] : m_action_types_map)
                if (const auto &it = action_types_map.find(name);
                        it != action_types_map.end())
                    return it->second;

            assert(false);
        }

        [[nodiscard]] const ast::action_type_ptr &get_action_type_decl(error_manager_ptr &err_manager,
                                                                       const ast::identifier_ptr &name) const {
            assert_declared_action_type(err_manager, name);
            return get_action_type_decl(name->get_token().get_lexeme());
        }

        [[nodiscard]] typed_var_list get_formal_param_types_action_type(const std::string &name) const {
            for (const auto &[lib_name, action_type_signatures] : m_action_type_signatures)
                if (const auto &it = action_type_signatures.find(name);
                        it != action_type_signatures.end())
                    return it->second;

            assert(false);
        }

        [[nodiscard]] typed_var_list get_formal_param_types_action_type(error_manager_ptr &err_manager,
                                                                        const ast::identifier_ptr &name) const {
            assert_declared_action_type(err_manager, name);
            return get_formal_param_types_action_type(name->get_token().get_lexeme());
        }

        [[nodiscard]] const ast::identifier_list &get_obs_types(const std::string &name) const {
            for (const auto &[lib_name, obs_types_map] : m_obs_types_map)
                if (const auto &it = obs_types_map.find(name);
                        it != obs_types_map.end())
                    return it->second;

            assert(false);
        }

        [[nodiscard]] const ast::identifier_list &get_obs_types(error_manager_ptr &err_manager,
                                                                const ast::identifier_ptr &name) const {
            assert_declared_action_type(err_manager, name);
            return get_obs_types(name->get_token().get_lexeme());
        }

        [[nodiscard]] bool is_declared_action_type(const ast::identifier_ptr &name) const {
            return std::any_of(m_action_type_signatures.begin(), m_action_type_signatures.end(),
                               [&](const auto &signatures) {
                                   return context_utils::is_declared(name, signatures.second);
                               });
        }

        void assert_declared_action_type(error_manager_ptr &err_manager, const ast::identifier_ptr &name) const {
            if (is_declared_action_type(name)) return;

            err_manager->throw_error(error_type::undeclared_element, name->get_token_ptr(),
                                     {error_manager::get_error_info(decl_type::type_name)});
        }

        void assert_not_declared_action_type(error_manager_ptr &err_manager, const ast::identifier_ptr &name) const {
            if (not is_declared_action_type(name)) return;

            const ast::action_type_ptr &previous = get_action_type_decl(err_manager, name);

            err_manager->throw_error(error_type::action_type_redeclaration, name->get_token_ptr(),
                                     {m_action_types_library.at(previous->get_name()->get_token().get_lexeme()),
                                      std::to_string(previous->get_info().m_row),
                                      std::to_string(previous->get_info().m_col)});
        }

        void add_decl_action_type(const types_context &types_context, entities_context &entities_context,
                                  error_manager_ptr &err_manager, const ast::identifier_ptr &lib_name,
                                  const ast::action_type_ptr &action_type) {
            assert_not_declared_action_type(err_manager, action_type->get_name());
            const type_ptr &event = types_context.get_type("event");

            // Checking for duplicate variables in action type signature
            const std::string &err_info = error_manager::get_error_info(
                    decl_type::action_type_decl, action_type->get_name()->get_token().get_lexeme());

            entities_context.push();
            err_manager->push_error_info(err_info);

            entities_context.add_decl_list(err_manager, action_type->get_events(),
                                           either_type{types_context.get_type_id(event)},
                                           true);

            err_manager->pop_error_info();
            entities_context.pop();

            const std::string
                &name = action_type->get_name()->get_token().get_lexeme(),
                lib_name_str = lib_name->get_token().get_lexeme();
            typed_var_list typed_vars;

            for (const ast::variable_ptr &e : action_type->get_events())
                typed_vars.emplace_back(e->get_token().get_lexeme(),
                                        either_type{types_context.get_type_id(event)});

            m_action_types_library[name] = lib_name_str;
            m_action_type_signatures[lib_name_str][name] = std::move(typed_vars);
            m_obs_types_map[lib_name_str][name] = action_type->get_obs_types();
            m_action_types_map[lib_name_str][name] = action_type;
        }

        void add_decl_action_type(const types_context &types_context, const std::string &name) {
            assert(name == "basic");

            const type_ptr &event = types_context.get_type("event");
            m_action_type_signatures[";basic"][name] =
                    typed_var_list{{"?e", either_type{types_context.get_type_id(event)}}};
        }

    private:
        string_string_map m_action_types_library;
        std::unordered_map<std::string, signature_map> m_action_type_signatures;
        std::unordered_map<std::string, ast_node_map<ast::action_type_ptr>> m_action_types_map;
        std::unordered_map<std::string, ast_node_map<ast::identifier_list>> m_obs_types_map;
    };
}

#endif //EPDDL_ACTION_TYPES_CONTEXT_H
