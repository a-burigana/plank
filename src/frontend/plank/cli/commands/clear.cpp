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

#include "../../../../../include/frontend/plank/cli/commands/clear.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"

using namespace plank;
using namespace plank::commands;

void clear::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(clear::get_name());

    menu->Insert(
        commands::clear::get_name(),
        commands::clear::run_cmd(menu, data, exit_code),
        commands::clear::get_help(),
        {commands::clear::get_cmd_syntax()}
    );
}

std::string clear::get_name() {
    return PLANK_CMD_CLEAR;
}

std::string clear::get_help() {
    return "Clear the specified data";
}

std::string clear::get_cmd_syntax() {
    std::string str;
    std::string desc = clipp::usage_lines(clear::get_cli(str)).str();

    return "  " + cli_utils::ltrim(desc);
}

clipp::group clear::get_cli(std::string &operation) {
    return clipp::group{
        clipp::one_of(
            clipp::required(PLANK_SUB_CMD_DOMAIN).set(operation),
            clipp::required(PLANK_SUB_CMD_FORMULAS).set(operation),
            clipp::required(PLANK_SUB_CMD_LIBRARIES).set(operation),
            clipp::required(PLANK_SUB_CMD_PROBLEM).set(operation),
            clipp::required(PLANK_SUB_CMD_STATES).set(operation),
            clipp::required(PLANK_SUB_CMD_TASKS).set(operation),
            clipp::required(PLANK_SUB_CMD_SPEC).set(operation)
        )
    };
}

cmd_function<string_vector> clear::run_cmd(std::unique_ptr<cli::Menu> &menu, cli_data &data,
                                           plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation;
        auto cli = clear::get_cli(operation);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, clear::get_name());
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        if (operation == PLANK_SUB_CMD_DOMAIN)
            exit_code = clear::clear_domain(out, data);
        else if (operation == PLANK_SUB_CMD_FORMULAS)
            exit_code = clear::clear_formulas(out, data);
        else if (operation == PLANK_SUB_CMD_LIBRARIES)
            exit_code = clear::clear_libraries(out, data);
        else if (operation == PLANK_SUB_CMD_PROBLEM)
            exit_code = clear::clear_problem(out, data);
        else if (operation == PLANK_SUB_CMD_STATES)
            exit_code = clear::clear_states(out, data);
        else if (operation == PLANK_SUB_CMD_TASKS)
            exit_code = clear::clear_tasks(out, menu, data);
        else if (operation == PLANK_SUB_CMD_SPEC)
            exit_code = clear::clear_spec(out, data);
    };
}

plank::exit_code clear::clear_domain(std::ostream &out, cli_data &data) {
    if (not data.is_opened_task()) {
        out << clear::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.get_current_task_data().reset_domain_path();
    return plank::exit_code::all_good;
}

plank::exit_code clear::clear_formulas(std::ostream &out, cli_data &data) {
    if (not data.is_opened_task()) {
        out << clear::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.get_current_task_data().reset_formulas();
    return plank::exit_code::all_good;
}

plank::exit_code clear::clear_libraries(std::ostream &out, cli_data &data) {
    if (not data.is_opened_task()) {
        out << clear::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.get_current_task_data().reset_libraries_paths();
    return plank::exit_code::all_good;
}

plank::exit_code clear::clear_problem(std::ostream &out, cli_data &data) {
    if (not data.is_opened_task()) {
        out << clear::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.get_current_task_data().reset_problem_path();
    return plank::exit_code::all_good;
}

plank::exit_code clear::clear_states(std::ostream &out, cli_data &data) {
    if (not data.is_opened_task()) {
        out << clear::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.get_current_task_data().reset_states();
    return plank::exit_code::all_good;
}

plank::exit_code clear::clear_tasks(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    if (data.is_opened_task())
        menu->set_prompt(PLANK_NAME);

    data.reset_tasks();
    return plank::exit_code::all_good;
}

plank::exit_code clear::clear_spec(std::ostream &out, cli_data &data) {
    if (not data.is_opened_task()) {
        out << clear::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.get_current_task_data().reset_spec_paths();
    return plank::exit_code::all_good;
}
