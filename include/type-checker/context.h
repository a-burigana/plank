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
#include "../ast/common/formulas_ast.h"
#include "type.h"
#include "../error-manager/epddl_exception.h"
#include <algorithm>
#include <any>
#include <iterator>
#include <optional>
#include <string>
#include <type_traits>
#include <map>
#include <unordered_set>
#include <variant>

namespace epddl::type_checker {
    using type_map = std::unordered_map<std::string, either_type>;
    using type_set = std::unordered_set<std::string>;
    using signature_map = std::unordered_map<std::string, either_type_list>;
    using static_predicate_map = std::unordered_map<std::string, bool>;

    class scope {
    public:
        scope() = default;

        [[nodiscard]] bool is_declared(const ast::term &term) const {
            return std::visit([&](auto &&arg) -> bool {
                return m_name_set.find(arg->get_token().get_lexeme()) != m_name_set.end();
            }, term);
        }

        [[nodiscard]] bool has_type(const ast::term &term, const type_ptr &type) const {
            return std::visit([&](auto &&arg) -> bool {
                const either_type &term_type_list = m_name_map.at(arg->get_token().get_lexeme());

                return std::any_of(term_type_list.begin(), term_type_list.end(),
                                   [&](const type_ptr &t) { return t->is_sub_type_of(type); });
            }, term);
        }

        [[nodiscard]] either_type get_type(const ast::term &term) const {
            return std::visit([&](auto &&arg) {
                const auto &term_type_list = m_name_map.find(arg->get_token().get_lexeme());
                return term_type_list == m_name_map.end() ? either_type{} : m_name_map.at(arg->get_token().get_lexeme());
            }, term);
        }

        void add_decl(const ast::term &term, either_type types) {
            std::visit([&](auto &&arg) {
                m_name_map[arg->get_token().get_lexeme()] = std::move(types);
                m_name_set.emplace(arg->get_token().get_lexeme());
            }, term);
        }

    private:
        type_map m_name_map;
        type_set m_name_set;
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

        /*** TERMS ***/

        [[nodiscard]] bool is_declared(const ast::term &term) const {
            return std::any_of(m_scopes.begin(), m_scopes.end(),
                               [&](const scope &scope) { return scope.is_declared(term); });
        }

        [[nodiscard]] bool has_type(const ast::term &term, const type_ptr &type) const {
            assert_declared(term);

            return std::any_of(m_scopes.begin(), m_scopes.end(),
                               [&](const scope &scope) { return scope.has_type(term, type); });
        }

        [[nodiscard]] either_type get_type(const ast::term &term) const {
            assert_declared(term);

            for (const auto &scope : m_scopes)
                if (const either_type &type = scope.get_type(term); not type.empty())
                    return type;

            return either_type{};
        }

        void assert_declared(const ast::term &term) const {
            if (is_declared(term)) return;

            // todo: throw error
        }

        void assert_declared(const ast::term_list &terms) const {
            for (const ast::term &term : terms)
                assert_declared(term);
        }

        void assert_not_declared(const ast::term &term) const {
            if (not is_declared(term)) return;

            // todo: throw error
        }

        void check_type(const ast::term &term, const type_ptr &type) const {
            assert_declared(term);

            if (std::any_of(m_scopes.begin(), m_scopes.end(),
                            [&](const scope &scope) { return scope.has_type(term, type); }))
                return;

            // todo: throw error
        }

        void add_decl_list(const ast::typed_identifier_list &entities, const type_ptr &default_type,
                           const type_ptr &types_tree) {
            for (const auto &entity : entities) {
                assert_not_declared(entity->get_id());

                either_type entity_type = build_type(entity->get_type(), types_tree, default_type);
                m_scopes.back().add_decl(entity->get_id(), std::move(entity_type));
            }
        }

        void add_decl_list(const ast::typed_variable_list &entities, const type_ptr &default_type,
                           const type_ptr &types_tree) {
            for (const auto &entity : entities) {
                assert_not_declared(entity->get_var());

                either_type entity_type = build_type(entity->get_type(), types_tree, default_type);
                m_scopes.back().add_decl(entity->get_var(), std::move(entity_type));
            }
        }

        void add_decl_list(const ast::identifier_list &ids, const type_ptr &type, const type_ptr &types_tree) {
            for (const auto &id : ids) {
                assert_not_declared(id);

                either_type entity_type = build_type(id, types_tree, type);
                m_scopes.back().add_decl(id, std::move(entity_type));
            }
        }

