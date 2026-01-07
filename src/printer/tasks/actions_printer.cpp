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

#include "../../../include/printer/tasks/actions_printer.h"
#include "../../../include/printer/tasks/formulas_printer.h"

using namespace printer;

json actions_printer::build_actions_json(const del::action_map &actions) {
    json actions_json = json::array();

    for (const auto &[action_name, action] : actions)
        actions_json.emplace_back(json::object({ {
            "action",
            actions_printer::build_action_json(action)
        } }));

    return actions_json;
}

json actions_printer::build_action_json(const del::action_ptr &action) {
    json events_json = json::array(), des_events_json = json::array();

    for (del::event_id e = 0; e < action->get_events_number(); ++e)
        events_json.emplace_back(action->get_event_name(e));

    for (del::event_id e_d : action->get_designated_events())
        des_events_json.emplace_back(action->get_event_name(e_d));

    json q_json = actions_printer::build_relations(action);
    json pre_json = actions_printer::build_preconditions(action);
    json post_json = actions_printer::build_postconditions(action);
    json obs_json = actions_printer::build_obs_conditions(action);

    return json::array({
        json::object({ {"action-name", action->get_name()} }),
        json::object({ {"action-type", action->get_action_type_name()} }),
        json::object({ {"events", std::move(events_json)} }),
        json::object({ {"relations", std::move(q_json)} }),
        json::object({ {"designated", std::move(des_events_json)} }),
        json::object({ {"preconditions", std::move(pre_json)} }),
        json::object({ {"effects", std::move(post_json)} }),
        json::object({ {"observability-conditions", std::move(obs_json)} })
    });
}

json actions_printer::build_relations(const del::action_ptr &action) {
    json q_json = json::array();

    for (del::obs_type t = 0; t < action->get_obs_types_number(); ++t) {
        json q_t = json::array();

        for (del::event_id e = 0; e < action->get_events_number(); ++e) {
            json e_events = json::array();

            for (const del::event_id f: action->get_obs_type_possible_events(t, e))
                e_events.emplace_back(action->get_event_name(f));

            q_t.emplace_back(json::object({ {action->get_event_name(e), std::move(e_events)} }));
        }
        q_json.emplace_back(json::object({ {action->get_obs_type_name(t), std::move(q_t)} }));
    }
    return q_json;
}

json actions_printer::build_preconditions(const del::action_ptr &action) {
    json pre_json = json::array();

    for (del::event_id e = 0; e < action->get_events_number(); ++e)
        pre_json.emplace_back(json::object({ {
            action->get_event_name(e),
            formulas_printer::build_formula_json(action->get_language(), action->get_precondition(e))
        } }));

    return pre_json;
}

json actions_printer::build_postconditions(const del::action_ptr &action) {
    json post_json = json::array();

    for (del::event_id e = 0; e < action->get_events_number(); ++e) {
        json post_e_json = json::array();

        for (const auto &[p, cond]: action->get_postconditions(e))
            post_e_json.emplace_back(json::object({ {
            action->get_language()->get_atom_name(p),
            formulas_printer::build_formula_json(action->get_language(), cond)
        } }));

        post_json.emplace_back(json::object({ {
            action->get_event_name(e),
            std::move(post_e_json)
        } }));
    }
    return post_json;
}

json actions_printer::build_obs_conditions(const del::action_ptr &action) {
    json obs_json = json::array();

    for (del::agent i = 0; i < action->get_language()->get_agents_number(); ++i) {
        json obs_i_json = json::array();

        for (del::obs_type t = 0; t < action->get_obs_types_number(); ++t)
            if (action->get_agent_obs_conditions(i).find(t) != action->get_agent_obs_conditions(i).end())
                obs_i_json.emplace_back(json::object({{
                    action->get_obs_type_name(t),
                    formulas_printer::build_formula_json(
                            action->get_language(), action->get_obs_condition(i, t))
                }}));

        obs_json.emplace_back(json::object({ {
            action->get_language()->get_agent_name(i),
            std::move(obs_i_json)
        } }));
    }
    return obs_json;
}

