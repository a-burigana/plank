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

#include "../../../../include/lib/type-checker/domains/actions_type_checker.h"
#include "../../../../include/lib/type-checker/common/formulas_and_lists_type_checker.h"
#include "../../../../include/lib/grounder/formulas/formulas_and_lists_grounder.h"
#include <unordered_map>
#include <variant>

using namespace epddl;
using namespace epddl::type_checker;

void actions_type_checker::check(const ast::action_ptr &action, context &context, error_manager_ptr &err_manager) {
    context.entities.push();
    const std::string &action_name = action->get_name()->get_token().get_lexeme();

    const std::string params_err_info = error_manager::get_error_info(decl_type::action_params_decl, action_name);
    err_manager->push_error_info(params_err_info);

    formulas_and_lists_type_checker::check_list_comprehension(
            action->get_params(), context, err_manager, context.types.get_type("entity"));

    err_manager->pop_error_info();

    actions_type_checker::check_action_signature(
            action->get_signature(), context, err_manager,
            error_manager::get_error_info(decl_type::action_signature_decl, action_name));

    const type_ptr &obs_type = context.types.get_type("obs-type");

    if (action->get_obs_conditions().has_value()) {
        auto action_obs_types = context.action_types.get_obs_types(action->get_signature()->get_name()->get_token().get_lexeme());

        const std::string obs_cond_err_info = error_manager::get_error_info(decl_type::action_obs_cond_decl,
                                                                   action_name);

        context.entities.add_decl_list(err_manager, action_obs_types,
                                       either_type{context.types.get_type_id(obs_type)});
        context.entities.update_typed_entities_sets(context.types);

        auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::obs_cond>(
            [&](const ast::obs_cond &cond, class context &context,
                error_manager_ptr &err_manager, const type_ptr &default_type) {
                actions_type_checker::check_obs_conditions(cond, context, err_manager);
            });

        formulas_and_lists_type_checker::check_list(
                *action->get_obs_conditions(), check_elem, context, err_manager,
                context.types.get_type("agent"));

        err_manager->push_error_info(obs_cond_err_info);

        std::string default_t;
        check_default_obs_cond(*action->get_obs_conditions(), context, err_manager, obs_cond_err_info, default_t);
        check_missing_else_cond(*action->get_obs_conditions(), context, err_manager, obs_cond_err_info, default_t);
//        check_missing_obs_cond(*action->get_obs_conditions(), info, default_t);

        context.actions.set_default_obs_type(action->get_name()->get_token().get_lexeme(), default_t);

        err_manager->pop_error_info();
    } else if (not action->get_signature()->is_basic()) {
        const std::string obs_cond_err_info = error_manager::get_error_info(decl_type::action_decl,
                                                                   action_name);
        err_manager->push_error_info(obs_cond_err_info);

        err_manager->throw_error(error_type::missing_obs_cond, action->get_name()->get_token_ptr());
    }

    context.entities.pop();
}

void actions_type_checker::check_action_signature(const ast::action_signature_ptr &signature, context &context,
                                                  error_manager_ptr &err_manager, const std::string &err_info) {
    typed_var_list action_type_types = context.action_types.get_formal_param_types_action_type(
            signature->get_name()->get_token().get_lexeme());

    err_manager->push_error_info(err_info);

    if (action_type_types.size() != signature->get_events().size())
        context_utils::throw_arguments_number_error(err_manager, signature->get_name(), action_type_types,
                                                    signature->get_events(), "action type");

    for (const ast::event_signature_ptr &e: signature->get_events())
        context.events.check_event_signature(context.types, context.entities, e);

    if (not signature->is_basic())
        actions_type_checker::check_events_conditions(signature, context, err_manager, err_info);

    err_manager->pop_error_info();
}

