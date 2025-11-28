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

#include "../../../include/type-checker/domains/events_type_checker.h"
#include "../../../include/type-checker/common/formulas_and_lists_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void events_type_checker::check(const ast::event_ptr &event, context &context, const type_ptr &types_tree) {
    context.entities.push();

    if (event->get_params().has_value())
        context.entities.add_decl_list(*event->get_params(), type_utils::find(types_tree, "entity"), types_tree);

    if (event->get_precondition().has_value())
        formulas_and_lists_type_checker::check_formula(*event->get_precondition(), context, types_tree);

    if (event->get_postconditions().has_value()) {
        auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::postcondition>(
                [&] (const ast::postcondition &post, class context &context, const type_ptr &types_tree) {
                    check_postconditions(post, context, types_tree);
                });

        formulas_and_lists_type_checker::check_list(*event->get_postconditions(), check_elem, context, types_tree, type_utils::find(types_tree, "object"));
    }
    context.entities.pop();
}

void events_type_checker::check_postconditions(const ast::postcondition &post, context &context,
                                               const type_ptr &types_tree) {
    std::visit([&](auto &&arg) {
        check_postconditions(arg, context, types_tree);
    }, post);
}

void events_type_checker::check_postconditions(const ast::literal_postcondition_ptr &post, context &context,
                                               const type_ptr &types_tree) {
    formulas_and_lists_type_checker::check_literal(post->get_literal(), context, types_tree);
}

void events_type_checker::check_postconditions(const ast::when_postcondition_ptr &post, context &context,
                                               const type_ptr &types_tree) {
    formulas_and_lists_type_checker::check_formula(post->get_cond(), context, types_tree);

    auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::literal_ptr>(
                [&] (const ast::literal_ptr &l, class context &context, const type_ptr &types_tree) {
                    formulas_and_lists_type_checker::check_literal(l, context, types_tree);
                });

    formulas_and_lists_type_checker::check_list(post->get_literals(), check_elem, context, types_tree, type_utils::find(types_tree, "object"));
}

void events_type_checker::check_postconditions(const ast::iff_postcondition_ptr &post, context &context,
                                               const type_ptr &types_tree) {
    formulas_and_lists_type_checker::check_formula(post->get_cond(), context, types_tree);

    auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::literal_ptr>(
                [&] (const ast::literal_ptr &l, class context &context, const type_ptr &types_tree) {
                    formulas_and_lists_type_checker::check_literal(l, context, types_tree);
                });

    formulas_and_lists_type_checker::check_list(post->get_literals(), check_elem, context, types_tree, type_utils::find(types_tree, "object"));
}