        void add_decl_list(const ast::variable_list &variables, const type_ptr &type, const type_ptr &types_tree) {
            for (const auto &var : variables) {
                assert_not_declared(var);

                either_type entity_type = build_type(var, types_tree, type);
                m_scopes.back().add_decl(var, std::move(entity_type));
            }
        }

        /*** PREDICATES ***/

        [[nodiscard]] bool is_declared(const ast::identifier_ptr &id, const signature_map &signatures) const {
            return signatures.find(id->get_token().get_lexeme()) != signatures.end();
        }

        [[nodiscard]] either_type_list get_formal_param_types(const ast::identifier_ptr &id) const {
            assert_declared_predicate(id);

            return m_predicate_signatures.at(id->get_token().get_lexeme());
        }

        void assert_declared_predicate(const ast::identifier_ptr &id) const {
            if (is_declared(id, m_predicate_signatures)) return;

            // todo: throw error
        }

        void assert_not_declared_predicate(const ast::identifier_ptr &id) const {
            if (not is_declared(id, m_predicate_signatures)) return;

            // todo: throw error
        }

        void add_decl_predicate(const ast::predicate_decl_ptr &pred, const type_ptr &types_tree) {
            assert_declared_predicate(pred->get_name());

            const type_ptr &object = types_tree->find("object");
            m_predicate_signatures[pred->get_name()->get_token().get_lexeme()] = build_type_list(pred->get_params(), types_tree, object);
            m_static_predicates[pred->get_name()->get_token().get_lexeme()] = pred->is_static();
        }

        void check_predicate_signature(const ast::identifier_ptr &id, const ast::term_list &terms) const {
            assert_declared_predicate(id);
            assert_declared(terms);
            check_signature(m_predicate_signatures, id, terms);
        }

        /*** EVENTS ***/

        void assert_declared_event(const ast::identifier_ptr &id) const {
            if (is_declared(id, m_event_signatures)) return;

            // todo: throw error
        }

        void assert_not_declared_event(const ast::identifier_ptr &id) const {
            if (not is_declared(id, m_event_signatures)) return;

            // todo: throw error
        }

        void add_decl_event(const ast::event_ptr &event, const type_ptr &types_tree) {
            assert_not_declared_event(event->get_name());

            const type_ptr &object = types_tree->find("object");
            const std::string &name = event->get_name()->get_token().get_lexeme();

            if (event->get_params().has_value())
                m_event_signatures[name] = build_type_list((*event->get_params())->get_formal_params(), types_tree, object);
            else
                m_event_signatures[name] = either_type_list{};
        }

        void check_event_signature(const ast::identifier_ptr &id, const ast::term_list &terms) const {
            assert_declared_event(id);
            assert_declared(terms);
            check_signature(m_event_signatures, id, terms);
        }

        /*** ACTION TYPES ***/

        void assert_declared_action_type(const ast::identifier_ptr &id) const {
            if (is_declared(id, m_action_type_signatures)) return;

            // todo: throw error
        }

        void assert_not_declared_action_type(const ast::identifier_ptr &id) const {
            if (not is_declared(id, m_action_type_signatures)) return;

            // todo: throw error
        }

        void add_decl_action_type(const ast::action_type_ptr &action_type, const type_ptr &types_tree) {
            assert_not_declared_action_type(action_type->get_name());

            const type_ptr &event = types_tree->find("event");
            const std::string &name = action_type->get_name()->get_token().get_lexeme();

            auto type_list = either_type_list{action_type->get_events().size(), either_type{event}};
            m_action_signatures[name] = std::move(type_list);
        }

        void check_action_type_signature(const ast::identifier_ptr &id, const ast::term_list &terms) const {
            assert_declared_action_type(id);
            assert_declared(terms);
            check_signature(m_action_type_signatures, id, terms);
        }

        /*** ACTIONS ***/

        void assert_declared_action(const ast::identifier_ptr &id) const {
            if (is_declared(id, m_action_signatures)) return;

            // todo: throw error
        }

        void assert_not_declared_action(const ast::identifier_ptr &id) const {
            if (not is_declared(id, m_action_signatures)) return;

            // todo: throw error
        }

        void add_decl_action(const ast::action_ptr &action, const type_ptr &types_tree) {
            assert_not_declared_action(action->get_name());

            const type_ptr &object = types_tree->find("object");
            const std::string &name = action->get_name()->get_token().get_lexeme();
            m_action_signatures[name] = build_type_list(action->get_params()->get_formal_params(), types_tree, object);
        }

