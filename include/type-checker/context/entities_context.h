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

#ifndef EPDDL_ENTITIES_CONTEXT_H
#define EPDDL_ENTITIES_CONTEXT_H

#include "context_types.h"
#include "scope.h"
#include "types_context.h"
#include "context_utils.h"

namespace epddl::type_checker {
    class entities_context {
    public:
        entities_context() {
            m_scopes.emplace_back();
        }

        void pop() {
            m_scopes.pop_back();
        }

        void push() {
            m_scopes.emplace_back();
        }

        [[nodiscard]] const std::deque<scope> &get_scopes() const { return m_scopes; }
        [[nodiscard]] const ast_node_map<ast::agent_group_decl_ptr> &get_agent_groups_map() const { return m_agent_groups_map; }

        [[nodiscard]] const std::string &get_entity_name(unsigned long id) const {
            return m_entities_names[id];
        }

        [[nodiscard]] unsigned long get_entity_id(const std::string &name) const {
            return m_entities_ids.at(name);
        }

        [[nodiscard]] bool is_declared(const ast::term &term) const {
            return context_utils::is_declared(m_scopes, term);
        }

        [[nodiscard]] either_type get_type(const ast::term &term) const {
            return context_utils::get_type(m_scopes, term);
        }

        [[nodiscard]] bool has_compatible_type(const ast::term &term, const either_type &type) const {
            return type::is_compatible_with(get_type(term), type);
        }

        [[nodiscard]] bool has_compatible_type(const ast::term &term, const type_ptr &type) const {
            return has_compatible_type(term, either_type{type});
        }

        [[nodiscard]] const bit_deque &get_entities_with_type(const types_context &types_context, const std::string &type) const {
            return m_type_entity_sets[types_context.get_type_id(type)];
        }

        [[nodiscard]] const bit_deque &get_entities_with_type(const types_context &types_context, const type_ptr &type) const {
            return get_entities_with_type(types_context, type->get_name());
        }

        [[nodiscard]] std::optional<ast::term> get_term(const std::string &name) const {
            for (const auto &scope : m_scopes)
                if (const auto &t = scope.get_term(name); t.has_value())
                    return t;

            return std::nullopt;
        }

        void assert_declared(const ast::term &term) const {
            context_utils::assert_declared(m_scopes, term);
        }

        void assert_declared(const ast::term_list &terms) const {
            for (const ast::term &term : terms)
                assert_declared(term);
        }

        void assert_not_declared(const ast::term &term) const {
            if (not is_declared(term)) return;

            std::visit([&](auto &&arg) {
                using token_type = typename std::remove_reference_t<decltype(*arg)>::token_type;
                const auto &previous = get_term(arg->get_token().get_lexeme());
                const token_ptr &tok = std::visit([&](auto &&arg_) {
                    return arg_->get_token_ptr();
                }, *previous);

                throw EPDDLException(arg->get_info(), "Redeclaration of " + std::string{token_type::name} +
                                                      " '" + arg->get_token().get_lexeme() +
                                                      "'. Previous declaration at (" + std::to_string(tok->get_row()) +
                                                      ":" + std::to_string(tok->get_col()) + ").");
            }, term);
        }

        void check_type(const ast::term &term, const either_type &type) const {
            if (has_compatible_type(term, type)) return;

            type::throw_incompatible_types(type, get_type(term), term);
        }

        void check_type(const ast::term &term, const type_ptr &type) const {
            check_type(term, either_type{type});
        }

        void add_decl_list(const ast::typed_identifier_list &entities, const type_ptr &default_type,
                           const type_ptr &types_tree) {
            either_type_list entities_types;
            either_type current_type = either_type{default_type};

            // We visit the list of entities backwards to determine the type of each identifier
            for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
                current_type = types_context::build_type((*it)->get_type(), types_tree, current_type);
                entities_types.push_front(current_type);
            }

            for (auto [e, t] = std::tuple{entities.begin(), entities_types.begin()} ; e != entities.end(); ++e, ++t) {
                assert_not_declared((*e)->get_id());

                if ((*e)->get_type().has_value()) {
                    types_context::assert_declared_type(types_tree, *(*e)->get_type());
                    types_context::assert_compatible_decl_type(*(*e)->get_type(),
                                                               types_context::build_type(*(*e)->get_type(), types_tree,
                                                                                         either_type{default_type}), default_type);
                }
                m_scopes.back().add_decl((*e)->get_id(), *t);

                m_entities_names.emplace_back((*e)->get_id()->get_token().get_lexeme());
                m_entities_ids[(*e)->get_id()->get_token().get_lexeme()] = m_entities_names.size() - 1;
            }
        }

