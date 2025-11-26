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
#include "../../../include/type-checker/common/formulas_and_lists_type_checker.h"
#include <unordered_map>
#include <variant>

using namespace epddl;
using namespace epddl::type_checker;

void actions_type_checker::check(const ast::action_ptr &action, context &context, const type_ptr &types_tree) {
    context.push();

    formulas_and_lists_type_checker::check_list_comprehension(action->get_params(), context, types_tree,
                                                              type_utils::find(types_tree, "entity"));

    actions_type_checker::check_action_signature(action->get_signature(), context, types_tree);

    if (action->get_obs_conditions().has_value()) {
        context.add_decl_obs_groups(action->get_signature()->get_name(), types_tree);

        auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::obs_cond>(
                [&](const ast::obs_cond &cond, class context &context, const type_ptr &types_tree) {
                    actions_type_checker::check_obs_conditions(cond, context, types_tree);
                });

        formulas_and_lists_type_checker::check_list(*action->get_obs_conditions(), check_elem, context, types_tree,
                                                    type_utils::find(types_tree, "entity"));
    } else if (not action->get_signature()->is_basic())
        throw EPDDLException{action->get_name()->get_info(),
                             std::string{"Missing observability conditions for action '" +
                                         action->get_name()->get_token().get_lexeme() + "'."}};

    context.pop();
}

void actions_type_checker::check_action_signature(const ast::action_signature_ptr &signature, context &context,
                                                  const type_ptr &types_tree) {
    either_type_list action_type_types = context.get_formal_param_types_action_type(signature->get_name());

    if (action_type_types.size() != signature->get_events().size())
        context::throw_arguments_number_error(signature->get_name(), action_type_types, signature->get_events(),
                                              "action type");

    for (const ast::event_signature_ptr &e: signature->get_events())
        context.check_event_signature(e);

    actions_type_checker::check_events_conditions(signature, context, types_tree);
}

void actions_type_checker::check_events_conditions(const ast::action_signature_ptr &signature,
                                                   context &context, const type_ptr &types_tree) {
    const ast::action_type_ptr &act_type =
            context.get_action_type_decl(signature->get_name()->get_token().get_lexeme());

    if (not act_type->get_conditions().has_value())
        return;

    std::unordered_map<std::string, std::string> events_map;
    std::unordered_map<std::string, ast::event_condition_list> conditions_map;
    const auto event_variables = act_type->get_events();
    const auto event_arguments = signature->get_events();

    for (auto [e_var, e_arg] = std::tuple{event_variables.begin(), event_arguments.begin()};
         e_var != event_variables.end();
         ++e_var, ++e_arg)
        events_map[(*e_var)->get_token().get_lexeme()] = (*e_arg)->get_name()->get_token().get_lexeme();

    for (const ast::event_conditions_ptr &e_conditions : (*act_type->get_conditions())->get_conditions())
        conditions_map[e_conditions->get_event()->get_token().get_lexeme()] = e_conditions->get_conditions();

    for (const auto &[e_var, e_arg]: events_map) {
        const ast::event_ptr &e = context.get_event_decl(e_arg);

        for (const ast::event_condition_ptr &cond: conditions_map[e_var])
            actions_type_checker::check_event_condition(e, cond, e_var, act_type->get_name()->get_token().get_lexeme(),
                                                        context, types_tree);
    }
}

