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

#ifndef EPDDL_FORMULAS_AND_LISTS_GROUNDER_H
#define EPDDL_FORMULAS_AND_LISTS_GROUNDER_H

#include "../../type-checker/context/context.h"
#include "../../del/language/language.h"
#include "../../del/language/formulas.h"
#include "../combinations_handler.h"
#include "../variables_assignment.h"
#include <algorithm>
#include <variant>

using namespace epddl::type_checker;

namespace epddl::grounder {
    class list_comprehensions_handler {
    public:
//        [[nodiscard]] static bool has_next(combinations_handler &handler, const del::formula_ptr &condition,
//                                           const del::atom_set &s_static) {
//            return false;
//        }

//        [[nodiscard]] static const combination &next(combinations_handler &handler, const del::formula_ptr &condition, const del::atom_set &s_static) {
//            return handler.next();
////            while (not holds_condition(handler.next()))
//        }

        [[nodiscard]] static combination_deque all(combinations_handler &handler, const del::formula_ptr &f,
                                                   const del::atom_set &s_static) {
            combination_deque all;

            while (handler.has_next())
                if (combination next = handler.next(); holds_condition(next, f, s_static))
                    all.emplace_back(next);

            return all;
        }

    private:
        [[nodiscard]] static bool holds_condition(const combination &combination, const del::formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return std::visit([&](auto &&arg) -> bool {
                return list_comprehensions_handler::holds_condition(combination, arg, s_static);
            }, f);
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::true_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return true;
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::false_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return false;
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::atom_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return s_static.find(f->get_atom());
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::not_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return not list_comprehensions_handler::holds_condition(combination, f->get_formula(), s_static);
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::and_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return std::all_of(f->get_formulas().begin(), f->get_formulas().end(),
                               [&](const del::formula_ptr &f_) -> bool {
                return list_comprehensions_handler::holds_condition(combination, f_, s_static);
            });
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::or_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return std::any_of(f->get_formulas().begin(), f->get_formulas().end(),
                               [&](const del::formula_ptr &f_) -> bool {
                return list_comprehensions_handler::holds_condition(combination, f_, s_static);
            });
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::imply_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return not list_comprehensions_handler::holds_condition(combination, f->get_first_formula(), s_static) or
                    list_comprehensions_handler::holds_condition(combination, f->get_second_formula(), s_static);
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::box_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return false;
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::diamond_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return false;
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::kw_box_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return false;
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::kw_diamond_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return false;
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::c_box_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return false;
        }

        [[nodiscard]] static bool holds_condition(const combination &combination, const del::c_diamond_formula_ptr &f,
                                                  const del::atom_set &s_static) {
            return false;
        }
    };

    class formulas_and_lists_grounder {
    public:
        static del::formula_ptr build_goal(const planning_specification &spec, const context &context, const type_ptr &types_tree,
                                           const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);


        template<typename input_type, typename output_type, typename... Args>
        using grounding_function_t = std::function<output_type(
                const input_type &,
                const context &,
                const type_ptr &,
                const type_ptr &,
                variables_assignment &,
                const del::atom_set &,
                const del::language_ptr &,
                Args...)>;

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::list<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 const context &context, const type_ptr &types_tree,
                                                 const type_ptr &default_type, variables_assignment &assignment,
                                                 const del::atom_set &s_static, const del::language_ptr &language,
                                                 Args... args) {
            return std::visit([&](auto &&arg) -> std::list<output_type> {
                return formulas_and_lists_grounder::build_list<input_type, output_type, Args...>(
                        arg, ground_elem, context, types_tree, default_type, assignment, s_static, language, args...);
            }, list);
        }

    private:
        static del::formula_ptr build_formula(const ast::true_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::false_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::predicate_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::eq_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::neq_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::not_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::and_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::or_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::imply_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::forall_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::exists_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::box_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::diamond_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &s_static, const del::language_ptr &language);

        static del::agent_set build_agent_group(const ast::modality_index_ptr &m, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &s_static, const del::language_ptr &language);

        static del::agent_set build_agent_group(const ast::term &m, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &s_static, const del::language_ptr &language);

        static del::agent_set build_agent_group(const ast::list<ast::simple_agent_group_ptr> &m, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &s_static, const del::language_ptr &language);

        static del::agent_set build_agent_group(const ast::all_group_modality_ptr &m, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &s_static, const del::language_ptr &language);

        static del::formula_ptr build_condition(const std::optional<formula_ptr> &f, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &s_static, const del::language_ptr &language);


        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::singleton_list_ptr<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 const context &context, const type_ptr &types_tree,
                                                 const type_ptr &default_type, variables_assignment &assignment,
                                                 const del::atom_set &s_static, const del::language_ptr &language,
                                                 Args... args) {
            return std::list<output_type>{ground_elem(list->get_elem(), context, types_tree, default_type,
                                                     assignment, s_static, language, args...)};
        }

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::and_list_ptr<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 const context &context, const type_ptr &types_tree,
                                                 const type_ptr &default_type, variables_assignment &assignment,
                                                 const del::atom_set &s_static, const del::language_ptr &language,
                                                 Args... args) {
            std::list<output_type> output_list;

            for (const ast::list<input_type> &elem : list->get_list()) {
                auto ground_elem_list = formulas_and_lists_grounder::build_list<input_type, output_type, Args...>(
                        elem, ground_elem, context, types_tree, default_type, assignment, s_static, language, args...);

                for (output_type ground_elem_ : ground_elem_list)
                    output_list.emplace_back(std::move(ground_elem_));
            }
            return output_list;
        }

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::forall_list_ptr<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 const context &context, const type_ptr &types_tree,
                                                 const type_ptr &default_type, variables_assignment &assignment,
                                                 const del::atom_set &s_static, const del::language_ptr &language,
                                                 Args... args) {
            std::list<output_type> output_list;

            del::formula_ptr condition = formulas_and_lists_grounder::build_condition(
                    list->get_list_compr()->get_condition(), context, types_tree, assignment, s_static, language);

            combinations_handler handler{list->get_list_compr()->get_formal_params(), context, types_tree,
                                         type_checker::either_type{type_utils::find(types_tree, "object")}};

            for (const combination &combination : list_comprehensions_handler::all(handler, condition, s_static)) {
                assignment.push(handler.get_typed_vars(), combination);
                auto ground_elem_list = formulas_and_lists_grounder::build_list<input_type, output_type, Args...>(
                                list->get_list(), ground_elem, context, types_tree,
                                default_type, assignment, s_static, language, args...);

                for (output_type ground_elem_ : ground_elem_list)
                    output_list.emplace_back(std::move(ground_elem_));

                assignment.pop();
            }

            return output_list;
        }
    };
}

#endif //EPDDL_FORMULAS_AND_LISTS_GROUNDER_H
