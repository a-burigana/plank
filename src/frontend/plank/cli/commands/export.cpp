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

#include "../../../../../include/frontend/plank/cli/commands/export.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"
#include "../../../../../include/frontend/plank/cli/cli_utils.h"
#include "../../../../../include/frontend/plank/printer/graphviz_printer.h"
#include "../../../../../include/lib/epddl/json-printer/planning_task_printer.h"
#include <filesystem>

using namespace plank;
using namespace plank::commands;

namespace fs = std::filesystem;

void export_::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(export_::get_name());

    menu->Insert(
        commands::export_::get_name(),
        commands::export_::run_cmd(data, exit_code),
        commands::export_::get_help(),
        {commands::export_::get_cmd_syntax()}
    );
}

std::string export_::get_name() {
    return PLANK_CMD_EXPORT;
}

std::string export_::get_help() {
    return "Export task, state or action to file";
}

std::string export_::get_cmd_syntax() {
    std::string str1, str2, str3, str4;
    bool b1, b2;
    std::string desc = clipp::usage_lines(export_::get_cli(str1, str2, str3, str4, b1, b2)).str();

    return "\n\t" + cli_utils::ltrim(desc);
}

clipp::group export_::get_cli(std::string &operation, std::string &name, std::string &dir_path,
                              std::string &file_ext, bool &print_all, bool &ground) {
    auto file_options = clipp::group(
        clipp::one_of(
            clipp::value("name", name),
            clipp::command(PLANK_CMD_FLAG_ALL).set(print_all)
        ),
        clipp::one_of(
            clipp::option(PLANK_CMD_FLAG_PDF).set(file_ext),
            clipp::option(PLANK_CMD_FLAG_PNG).set(file_ext),
            clipp::option(PLANK_CMD_FLAG_JPG).set(file_ext),
            clipp::option(PLANK_CMD_FLAG_SVG).set(file_ext),
            clipp::option(PLANK_CMD_FLAG_EPS).set(file_ext),
            clipp::option(PLANK_CMD_FLAG_PS) .set(file_ext)
        )
    );

    return clipp::group(
        clipp::one_of(
            clipp::command(PLANK_SUB_CMD_TASK).set(operation)
                & clipp::group(
                    clipp::value("task name", name),
                    clipp::option("-g", "--ground").set(ground)
                ),
            clipp::command(PLANK_SUB_CMD_STATE).set(operation)
                & clipp::group(
                    clipp::one_of(
                        clipp::value("state name", name),
                        clipp::command(PLANK_CMD_FLAG_ALL).set(print_all)
                    ),
                    file_options
                ),
            clipp::command(PLANK_SUB_CMD_ACTION).set(operation)
                & clipp::group(
                    clipp::one_of(
                        clipp::value("action name", name),
                        clipp::command(PLANK_CMD_FLAG_ALL).set(print_all)
                    ),
                    file_options,
                    clipp::option("-g", "--ground").set(ground)
                )
        ),
        clipp::opt_value("path to directory", dir_path)
    );
}

cmd_function<string_vector> export_::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation, name, dir_path, file_ext = PLANK_CMD_FLAG_PDF;
        bool print_all, ground;

        auto cli = export_::get_cli(operation, name, dir_path, file_ext, print_all, ground);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, export_::get_name());
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        fs::path target = cli_utils::get_absolute_path(data.get_current_working_dir(), dir_path);

        if (operation == PLANK_SUB_CMD_TASK)
            exit_code = export_::export_task(out, data, name, target, ground);
        else if (operation == PLANK_SUB_CMD_STATE)
            exit_code = export_::export_state(out, data, name, target, file_ext, print_all);
        else if (operation == PLANK_SUB_CMD_ACTION)
            exit_code = export_::export_action(out, data, name, target, file_ext, print_all, ground);
    };
}

plank::exit_code export_::export_task(std::ostream &out, cli_data &data, const std::string &task_name,
                                      fs::path &dir_path, bool ground) {
    const std::string &json_task_name = task_name;

    if (not cli_utils::check_name(out, task_name, export_::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (json_task_name.empty()) {
        out << export_::get_name() << ": expected task name." << std::endl;
        return plank::exit_code::cli_cmd_error;
    } else if (not data.is_defined_task(json_task_name)) {
        out << export_::get_name() << ": undefined task "
            << cli_utils::quote(json_task_name) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    fs::path json_path = cli_utils::get_absolute_path(
            data.get_current_working_dir(), dir_path / fs::path{json_task_name + ".json"});

    const std::string current_task_name = data.get_current_task();
    data.set_current_task(json_task_name);

    cli_task_data &current_task_data = data.get_current_task_data();

    if ((ground or not current_task_data.is_set_task()) and
        current_task_data.ground(out, export_::get_name()) != plank::exit_code::all_good)
        return plank::exit_code::cli_cmd_error;

    if (current_task_data.is_set_info() and current_task_data.is_set_task()) {
        out << "Printing..." << std::flush;

        printer::planning_task_printer::print_planning_task_json(
                current_task_data.get_task(),
                current_task_data.get_info(),
                json_path);

        out << "done." << std::endl;
    }

    data.set_current_task(current_task_name);
    return plank::exit_code::all_good;
}

plank::exit_code export_::export_state(std::ostream &out, cli_data &data, const std::string &state_name,
                                       fs::path &dir_path, const std::string &file_ext, bool print_all) {
    if (not print_all and not cli_utils::check_name(out, state_name, export_::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_opened_task())
        out << export_::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << export_::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else {
        fs::path pdf_path = cli_utils::get_absolute_path(data.get_current_working_dir(), dir_path);

        if (not print_all) {
            const del::state_ptr &s = data.get_current_task_data().get_state(state_name);
            printer::graphviz::print_state(s, pdf_path, state_name, file_ext);
        } else {
            out << "Exporting all states..." << std::flush;

            for (const auto &[name, state_n_desc]: data.get_current_task_data().get_states())
                printer::graphviz::print_state(state_n_desc.first, pdf_path, name, file_ext);

            out << "done." << std::endl;
        }

        return plank::exit_code::all_good;
    }
    return plank::exit_code::cli_cmd_error;
}

plank::exit_code export_::export_action(std::ostream &out, cli_data &data, const std::string &action_name,
                                        fs::path &dir_path, const std::string &file_ext, bool print_all,
                                        bool ground) {
    if (not print_all and not cli_utils::check_name(out, action_name, export_::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_opened_task()) {
        out << export_::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    if ((ground or not data.get_current_task_data().is_set_task()) and
        data.get_current_task_data().ground(out, export_::get_name()) != plank::exit_code::all_good)
        return plank::exit_code::cli_cmd_error;

    auto actions = data.get_current_task_data().get_task().actions;

    if (not print_all and actions.find(action_name) == actions.end()) {
        out << export_::get_name() << ": undefined action "
            << cli_utils::quote(action_name) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    fs::path pdf_path = cli_utils::get_absolute_path(data.get_current_working_dir(), dir_path);

    if (not print_all) {
        const del::action_ptr &a = actions.at(action_name);
        printer::graphviz::print_action(a, pdf_path, action_name, file_ext);
    } else {
        out << "Exporting all actions..." << std::flush;

        for (const auto &[name, action]: actions)
            printer::graphviz::print_action(action, pdf_path, name, file_ext);

        out << "done." << std::endl;
    }

    return plank::exit_code::all_good;
}
