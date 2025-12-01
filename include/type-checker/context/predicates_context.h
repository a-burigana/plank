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

#ifndef EPDDL_PREDICATES_CONTEXT_H
#define EPDDL_PREDICATES_CONTEXT_H

#include "context_types.h"
#include "entities_context.h"
#include "types_context.h"
#include "context_utils.h"

namespace epddl::type_checker {
    class predicates_context {
    public:
        predicates_context() = default;

        [[nodiscard]] const signature_map &get_predicate_signatures() const { return m_predicate_signatures; }
        [[nodiscard]] const ast_node_map<ast::predicate_decl_ptr> &get_predicates_map() const { return m_predicates_map; }
        [[nodiscard]] const string_bool_map &get_static_predicates() const { return m_static_predicates; }

        [[nodiscard]] const ast::predicate_decl_ptr &get_predicate_decl(const ast::identifier_ptr &id) const {
            assert_declared_predicate(id);
            return m_predicates_map.at(id->get_token().get_lexeme());
        }

        [[nodiscard]] const typed_var_list &get_formal_param_types_predicate(const ast::identifier_ptr &id) const {
            assert_declared_predicate(id);
            return m_predicate_signatures.at(id->get_token().get_lexeme());
        }

        void assert_declared_predicate(const ast::identifier_ptr &id) const {
            if (context_utils::is_declared(id, m_predicate_signatures)) return;

            throw EPDDLException(id->get_info(), "Use of undeclared predicate name '" + id->get_token().get_lexeme() + "'.");
        }

        void assert_not_declared_predicate(const ast::identifier_ptr &id) const {
            if (not context_utils::is_declared(id, m_predicate_signatures)) return;
            const ast::info &previous_info = m_predicates_map.at(id->get_token().get_lexeme())->get_info();

            throw EPDDLException(id->get_info(), "Redeclaration of predicate '" + id->get_token().get_lexeme() +
                                                 "'. Previous declaration at (" + std::to_string(previous_info.m_row) + ":" +
                                                 std::to_string(previous_info.m_col) + ").");
        }

        [[nodiscard]] bool is_static_predicate(const ast::identifier_ptr &id) const {
            assert_declared_predicate(id);
            return m_static_predicates.at(id->get_token().get_lexeme());
        }

        void assert_static_predicate(const ast::identifier_ptr &id) const {
            if (is_static_predicate(id)) return;

            throw EPDDLException(id->get_info(), "Predicate '" + id->get_token().get_lexeme() + "' is not static.");
        }

        void add_decl_predicate(entities_context &entities_context, const ast::predicate_decl_ptr &pred, const type_ptr &types_tree) {
            assert_not_declared_predicate(pred->get_name());

            // Checking for duplicate variables in predicate signature
            entities_context.push();
            entities_context.add_decl_list(pred->get_params(), type_utils::find(types_tree, "entity"), types_tree);
            entities_context.pop();

            const type_ptr &object = type_utils::find(types_tree, "object");
            m_predicate_signatures[pred->get_name()->get_token().get_lexeme()] = types_context::build_typed_var_list(pred->get_params(), types_tree, either_type{object});
            m_static_predicates[pred->get_name()->get_token().get_lexeme()] = pred->is_static();

            m_predicates_map[pred->get_name()->get_token().get_lexeme()] = pred;
        }

        void check_predicate_signature(const entities_context &entities_context, const ast::identifier_ptr &id, const ast::term_list &terms) const {
            assert_declared_predicate(id);
            entities_context.assert_declared(terms);
            context_utils::check_signature(m_predicate_signatures, id, terms, entities_context.get_scopes(), "predicate");
        }

    private:
        signature_map m_predicate_signatures;
        string_bool_map m_static_predicates;
        ast_node_map<ast::predicate_decl_ptr> m_predicates_map;
    };
}

#endif //EPDDL_PREDICATES_CONTEXT_H
