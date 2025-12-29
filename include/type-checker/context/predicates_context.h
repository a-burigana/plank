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
        explicit predicates_context(error_manager_ptr domain_err_manager) :
                m_domain_err_manager{std::move(domain_err_manager)} {}

        [[nodiscard]] const signature_map &get_predicate_signatures() const { return m_predicate_signatures; }
        [[nodiscard]] const ast_node_map<ast::predicate_decl_ptr> &get_predicates_map() const { return m_predicates_map; }
        [[nodiscard]] const string_bool_map &get_facts() const { return m_facts; }

        [[nodiscard]] const ast::predicate_decl_ptr &get_predicate_decl(const ast::identifier_ptr &id) const {
//            assert_declared_predicate(id);
            return m_predicates_map.at(id->get_token().get_lexeme());
        }

        [[nodiscard]] const typed_var_list &get_formal_param_types_predicate(const ast::identifier_ptr &id) const {
//            assert_declared_predicate(id);
            return m_predicate_signatures.at(id->get_token().get_lexeme());
        }

        void assert_declared_predicate(error_manager_ptr &err_manager, const ast::identifier_ptr &id) const {
            if (context_utils::is_declared(id, m_predicate_signatures)) return;

            err_manager->throw_error(error_type::undeclared_element, id->get_token_ptr(),
                                     {error_manager::get_error_info(decl_type::predicate_name)});
        }

        void assert_not_declared_predicate(const ast::identifier_ptr &id) const {
            if (not context_utils::is_declared(id, m_predicate_signatures)) return;
            const ast::info &previous_info = m_predicates_map.at(id->get_token().get_lexeme())->get_info();

            m_domain_err_manager->push_error_info(error_manager::get_error_info(
                    decl_type::predicate_decl, id->get_token().get_lexeme()));
            m_domain_err_manager->throw_error(error_type::element_redeclaration, id->get_token_ptr(),
                                              {error_manager::get_error_info(decl_type::predicate),
                                               std::to_string(previous_info.m_row),
                                               std::to_string(previous_info.m_col)});
        }

        [[nodiscard]] bool is_fact(const std::string &name) const {
            return m_facts.at(name);
        }

        [[nodiscard]] bool is_fact(error_manager_ptr &err_manager, const ast::identifier_ptr &id) const {
            assert_declared_predicate(err_manager, id);
            return m_facts.at(id->get_token().get_lexeme());
        }

        void assert_fact(error_manager_ptr &err_manager, const ast::identifier_ptr &id) const {
            if (is_fact(err_manager, id)) return;

            err_manager->throw_error(error_type::predicate_is_not_fact, id->get_token_ptr());
        }

        void add_decl_predicate(const types_context &types_context, entities_context &entities_context,
                                const ast::predicate_decl_ptr &pred) {
            assert_not_declared_predicate(pred->get_name());
            const type_ptr
                &entity = types_context.get_type("entity"),
                &object = types_context.get_type("object");

            // Checking for duplicate variables in predicate signature
            entities_context.push();
            entities_context.add_decl_list(types_context, m_domain_err_manager, pred->get_params(), entity);
            entities_context.pop();

            const std::string &pred_name = pred->get_name()->get_token().get_lexeme();

            m_predicate_signatures[pred_name] = types_context.build_typed_var_list(
                    m_domain_err_manager, pred->get_params(),
                    either_type{types_context.get_type_id(object)});
            m_facts[pred_name] = pred->is_fact();

            m_predicates_map[pred_name] = pred;
        }

        void check_predicate_signature(const types_context &types_context, const entities_context &entities_context,
                                       error_manager_ptr &err_manager, const ast::identifier_ptr &id,
                                       const ast::term_list &terms) {
            assert_declared_predicate(err_manager, id);

            entities_context.assert_declared(err_manager, terms);
            context_utils::check_signature(types_context, entities_context, err_manager,
                                           m_predicate_signatures, id, terms, "predicate");
        }

    private:
        error_manager_ptr m_domain_err_manager;
        signature_map m_predicate_signatures;
        string_bool_map m_facts;
        ast_node_map<ast::predicate_decl_ptr> m_predicates_map;
    };
}

#endif //EPDDL_PREDICATES_CONTEXT_H
