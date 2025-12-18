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

#include "../../../include/grounder/actions/actions_grounder.h"
#include "../../../include/grounder/actions/events_grounder.h"
#include "../../../include/grounder/actions/obs_conditions_grounder.h"
#include "../../../include/grounder/relations/relations_grounder.h"
#include <memory>
#include <string>

using namespace epddl;
using namespace epddl::grounder;

del::action_deque actions_grounder::build_actions(const planning_specification &spec, grounder_info &info) {
    del::action_deque actions;

    for (const std::string &action_name : info.context.actions.get_action_names()) {
        const ast::action_ptr &action = info.context.actions.get_action_decl(action_name);
        typed_var_list typed_vars = info.context.actions.get_formal_param_types_action(action->get_name());
        combinations_handler handler{typed_vars, info.context};

        while (handler.has_next()) {
            const combination &combination = handler.next();
            info.assignment.push(typed_vars, combination);

            if (list_comprehensions_handler::holds_condition(action->get_params()->get_condition(), info))
                actions.emplace_back(actions_grounder::build_action(action, info));

            info.assignment.pop();
        }
    }
    return actions;
}

del::action_ptr actions_grounder::build_action(const ast::action_ptr &action, grounder_info &info) {
    info.context.entities.push();
    info.context.entities.add_decl_list(info.context.types, action->get_params()->get_formal_params(),
                                        info.context.types.get_type("entity"));

    info.context.entities.update_typed_entities_sets(info.context.types);

    del::action_ptr del_action = action->get_signature()->is_basic()
            ? actions_grounder::build_basic_action(action, info)
            : actions_grounder::build_non_basic_action(action, info);

    info.context.entities.pop();
    return del_action;
}

del::action_ptr actions_grounder::build_non_basic_action(const ast::action_ptr &action, grounder_info &info) {
    const ast::action_type_ptr &action_type =
            info.context.action_types.get_action_type_decl(action->get_signature()->get_name());
    unsigned long events_no = action_type->get_events().size();

    name_vector event_vars_names, ground_events_names, obs_types_names;
    name_id_map events_ids;
    del::event_id id = 0;

    for (auto [e_var, e_arg] = std::tuple{
            action_type->get_events().begin(),
            action->get_signature()->get_events().begin()};
         e_var != action_type->get_events().end();
         ++e_var, ++e_arg) {
        const std::string
                &var_name = (*e_var)->get_token().get_lexeme(),
                &arg_name = (*e_arg)->get_name()->get_token().get_lexeme();

        events_ids[var_name] = id++;
        event_vars_names.emplace_back(var_name);
        ground_events_names.emplace_back(arg_name);
    }

    for (const ast::identifier_ptr &obs_type : action_type->get_obs_types())
        obs_types_names.emplace_back(obs_type->get_token().get_lexeme());

    del::action_relations q =
            actions_grounder::build_action_relations(action, action_type, info, events_ids);
    auto [pre, post] = events_grounder::build_pre_post(action, info);
    del::obs_conditions obs = obs_conditions_grounder::build_obs_conditions(action, info);

    del::event_bitset designated = actions_grounder::build_designated_events(action_type, events_ids, events_no);
    del::action_params params = actions_grounder::build_action_params(action, info);

    boost::dynamic_bitset<> is_ontic = actions_grounder::build_is_ontic(info, events_ids, ground_events_names, events_no);

    std::string action_name = actions_grounder::build_action_name(action, info);
    std::string action_type_name = action_type->get_name()->get_token().get_lexeme();

    return std::make_shared<del::action>(info.language, std::move(action_name), std::move(action_type_name),
                                         events_no, std::move(q), std::move(pre), std::move(post),
                                         std::move(obs), std::move(designated), std::move(params),
                                         std::move(ground_events_names), std::move(event_vars_names),
                                         std::move(obs_types_names), std::move(is_ontic));
}

