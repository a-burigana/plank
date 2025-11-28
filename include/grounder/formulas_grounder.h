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

#ifndef EPDDL_FORMULAS_GROUNDER_H
#define EPDDL_FORMULAS_GROUNDER_H

#include "../type-checker/context/context.h"
#include "../del/language/language.h"
#include "../del/language/formulas.h"
#include "combinations_handler.h"
#include "../del/del_types.h"

using namespace epddl::type_checker;

namespace epddl::grounder {
    class formulas_grounder {
    public:
        static del::formula_ptr build_goal(const planning_specification &spec, const context &context,
                                           const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::formula_ptr &f, const context &context, const del::language_ptr &language);

        template<typename input_type, typename output_type, typename... Args>
        using build_function_t = std::function<output_type(const input_type &, context &, const type_ptr &, Args...)>;

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::list<input_type> &list,
                               const build_function_t<input_type, output_type, Args...> &build_elem, context &context,
                               const type_ptr &types_tree, const type_ptr &default_type, Args... args) {
            return std::visit([&](auto &&arg) -> std::list<output_type> {
                return formulas_grounder::build_list<input_type, output_type, Args...>(arg, build_elem, context, types_tree, default_type, args...);
            }, list);
        }

    private:
        static del::formula_ptr build_formula(const ast::true_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::false_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::predicate_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::not_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::and_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::or_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::imply_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::box_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::diamond_formula_ptr &f, const context &context, const del::language_ptr &language);

        static del::agent_group build_agent_group(const ast::modality_index_ptr &m, const context &context, const del::language_ptr &language);

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::singleton_list_ptr<input_type> &list,
                               const build_function_t<input_type, output_type, Args...> &build_elem, context &context,
                               const type_ptr &types_tree, const type_ptr &default_type, Args... args) {
            return std::list<output_type>{build_elem(list->get_elem(), context, types_tree, args...)};
        }

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::and_list_ptr<input_type> &list,
                               const build_function_t<input_type, output_type, Args...> &build_elem, context &context,
                               const type_ptr &types_tree, const type_ptr &default_type, Args... args) {
            std::list<output_type> concat;

            for (const ast::list<input_type> &elem : list->get_list()) {
                auto ground_elem_list = formulas_grounder::build_list<input_type, output_type, Args...>
                        (elem, build_elem, context, types_tree, default_type, args...);

                for (output_type ground_elem : ground_elem_list)
                    concat.emplace_back(std::move(ground_elem));
            }
        }

        template<typename input_type, typename output_type, typename... Args>
        static std::list<output_type> build_list(const ast::forall_list_ptr<input_type> &list,
                               const build_function_t<input_type, output_type, Args...> &build_elem, context &context,
                               const type_ptr &types_tree, const type_ptr &default_type, Args... args) {
//            formulas_grounder::build_list_comprehension(list->get_list_compr(), context, types_tree, default_type);
            formulas_grounder::build_list<input_type, output_type, Args...>(list->get_list(), build_elem, context, types_tree, default_type, args...);
        }
    };

    class list_comprehensions_handler {
    public:
        [[nodiscard]] static bool has_next(combinations_handler &handler, del::formula_ptr &condition, del::atom_set s_static) {

        }

        [[nodiscard]] static const combination &next(combinations_handler &handler, del::formula_ptr &condition, del::atom_set s_static) {
//            while (not holds_condition(handler.next()))
        }

    private:
        [[nodiscard]] static bool holds_condition(del::formula_ptr &condition, del::atom_set s_static);
    };
}

#endif //EPDDL_FORMULAS_GROUNDER_H
