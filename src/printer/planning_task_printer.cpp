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

#include "../../include/printer/planning_task_printer.h"
#include "../../include/printer/language_printer.h"
#include "../../include/printer/formulas_printer.h"
#include "../../include/printer/initial_state_printer.h"
#include "../../include/printer/actions_printer.h"

using namespace epddl::printer;

json planning_task_printer::build_planning_task_json(const del::planning_task &task,
                                                     const grounder::grounder_info &info) {
    const auto &[s0, actions, goal] = task;

    json info_json     = planning_task_printer::build_planning_task_info_json(task, info);
    json language_json = language_printer::build_language_json(s0->get_language());
    json s0_json       = initial_state_printer::build_state_json(s0);
    json actions_json  = actions_printer::build_actions_json(actions);
    json goal_json     = formulas_printer::build_formula_json(s0->get_language(), goal);

    return json::array({
        {"planning-task-info", std::move(info_json)},
        {"language",           std::move(language_json)},
        {"initial-state",      std::move(s0_json)},
        {"actions",            std::move(actions_json)},
        {"goal",               std::move(goal_json)}
    });
}

json planning_task_printer::build_planning_task_info_json(const del::planning_task &task,
                                                          const grounder::grounder_info &info) {
    const auto &[s0, actions, goal] = task;
    json info_json = json::array();

    info_json.emplace_back(json::object({ {
        "problem", info.context.components_names.get_problem_name()
    } }));

    info_json.emplace_back(json::object({ {
        "domain", info.context.components_names.get_domain_name()
    } }));

    json libraries_json = json::array();

    for (const std::string &lib_name : info.context.components_names.get_libraries_names())
        libraries_json.emplace_back(lib_name);

    info_json.emplace_back(json::object({ {
        "libraries", std::move(libraries_json)
    } }));

    info_json.emplace_back(json::object({ {
        "agents-number", info.language->get_agents_number()
    } }));

    info_json.emplace_back(json::object({ {
        "atoms-number", info.language->get_atoms_number()
    } }));

    info_json.emplace_back(json::object({ {
        "initial-worlds-number", s0->get_worlds_number()
    } }));

    info_json.emplace_back(json::object({ {
        "actions-number", actions.size()
    } }));

    info_json.emplace_back(json::object({ {
        "goal-modal-depth", del::formulas_utils::get_modal_depth(goal)
    } }));

    info_json.emplace_back(json::object({ {
        "goal-size", del::formulas_utils::get_size(goal)
    } }));

    return info_json;
}
