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

#ifndef EPDDL_CONTEXT_H
#define EPDDL_CONTEXT_H

#include "entity_kinds.h"
#include "type.h"
#include "../error-manager/epddl_exception.h"
#include "../ast/libraries/act_type_library_ast.h"
#include "../ast/domains/domain_ast.h"
#include "../ast/problems/problem_ast.h"
#include "../ast/common/formulas_ast.h"
#include "../ast/domains/predicates_decl_ast.h"
#include "../ast/domains/events/event_decl_ast.h"
#include "../ast/libraries/act_type_decl_ast.h"
#include "../ast/domains/actions/action_decl_ast.h"
#include <algorithm>
#include <any>
#include <iterator>
#include <optional>
#include <string>
#include <type_traits>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <variant>
#include <cassert>
#include <iostream>

namespace epddl::type_checker {
    using planning_specification = std::tuple<ast::problem_ptr, ast::domain_ptr, std::list<ast::act_type_library_ptr>>;

    using type_map = std::unordered_map<std::string, either_type>;
    using term_set = std::set<ast::term>;
    using string_set = std::unordered_set<std::string>;
    using signature_map = std::unordered_map<std::string, either_type_list>;
    using static_predicate_map = std::unordered_map<std::string, bool>;

    template<typename ast_node_type>
    using ast_node_map = std::unordered_map<std::string, ast_node_type>;

    class scope {
    public:
        scope() = default;

        [[nodiscard]] const type_map &get_type_map() const { return m_name_map; }

        [[nodiscard]] bool is_declared(const ast::term &term) const {
            return m_name_set.find(term) != m_name_set.end();
        }

        static bool is_compatible_with(const either_type &type_actual, const either_type &type_formal) {
            // Let (either ft_1 ft_2 ... ft_m) and (either at_1 at_2 ... at_n) be the types of the formal and
            // actual parameter, respectively. If for all primitive types at_j there exists a primitive type ft_i
            // such that at_j is a subtype of ft_i, then the two either-types are compatible
            return std::all_of(type_actual.begin(), type_actual.end(),
                               [&](const type_ptr &at) {
                                   return std::any_of(type_formal.begin(), type_formal.end(),
                                                      [&](const type_ptr &ft) {
                                                          return at->is_compatible_with(ft);
                                                      });
                               });
        }

        [[nodiscard]] bool has_type(const ast::term &term, const either_type &type) const {
            return std::visit([&](auto &&arg) -> bool {
                const either_type &term_type_list = m_name_map.at(arg->get_token().get_lexeme());
                return is_compatible_with(term_type_list, type);;
            }, term);
        }

        [[nodiscard]] bool has_type(const ast::term &term, const type_ptr &type) const {
            return has_type(term, either_type{type});
        }

        [[nodiscard]] either_type get_type(const ast::term &term) const {
            return std::visit([&](auto &&arg) {
                const auto &term_type_list = m_name_map.find(arg->get_token().get_lexeme());
                return term_type_list == m_name_map.end() ? either_type{} : m_name_map.at(arg->get_token().get_lexeme());
            }, term);
        }

        [[nodiscard]] std::optional<ast::term> get_term(const std::string &name) const {
            if (const auto it = m_entities_map.find(name); it != m_entities_map.end())
                return it->second;

            return std::nullopt;
        }

        void add_decl(const ast::term &term, either_type types) {
            std::visit([&](auto &&arg) {
                m_name_map[arg->get_token().get_lexeme()] = std::move(types);
                m_entities_map[arg->get_token().get_lexeme()] = term;
            }, term);

            m_name_set.emplace(term);
        }

        [[nodiscard]] const ast::term& get_decl(const std::string &name) const {
            return m_entities_map.at(name);
        }

    private:
        type_map m_name_map;
        term_set m_name_set;

        ast_node_map<ast::term> m_entities_map;
    };

    class context {
    public:
        context() {
            m_scopes.emplace_back();
        }

        void pop() {
            m_scopes.pop_back();
        }

        void push() {
            m_scopes.emplace_back();
        }

        [[nodiscard]] const std::deque<scope> &get_scopes() const { return m_scopes; }

        void assert_declared_type(const type_ptr &types_tree, const ast::type &type) {
            std::visit([&](auto && arg) { assert_declared_type(types_tree, arg); }, type);
        }

