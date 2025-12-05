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

#include "../grounder_info.h"
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
        static bool holds_condition(const std::optional<ast::formula_ptr> &f, grounder_info &info) {
            return not f.has_value() or std::visit([&](auto &&arg) -> bool {
                return list_comprehensions_handler::holds_condition(arg, info);
            }, *f);
        }

        [[nodiscard]]
        static combination_deque all(const std::optional<ast::formula_ptr> &f, combinations_handler &handler,
                                     grounder_info &info) {
            combination_deque all;

            while (handler.has_next()) {
                combination next = handler.next();
                info.assignment.push(handler.get_typed_vars(), next);

                if (not f.has_value() or holds_condition(*f, info))
                    all.emplace_back(next);

                info.assignment.pop();
            }
            return all;
        }

    private:
        [[nodiscard]]
        static bool holds_condition(const ast::true_formula_ptr &f, grounder_info &info) {
            return true;
        }

        [[nodiscard]]
        static bool holds_condition(const ast::false_formula_ptr &f, grounder_info &info) {
            return false;
        }

        [[nodiscard]]
        static bool holds_condition(const ast::predicate_formula_ptr &f, grounder_info &info) {
            unsigned long id = language_grounder::get_predicate_id(f->get_predicate(), info);
            return info.static_atoms.find(id);
        }

        [[nodiscard]]
        static bool holds_condition(const ast::eq_formula_ptr &f, grounder_info &info) {
            unsigned long id_1 = language_grounder::get_term_id(f->get_first_term(), info);
            unsigned long id_2 = language_grounder::get_term_id(f->get_second_term(), info);

            return id_1 == id_2;
        }

        [[nodiscard]]
        static bool holds_condition(const ast::neq_formula_ptr &f, grounder_info &info) {
            unsigned long id_1 = language_grounder::get_term_id(f->get_first_term(), info);
            unsigned long id_2 = language_grounder::get_term_id(f->get_second_term(), info);

            return id_1 != id_2;
        }

        [[nodiscard]]
        static bool holds_condition(const ast::not_formula_ptr &f, grounder_info &info) {
            return not list_comprehensions_handler::holds_condition(f->get_formula(), info);
        }

        [[nodiscard]]
        static bool holds_condition(const ast::and_formula_ptr &f, grounder_info &info) {
            return std::all_of(f->get_formulas().begin(), f->get_formulas().end(),
                               [&](const ast::formula_ptr &f_) -> bool {
                return list_comprehensions_handler::holds_condition(f_, info);
            });
        }

        [[nodiscard]]
        static bool holds_condition(const ast::or_formula_ptr &f, grounder_info &info) {
            return std::any_of(f->get_formulas().begin(), f->get_formulas().end(),
                               [&](const ast::formula_ptr &f_) -> bool {
                return list_comprehensions_handler::holds_condition(f_, info);
            });
        }

        [[nodiscard]]
        static bool holds_condition(const ast::imply_formula_ptr &f, grounder_info &info) {
            return
                not list_comprehensions_handler::holds_condition(f->get_first_formula(), info) or
                    list_comprehensions_handler::holds_condition(f->get_second_formula(), info);
        }

        [[nodiscard]]
        static bool holds_condition(const ast::box_formula_ptr &f, grounder_info &info) {
            return false;
        }
    };

    class formulas_and_lists_grounder {
    public:
        static del::formula_ptr build_goal(const planning_specification &spec, grounder_info &info);

        static del::formula_ptr build_formula(const ast::formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_condition(const std::optional<formula_ptr> &f, grounder_info &info);


        template<typename input_type, typename output_type, typename... Args>
        using grounding_function_t = std::function<output_type(
                const input_type &,
                grounder_info &,
                const type_ptr &,
                Args...)>;

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::list<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 grounder_info &info, const type_ptr &default_type, Args... args) {
            return std::visit([&](auto &&arg) -> std::list<output_type> {
                return formulas_and_lists_grounder::build_list<input_type, output_type, Args...>(
                        arg, ground_elem, info, default_type, args...);
            }, list);
        }

    private:
        static del::formula_ptr build_formula(const ast::true_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::false_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::predicate_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::eq_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::neq_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::not_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::and_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::or_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::imply_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::forall_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::exists_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::box_formula_ptr &f, grounder_info &info);

        static del::formula_ptr build_formula(const ast::diamond_formula_ptr &f, grounder_info &info);

        static del::formula_deque build_formula_list(const ast::list_comprehension_ptr &list_compr,
                                                     const ast::formula_ptr &f, grounder_info &info);

        static del::agent_set build_agent_group(const ast::modality_index_ptr &m, grounder_info &info);

        static del::agent_set build_agent_group(const ast::term &m, grounder_info &info);

        static del::agent_set build_agent_group(const ast::list<ast::simple_agent_group_ptr> &m, grounder_info &info);

        static del::agent_set build_agent_group(const ast::all_group_modality_ptr &m, grounder_info &info);


        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::singleton_list_ptr<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 grounder_info &info, const type_ptr &default_type, Args... args) {
            return std::list<output_type>{ground_elem(list->get_elem(), info, default_type, args...)};
        }

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::and_list_ptr<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 grounder_info &info, const type_ptr &default_type, Args... args) {
            std::list<output_type> output_list;

            for (const ast::list<input_type> &elem : list->get_list()) {
                auto ground_elem_list = formulas_and_lists_grounder::build_list<input_type, output_type, Args...>(
                        elem, ground_elem, info, default_type, args...);

                for (output_type ground_elem_ : ground_elem_list)
                    output_list.emplace_back(std::move(ground_elem_));
            }
            return output_list;
        }

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::forall_list_ptr<input_type> &list,
                                                 const grounding_function_t<input_type, output_type, Args...> &ground_elem,
                                                 grounder_info &info, const type_ptr &default_type, Args... args) {
            std::list<output_type> output_list;

//            del::formula_ptr condition = formulas_and_lists_grounder::build_condition(
//                    list->get_list_compr()->get_condition(), context, types_tree, assignment, static_atoms, language);

            combinations_handler handler{list->get_list_compr()->get_formal_params(), info.context,
                                         type_checker::either_type{info.context.types.get_type_id(default_type)}};

            for (const combination &combination :
                list_comprehensions_handler::all(list->get_list_compr()->get_condition(), handler, info)) {
                info.assignment.push(handler.get_typed_vars(), combination);
                auto ground_elem_list = formulas_and_lists_grounder::build_list<input_type, output_type, Args...>(
                                list->get_list(), ground_elem, info, default_type, args...);

                for (output_type ground_elem_ : ground_elem_list)
                    output_list.emplace_back(std::move(ground_elem_));

                info.assignment.pop();
            }

            return output_list;
        }
    };
}

#endif //EPDDL_FORMULAS_AND_LISTS_GROUNDER_H
