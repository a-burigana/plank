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
#include "../language_grounder.h"
#include "../variables_assignment.h"
#include <algorithm>
#include <variant>

using namespace epddl::type_checker;

namespace epddl::grounder {
    class list_comprehensions_handler {
    public:
//        [[nodiscard]] static bool has_next(combinations_handler &handler,
//                                           const std::optional<ast::formula_ptr> &condition,
//                                           const del::atom_set &static_atoms) {
//            return false;
//        }
//
//        [[nodiscard]] static const combination &next(combinations_handler &handler,
//                                                     const std::optional<ast::formula_ptr> &condition,
//                                                     const del::atom_set &static_atoms) {
//            return handler.next();
////            while (not holds_condition(handler.next()))
//        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const std::optional<ast::formula_ptr> &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            return not f.has_value() or std::visit([&](auto &&arg) -> bool {
                return list_comprehensions_handler::holds_condition(entities, assignment, arg, static_atoms, language);
            }, *f);
        }

        [[nodiscard]]
        static combination_deque all(combinations_handler &handler, const entities_context &entities,
                                     variables_assignment &assignment, const std::optional<ast::formula_ptr> &f,
                                     const del::atom_set &static_atoms, const del::language_ptr &language) {
            combination_deque all;

            while (handler.has_next()) {
                combination next = handler.next();
                assignment.push(handler.get_typed_vars(), next);

                if (not f.has_value() or holds_condition(entities, assignment, *f, static_atoms, language))
                    all.emplace_back(next);

                assignment.pop();
            }
            return all;
        }

    private:
        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::true_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            return true;
        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::false_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            return false;
        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::predicate_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            unsigned long id = language_grounder::get_predicate_id(f->get_predicate(), assignment, language);
            return static_atoms.find(id);
        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::eq_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            unsigned long id_1 = language_grounder::get_term_id(f->get_first_term(), entities, assignment);
            unsigned long id_2 = language_grounder::get_term_id(f->get_second_term(), entities, assignment);

            return id_1 == id_2;
        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::neq_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            unsigned long id_1 = language_grounder::get_term_id(f->get_first_term(), entities, assignment);
            unsigned long id_2 = language_grounder::get_term_id(f->get_second_term(), entities, assignment);

            return id_1 != id_2;
        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::not_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            return not list_comprehensions_handler::holds_condition(
                    entities, assignment, f->get_formula(), static_atoms, language);
        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::and_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            return std::all_of(f->get_formulas().begin(), f->get_formulas().end(),
                               [&](const ast::formula_ptr &f_) -> bool {
                return list_comprehensions_handler::holds_condition(entities, assignment, f_, static_atoms, language);
            });
        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::or_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            return std::any_of(f->get_formulas().begin(), f->get_formulas().end(),
                               [&](const ast::formula_ptr &f_) -> bool {
                return list_comprehensions_handler::holds_condition(entities, assignment, f_, static_atoms, language);
            });
        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::imply_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            return
                not list_comprehensions_handler::holds_condition(
                            entities, assignment, f->get_first_formula(), static_atoms, language) or
                    list_comprehensions_handler::holds_condition(
                            entities, assignment, f->get_second_formula(), static_atoms, language);
        }

        [[nodiscard]]
        static bool holds_condition(const entities_context &entities, const variables_assignment &assignment,
                                    const ast::box_formula_ptr &f, const del::atom_set &static_atoms,
                                    const del::language_ptr &language) {
            return false;
        }
    };

    class formulas_and_lists_grounder {
    public:
        static del::formula_ptr build_goal(const planning_specification &spec, const context &context, const type_ptr &types_tree,
                                           const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_condition(const std::optional<formula_ptr> &f, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &static_atoms, const del::language_ptr &language);


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
                                                 const del::atom_set &static_atoms, const del::language_ptr &language,
                                                 Args... args) {
            return std::visit([&](auto &&arg) -> std::list<output_type> {
                return formulas_and_lists_grounder::build_list<input_type, output_type, Args...>(
                        arg, ground_elem, context, types_tree, default_type, assignment, static_atoms, language, args...);
            }, list);
        }

    private:
        static del::formula_ptr build_formula(const ast::true_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::false_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::predicate_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::eq_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::neq_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::not_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::and_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::or_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::imply_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::forall_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::exists_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::box_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::diamond_formula_ptr &f, const context &context,
                                              const type_ptr &types_tree, variables_assignment &assignment,
                                              const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::agent_set build_agent_group(const ast::modality_index_ptr &m, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::agent_set build_agent_group(const ast::term &m, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::agent_set build_agent_group(const ast::list<ast::simple_agent_group_ptr> &m, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &static_atoms, const del::language_ptr &language);

        static del::agent_set build_agent_group(const ast::all_group_modality_ptr &m, const context &context,
                                                const type_ptr &types_tree, variables_assignment &assignment,
                                                const del::atom_set &static_atoms, const del::language_ptr &language);


        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::singleton_list_ptr<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 const context &context, const type_ptr &types_tree,
                                                 const type_ptr &default_type, variables_assignment &assignment,
                                                 const del::atom_set &static_atoms, const del::language_ptr &language,
                                                 Args... args) {
            return std::list<output_type>{ground_elem(list->get_elem(), context, types_tree, default_type,
                                                     assignment, static_atoms, language, args...)};
        }

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::and_list_ptr<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 const context &context, const type_ptr &types_tree,
                                                 const type_ptr &default_type, variables_assignment &assignment,
                                                 const del::atom_set &static_atoms, const del::language_ptr &language,
                                                 Args... args) {
            std::list<output_type> output_list;

            for (const ast::list<input_type> &elem : list->get_list()) {
                auto ground_elem_list = formulas_and_lists_grounder::build_list<input_type, output_type, Args...>(
                        elem, ground_elem, context, types_tree, default_type, assignment, static_atoms, language, args...);

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
                                                 const del::atom_set &static_atoms, const del::language_ptr &language,
                                                 Args... args) {
            std::list<output_type> output_list;

//            del::formula_ptr condition = formulas_and_lists_grounder::build_condition(
//                    list->get_list_compr()->get_condition(), context, types_tree, assignment, static_atoms, language);

            combinations_handler handler{list->get_list_compr()->get_formal_params(), context, types_tree,
                                         type_checker::either_type{type_utils::find(types_tree, "object")}};

            for (const combination &combination :
                list_comprehensions_handler::all(handler, context.entities, assignment,
                                                 list->get_list_compr()->get_condition(), static_atoms, language)) {
                assignment.push(handler.get_typed_vars(), combination);
                auto ground_elem_list = formulas_and_lists_grounder::build_list<input_type, output_type, Args...>(
                                list->get_list(), ground_elem, context, types_tree,
                                default_type, assignment, static_atoms, language, args...);

                for (output_type ground_elem_ : ground_elem_list)
                    output_list.emplace_back(std::move(ground_elem_));

                assignment.pop();
            }

            return output_list;
        }
    };
}

#endif //EPDDL_FORMULAS_AND_LISTS_GROUNDER_H