void actions_type_checker::check_event_condition(const ast::event_ptr &e, const ast::event_condition_ptr &cond,
                                                 const std::string &e_var_name, const std::string &act_type_name,
                                                 context &context, const type_ptr &types_tree) {
    const token_type &cond_type = cond->get_cond()->get_type();

    if (std::holds_alternative<event_condition_token::prop_pre>(cond_type))
        actions_type_checker::check_prop_precondition(e, e_var_name, act_type_name, context, types_tree);
    else if (std::holds_alternative<event_condition_token::prop_post>(cond_type))
        actions_type_checker::check_prop_postconditions(e, e_var_name, act_type_name, context, types_tree);
    else if (std::holds_alternative<event_condition_token::prop_event>(cond_type))
        actions_type_checker::check_prop_event(e, e_var_name, act_type_name, context, types_tree);
    else if (std::holds_alternative<event_condition_token::trivial_pre>(cond_type))
        actions_type_checker::check_trivial_precondition(e, e_var_name, act_type_name, context, types_tree, true);
    else if (std::holds_alternative<event_condition_token::trivial_post>(cond_type))
        actions_type_checker::check_trivial_postconditions(e, e_var_name, act_type_name, context, types_tree, true);
    else if (std::holds_alternative<event_condition_token::trivial_event>(cond_type))
        actions_type_checker::check_trivial_event(e, e_var_name, act_type_name, context, types_tree, true);
    else if (std::holds_alternative<event_condition_token::non_trivial_pre>(cond_type))
        actions_type_checker::check_trivial_precondition(e, e_var_name, act_type_name, context, types_tree, false);
    else if (std::holds_alternative<event_condition_token::non_trivial_post>(cond_type))
        actions_type_checker::check_trivial_postconditions(e, e_var_name, act_type_name, context, types_tree, false);
    else if (std::holds_alternative<event_condition_token::non_trivial_event>(cond_type))
        actions_type_checker::check_trivial_event(e, e_var_name, act_type_name, context, types_tree, false);
}

void actions_type_checker::check_prop_precondition(const ast::event_ptr &e, const std::string &e_var_name,
                                                   const std::string &act_type_name,
                                                   context &context, const type_ptr &types_tree) {
    if (not e->get_precondition().has_value() or
        formulas_and_lists_type_checker::is_propositional_formula(*e->get_precondition()))
        return;

    throw EPDDLException{e->get_name()->get_info(),
                         std::string{"Could not bind event '" + e->get_name()->get_token().get_lexeme() +
                                     "' to event variable '" + e_var_name + "' (action type '" + act_type_name +
                                     "'). Event precondition is required to be propositional."}};
}

void actions_type_checker::check_prop_postconditions(const ast::event_ptr &e, const std::string &e_var_name,
                                                     const std::string &act_type_name,
                                                     context &context, const type_ptr &types_tree) {
    if (not e->get_postconditions().has_value() or
        actions_type_checker::has_prop_postconditions(e, context, types_tree))
        return;

    throw EPDDLException{e->get_name()->get_info(),
                         std::string{"Could not bind event '" + e->get_name()->get_token().get_lexeme() +
                                     "' to event variable '" + e_var_name + "' (action type '" + act_type_name +
                                     "'). Event postconditions are required to be propositional."}};
}

void actions_type_checker::check_prop_event(const ast::event_ptr &e, const std::string &e_var_name,
                                            const std::string &act_type_name,
                                            context &context, const type_ptr &types_tree) {
    actions_type_checker::check_prop_precondition(e, e_var_name, act_type_name, context, types_tree);
    actions_type_checker::check_prop_postconditions(e, e_var_name, act_type_name, context, types_tree);
}

bool actions_type_checker::has_prop_postconditions(const ast::event_ptr &e, context &context, const type_ptr &types_tree) {
    bool has_prop_postconditions = true;

    auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::postcondition>(
        [&] (const ast::postcondition &post, class context &context, const type_ptr &types_tree) {
            bool good = false;
            if (std::holds_alternative<ast::literal_postcondition_ptr>(post))
                good = true;
            else if (std::holds_alternative<ast::when_postcondition_ptr>(post))
                good = formulas_and_lists_type_checker::is_propositional_formula(
                        std::get<ast::when_postcondition_ptr>(post)->get_cond());
            else if (std::holds_alternative<ast::iff_postcondition_ptr>(post))
                good = formulas_and_lists_type_checker::is_propositional_formula(
                        std::get<ast::iff_postcondition_ptr>(post)->get_cond());

            if (not good)
                has_prop_postconditions = false;
        });

    formulas_and_lists_type_checker::check_list(
            *e->get_postconditions(), check_elem, context, types_tree, type_utils::find(types_tree, "object"));
    return has_prop_postconditions;
}