del::action_ptr actions_grounder::build_basic_action(const ast::action_ptr &action, grounder_info &info) {
    unsigned long events_no = 1, obs_types_no = 1;
    const auto &event_name = action->get_signature()->get_events().front()->get_name();

    name_vector
        event_vars_names{"?e"},
        ground_events_names{event_name->get_token().get_lexeme()},
        obs_types_names{"Fully"};

    del::event_bitset all_events(events_no);
    all_events.push_back(0);

    del::action_relations q(obs_types_no);
    q[0] = del::action_agent_relations{std::move(all_events)};

    auto [pre, post] = events_grounder::build_pre_post(action, info);
    del::obs_conditions obs = obs_conditions_grounder::build_obs_conditions(action, info);

    del::event_bitset designated{events_no};
    designated.push_back(0);

    del::action_params params = actions_grounder::build_action_params(action, info);

    boost::dynamic_bitset<> is_ontic(events_no);

    std::string action_name = actions_grounder::build_action_name(action, info);
    std::string action_type_name = "basic";

    return std::make_shared<del::action>(info.language, std::move(action_name), std::move(action_type_name),
                                         events_no, std::move(q), std::move(pre), std::move(post),
                                         std::move(obs), std::move(designated), std::move(params),
                                         std::move(ground_events_names), std::move(event_vars_names),
                                         std::move(obs_types_names), std::move(is_ontic));
}

del::action_relations
actions_grounder::build_action_relations(const ast::action_ptr &action, const ast::action_type_ptr &action_type,
                                         grounder_info &info, const name_id_map &events_ids) {
    info.context.entities.push();

    info.context.entities.add_decl_list(action_type->get_events(),
                                        type_checker::either_type{info.context.types.get_type_id("event")}, true);
    info.context.entities.add_decl_list(action_type->get_obs_types(),
                                        type_checker::either_type{info.context.types.get_type_id("obs-type")});

    info.context.entities.update_typed_entities_sets(info.context.types);

    name_id_map obs_types_ids;
    del::obs_type id = 0;

    for (const ast::identifier_ptr &obs_type_name : action_type->get_obs_types())
        obs_types_ids[obs_type_name->get_token().get_lexeme()] = id++;

    del::action_relations q = relations_grounder::build_relations<ast::variable_ptr>(
            action_type->get_relations(), info, events_ids, obs_types_ids,
            action_type->get_obs_types().size(), action_type->get_events().size());

    info.context.entities.pop();
    return q;
}

del::event_bitset
actions_grounder::build_designated_events(const ast::action_type_ptr &action_type, const name_id_map &events_ids,
                                          const del::event_id events_no) {
    del::event_bitset designated{events_no};

    for (const ast::variable_ptr &e_d: action_type->get_designated())
        designated.push_back(events_ids.at(e_d->get_token().get_lexeme()));

    return designated;
}

del::action_params
actions_grounder::build_action_params(const ast::action_ptr &action, grounder_info &info) {
    typed_var_list typed_vars = info.context.actions.get_formal_param_types_action(action->get_name());
    del::formula_ptr condition = formulas_and_lists_grounder::build_condition(
            action->get_params()->get_condition(), info);

    return del::action_params{std::move(typed_vars), std::move(condition)};
}

boost::dynamic_bitset<>
actions_grounder::build_is_ontic(grounder_info &info, const name_id_map &events_ids,
                                 const name_vector &ground_events_names, const del::event_id events_no) {
    boost::dynamic_bitset<> is_ontic{events_no};

    for (auto [e_id, e_name] = std::tuple{events_ids.begin(), ground_events_names.begin()};
         e_id != events_ids.end();
         ++e_id, ++e_name) {
        is_ontic[e_id->second] = info.context.events.is_ontic(*e_name);
    }

    return is_ontic;
}

std::string
actions_grounder::build_action_name(const ast::action_ptr &action, grounder_info &info) {
    std::string action_name = action->get_name()->get_token().get_lexeme();

    for (const ast::formal_param &param : action->get_params()->get_formal_params()) {
        const std::string &var_name = param->get_var()->get_token().get_lexeme();
        action_name += "_" + info.assignment.get_assigned_entity_name(info.context.entities, var_name);
    }

    return action_name;
}
