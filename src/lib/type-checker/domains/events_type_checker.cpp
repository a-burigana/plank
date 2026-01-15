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

#include "../../../../include/lib/type-checker/domains/events_type_checker.h"
#include "../../../../include/lib/type-checker/common/formulas_and_lists_type_checker.h"
#include <string>

using namespace epddl;
using namespace epddl::type_checker;

void events_type_checker::check(const ast::event_ptr &event, context &context, error_manager_ptr &err_manager) {
    context.entities.push();
    const std::string &event_name = event->get_name()->get_token().get_lexeme();

    if (event->get_params().has_value()) {
        const std::string params_err_info = error_manager::get_error_info(
                decl_type::event_params_decl, event_name);

        err_manager->push_error_info(params_err_info);

        context.entities.add_decl_list(context.types, err_manager, *event->get_params(),
                                       context.types.get_type("entity"));

        err_manager->pop_error_info();
    }

    context.entities.update_typed_entities_sets(context.types);

    if (event->get_precondition().has_value()) {
        const std::string pre_err_info = error_manager::get_error_info(
                decl_type::event_pre_decl, event_name);

        err_manager->push_error_info(pre_err_info);

        formulas_and_lists_type_checker::check_formula(
                *event->get_precondition(), context, err_manager);

        err_manager->pop_error_info();
    }

    if (event->get_postconditions().has_value()) {
        const std::string eff_err_info = error_manager::get_error_info(
                decl_type::event_effects_decl, event_name);

        err_manager->push_error_info(eff_err_info);

        auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::postcondition>(
                [&] (const ast::postcondition &post, class context &context,
                        error_manager_ptr &err_manager, const type_ptr &default_type) {
                    check_postconditions(post, context, err_manager);
                });

        formulas_and_lists_type_checker::check_list(
                *event->get_postconditions(), check_elem, context, err_manager,
                context.types.get_type("object"));

        err_manager->pop_error_info();
    }
    context.entities.pop();
}

void events_type_checker::check_postconditions(const ast::postcondition &post, context &context,
                                               error_manager_ptr &err_manager) {
    std::visit([&](auto &&arg) {
        check_postconditions(arg, context, err_manager);
    }, post);
}

void events_type_checker::check_postconditions(const ast::literal_postcondition_ptr &post, context &context,
                                               error_manager_ptr &err_manager) {
    formulas_and_lists_type_checker::check_literal(post->get_literal(), context, err_manager);
}

void events_type_checker::check_postconditions(const ast::when_postcondition_ptr &post, context &context,
                                               error_manager_ptr &err_manager) {
    formulas_and_lists_type_checker::check_formula(post->get_cond(), context, err_manager);

    auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::literal_ptr>(
                [&] (const ast::literal_ptr &l, class context &context,
                        error_manager_ptr &err_manager, const type_ptr &default_type) {
                    formulas_and_lists_type_checker::check_literal(l, context, err_manager);
                });

    formulas_and_lists_type_checker::check_list(
            post->get_literals(), check_elem, context, err_manager,
            context.types.get_type("object"));
}

void events_type_checker::check_postconditions(const ast::iff_postcondition_ptr &post, context &context,
                                               error_manager_ptr &err_manager) {
    formulas_and_lists_type_checker::check_formula(post->get_cond(), context, err_manager);

    auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::literal_ptr>(
                [&] (const ast::literal_ptr &l, class context &context,
                        error_manager_ptr &err_manager, const type_ptr &default_type) {
                    formulas_and_lists_type_checker::check_literal(l, context, err_manager);
                });

    formulas_and_lists_type_checker::check_list(
            post->get_literals(), check_elem, context, err_manager,
            context.types.get_type("object"));
}