void actions_type_checker::check_trivial_precondition(const ast::event_ptr &e, const std::string &e_var_name,
                                                      const std::string &act_type_name, context &context,
                                                      const type_ptr &types_tree, bool check_positive) {
    bool has_trivial_pre = not e->get_precondition().has_value() or
                           std::holds_alternative<ast::true_formula_ptr>(*e->get_precondition());

    if (has_trivial_pre == check_positive)
        return;

    std::string trivial_str = check_positive ? "trivial" : "non-trivial";
    throw EPDDLException{e->get_name()->get_info(),
                         std::string{"Could not bind event '" + e->get_name()->get_token().get_lexeme() +
                                     "' to event variable '" + e_var_name + "' (action type '" + act_type_name +
                                     "'). Event precondition is required to be " + trivial_str + "."}};
}

void actions_type_checker::check_trivial_postconditions(const ast::event_ptr &e, const std::string &e_var_name,
                                                        const std::string &act_type_name, context &context,
                                                        const type_ptr &types_tree, bool check_positive) {
    bool has_trivial_post = not e->get_postconditions().has_value();

    if (has_trivial_post == check_positive)
        return;

    std::string trivial_str = check_positive ? "trivial" : "non-trivial";
    throw EPDDLException{e->get_name()->get_info(),
                         std::string{"Could not bind event '" + e->get_name()->get_token().get_lexeme() +
                                     "' to event variable '" + e_var_name + "' (action type '" + act_type_name +
                                     "'). Event postconditions are required to be " + trivial_str + "."}};
}

void actions_type_checker::check_trivial_event(const ast::event_ptr &e, const std::string &e_var_name,
                                               const std::string &act_type_name, context &context,
                                               const type_ptr &types_tree, bool check_positive) {
    actions_type_checker::check_trivial_precondition(e, e_var_name, act_type_name, context, types_tree, check_positive);
    actions_type_checker::check_trivial_postconditions(e, e_var_name, act_type_name, context, types_tree, check_positive);
}


void actions_type_checker::check_obs_conditions(const ast::obs_cond &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    std::visit([&](auto &&arg) {
        actions_type_checker::check_obs_conditions(arg, context, types_tree);
    }, obs_cond);
}

void actions_type_checker::check_obs_conditions(const ast::static_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    const type_ptr &obs_group = type_utils::find(types_tree, "obs-type"), &agent = type_utils::find(types_tree, "agent");
    context.check_type(obs_cond->get_obs_group(), obs_group);
    context.check_type(obs_cond->get_agent(), agent);
}

void actions_type_checker::check_obs_conditions(const ast::if_then_else_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    actions_type_checker::check_obs_conditions(obs_cond->get_if_cond(), context, types_tree);

    for (const ast::else_if_obs_cond_ptr &obs_cond_ : obs_cond->get_else_if_conds())
        actions_type_checker::check_obs_conditions(obs_cond_, context, types_tree);

    if (obs_cond->get_else_cond().has_value())
        actions_type_checker::check_obs_conditions(*obs_cond->get_else_cond(), context, types_tree);
}

void actions_type_checker::check_obs_conditions(const ast::if_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    formulas_and_lists_type_checker::check_formula(obs_cond->get_cond(), context, types_tree);
    actions_type_checker::check_obs_conditions(obs_cond->get_obs_cond(), context, types_tree);
}

void actions_type_checker::check_obs_conditions(const ast::else_if_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    formulas_and_lists_type_checker::check_formula(obs_cond->get_cond(), context, types_tree);
    actions_type_checker::check_obs_conditions(obs_cond->get_obs_cond(), context, types_tree);
}

void actions_type_checker::check_obs_conditions(const ast::else_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    const type_ptr &obs_group = type_utils::find(types_tree, "obs-type"), &agent = type_utils::find(types_tree, "agent");
    context.check_type(obs_cond->get_obs_group(), obs_group);
    context.check_type(obs_cond->get_agent(), agent);
}

void actions_type_checker::check_obs_conditions(const ast::default_obs_cond_ptr &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    const type_ptr &obs_group = type_utils::find(types_tree, "obs-type");
    context.check_type(obs_cond->get_obs_group(), obs_group);
}