        void assert_declared_type(const type_ptr &types_tree, const ast::identifier_ptr &type) {
            if (not type_utils::find(types_tree, type))
                throw EPDDLException(type->get_info(), "Use of undeclared type '" + type->get_token().get_lexeme() + "'.");
        }

        void assert_declared_type(const type_ptr &types_tree, const ast::either_type_ptr &type) {
            for (const ast::identifier_ptr &t : type->get_ids())
                assert_declared_type(types_tree, t);
        }

        void assert_compatible_decl_type(const ast::type &type, const either_type &given_type, const type_ptr &decl_type) {
            if (not scope::is_compatible_with(given_type, either_type{decl_type}))
                std::visit([&](auto &&arg) {
                    throw EPDDLException(arg->get_info(), "Type '" + to_string(given_type) +
                                         "' is incompatible with expected type '" + decl_type->get_name() + "'.");
                }, type);
        }

        /*** REQUIREMENTS ***/

        [[nodiscard]] bool is_declared_requirement(const std::string &req) const {
            return m_requirements.find(req) != m_requirements.end();
        }

        void check_declared_requirement(const std::string &req, const std::string &error, std::optional<ast::info> location = std::nullopt) const {
            if (is_declared_requirement(req)) return;

            if (location.has_value()) {
                auto e = EPDDLException{location->m_path, location->m_row, location->m_col, error};
                std::cerr << e.what();
            } else
                std::cerr << error << "\n\n";
        }

        [[nodiscard]] const string_set &get_requirements() const {
            return m_requirements;
        }

        void add_requirement(const ast::requirement_ptr &req) {
            m_requirements.emplace(req->get_token()->get_lexeme());
        }

        void add_requirement(const std::string &req) {
            m_requirements.emplace(req);
        }

        void clear_requirements() {
            m_requirements.clear();
        }

        void expand_requirements() {
            expand_del();
            expand_general_formulas();      // todo: check requirements on paper and fix expansion
            expand_negative_formulas();
            expand_postconditions();

            expand_finitary_S5_theories();
            expand_common_knowledge();
            expand_groups();
        }

        /*** TERMS ***/

        [[nodiscard]] bool is_declared(const ast::term &term) const {
            return std::any_of(m_scopes.begin(), m_scopes.end(),
                               [&](const scope &scope) { return scope.is_declared(term); });
        }

        [[nodiscard]] bool has_type(const ast::term &term, const either_type &type) const {
            assert_declared(term);

            return std::any_of(m_scopes.begin(), m_scopes.end(),
                               [&](const scope &scope) { return scope.has_type(term, type); });
        }

        [[nodiscard]] bool has_type(const ast::term &term, const type_ptr &type) const {
            return has_type(term, either_type{type});
        }

        [[nodiscard]] either_type get_type(const ast::term &term) const {
            assert_declared(term);

            for (const auto &scope : m_scopes)
                if (const either_type &type = scope.get_type(term); not type.empty())
                    return type;

            return either_type{};
        }

        [[nodiscard]] std::optional<ast::term> get_term(const std::string &name) const {
            for (const auto &scope : m_scopes)
                if (const auto &t = scope.get_term(name); t.has_value())
                    return t;

            return std::nullopt;
        }

        void assert_declared(const ast::term &term) const {
            if (is_declared(term)) return;

            std::visit([&](auto &&arg) {
                using token_type = typename std::remove_reference_t<decltype(*arg)>::token_type;
                throw EPDDLException(arg->get_info(), "Use of undeclared " + std::string{token_type::name} +
                                     " '" + arg->get_token().get_lexeme() + "'.");
            }, term);
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
            assert_declared(term);

            if (std::any_of(m_scopes.begin(), m_scopes.end(),
                            [&](const scope &scope) { return scope.has_type(term, type); }))
                return;

            throw_incompatible_types(type, term);
        }

        void check_type(const ast::term &term, const type_ptr &type) const {
            check_type(term, either_type{type});
        }

        void add_decl_list(const ast::typed_identifier_list &entities, const type_ptr &default_type,
                           const type_ptr &types_tree) {
            either_type_list entities_types;
            either_type current_type = either_type{default_type};

            for (const typed_identifier_ptr &typed_id : entities) {
                assert_not_declared(typed_id->get_id());
                if (typed_id->get_type().has_value()) {
                    assert_declared_type(types_tree, *typed_id->get_type());
                    assert_compatible_decl_type(*typed_id->get_type(),
                                                build_type(*typed_id->get_type(), types_tree, either_type{default_type}),
                                                default_type);
                }
            }

            // We visit the list of entities backwards to determine the type of each identifier
            for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
                current_type = build_type((*it)->get_type(), types_tree, current_type);
                entities_types.push_front(current_type);
            }

