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

#ifndef PLANK_ENTITIES_CONTEXT_H
#define PLANK_ENTITIES_CONTEXT_H

#include "context_types.h"
#include "scope.h"
#include "types_context.h"
#include <iterator>

namespace epddl::type_checker {
    class entities_context {
    public:
        entities_context() {
            m_scopes.emplace_back();
        }

        void push() {
            size_t
                    ent_offset = m_scopes.empty() ? 0 : m_scopes.back().get_next_entities_offset(),
                    var_offset = m_scopes.empty() ? 0 : m_scopes.back().get_next_variables_offset();

            m_scopes.emplace_back(ent_offset, var_offset);
        }

        void pop() {
            m_scopes.pop_back();
        }

        [[nodiscard]] unsigned long get_entities_no() const {
            return m_scopes.empty() ? 0 : m_scopes.back().get_entities_no();
        }

        [[nodiscard]] unsigned long get_variables_no() const {
            return m_scopes.empty() ? 0 : m_scopes.back().get_variables_no();
        }

        [[nodiscard]] const std::deque<scope> &get_scopes() const { return m_scopes; }

        [[nodiscard]] const ast_node_map<ast::agent_group_decl_ptr> &
        get_agent_groups_map() const { return m_agent_groups_map; }

        [[nodiscard]] const std::string &get_entity_name(unsigned long id) const {
            for (const scope &scope: m_scopes)
                if (id < scope.get_entities_no())
                    return scope.get_entity_name(id);

            assert(false);
//            return m_entities_names[id];
        }

        [[nodiscard]] unsigned long get_entity_id(const std::string &name) const {
            for (const scope &scope: m_scopes)
                if (scope.is_declared(name))
                    return scope.get_entity_id(name);

            assert(false);
//            return m_entities_ids.at(name);
        }

        [[nodiscard]] const std::string &get_variable_name(unsigned long id) const {
            for (const scope &scope: m_scopes)
                if (id < scope.get_variables_no())
                    return scope.get_variable_name(id);

            assert(false);
        }

        [[nodiscard]] unsigned long get_variable_id(const std::string &name) const {
            for (const scope &scope: m_scopes)
                if (scope.is_declared(name))
                    return scope.get_variable_id(name);

            assert(false);
        }

        [[nodiscard]] bool is_declared(const ast::term &term) const {
            return std::any_of(m_scopes.begin(), m_scopes.end(),
                               [&](const scope &scope) { return scope.is_declared(term); });
        }

        void assert_declared(error_manager_ptr &err_manager, const ast::term &term) const {
            if (is_declared(term)) return;

            std::visit([&](auto &&arg) {
                using token_type = typename std::remove_reference_t<decltype(*arg)>::token_type;

                err_manager->throw_error(error_type::undeclared_element, arg->get_token_ptr(),
                                         {std::string{token_type::name}});
            }, term);
        }

        [[nodiscard]] either_type get_type(const std::string &name) const {
            for (const auto &scope: m_scopes)
                if (const either_type &type = scope.get_type(name); not type.empty())
                    return type;

            return either_type{};
        }

        [[nodiscard]] either_type get_type(error_manager_ptr &err_manager,
                                           const ast::term &term) const {
            assert_declared(err_manager, term);

            for (const auto &scope: m_scopes)
                if (const either_type &type = scope.get_type(term); not type.empty())
                    return type;

            return either_type{};
        }

        [[nodiscard]] bool has_compatible_type(const types_context &types_context, error_manager_ptr &err_manager,
                                               const ast::term &term, const either_type &type) const {
            return types_context.is_compatible_with(get_type(err_manager, term), type);
        }

        [[nodiscard]] bool has_compatible_type(const types_context &types_context, error_manager_ptr &err_manager,
                                               const ast::term &term, const type_ptr &type) const {
            return has_compatible_type(types_context, err_manager,
                                       term, either_type{types_context.get_type_id(type)});
        }

        [[nodiscard]] const bit_deque &
        get_entities_with_type(const types_context &types_context, const type_id type) const {
            return m_scopes.back().get_entities_with_type(types_context, type);
        }

        [[nodiscard]] const bit_deque &
        get_entities_with_type(const types_context &types_context, const std::string &type) const {
            return m_scopes.back().get_entities_with_type(types_context, type);
        }

        [[nodiscard]] const bit_deque &
        get_entities_with_type(const types_context &types_context, const type_ptr &type) const {
            return get_entities_with_type(types_context, type->get_name());
        }

        [[nodiscard]] std::optional<ast::term> get_term(const std::string &name) const {
            for (const auto &scope: m_scopes)
                if (const auto &t = scope.get_term(name); t.has_value())
                    return t;

            return std::nullopt;
        }

