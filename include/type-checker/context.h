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
#include <algorithm>
#include <iterator>
#include <string>
#include <type_traits>
#include <map>
#include <unordered_set>
#include <variant>

namespace epddl::type_checker {
    using identifier_map = std::unordered_map<ast::identifier_ptr, type_ptr>;
    using variable_map = std::unordered_map<ast::variable_ptr, type_ptr>;
    using name_map = std::unordered_map<std::string, type_ptr>;
    using name_set = std::unordered_set<std::string>;

    class scope {
    public:
        scope(const type_ptr &types_tree) :
            m_types_tree{types_tree} {}

        [[nodiscard]] bool is_declared(const ast::term &term) const {
            return std::visit([&](auto &&arg) -> bool {
                return m_name_set.find(arg->get_token().get_lexeme()) != m_name_set.end();
            }, term);
//            return std::holds_alternative<ast::identifier_ptr>(term)
//                    ? m_id_map .find(std::get<ast::identifier_ptr>(term)) != m_id_map .end()
//                    : m_var_map.find(std::get<ast::variable_ptr  >(term)) != m_var_map.end();
        }

        [[nodiscard]] bool has_type(const ast::term &term, const type_ptr &type) const {
            return std::visit([&](auto &&arg) -> bool {
                return m_name_map.at(arg->get_token().get_lexeme()) == type;
            }, term);
//            return std::holds_alternative<ast::identifier_ptr>(term)
//                   ? m_id_map .at(std::get<ast::identifier_ptr>(term)) == type
//                   : m_var_map.at(std::get<ast::variable_ptr  >(term)) == type;
        }

        void assert_declared(const ast::term &term) const {
            if (is_declared(term)) return;

            // todo: throw error
        }

        void assert_not_declared(const ast::term &term) const {
            if (not is_declared(term)) return;

            // todo: throw error
        }

        void check_type(const ast::term &term, const type_ptr &type) const {
            assert_declared(term);
            if (has_type(term, type)) return;

            // todo: throw error
        }

        void add_decl(const ast::term &term, const type_ptr &type) {
            assert_not_declared(term);

            std::visit([&](auto &&arg) {
                m_name_map[arg->get_token().get_lexeme()] = type;
                m_name_set.emplace(arg->get_token().get_lexeme());
            }, term);
//            if (std::holds_alternative<ast::identifier_ptr>(term))
//                m_id_map[std::get<ast::identifier_ptr>(term)] = type;
//            else
//                m_var_map[std::get<ast::variable_ptr>(term)] = type;
        }

        void add_decl_list(const ast::typed_identifier_list &entities, const type_ptr &default_type) {
            for (const auto &entity : entities) {
                auto &entity_id = entity->get_id();
                auto &entity_type_id = entity->get_type();

                auto entity_type = entity_type_id.has_value()
                                   ? m_types_tree->find((*entity_type_id)->get_token().get_lexeme())
                                   : default_type;

                add_decl(entity_id, entity_type);
            }
        }

        [[nodiscard]] bool is_disjoint(const scope &scope) const {
            name_set intersection;
            std::set_intersection(m_name_set.begin(), m_name_set.end(),
                                  scope.m_name_set.begin(), scope.m_name_set.end(),
                                  std::inserter(intersection, std::next(intersection.begin())));
            return intersection.empty();
        }

        void assert_disjoint(const scope &scope) const {
            if (is_disjoint(scope)) return;

            // todo: throw error
        }

    private:
        const type_ptr &m_types_tree;
//        identifier_map m_id_map;
//        variable_map  m_var_map;
        name_map m_name_map;
        name_set m_name_set;
    };

    class context {
    public:
        context() = default;

        void pop() {
            m_scopes.pop_back();
        }

        void push(scope scope) {
            assert_disjoint(scope);
            m_scopes.push_back(std::move(scope));
        }

        void assert_declared(const ast::term &term) const {
            if (std::any_of(m_scopes.begin(), m_scopes.end(),
                            [&](const scope &scope) { return scope.is_declared(term); }))
                return;

            // todo: throw error
        }

        void check_type(const ast::term &term, const type_ptr &type) const {
            if (std::any_of(m_scopes.begin(), m_scopes.end(),
                            [&](const scope &scope) { return scope.has_type(term, type); }))
                return;

            // todo: throw error
        }

    private:
        std::deque<scope> m_scopes;

        void assert_disjoint(const scope &scope) const {
            for (const auto &s : m_scopes)
                s.assert_disjoint(scope);
        }
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