            for (auto [e, t] = std::tuple{entities.begin(), entities_types.begin()} ; e != entities.end(); ++e, ++t)
                m_scopes.back().add_decl((*e)->get_id(), std::move(*t));
        }

        void add_decl_list(const ast::typed_variable_list &entities, const type_ptr &default_type,
                           const type_ptr &types_tree) {
            either_type_list entities_types;
            either_type current_type = either_type{default_type};

            for (const typed_variable_ptr &typed_var : entities) {
                assert_not_declared(typed_var->get_var());
                if (typed_var->get_type().has_value()) {
                    assert_declared_type(types_tree, *typed_var->get_type());
                    assert_compatible_decl_type(*typed_var->get_type(),
                                                build_type(*typed_var->get_type(), types_tree, either_type{default_type}),
                                                default_type);
                }
            }

            // We visit the list of entities backwards to determine the type of each variable
            for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
                current_type = build_type((*it)->get_type(), types_tree, current_type);
                entities_types.push_front(current_type);
            }

            for (auto [e, t] = std::tuple{entities.begin(), entities_types.begin()} ; e != entities.end(); ++e, ++t)
                m_scopes.back().add_decl((*e)->get_var(), std::move(*t));
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

            either_type agent_group_type = either_type{type_utils::find(types_tree, ";agent-group")};
            m_scopes.back().add_decl(agent_group->get_group_name(), std::move(agent_group_type));

