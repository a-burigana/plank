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

#ifndef EPDDL_TYPE_CHECKER_HELPER_H
#define EPDDL_TYPE_CHECKER_HELPER_H

#include <deque>
#include <tuple>
#include "../ast/problems/problem_ast.h"
#include "../ast/domains/domain_ast.h"
#include "../ast/libraries/act_type_library_ast.h"
#include "context.h"
#include "type.h"

namespace epddl::type_checker {
    using planning_task = std::tuple<ast::problem_ptr, ast::domain_ptr, std::deque<ast::act_type_library_ptr>>;

    class type_checker_helper {
    public:
        static void do_semantic_check(const planning_task &task);

    private:
        static type_ptr build_type_tree(const planning_task &task);
        static context build_context(const epddl::type_checker::planning_task &task, const epddl::type_checker::type_ptr &types_tree);

        static void build_entities(const planning_task &task, context &context, const type_ptr &types_tree);
        static void build_predicate_signatures(const planning_task &task, context &context, const type_ptr &types_tree);

        static void check_formula(const ast::formula_ptr &f, context &context, const type_ptr &types_tree);

        static void check_formula(const ast::true_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::false_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::predicate_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::eq_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::neq_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::in_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::not_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::and_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::or_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::imply_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::box_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::diamond_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::forall_formula_ptr &f, context &context, const type_ptr &types_tree);
        static void check_formula(const ast::exists_formula_ptr &f, context &context, const type_ptr &types_tree);

        static void check_list_comprehension(const ast::list_comprehension_ptr &list_compr, context &context, const type_ptr &types_tree);
        static void check_list(const ast::list_ptr &list, context &context, const type_ptr &types_tree);
        static void check_modality_index(const ast::modality_index_ptr &index, context &context, const type_ptr &types_tree);

        static void build_event_signatures();
        static void build_act_type_signatures();
    };
}

#endif //EPDDL_TYPE_CHECKER_HELPER_H