void actions_type_checker::check_events_conditions(const ast::action_signature_ptr &signature,
                                                   context &context, error_manager_ptr &err_manager,
                                                   const std::string &err_info) {
    const ast::action_type_ptr &act_type = context.action_types.get_action_type_decl(
            signature->get_name()->get_token().get_lexeme());

    if (not act_type->get_conditions().has_value())
        return;

    event_signature_map events_map;
    event_conditions_map conditions_map;
    const auto event_variables = act_type->get_events();
    const auto event_arguments = signature->get_events();

    for (auto [e_var, e_sign] = std::tuple{event_variables.begin(), event_arguments.begin()};
         e_var != event_variables.end();
         ++e_var, ++e_sign)
        events_map[(*e_var)->get_token().get_lexeme()] = *e_sign;

    for (const ast::event_conditions_ptr &e_conditions : (*act_type->get_conditions())->get_conditions())
        conditions_map[e_conditions->get_event()->get_token().get_lexeme()] = e_conditions->get_conditions();

    for (const auto &[e_var, e_sign]: events_map) {
        const ast::event_ptr &e = context.events.get_event_decl(e_sign->get_name());

        for (const ast::event_condition_ptr &cond: conditions_map[e_var])
            actions_type_checker::check_event_condition(e, cond, e_var, events_map,
                                                        act_type->get_name()->get_token().get_lexeme(),
                                                        context, err_manager, err_info);
    }
}

void actions_type_checker::check_event_condition(const ast::event_ptr &e, const ast::event_condition_ptr &cond,
                                                 const std::string &e_var_name,
                                                 const event_signature_map &events_map, const std::string &act_type_name,
                                                 context &context, error_manager_ptr &err_manager,
                                                 const std::string &err_info) {
    const token_type &cond_type = cond->get_cond()->get_type();

    if (std::holds_alternative<event_condition_token::prop_pre>(cond_type))
        actions_type_checker::check_prop_precondition(e, e_var_name, events_map, act_type_name, context, err_manager, err_info);
    else if (std::holds_alternative<event_condition_token::prop_post>(cond_type))
        actions_type_checker::check_prop_postconditions(e, e_var_name, events_map, act_type_name, context, err_manager, err_info);
    else if (std::holds_alternative<event_condition_token::prop_event>(cond_type))
        actions_type_checker::check_prop_event(e, e_var_name, events_map, act_type_name, context, err_manager, err_info);
    else if (std::holds_alternative<event_condition_token::trivial_pre>(cond_type))
        actions_type_checker::check_trivial_precondition(err_manager, e, e_var_name, events_map, act_type_name, context, true);
    else if (std::holds_alternative<event_condition_token::trivial_post>(cond_type))
        actions_type_checker::check_trivial_postconditions(err_manager, e, e_var_name, events_map, act_type_name, context, true);
    else if (std::holds_alternative<event_condition_token::trivial_event>(cond_type))
        actions_type_checker::check_trivial_event(err_manager, e, e_var_name, events_map, act_type_name, context, true);
    else if (std::holds_alternative<event_condition_token::non_trivial_pre>(cond_type))
        actions_type_checker::check_trivial_precondition(err_manager, e, e_var_name, events_map, act_type_name, context, false);
    else if (std::holds_alternative<event_condition_token::non_trivial_post>(cond_type))
        actions_type_checker::check_trivial_postconditions(err_manager, e, e_var_name, events_map, act_type_name, context, false);
    else if (std::holds_alternative<event_condition_token::non_trivial_event>(cond_type))
        actions_type_checker::check_trivial_event(err_manager, e, e_var_name, events_map, act_type_name, context, false);
}

void actions_type_checker::check_prop_precondition(const ast::event_ptr &e, const std::string &e_var_name,
                                                   const event_signature_map &events_map,
                                                   const std::string &act_type_name,
                                                   context &context, error_manager_ptr &err_manager,
                                                   const std::string &err_info) {
    if (not e->get_precondition().has_value() or
        formulas_and_lists_type_checker::is_propositional_formula(*e->get_precondition()))
        return;

    err_manager->throw_error(error_type::events_conditions_unsatisfied,
                             events_map.at(e_var_name)->get_name()->get_token_ptr(),
                             {e_var_name, act_type_name,
                              "event precondition is required to be propositional."});
}

void actions_type_checker::check_prop_postconditions(const ast::event_ptr &e, const std::string &e_var_name,
                                               const event_signature_map &events_map,
                                                     const std::string &act_type_name,
                                                     context &context, error_manager_ptr &err_manager,
                                                     const std::string &err_info) {
    if (not e->get_postconditions().has_value() or
        actions_type_checker::has_prop_postconditions(e, context, err_manager, err_info))
        return;

    err_manager->throw_error(error_type::events_conditions_unsatisfied,
                             events_map.at(e_var_name)->get_name()->get_token_ptr(),
                             {e_var_name, act_type_name,
                              "event postconditions are required to be propositional."});
}