            m_agent_groups_map[agent_group->get_group_name()->get_token().get_name()] = agent_group;
        }

        /*** PREDICATES ***/

        [[nodiscard]] static bool is_declared(const ast::identifier_ptr &id, const signature_map &signatures) {
            return signatures.find(id->get_token().get_lexeme()) != signatures.end();
        }

        [[nodiscard]] either_type_list get_formal_param_types_predicate(const ast::identifier_ptr &id) const {
            assert_declared_predicate(id);

            return m_predicate_signatures.at(id->get_token().get_lexeme());
        }

        void assert_declared_predicate(const ast::identifier_ptr &id) const {
            if (is_declared(id, m_predicate_signatures)) return;

            throw EPDDLException(id->get_info(), "Use of undeclared predicate name '" + id->get_token().get_lexeme() + "'.");
        }

        void assert_not_declared_predicate(const ast::identifier_ptr &id) const {
            if (not is_declared(id, m_predicate_signatures)) return;
            const ast::info &previous_info = m_predicates_map.at(id->get_token().get_lexeme())->get_info();

            throw EPDDLException(id->get_info(), "Redeclaration of predicate '" + id->get_token().get_lexeme() +
                                 "'. Previous declaration at (" + std::to_string(previous_info.m_row) + ":" +
                                 std::to_string(previous_info.m_col) + ").");
        }

        void assert_static_predicate(const ast::identifier_ptr &id) const {
            if (m_static_predicates.at(id->get_token().get_lexeme())) return;

            throw EPDDLException(id->get_info(), "Predicate '" + id->get_token().get_lexeme() + "' is not static.");
        }

        void add_decl_predicate(const ast::predicate_decl_ptr &pred, const type_ptr &types_tree) {
            assert_not_declared_predicate(pred->get_name());

            const type_ptr &object = type_utils::find(types_tree, "object");
            m_predicate_signatures[pred->get_name()->get_token().get_lexeme()] = build_type_list(pred->get_params(), types_tree, either_type{object});
            m_static_predicates[pred->get_name()->get_token().get_lexeme()] = pred->is_static();

            m_predicates_map[pred->get_name()->get_token().get_lexeme()] = pred;
        }

        void check_predicate_signature(const ast::identifier_ptr &id, const ast::term_list &terms) const {
            assert_declared_predicate(id);
            assert_declared(terms);
            check_signature(m_predicate_signatures, id, terms, "predicate");
        }

        /*** EVENTS ***/

        [[nodiscard]] either_type_list get_formal_param_types_event(const ast::identifier_ptr &id) const {
            assert_declared_event(id);

            return m_event_signatures.at(id->get_token().get_lexeme());
        }

        void assert_declared_event(const ast::identifier_ptr &id) const {
            if (is_declared(id, m_event_signatures)) return;

            throw EPDDLException(id->get_info(), "Use of undeclared event name '" + id->get_token().get_lexeme() + "'.");
        }

        void assert_not_declared_event(const ast::identifier_ptr &id) const {
            if (not is_declared(id, m_event_signatures)) return;
            const ast::info &previous_info = m_events_map.at(id->get_token().get_lexeme())->get_info();

            throw EPDDLException(id->get_info(), "Redeclaration of event '" + id->get_token().get_lexeme() +
                                                 "'. Previous declaration at (" + std::to_string(previous_info.m_row) + ":" +
                                                 std::to_string(previous_info.m_col) + ").");
        }

        void add_decl_event(const ast::event_ptr &event, const type_ptr &types_tree) {
            assert_not_declared_event(event->get_name());

            const type_ptr &object = type_utils::find(types_tree, "object");
            const std::string &name = event->get_name()->get_token().get_lexeme();

            m_event_signatures[name] = event->get_params().has_value()
                    ? build_type_list((*event->get_params())->get_formal_params(), types_tree, either_type{object})
                    : m_event_signatures[name] = either_type_list{};

            m_events_map[name] = event;
        }

        void check_event_signature(const ast::event_signature_ptr &e) const {
            assert_declared_event(e->get_name());

            assert_declared(e->get_params());
            check_signature(m_event_signatures, e->get_name(), e->get_params(), "event");
        }

        /*** ACTION TYPES ***/

        [[nodiscard]] either_type_list get_formal_param_types_action_type(const ast::identifier_ptr &id) const {
            assert_declared_action_type(id);

            return m_action_type_signatures.at(id->get_token().get_lexeme());
        }

        void assert_declared_action_type(const ast::identifier_ptr &id) const {
            if (is_declared(id, m_action_type_signatures)) return;

            throw EPDDLException(id->get_info(), "Use of undeclared action type name '" + id->get_token().get_lexeme() + "'.");
        }

        void assert_not_declared_action_type(const ast::identifier_ptr &id) const {
            if (not is_declared(id, m_action_type_signatures)) return;
            const ast::info &previous_info = m_action_types_map.at(id->get_token().get_lexeme())->get_info();

            throw EPDDLException(id->get_info(), "Redeclaration of action type '" + id->get_token().get_lexeme() +
                                                 "'. Previous declaration at (" + std::to_string(previous_info.m_row) + ":" +
                                                 std::to_string(previous_info.m_col) + ").");
        }

        void add_decl_action_type(const ast::action_type_ptr &action_type, const type_ptr &types_tree) {
            assert_not_declared_action_type(action_type->get_name());

            const type_ptr &event = type_utils::find(types_tree, "event"), &obs_group = type_utils::find(types_tree, ";obs-group");
            const std::string &name = action_type->get_name()->get_token().get_lexeme();

            auto type_list = either_type_list{action_type->get_events().size(), either_type{event}};
            m_action_signatures[name] = std::move(type_list);
            m_obs_groups_map[name] = action_type->get_obs_groups();

            m_action_types_map[name] = action_type;
        }

        void add_decl_action_type(const std::string &action_type_name, const type_ptr &types_tree) {
            assert(action_type_name == "basic");

            const type_ptr &event = type_utils::find(types_tree, "event");
            m_action_signatures[action_type_name] = either_type_list{either_type{event}};
        }

        void check_action_type_signature(const ast::identifier_ptr &id, const ast::term_list &terms) const {
            assert_declared_action_type(id);
            assert_declared(terms);
            check_signature(m_action_type_signatures, id, terms, "action type");
        }

        void add_decl_obs_groups(const ast::identifier_ptr &id, const type_ptr &types_tree) {
            const type_ptr &obs_group = type_utils::find(types_tree, ";obs-group");
            add_decl_list(m_obs_groups_map.at(id->get_token().get_lexeme()), either_type{obs_group}, types_tree);
        }

        /*** ACTIONS ***/

        [[nodiscard]] either_type_list get_formal_param_types_action(const ast::identifier_ptr &id) const {
            assert_declared_action(id);

            return m_action_signatures.at(id->get_token().get_lexeme());
        }

        void assert_declared_action(const ast::identifier_ptr &id) const {
            if (is_declared(id, m_action_signatures)) return;

            throw EPDDLException(id->get_info(), "Use of undeclared action name '" + id->get_token().get_lexeme() + "'.");
        }

        void assert_not_declared_action(const ast::identifier_ptr &id) const {
            if (not is_declared(id, m_action_signatures)) return;
            const ast::info &previous_info = m_actions_map.at(id->get_token().get_lexeme())->get_info();

            throw EPDDLException(id->get_info(), "Redeclaration of action '" + id->get_token().get_lexeme() +
                                                 "'. Previous declaration at (" + std::to_string(previous_info.m_row) + ":" +
                                                 std::to_string(previous_info.m_col) + ").");
        }

        void add_decl_action(const ast::action_ptr &action, const type_ptr &types_tree) {
            assert_not_declared_action(action->get_name());

            const type_ptr &object = type_utils::find(types_tree, "object");
            const std::string &name = action->get_name()->get_token().get_lexeme();
            m_action_signatures[name] = build_type_list(action->get_params()->get_formal_params(), types_tree, either_type{object});

            m_actions_map[name] = action;
        }

        void check_action_signature(const ast::identifier_ptr &id, const ast::term_list &terms) const {
            assert_declared_action(id);
            assert_declared(terms);
            check_signature(m_action_signatures, id, terms, "action");
        }

        template<typename T, typename U>
        static void throw_arguments_number_error(const ast::identifier_ptr &id, const std::list<T> &expected_list,
                                                 const std::list<U> &found_list, const std::string &decl_str) {
            std::string many_few = expected_list.size() < found_list.size() ? "many" : "few";

            throw EPDDLException{std::string{""}, id->get_token().get_row(), id->get_token().get_col(),
                                 std::string{"Too " + many_few + " arguments for " + decl_str + " '" +
                                             id->get_token().get_lexeme() + "'. Expected " +
                                             std::to_string(expected_list.size()) + ", found " +
                                             std::to_string(found_list.size()) + "."}};
        }

        [[nodiscard]] static std::string to_string(const either_type &type) {
            if (type.size() == 1) return type.back()->get_name();

            std::string type_str = "(either";
            for (const type_ptr &t : type) type_str.append(" " + t->get_name());
            return type_str + ")";
        }

    private:
        std::deque<scope> m_scopes;
        string_set m_requirements;
        signature_map m_predicate_signatures, m_event_signatures, m_action_type_signatures, m_action_signatures;
        static_predicate_map m_static_predicates;
        ast_node_map<ast::identifier_list> m_obs_groups_map;

        ast_node_map<ast::predicate_decl_ptr> m_predicates_map;
        ast_node_map<ast::agent_group_decl_ptr> m_agent_groups_map;
        ast_node_map<ast::event_ptr> m_events_map;
        ast_node_map<ast::action_ptr> m_actions_map;
        ast_node_map<ast::action_type_ptr> m_action_types_map;

        void check_signature(const signature_map &signatures, const ast::identifier_ptr &id,
                             const ast::term_list &terms, const std::string &decl_str) const {
            const auto &types = signatures.at(id->get_token().get_lexeme());

            if (types.size() != terms.size())
                throw_arguments_number_error(id, types, terms, decl_str);

            for (auto [type, term] = std::tuple{types.begin(), terms.begin()}; type != types.end(); ++type, ++term) {
                // We want to check that the type of our current actual parameter is compatible with that of
                // our current formal parameter
                const either_type &param_type = *type;            // Type of the formal parameter declared in the predicate definition
                const either_type &term_type  = get_type(*term);  // Type of the actual parameter passed to the predicate

                // We check that the type of the actual parameter is compatible with that of the formal parameter
                if (not scope::is_compatible_with(term_type, param_type))
                    throw_incompatible_types(param_type, *term);
            }
        }

        either_type_list build_type_list(const ast::formal_param_list &params, const type_ptr &types_tree,
                                                const either_type &default_type) {
            either_type_list types;

            for (const ast::formal_param &param : params)
                types.push_back(build_type(param->get_type(), types_tree, default_type));

            return types;
        }

        either_type build_type(const std::optional<ast::type> &entity_decl_type, const type_ptr &types_tree,
                               const either_type &default_type) {
            either_type entity_type;

            if (entity_decl_type.has_value()) {
                check_declared_requirement(":typing", "");

                if (std::holds_alternative<ast::identifier_ptr>(*entity_decl_type))
                    entity_type = either_type{type_utils::find(types_tree, std::get<ast::identifier_ptr>(*entity_decl_type))};
                else if (std::holds_alternative<ast::either_type_ptr>(*entity_decl_type)) {
                    const ast::identifier_list &either_type_list =
                            std::get<ast::either_type_ptr>(*entity_decl_type)->get_ids();

                    for (const ast::identifier_ptr &id : either_type_list)
                        entity_type.push_back(type_utils::find(types_tree, id));
                }
            } else
                entity_type = default_type;

            return entity_type;
        }

        void throw_incompatible_types(const either_type &type_formal, const ast::term &term) const {
            std::visit([&](auto &&arg) {
                const std::string &arg_name = arg->get_token().get_lexeme();
                throw EPDDLException(arg->get_info(), "Type error. Expected term with type '" + to_string(type_formal) +
                                                      "', found '" + arg->get_token().get_lexeme() + "' with type '" +
                                                      to_string(get_type(term)) + "'.");
            }, term);
        }

        void expand_del() {
            if (m_requirements.find(":del") != m_requirements.end()) {
                add_requirement(":typing");
                add_requirement(":equality");
                add_requirement(":partial-observability");
                add_requirement(":ontic-actions");
                add_requirement(":multi-pointed-models");
                add_requirement(":general-formulas");
            }
        }

        void expand_general_formulas() {
            if (m_requirements.find(":general-formulas") != m_requirements.end())
                for (const std::string &formula_type : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                    add_requirement(":general-" + formula_type);

            for (const std::string &formula_type : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                if (m_requirements.find(":general-" + formula_type) != m_requirements.end())
                    for (const std::string &str : {"negative", "disjunctive", "modal", "existential", "universal", "quantified"})
                        if (formula_type != "list-formulas" or str != "modal")
                            add_requirement(":" + str + "-" + formula_type);
        }

        void expand_negative_formulas() {
            for (const std::string &str : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                if (m_requirements.find(":negative-" + str) != m_requirements.end())
                    add_requirement(":disjunctive-" + str);
        }

        void expand_postconditions() {
            for (const std::string &str : {"negative", "disjunctive", "modal", "existential", "universal", "quantified", "general"})
                if (m_requirements.find(":" + str + "-postconditions") != m_requirements.end())
                    add_requirement(":conditional-effects");
        }

        void expand_finitary_S5_theories() {
            if (m_requirements.find(":finitary-S5-theories") != m_requirements.end()) {
                add_requirement(":common-knowledge");
                add_requirement(":knowing-whether");
            }
        }

        void expand_common_knowledge() {
            if (m_requirements.find(":common-knowledge") != m_requirements.end())
                add_requirement(":group-modalities");

            if (m_requirements.find(":static-common-knowledge") != m_requirements.end()) {
                add_requirement(":group-modalities");
                add_requirement(":static-predicates");
            }
        }

        void expand_groups() {
            if (m_requirements.find(":agent-groups") != m_requirements.end() or
                m_requirements.find(":group-modalities") != m_requirements.end())
                add_requirement(":lists");
        }
//        void assert_disjoint(const scope &scope) const {
//            for (const auto &s : m_scopes)
//                s.assert_disjoint(scope);
//        }
    };

//    using entity_map     = std::map<token_ptr, epddl_entity_decl>;
//    using del_entity_map = std::map<token_ptr, del_entity_decl>;

//    public:
//        scope() = default;
//
//        void add_entity(entity_decl decl) {
//            std::visit([&](auto &&arg) {
//                using arg_type = std::remove_reference_t<decltype(arg)>;
//
//                if constexpr (std::is_same_v<arg_type, epddl_entity_decl>)
//                    m_entities.emplace(arg.get_tok(), std::forward<arg_type>(arg));
//                else if constexpr (std::is_same_v<arg_type, del_entity_decl>)
//                    m_del_entities.emplace(arg.get_tok(), std::forward<arg_type>(arg));
//            }, decl);
//        }
//
//        [[nodiscard]] bool find(const token_ptr &tok) const {
//           return m_entities.find(tok) != m_entities.end() or m_del_entities.find(tok) != m_del_entities.end();
//        }
//
//    private:
//        entity_map m_entities;
//        del_entity_map m_del_entities;
}

#endif //EPDDL_CONTEXT_H