        void add_decl_list(const ast::typed_variable_list &entities, const type_ptr &default_type,
                           const type_ptr &types_tree) {
            either_type_list entities_types;
            either_type current_type = either_type{default_type};

            /*for (const typed_variable_ptr &typed_var : entities) {
                assert_not_declared(typed_var->get_var());
                if (typed_var->get_type().has_value()) {
                    types_context::assert_declared_type(types_tree, *typed_var->get_type());
                    types_context::assert_compatible_decl_type(*typed_var->get_type(),
                                                types_context::build_type(*typed_var->get_type(), types_tree,
                                                                          either_type{default_type}), default_type);
                }
            }*/

            // We visit the list of entities backwards to determine the type of each variable
            for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
                current_type = types_context::build_type((*it)->get_type(), types_tree, current_type);
                entities_types.push_front(current_type);
            }

            for (auto [e, t] = std::tuple{entities.begin(), entities_types.begin()} ; e != entities.end(); ++e, ++t) {
                assert_not_declared((*e)->get_var());

                if ((*e)->get_type().has_value()) {
                    types_context::assert_declared_type(types_tree, *(*e)->get_type());
                    types_context::assert_compatible_decl_type(*(*e)->get_type(),
                                                               types_context::build_type(*(*e)->get_type(), types_tree,
                                                                                         either_type{default_type}), default_type);
                }
                m_scopes.back().add_decl((*e)->get_var(), *t);
            }
        }

        void add_decl_list(const ast::identifier_list &ids, const either_type &default_type, const type_ptr &types_tree) {
            for (const auto &id : ids) {
                assert_not_declared(id);
                m_scopes.back().add_decl(id, default_type);
            }
        }

        void add_decl_list(const ast::variable_list &variables, const either_type &default_type, const type_ptr &types_tree) {
            for (const auto &var : variables) {
                assert_not_declared(var);
                m_scopes.back().add_decl(var, default_type);
            }
        }

        void add_agent_group(const ast::agent_group_decl_ptr &agent_group, const type_ptr &types_tree) {
            assert_not_declared(agent_group->get_group_name());

            either_type agent_group_type =
                    types_context::build_type(agent_group->get_group_type(), types_tree,
                                              either_type{type_utils::find(types_tree, "agent-group")});
            m_scopes.back().add_decl(agent_group->get_group_name(), std::move(agent_group_type));

            const std::string &agent_group_name = agent_group->get_group_name()->get_token().get_lexeme();

            m_agent_groups_map[agent_group_name] = agent_group;
            m_entities_names.emplace_back(agent_group_name);
            m_entities_ids[agent_group_name] = m_entities_names.size() - 1;
        }

        void build_typed_entities_sets(const types_context &types_context, const type_ptr &types_tree) {
            const scope &base_scope = m_scopes.front();

            for (unsigned long i = 0; i < types_context.get_types_size(); ++i)
                m_type_entity_sets.emplace_back(m_entities_names.size());

            // Function 'init_entities' adds the given entity id to the bit_deque corresponding to the given type_ptr
            // and recursively adds the entity to all super types of 'type'
            std::function<void(const type_ptr &, unsigned long)>
                    init_entities = [&](const type_ptr &type, unsigned long e_id) {
                unsigned long type_id = types_context.get_type_id(type->get_name());
                m_type_entity_sets[type_id].push_back(e_id);

                if (type->get_name() != "entity" and type->get_parent())
                    init_entities(type->get_parent(), e_id);
            };

            for (const auto &[name, types] : base_scope.get_type_map()) {
                const std::string &type_name = types.front()->get_name();           // types has always size 1 here
                const type_ptr &type = type_utils::find(types_tree, type_name);

                init_entities(type, m_entities_ids.at(name));
            }
        }

    private:
        std::deque<scope> m_scopes;

        name_vector m_entities_names;
        name_id_map m_entities_ids;
        bit_deque_vector m_type_entity_sets;

        ast_node_map<ast::agent_group_decl_ptr> m_agent_groups_map;
    };
}

#endif //EPDDL_ENTITIES_CONTEXT_H