void actions_type_checker::check_prop_event(const ast::event_ptr &e, const std::string &e_var_name,
                                            const event_signature_map &events_map, const std::string &act_type_name,
                                            context &context, error_manager_ptr &err_manager,
                                            const std::string &err_info) {
    actions_type_checker::check_prop_precondition(e, e_var_name, events_map, act_type_name,
                                                  context, err_manager, err_info);
    actions_type_checker::check_prop_postconditions(e, e_var_name, events_map, act_type_name,
                                                    context, err_manager, err_info);
}

bool actions_type_checker::has_prop_postconditions(const ast::event_ptr &e, context &context,
                                                   error_manager_ptr &err_manager, const std::string &err_info) {
    bool has_prop_postconditions = true;

    auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::postcondition>(
        [&] (const ast::postcondition &post, class context &context,
             error_manager_ptr &err_manager, const type_ptr &default_type) {
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
            *e->get_postconditions(), check_elem, context, err_manager,
            context.types.get_type("object"));
    return has_prop_postconditions;
}

void actions_type_checker::check_trivial_precondition(error_manager_ptr &err_manager, const ast::event_ptr &e,
                                                      const std::string &e_var_name,
                                               const event_signature_map &events_map, const std::string &act_type_name,
                                                      context &context, bool check_positive) {
    bool has_trivial_pre = not e->get_precondition().has_value() or
                           std::holds_alternative<ast::true_formula_ptr>(*e->get_precondition());

    if (has_trivial_pre == check_positive)
        return;

    std::string trivial_str = check_positive ? "trivial" : "non-trivial";
    err_manager->throw_error(error_type::events_conditions_unsatisfied,
                             events_map.at(e_var_name)->get_name()->get_token_ptr(),
                             {e_var_name, act_type_name,
                              "event precondition is required to be " + trivial_str + "."});
}

void actions_type_checker::check_trivial_postconditions(error_manager_ptr &err_manager, const ast::event_ptr &e,
                                                        const std::string &e_var_name,
                                                        const event_signature_map &events_map, const std::string &act_type_name,
                                                        context &context, bool check_positive) {
    bool has_trivial_post = not e->get_postconditions().has_value();

    if (has_trivial_post == check_positive)
        return;

    std::string trivial_str = check_positive ? "trivial" : "non-trivial";
    err_manager->throw_error(error_type::events_conditions_unsatisfied,
                             events_map.at(e_var_name)->get_name()->get_token_ptr(),
                             {e_var_name, act_type_name,
                              "event postconditions are required to be " + trivial_str + "."});
}

void actions_type_checker::check_trivial_event(error_manager_ptr &err_manager, const ast::event_ptr &e,
                                               const std::string &e_var_name,
                                               const event_signature_map &events_map, const std::string &act_type_name,
                                               context &context, bool check_positive) {
    actions_type_checker::check_trivial_precondition(err_manager, e, e_var_name, events_map, act_type_name,
                                                     context, check_positive);
    actions_type_checker::check_trivial_postconditions(err_manager, e, e_var_name, events_map, act_type_name,
                                                       context, check_positive);
}


void actions_type_checker::check_obs_conditions(const ast::obs_cond &obs_cond, context &context,
                                         error_manager_ptr &err_manager) {
    std::visit([&](auto &&arg) {
        actions_type_checker::check_obs_conditions(arg, context, err_manager);
    }, obs_cond);
}

void actions_type_checker::check_obs_conditions(const ast::static_obs_cond_ptr &obs_cond, context &context,
                                                error_manager_ptr &err_manager) {
    const type_ptr &agent = context.types.get_type("agent"), &obs_type = context.types.get_type("obs-type");
    context.entities.check_type(context.types, err_manager, obs_cond->get_agent(), agent);
    context.entities.check_type(context.types, err_manager, obs_cond->get_obs_type(), obs_type);
}

void actions_type_checker::check_obs_conditions(const ast::if_then_else_obs_cond_ptr &obs_cond, context &context,
                                         error_manager_ptr &err_manager) {
    const type_ptr &agent = context.types.get_type("agent");
    context.entities.check_type(context.types, err_manager, obs_cond->get_agent(), agent);

    actions_type_checker::check_obs_conditions(obs_cond->get_if_cond(), context, err_manager);

    for (const ast::else_if_obs_cond_ptr &obs_cond_ : obs_cond->get_else_if_conds())
        actions_type_checker::check_obs_conditions(obs_cond_, context, err_manager);

    if (obs_cond->get_else_cond().has_value())
        actions_type_checker::check_obs_conditions(*obs_cond->get_else_cond(), context, err_manager);
}

void actions_type_checker::check_obs_conditions(const ast::if_obs_cond_ptr &obs_cond, context &context,
                                         error_manager_ptr &err_manager) {
    const type_ptr &obs_type = context.types.get_type("obs-type");
    formulas_and_lists_type_checker::check_formula(obs_cond->get_cond(), context, err_manager);
    context.entities.check_type(context.types, err_manager, obs_cond->get_obs_type(), obs_type);
}

void actions_type_checker::check_obs_conditions(const ast::else_if_obs_cond_ptr &obs_cond, context &context,
                                         error_manager_ptr &err_manager) {
    const type_ptr &obs_type = context.types.get_type("obs-type");
    formulas_and_lists_type_checker::check_formula(obs_cond->get_cond(), context, err_manager);
    context.entities.check_type(context.types, err_manager, obs_cond->get_obs_type(), obs_type);
}

void actions_type_checker::check_obs_conditions(const ast::else_obs_cond_ptr &obs_cond, context &context,
                                         error_manager_ptr &err_manager) {
    const type_ptr &obs_type = context.types.get_type("obs-type"), &agent = context.types.get_type("agent");
    context.entities.check_type(context.types, err_manager, obs_cond->get_obs_type(), obs_type);
}

void actions_type_checker::check_obs_conditions(const ast::default_obs_cond_ptr &obs_cond, context &context,
                                         error_manager_ptr &err_manager) {
    const type_ptr &obs_type = context.types.get_type("obs-type");
    context.entities.check_type(context.types, err_manager, obs_cond->get_obs_type(), obs_type);
}

void actions_type_checker::check_default_obs_cond(const ast::list<ast::obs_cond> &obs_conditions,
                                                  context &context, error_manager_ptr &err_manager,
                                                  const std::string &err_info, std::string &default_t) {
    auto ground_elem = formulas_and_lists_type_checker::check_function_t<
        ast::obs_cond, std::string &>(
        [&](const ast::obs_cond &obs, class context &context,
            error_manager_ptr &err_manager, const type_ptr &default_type,
            std::string &default_t) {
            if (std::holds_alternative<ast::default_obs_cond_ptr>(obs)) {
                const auto &default_obs = std::get<ast::default_obs_cond_ptr>(obs);

                if (not default_t.empty())
                    err_manager->throw_error(error_type::default_obs_cond_redeclaration,
                                             default_obs->get_obs_type()->get_token_ptr());

                default_t = default_obs->get_obs_type()->get_token().get_lexeme();
            }
        });

    formulas_and_lists_type_checker::check_list<ast::obs_cond, std::string &>(
            obs_conditions, ground_elem, context, err_manager,
            context.types.get_type("agent"), default_t);
}

void actions_type_checker::check_missing_else_cond(const ast::list<ast::obs_cond> &obs_conditions,
                                                   context &context, error_manager_ptr &err_manager,
                                                   const std::string &err_info, std::string &default_t) {
    bool missing_default_cond = default_t.empty();

    auto ground_elem = formulas_and_lists_type_checker::check_function_t<
        ast::obs_cond>(
        [&](const ast::obs_cond &obs, class context &context,
            error_manager_ptr &err_manager, const type_ptr &default_type) {
            if (std::holds_alternative<ast::if_then_else_obs_cond_ptr>(obs)) {
                const auto &ite_obs = std::get<ast::if_then_else_obs_cond_ptr>(obs);

                if (not ite_obs->get_else_cond().has_value() and missing_default_cond)
                    err_manager->throw_error(error_type::missing_else_or_default_obs_cond,
                                             ite_obs->get_info());
            }
        });

    formulas_and_lists_type_checker::check_list<ast::obs_cond>(
            obs_conditions, ground_elem, context, err_manager,
            context.types.get_type("agent"));
}