        void assert_declared(error_manager_ptr &err_manager, const ast::term_list &terms) const {
            for (const ast::term &term: terms)
                assert_declared(err_manager, term);
        }

        void assert_not_declared(error_manager_ptr &err_manager, const ast::term &term) const {
            if (not is_declared(term)) return;

            std::visit([&](auto &&arg) {
                using token_type = typename std::remove_reference_t<decltype(*arg)>::token_type;
                const auto &previous = get_term(arg->get_token().get_lexeme());
                const token_ptr &tok = std::visit([&](auto &&arg_) {
                    return arg_->get_token_ptr();
                }, *previous);

                err_manager->throw_error(error_type::element_redeclaration, arg->get_token_ptr(),
                                         {std::string{token_type::name}, std::to_string(tok->get_row()),
                                          std::to_string(tok->get_col())});
            }, term);
        }

        void check_type(const types_context &types_context, error_manager_ptr &err_manager,
                        const ast::term &term, const either_type &type) const {
            if (has_compatible_type(types_context, err_manager, term, type)) return;

            types_context.throw_incompatible_types(err_manager, type,
                                                   get_type(err_manager, term), term);
        }

        void check_type(const types_context &types_context, error_manager_ptr &err_manager,
                        const ast::term &term, const type_ptr &type) const {
            check_type(types_context, err_manager, term, either_type{types_context.get_type_id(type)});
        }

        void add_decl_list(const types_context &types_context, error_manager_ptr &err_manager,
                           const ast::typed_identifier_list &entities, const type_ptr &default_type,
                           const type_ptr &max_type) {
            /*either_type_list entities_types;
            either_type current_type = either_type{types_context.get_type_id(default_type)};

            // We visit the list of entities backwards to determine the type of each identifier
            for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
                current_type = types_context.build_type((*it)->get_type(), current_type);
                entities_types.push_front(current_type);
            }

            for (auto [e, t] = std::tuple{entities.begin(), entities_types.begin()}; e != entities.end(); ++e, ++t) {
                assert_not_declared(err_manager, (*e)->get_id());

                if ((*e)->get_type().has_value()) {
                    types_context.assert_declared_type(err_manager, *(*e)->get_type());
                    // We check that e's type is compatible with 'max_type'
                    types_context.assert_compatible_decl_type(
                            err_manager, *(*e)->get_type(),
                            types_context.build_type(*(*e)->get_type(),
                                                     either_type{types_context.get_type_id(default_type)}), max_type);
                }
                m_scopes.back().add_id_decl((*e)->get_id(), *t);

//                m_entities_names.emplace_back((*e)->get_id()->get_token().get_lexeme());
//                m_entities_ids[(*e)->get_id()->get_token().get_lexeme()] = m_entities_names.size() - 1;
            }*/
            for (auto it = entities.begin(); it != entities.end(); ++it) {
                assert_not_declared(err_manager, (*it)->get_id());

                either_type id_type = get_typed_element_type<ast::typed_identifier_ptr>(
                        types_context, err_manager, entities, it, default_type);

                m_scopes.back().add_id_decl((*it)->get_id(), id_type);
            }
        }

        void add_decl_list(const types_context &types_context, error_manager_ptr &err_manager,
                           const ast::typed_variable_list &entities, const type_ptr &default_type,
                           bool rename_variables = false) {
            /*either_type_list entities_types;
            either_type current_type = either_type{types_context.get_type_id(default_type)};

            // We visit the list of entities backwards to determine the type of each variable
            for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
                current_type = types_context.build_type((*it)->get_type(), current_type);
                entities_types.push_front(current_type);
            }

            for (auto [e, t] = std::tuple{entities.begin(), entities_types.begin()}; e != entities.end(); ++e, ++t) {
                if (not rename_variables)
                    assert_not_declared(err_manager, (*e)->get_var());

                if ((*e)->get_type().has_value()) {
                    types_context.assert_declared_type(err_manager, *(*e)->get_type());
                    types_context.assert_compatible_decl_type(
                            err_manager, *(*e)->get_type(),
                            types_context.build_type(*(*e)->get_type(),
                                                     either_type{types_context.get_type_id(default_type)}),
                            default_type);
                }
                m_scopes.back().add_var_decl((*e)->get_var(), *t, rename_variables);
            }*/
            for (auto it = entities.begin(); it != entities.end(); ++it) {
                if (not rename_variables)
                    assert_not_declared(err_manager, (*it)->get_var());

                either_type var_type = get_typed_element_type<ast::typed_variable_ptr>(
                        types_context, err_manager, entities, it, default_type);

                m_scopes.back().add_var_decl((*it)->get_var(), var_type, rename_variables);
            }
        }

