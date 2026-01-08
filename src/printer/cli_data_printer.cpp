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

#include "../../include/printer/cli_data_printer.h"
#include "../../include/printer/specification_printer.h"
#include "../../include/printer/tasks/formulas_printer.h"
#include "../../include/printer/tasks/initial_state_printer.h"

using namespace printer;

void cli_data::save_data(const fs::path &json_path, plank::cli_data &data) {
    if (not fs::exists(json_path.parent_path()))
        fs::create_directories(json_path.parent_path());

    std::cout << "Saving session..." << std::flush;
    json cli_data_json = cli_data::build_json(data);

    std::ofstream json_of;
    json_of.open(json_path);

    if (json_of.is_open())
        json_of << cli_data_json.dump(4) << std::endl;
    else
        std::cerr << "Unable to save plank session." << std::endl;

    json_of.close();
    std::cout << "done." << std::endl;
}

json cli_data::build_json(plank::cli_data &data) {
    json tasks = json::array();

    for (const std::string &task_name : data.get_tasks_names())
        tasks.emplace_back(cli_data::build_task_json(data.get_task_data(task_name), task_name));

    return tasks;
}

json cli_data::build_task_json(plank::cli_task_data &task_data, const std::string &name) {
    return json::array({
        json::object({ {"name", name} }),
        json::object({ {"paths", specification_printer::build_specification_json(task_data.get_spec_paths())} }),
        json::object({ {"states", cli_data::build_states_json(task_data)} }),
        json::object({ {"formulas", cli_data::build_formulas_json(task_data)} })
    });
}

json cli_data::build_states_json(plank::cli_task_data &task_data) {
    json states = json::array();

    for (const std::string &state_name : task_data.get_states_names())
        states.emplace_back(
            json::array({
                json::object({ {"name", state_name} }),
                json::object({ {"state", initial_state_printer::build_state_json(
                        task_data.get_state(state_name))} }),
                json::object({ {"description", task_data.get_state_description(state_name)} })
            }));

    return states;
}

json cli_data::build_formulas_json(plank::cli_task_data &task_data) {
    json formulas = json::array();

    for (const std::string &formula_name : task_data.get_formulas_names())
        formulas.emplace_back(
            json::array({
                json::object({ {"name", formula_name} }),
                json::object({ {"formula", formulas_printer::build_formula_json(
                        task_data.get_info().language, task_data.get_formula(formula_name))} })
            }));

    return formulas;
}
