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

#ifndef PLANK_FORMULAS_AND_LISTS_TYPE_CHECKER_H
#define PLANK_FORMULAS_AND_LISTS_TYPE_CHECKER_H

#include <functional>

#include "../context/context.h"
#include "../../ast/common/formulas_ast.h"
#include <optional>

namespace epddl::type_checker {
    class formulas_and_lists_type_checker {
    public:
        static void check_formula(const ast::formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);

        static void check_formula(const ast::true_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::false_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::predicate_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::eq_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::neq_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
//        static void check_formula(const ast::in_formula_ptr &f, context &context,
//        error_manager_ptr &err_manager,
//        bool assert_static = false);
        static void check_formula(const ast::not_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::and_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::or_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::imply_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::box_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::diamond_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::forall_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);
        static void check_formula(const ast::exists_formula_ptr &f, context &context,
                                  error_manager_ptr &err_manager,
                                  bool assert_static = false);

        static void check_list_comprehension(const ast::list_comprehension_ptr &list_compr, context &context,
                                             error_manager_ptr &err_manager,
                                             const type_ptr &default_type);

        static void check_agent_group(const ast::list<ast::simple_agent_group_ptr> &list, context &context,
                                      error_manager_ptr &err_manager,
                                      bool group_only_modality = false);

        static void check_modality_index(const ast::modality_index_ptr &index, context &context,
                                         error_manager_ptr &err_manager,
                                         bool group_only_modality);

        static void check_modality_index_type(const ast::term &term, context &context,
                                              error_manager_ptr &err_manager,
                                              bool group_only_modality);

        static void check_literal(const ast::literal_ptr &l, context &context,
                                  error_manager_ptr &err_manager);

        template<typename Elem, typename... Args>
        using check_function_t = std::function<void(
                const Elem &,
                context &,
                error_manager_ptr &,
                const type_ptr &, Args...)>;

        template<typename Elem, typename... Args>
        static void check_list(const ast::list<Elem> &list,
                               const check_function_t<Elem, Args...> &check_elem, context &context,
                               error_manager_ptr &err_manager, const type_ptr &default_type, Args... args) {
            std::visit([&](auto &&arg) {
                formulas_and_lists_type_checker::check_list<Elem, Args...>(
                        arg, check_elem, context, err_manager, default_type, args...);
            }, list);
        }

        [[nodiscard]] static bool is_propositional_formula(const ast::formula_ptr &f);

    private:
        template<typename Elem, typename... Args>
        static void check_list(const ast::singleton_list_ptr<Elem> &list,
                               const check_function_t<Elem, Args...> &check_elem, context &context,
                               error_manager_ptr &err_manager, const type_ptr &default_type, Args... args) {
            check_elem(list->get_elem(), context, err_manager, default_type, args...);
        }

        template<typename Elem, typename... Args>
        static void check_list(const ast::and_list_ptr<Elem> &list,
                               const check_function_t<Elem, Args...> &check_elem, context &context,
                               error_manager_ptr &err_manager, const type_ptr &default_type, Args... args) {
            for (const ast::list<Elem> &elem : list->get_list())
                formulas_and_lists_type_checker::check_list<Elem, Args...>(elem, check_elem, context,
                                                                           err_manager, default_type, args...);
        }

        template<typename Elem, typename... Args>
        static void check_list(const ast::forall_list_ptr<Elem> &list,
                               const check_function_t<Elem, Args...> &check_elem, context &context,
                               error_manager_ptr &err_manager, const type_ptr &default_type, Args... args) {
            context.entities.push();
            formulas_and_lists_type_checker::check_list_comprehension(
                    list->get_list_compr(), context, err_manager, default_type);
            formulas_and_lists_type_checker::check_list<Elem, Args...>(list->get_list(), check_elem, context,
                                                                       err_manager, default_type, args...);
            context.entities.pop();
        }

        [[nodiscard]] static bool is_group_only_modality(const ast::modality_ptr &mod);

        static bool is_propositional_formula(const ast::true_formula_ptr &f);
        static bool is_propositional_formula(const ast::false_formula_ptr &f);
        static bool is_propositional_formula(const ast::predicate_formula_ptr &f);
        static bool is_propositional_formula(const ast::eq_formula_ptr &f);
        static bool is_propositional_formula(const ast::neq_formula_ptr &f);
        static bool is_propositional_formula(const ast::not_formula_ptr &f);
        static bool is_propositional_formula(const ast::and_formula_ptr &f);
        static bool is_propositional_formula(const ast::or_formula_ptr &f);
        static bool is_propositional_formula(const ast::imply_formula_ptr &f);
        static bool is_propositional_formula(const ast::box_formula_ptr &f);
        static bool is_propositional_formula(const ast::diamond_formula_ptr &f);
        static bool is_propositional_formula(const ast::forall_formula_ptr &f);
        static bool is_propositional_formula(const ast::exists_formula_ptr &f);

        [[nodiscard]] static bool is_static_formula(const ast::formula_ptr &f, context &context,
                                                    error_manager_ptr &err_manager);

        static bool is_static_formula(const ast::true_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::false_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::predicate_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::eq_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::neq_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::not_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::and_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::or_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::imply_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::box_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::diamond_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::forall_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
        static bool is_static_formula(const ast::exists_formula_ptr &f, context &context,
                                      error_manager_ptr &err_manager);
    };
}

#endif //PLANK_FORMULAS_AND_LISTS_TYPE_CHECKER_H
