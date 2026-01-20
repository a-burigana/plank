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

#ifndef PLANK_COMPONENTS_NAMES_CONTEXT_H
#define PLANK_COMPONENTS_NAMES_CONTEXT_H

#include <string>
#include <unordered_set>
#include "../../error-manager/epddl_exception.h"
#include "../../ast/libraries/act_type_library_ast.h"
#include "../../ast/domains/domain_ast.h"
#include "../../ast/problems/problem_ast.h"

namespace epddl::type_checker {
    class components_names_context {
    public:
        components_names_context() = default;

        [[nodiscard]] bool is_declared_library(const std::string &name) {
            return std::find(m_libraries_names.begin(),
                             m_libraries_names.end(), name) != m_libraries_names.end();
        }

        [[nodiscard]] bool is_declared_domain(const std::string &name) {
            return m_domain_name == name;
        }

        [[nodiscard]] bool is_declared_problem(const std::string &name) {
            return m_problem_name == name;
        }

        void assert_declared_library(error_manager_ptr &err_manager, const ast::identifier_ptr &id) {
            if (is_declared_library(id->get_token().get_lexeme())) return;

            err_manager->throw_error(error_type::undeclared_element, id->get_token_ptr(),
                                     {error_manager::get_error_info(decl_type::action_type_name)});
        }

        void assert_not_declared_library(error_manager_ptr &err_manager, const ast::identifier_ptr &id) {
            if (not is_declared_library(id->get_token().get_lexeme())) return;

            err_manager->throw_error(error_type::reserved_element_redeclaration, id->get_token_ptr(),
                                     {error_manager::get_error_info(decl_type::library)});
        }

        void assert_declared_domain(error_manager_ptr &err_manager, const ast::identifier_ptr &id) {
            if (is_declared_domain(id->get_token().get_lexeme())) return;

            err_manager->throw_error(error_type::reserved_element_redeclaration, id->get_token_ptr(),
                                     {error_manager::get_error_info(decl_type::domain)});
        }

        void add_library_name(error_manager_ptr &err_manager, const ast::act_type_library_ptr &library) {
            assert_not_declared_library(err_manager, library->get_name());
            m_libraries_names.emplace_back(library->get_name()->get_token().get_lexeme());
        }

        void set_domain_name(const ast::domain_ptr &domain) {
            m_domain_name = domain->get_name()->get_token().get_lexeme();
        }

        void set_problem_name(const ast::problem_ptr &problem) {
            m_problem_name = problem->get_name()->get_token().get_lexeme();
        }

        [[nodiscard]] const std::list<std::string> &get_libraries_names() const {
            return m_libraries_names;
        }

        [[nodiscard]] const std::string &get_domain_name() const {
            return m_domain_name;
        }

        [[nodiscard]] const std::string &get_problem_name() const {
            return m_problem_name;
        }

    private:
        std::string m_domain_name, m_problem_name;
        std::list<std::string> m_libraries_names;
    };
}
#endif //PLANK_COMPONENTS_NAMES_CONTEXT_H