        void check_action_signature(const ast::identifier_ptr &id, const ast::term_list &terms) const {
            assert_declared_action(id);
            assert_declared(terms);
            check_signature(m_action_signatures, id, terms);
        }

    private:
        std::deque<scope> m_scopes;
        signature_map m_predicate_signatures, m_event_signatures, m_action_type_signatures, m_action_signatures;
        static_predicate_map m_static_predicates;

        void check_signature(const signature_map &signatures, const ast::identifier_ptr &id,
                             const ast::term_list &terms) const {
            const auto &types = signatures.at(id->get_token().get_lexeme());

            if (types.size() != terms.size()) {
                std::string many_few = types.size() < terms.size() ? "many" : "few";

                throw EPDDLException{std::string{""}, id->get_token().get_row(), id->get_token().get_col(),
                                     std::string{"Too " + many_few + " arguments for predicate '" +
                                                 id->get_token().get_lexeme() + "'. Expected " +
                                                 std::to_string(types.size()) + ", found " +
                                                 std::to_string(terms.size()) + "."}};
            }

            auto types_it = types.begin();
            auto terms_it = terms.begin();

            while (types_it != types.end()) {
                // We want to check that the type of our current actual parameter is compatible with that of
                // our current formal parameter
                const either_type &param_type = *types_it;            // Type of the formal parameter declared in the predicate definition
                const either_type &term_type  = get_type(*terms_it);  // Type of the actual parameter passed to the predicate

                // We check that the type of the actual parameter is compatible with that of the formal parameter
                if (not are_compatible(param_type, term_type))
                    throw_incompatible_types(param_type, *terms_it, term_type);

                types_it = std::next(types_it);
                terms_it = std::next(terms_it);
            }
        }

        static either_type_list build_type_list(const ast::formal_param_list &params, const type_ptr &types_tree,
                                                const type_ptr &default_type) {
            either_type_list types;

            for (const ast::formal_param &param : params)
                types.push_back(build_type(param->get_type(), types_tree, default_type));

            return types;
        }

        static either_type build_type(const std::optional<ast::type> &entity_decl_type, const type_ptr &types_tree,
                                      const type_ptr &default_type) {
            either_type entity_type;

            if (entity_decl_type.has_value()) {
                if (std::holds_alternative<ast::identifier_ptr>(*entity_decl_type))
                    entity_type = either_type{types_tree->find(std::get<ast::identifier_ptr>(*entity_decl_type))};
                else if (std::holds_alternative<ast::either_type_ptr>(*entity_decl_type)) {
                    const ast::identifier_list &either_type_list =
                            std::get<ast::either_type_ptr>(*entity_decl_type)->get_ids();

                    for (const ast::identifier_ptr &id : either_type_list)
                        entity_type.push_back(types_tree->find(id));
                }
            } else
                entity_type = either_type{default_type};

            return entity_type;
        }

        static bool are_compatible(const either_type &type_formal, const either_type &type_actual) {
            // Let (either ft_1 ft_2 ... ft_m) and (either at_1 at_2 ... at_n) be the types of the formal and
            // actual parameter, respectively. If for all primitive types at_j there exists a primitive type ft_i
            // such that at_j is a subtype of ft_i, then the two either-types are compatible
            return std::all_of(type_actual.begin(), type_actual.end(),
                        [&](const type_ptr &at) {
                            return std::any_of(type_formal.begin(), type_formal.end(),
                                               [&](const type_ptr &ft) {
                                                   return at->is_sub_type_of(ft);
                                               });
                        });
        }

        static std::string to_string(const either_type &types) {
            if (types.size() == 1)
                return types.front()->get_name();
            else {
                std::string either_type = "(either";
                for (const type_ptr &t : types) either_type += " " + t->get_name();
                return either_type + ")";
            }
        }

        static void throw_incompatible_types(const either_type &type_formal, const ast::term &term,
                                             const either_type &type_actual) {
            const token &tok = std::visit([&](auto &&arg) -> const token & {
                return arg->get_token();
            }, term);

//                    if (std::holds_alternative<ast::identifier_ptr>(*terms_it))
//                        tok = std::get<ast::identifier_ptr>(*terms_it)->get_token_ptr();


            throw EPDDLException{std::string{""}, tok.get_row(), tok.get_col(),
                                 std::string{"Expected type '" + to_string(type_formal) +
                                             "' is incompatible with actual type '" + to_string(type_actual) + "'."}};
            // todo: improve error message like "in predicate p..."
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
