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
#include "types_tree.h"
#include <algorithm>
#include <type_traits>
#include <map>
#include <variant>

namespace epddl::type_checker {
    using identifier_map = std::unordered_map<ast::identifier_ptr, types_tree_ptr>;
    using variable_map = std::unordered_map<ast::variable_ptr, types_tree_ptr>;

    class scope {
    public:
        scope() = default;

        void check_declared_identifier(const ast::identifier_ptr &id) const {
            if (m_id_map.find(id) != m_id_map.end()) return;

            // todo: throw error
        }

        void check_type_identifier(const ast::identifier_ptr &id, const types_tree_ptr &type) const {
            check_declared_identifier(id);
            if (m_id_map.at(id) == type) return;

            // todo: throw error
        }

        void add_identifier_decl(const ast::identifier_ptr &id, const types_tree_ptr &type) {
            check_declared_identifier(id);
            m_id_map[id] = type;
        }

        void check_declared_variable(const ast::variable_ptr &var) const {
            if (m_var_map.find(var) != m_var_map.end()) return;

            // todo: throw error
        }

        void check_type_variable(const ast::variable_ptr &var, const types_tree_ptr &type) const {
            check_declared_variable(var);
            if (m_var_map.at(var) == type) return;

            // todo: throw error
        }

        void add_variable_decl(const ast::variable_ptr &var, const types_tree_ptr &type) {
            check_declared_variable(var);
            m_id_map[var] = type;
        }

        void check_disjoint_scope(const scope &scope) const {
            const auto &find_id = [&] (const identifier_map::value_type &id_type) {
                return m_id_map.find(id_type.first) == m_id_map.end();
            };

            const auto &find_var = [&] (const variable_map::value_type &var_type) {
                return m_var_map.find(var_type.first) == m_var_map.end();
            };

            bool disjoint_ids  = std::all_of(scope.m_id_map.begin(), scope.m_id_map.end(), find_id);
            bool disjoint_vars = std::all_of(scope.m_var_map.begin(), scope.m_var_map.end(), find_var);

            if (disjoint_ids and disjoint_vars) return;

            // todo: throw error
        }

    private:
        identifier_map m_id_map;
        variable_map  m_var_map;
    };

    class context {
    public:
        context() = default;

        void pop() {
            m_scopes.pop_back();
        }

        void push(scope scope) {
            check_disjoint_scope(scope);
            m_scopes.push_back(std::move(scope));
        }

        void check_declared_identifier(const ast::identifier_ptr &id) const {
            m_scopes.back().check_declared_identifier(id);
        }

        void check_type_identifier(const ast::identifier_ptr &id, const types_tree_ptr &type) const {
            m_scopes.back().check_type_identifier(id, type);
        }

        void check_declared_variable(const ast::variable_ptr &var) const {
            m_scopes.back().check_declared_variable(var);
        }

        void check_type_variable(const ast::variable_ptr &var, const types_tree_ptr &type) const {
            m_scopes.back().check_type_variable(var, type);
        }

    private:
        std::deque<scope> m_scopes;

        void check_disjoint_scope(const scope &scope) const {
            for (const auto &s : m_scopes)
                s.check_disjoint_scope(scope);
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
