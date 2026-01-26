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
        commands::clear::get_description(),
        {commands::clear::get_man_page()}
    );
}

std::string clear::get_name() {
    return PLANK_CMD_CLEAR;
}

std::string clear::get_description() {
    return "    Clear the specified data.";
}

std::string clear::get_man_page() {
    auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
    std::stringstream buffer;

    std::string str;

    buffer << make_man_page(clear::get_cli(str), clear::get_name(), fmt)
                .prepend_section("DESCRIPTION",
                                 cli_utils::get_formatted_man_description(clear::get_description()));

    return buffer.str();
}

clipp::group clear::get_cli(std::string &operation) {
    return clipp::group{
        "data to clear" %
        clipp::one_of(
            clipp::command(PLANK_SUB_CMD_PROBLEM).set(operation).doc("clear EPDDL problem path of current task"),
            clipp::command(PLANK_SUB_CMD_DOMAIN).set(operation).doc("clear EPDDL domain path of current task"),
            clipp::command(PLANK_SUB_CMD_LIBRARIES).set(operation).doc("clear EPDDL libraries paths of current task"),
            clipp::command(PLANK_SUB_CMD_SPEC).set(operation).doc("clear all EPDDL specification paths of current task"),
            clipp::command(PLANK_SUB_CMD_TASKS).set(operation).doc("clear tasks"),
            clipp::command(PLANK_SUB_CMD_STATES).set(operation).doc("clear states of current task"),
            clipp::command(PLANK_SUB_CMD_FORMULAS).set(operation).doc("clear formulas of current task"),
            clipp::command(PLANK_SUB_CMD_SCRIPTS).set(operation).doc("clear scripts")
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
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            std::cout << make_man_page(cli, clear::get_name(), fmt);
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
        else if (operation == PLANK_SUB_CMD_SCRIPTS)
            exit_code = clear::clear_scripts(data);
        else if (operation == PLANK_SUB_CMD_STATES)
            exit_code = clear::clear_states(out, data);
        else if (operation == PLANK_SUB_CMD_TASKS)
            exit_code = clear::clear_tasks(menu, data);
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

plank::exit_code clear::clear_scripts(plank::cli_data &data) {
    data.reset_scripts();
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

plank::exit_code clear::clear_tasks(std::unique_ptr<cli::Menu> &menu, cli_data &data) {
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