        void add_decl_list(error_manager_ptr &err_manager, const ast::identifier_list &ids,
                           const either_type &default_type) {
            for (const auto &id : ids) {
                assert_not_declared(err_manager, id);
                m_scopes.back().add_id_decl(id, default_type);
            }
        }

        void add_decl_list(error_manager_ptr &err_manager, const ast::variable_list &variables,
                           const either_type &default_type, bool treat_as_id = false) {
            for (const auto &var : variables) {
                assert_not_declared(err_manager, var);
                if (treat_as_id)
                    m_scopes.back().add_id_decl(var, default_type);
                else
                    m_scopes.back().add_var_decl(var, default_type);
            }
        }

        void add_agent_group(const types_context &types_context, error_manager_ptr &err_manager,
                              const ast::agent_group_decl_ptr &agent_group) {
            assert_not_declared(err_manager, agent_group->get_group_name());
            const type_ptr &default_type = types_context.get_type("agent-group");

            either_type agent_group_type = types_context.build_type(
                    agent_group->get_group_type(), either_type{types_context.get_type_id(default_type)});

            m_scopes.back().add_id_decl(agent_group->get_group_name(), agent_group_type);

            const std::string &agent_group_name = agent_group->get_group_name()->get_token().get_lexeme();

            m_agent_groups_map[agent_group_name] = agent_group;
//            m_entities_names.emplace_back(agent_group_name);
//            m_entities_ids[agent_group_name] = m_entities_names.size() - 1;
        }

        void build_typed_entities_sets(const types_context &types_context) {
            m_scopes.back().build_typed_entities_sets(types_context, bit_deque_vector{});
            /*const scope &base_scope = m_scopes.front();

            for (unsigned long i = 0; i < types_context.get_types_size(); ++i)
                m_type_entity_sets.emplace_back(m_entities_names.size());

            // Function 'init_entities' adds the given entity id to the bit_deque corresponding to the given type_ptr
            // and recursively adds the entity to all super types of 'type'
            std::function<void(const type_ptr &, unsigned long)>
                    init_entities = [&](const type_ptr &type, unsigned long e_id) {
                unsigned long type_id = types_context.get_type_id(type->get_name());
                m_type_entity_sets[type_id].push_back(e_id);

                if (type->get_name() != "entity" and types_context.get_parent(type))
                    init_entities(types_context.get_parent(type), e_id);
            };

            for (const auto &[name, types] : base_scope.get_type_map()) {
                const type_ptr &type = types_context.get_type(types.front());       // types has always size 1 here
                init_entities(type, m_entities_ids.at(name));
            }*/
        }

        void update_typed_entities_sets(const types_context &types_context) {
            const auto &scope = get_second_to_last_scope();
            const bit_deque_vector &previous = scope.get_entities_with_type_sets();
            m_scopes.back().build_typed_entities_sets(types_context, previous);
        }

    private:
        std::deque<scope> m_scopes;
        ast_node_map<ast::agent_group_decl_ptr> m_agent_groups_map;

        template<typename typed_elem_decl>
        either_type get_typed_element_type(const types_context &types_context, error_manager_ptr &err_manager,
                                           const std::list<typed_elem_decl> &entities,
                                           typename std::list<typed_elem_decl>::const_iterator it,
                                           const type_ptr &max_type) {
            // We iterate till we either reach the end of the list, or an element declared with its type
            while (it != entities.end() and not (*it)->get_type().has_value()) ++it;
            either_type entity_type = either_type{types_context.get_type_id(max_type)};

            // If no type had been explicitly declared, we return the default one (max_type)
            if (it == entities.end())
                return entity_type;

            // Otherwise, we check that the type has been correctly declared, we compute the entity's type,
            // we check that it is compatible with the greatest type allowed in the declaration, ...
            if ((*it)->get_type().has_value()) {
                types_context.assert_declared_type(err_manager, *(*it)->get_type());

                entity_type = types_context.build_type(
                        *(*it)->get_type(),
                        either_type{types_context.get_type_id(max_type)});

                types_context.assert_compatible_decl_type(
                        err_manager, *(*it)->get_type(), entity_type, max_type);
            }
            // ...and we return the type
            return entity_type;
        }

        const scope &get_second_to_last_scope() {
            assert(m_scopes.size() > 1);
            return *std::prev(std::prev(m_scopes.end()));
        }
//        type_map m_type_map;
//        name_vector m_entities_names;
//        name_id_map m_entities_ids;
//        bit_deque_vector m_type_entity_sets;
    };
}

#endif //PLANK_ENTITIES_CONTEXT_H
