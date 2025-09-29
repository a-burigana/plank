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
#include "../../../include/type-checker/common/formulas_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void events_type_checker::check(const ast::event_ptr &event, context &context, const type_ptr &types_tree) {
    context.assert_declared_event(event->get_name());
    context.push();

    if (event->get_params().has_value()) {
        const type_ptr &object = types_tree->find("object");
        context.add_decl_list((*event->get_params())->get_formal_params(), object, types_tree);
    }

    if (event->get_precondition().has_value())
        formulas_type_checker::check_formula(*event->get_precondition(), context, types_tree);

    if (event->get_postconditions().has_value())
        check_postconditions(*event->get_postconditions(), context, types_tree);

    context.pop();
}

void events_type_checker::check_postconditions(const ast::postconditions &post, context &context,
                                               const type_ptr &types_tree) {
    std::visit([&](auto &&arg) {
        check_postconditions(arg, context, types_tree);
    }, post);
}

void events_type_checker::check_postconditions(const ast::literal_postcondition_ptr &post, context &context,
                                               const type_ptr &types_tree) {
    formulas_type_checker::check_literal(post->get_literal(), context, types_tree);
}

void events_type_checker::check_postconditions(const ast::when_postcondition_ptr &post, context &context,
                                               const type_ptr &types_tree) {
    formulas_type_checker::check_formula(post->get_cond(), context, types_tree);

    for (const ast::literal_ptr &l : post->get_literals())
        formulas_type_checker::check_literal(l, context, types_tree);
}

void events_type_checker::check_postconditions(const ast::iff_postcondition_ptr &post, context &context,
                                               const type_ptr &types_tree) {
    formulas_type_checker::check_formula(post->get_cond(), context, types_tree);

    for (const ast::literal_ptr &l : post->get_literals())
        formulas_type_checker::check_literal(l, context, types_tree);
}

void events_type_checker::check_postconditions(const ast::forall_postcondition_ptr &post, context &context,
                                               const type_ptr &types_tree) {
    formulas_type_checker::check_list_comprehension(post->get_params(), context, types_tree);
    check_postconditions(post->get_post(), context, types_tree);
}

void events_type_checker::check_postconditions(const ast::and_postcondition_ptr &post, context &context,
                                               const type_ptr &types_tree) {
    for (const ast::postconditions &post_ : post->get_post_list())
        check_postconditions(post_, context, types_tree);
}
