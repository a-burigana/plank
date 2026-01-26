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

#include "json-printer/planning_task_printer.h"
#include "json-printer/language_printer.h"
#include "json-printer/formulas_printer.h"
#include "json-printer/initial_state_printer.h"
#include "json-printer/facts_printer.h"
#include "json-printer/actions_printer.h"

using namespace printer;

void planning_task_printer::print_planning_task_json(const del::planning_task &task,
                                                     const epddl::grounder::grounder_info &info,
                                                     const fs::path &output_path) {
    ordered_json task_json = planning_task_printer::build_planning_task_json(task, info);

    auto path = fs::path(output_path);

    if (not fs::exists(path.parent_path()))
        fs::create_directories(path.parent_path());

    auto json_path = (path.parent_path() / (path.stem().string() + ".json")).lexically_normal();

    std::ofstream json_of;
    json_of.open(json_path);

    if (json_of.is_open())
        json_of << task_json.dump(4) << std::endl;
    else
        std::cerr << "Unable to write to file '" << json_path << "'." << std::endl;

    json_of.close();
}

ordered_json planning_task_printer::build_planning_task_json(const del::planning_task &task,
                                                             const epddl::grounder::grounder_info &info) {
    const auto &[s0, actions_names, actions, goal] = task;
    ordered_json task_json;

    task_json["planning-task-info"] = planning_task_printer::build_planning_task_info_json(task, info);
    task_json["language"] = language_printer::build_language_json(s0->get_language());
    task_json["facts"] = facts_printer::build_facts_json(info.language, info.facts);
    task_json["initial-state"] = initial_state_printer::build_state_json(s0);
    task_json["actions"] = actions_printer::build_actions_json(actions_names, actions);
    task_json["goal"] = formulas_printer::build_formula_json(s0->get_language(), goal);

    return task_json;
}

ordered_json planning_task_printer::build_planning_task_info_json(const del::planning_task &task,
                                                          const epddl::grounder::grounder_info &info) {
    const auto &[s0, actions_names, actions, goal] = task;
    ordered_json info_json;

    json libraries_json = json::array();
    json requirements_json = json::array();

    for (const std::string &lib_name : info.context.components_names.get_libraries_names())
        libraries_json.emplace_back(lib_name);

    for (const std::string &req : info.context.requirements.get_total_requirements())
        requirements_json.emplace_back(req);

    info_json["problem"] = info.context.components_names.get_problem_name();
    info_json["domain"] = info.context.components_names.get_domain_name();
    info_json["libraries"] = libraries_json;

    info_json["requirements"] = requirements_json;

    info_json["agents-number"] = info.language->get_agents_number();
    info_json["atoms-number"] = info.language->get_atoms_number();
    info_json["facts-number"] = info.facts.size();
    info_json["actions-number"] = actions.size();
    info_json["initial-worlds-number"] = s0->get_worlds_number();

    info_json["goal-modal-depth"] = del::formulas_utils::get_modal_depth(goal);
    info_json["goal-size"] = del::formulas_utils::get_size(goal);

    return info_json;
}
