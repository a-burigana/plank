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

#include "../../../include/type-checker/domains/actions_type_checker.h"
#include "../../../include/type-checker/common/formulas_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void actions_type_checker::check(const ast::action_ptr &action, context &context, const type_ptr &types_tree) {
    context.push();

    formulas_type_checker::check_list_comprehension(action->get_params(), context, types_tree, type_utils::find(types_tree, "entity"));

    check_action_signature(action->get_signature(), context, types_tree);

    if (action->get_obs_conditions().has_value()) {
        context.add_decl_obs_groups(action->get_signature()->get_name(), types_tree);

        auto check_elem = formulas_type_checker::check_function_t<ast::obs_cond>(
                [&] (const ast::obs_cond &cond, class context &context, const type_ptr &types_tree) {
                    check_obs_conditions(cond, context, types_tree);
                });

        formulas_type_checker::check_list(*action->get_obs_conditions(), check_elem, context, types_tree, type_utils::find(types_tree, "agent"));
    } else if (not action->get_signature()->is_basic())
        throw EPDDLException{std::string{""},
                             action->get_name()->get_token().get_row(),
                             action->get_name()->get_token().get_col(),
                             std::string{"Missing observability conditions for action '" +
                             action->get_name()->get_token().get_lexeme() + "'."}};

    context.pop();
}

void actions_type_checker::check_action_signature(const ast::action_signature_ptr &signature, context &context,
                                                  const type_ptr &types_tree) {
    either_type_list action_type_types = context.get_formal_param_types_action_type(signature->get_name());

    if (action_type_types.size() != signature->get_events().size())
        context::throw_arguments_number_error(signature->get_name(), action_type_types, signature->get_events(), "action type");

    for (const ast::event_signature_ptr &e : signature->get_events())
        context.check_event_signature(e);
}

void actions_type_checker::check_obs_conditions(const ast::obs_cond &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    std::visit([&](auto &&arg) {
        check_obs_conditions(arg, context, types_tree);
    }, obs_cond);
}

void actions_type_checker::check_obs_conditions(const ast::static_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    const type_ptr &obs_group = type_utils::find(types_tree, ";obs-group"), &agent = type_utils::find(types_tree, "agent");
    context.check_type(obs_cond->get_obs_group(), obs_group);
    context.check_type(obs_cond->get_agent(), agent);
}

void actions_type_checker::check_obs_conditions(const ast::if_then_else_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    check_obs_conditions(obs_cond->get_if_cond(), context, types_tree);

    for (const ast::else_if_obs_cond_ptr &obs_cond_ : obs_cond->get_else_if_conds())
        check_obs_conditions(obs_cond_, context, types_tree);

    if (obs_cond->get_else_cond().has_value())
        check_obs_conditions(*obs_cond->get_else_cond(), context, types_tree);
}

void actions_type_checker::check_obs_conditions(const ast::if_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    formulas_type_checker::check_formula(obs_cond->get_cond(), context, types_tree);
    check_obs_conditions(obs_cond->get_obs_cond(), context, types_tree);
}

void actions_type_checker::check_obs_conditions(const ast::else_if_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    formulas_type_checker::check_formula(obs_cond->get_cond(), context, types_tree);
    check_obs_conditions(obs_cond->get_obs_cond(), context, types_tree);
}

void actions_type_checker::check_obs_conditions(const ast::else_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    const type_ptr &obs_group = type_utils::find(types_tree, ";obs-group"), &agent = type_utils::find(types_tree, "agent");
    context.check_type(obs_cond->get_obs_group(), obs_group);
    context.check_type(obs_cond->get_agent(), agent);
}

void actions_type_checker::check_obs_conditions(const ast::default_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    const type_ptr &obs_group = type_utils::find(types_tree, ";obs-group");
    context.check_type(obs_cond->get_obs_group(), obs_group);
}
