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

#include "../../../../../include/frontend/plank/cli/commands/task.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"
#include "../../../../../include/frontend/plank/cli/cli_utils.h"
#include "../../../../../include/frontend/plank/printer/specification_printer.h"
#include <filesystem>

using namespace plank;
using namespace plank::commands;

void task::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(task::get_name());

    menu->Insert(
        commands::task::get_name(),
        commands::task::run_cmd(menu, data, exit_code),
        commands::task::get_description(),
        {commands::task::get_man_page()}
    );
}

std::string task::get_name() {
    return PLANK_CMD_TASK;
}

std::string task::get_description() {
    return "    Create and manipulate epistemic planning tasks. A task contains all data relative to an EPDDL "
           "specification. Inside a task one can load the paths to EPDDL files (domain, problem, action type "
           "libraries) of a specification, and run several kinds of operations on them, such as:\n"
           " - Parsing and type-checking (command " + cli_utils::quote(PLANK_CMD_PARSE) + ").\n"
           " - Grounding (command " + cli_utils::quote(PLANK_CMD_GROUND) + ").\n"
           " - Export ground task to JSON (command " + cli_utils::quote(PLANK_CMD_EXPORT) + ").\n"
           " - Create and manipulate epistemic states (command " + cli_utils::quote(PLANK_CMD_STATE) + ").\n"
           " - Create and manipulate formulas (command " + cli_utils::quote(PLANK_CMD_FORMULA) + ").\n"
           " - Show task data (command " + cli_utils::quote(PLANK_CMD_SHOW) + ").\n"
           " - Run user defined scripts (command " + cli_utils::quote(PLANK_CMD_SCRIPT) + ").\n\n"
           "    Multiple tasks can be created in a single session. Each task provides a separate scope, so the "
           "data of each scope are separated.";
}

std::string task::get_man_page() {
    auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
    std::stringstream buffer;

    std::string str1, str2, str3, str4;

    buffer << make_man_page(task::get_cli(str1, str2, str3, str4), task::get_name(), fmt)
            .prepend_section("DESCRIPTION",
                             cli_utils::get_formatted_man_description(task::get_description()));

    return buffer.str();
}

clipp::group
task::get_cli(std::string &operation, std::string &task_name, std::string &path, std::string &new_task_name) {
    return clipp::group{
        clipp::one_of(
        clipp::command(PLANK_SUB_CMD_ADD).set(operation)
                & PLANK_SUB_CMD_ADD % clipp::group(
                    clipp::value("task name", task_name).doc("name of task to add")
                ),
            clipp::command(PLANK_SUB_CMD_REMOVE).set(operation)
                & PLANK_SUB_CMD_REMOVE % clipp::group(
                    clipp::value("task name", task_name).doc("name of task to remove")
                ),
            clipp::command(PLANK_SUB_CMD_RENAME).set(operation)
                & PLANK_SUB_CMD_RENAME % clipp::group(
                    clipp::value("task name", task_name).doc("name of task to rename")
                    & clipp::value("new task name", new_task_name).doc("new name of task")
                ),
            clipp::command(PLANK_SUB_CMD_COPY).set(operation)
                & PLANK_SUB_CMD_COPY % clipp::group(
                    clipp::value("task name", task_name).doc("name of task to copy")
                    & clipp::value("new task name", new_task_name).doc("name of new task")
                ),
            clipp::command(PLANK_SUB_CMD_OPEN).set(operation)
                & PLANK_SUB_CMD_OPEN % clipp::group(
                    clipp::value("task name", task_name).doc("name of task to open")
                ),
            clipp::command(PLANK_SUB_CMD_CLOSE).set(operation),
        clipp::command(PLANK_SUB_CMD_SAVE_SPEC).set(operation)
        & PLANK_SUB_CMD_SAVE_SPEC % clipp::group(
                    clipp::value("path", path).doc("path to file")
                ),
            clipp::command(PLANK_SUB_CMD_SWITCH).set(operation)
                & PLANK_SUB_CMD_SWITCH % clipp::group(
                    clipp::value("new task name", new_task_name).doc("name of task to switch to")
                )
        )
    };
}

cmd_function<string_vector> task::run_cmd(std::unique_ptr<cli::Menu> &menu, cli_data &data,
                                          plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation, task_name, path, new_task_name;
        auto cli = task::get_cli(operation, task_name, path, new_task_name);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            std::cout << make_man_page(cli, task::get_name(), fmt);
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        fs::path file_path = cli_utils::get_absolute_path(data.get_current_working_dir(), path);

        if (operation == PLANK_SUB_CMD_ADD)
            exit_code = task::add(out, data, task_name);
        else if (operation == PLANK_SUB_CMD_REMOVE)
            exit_code = task::remove(out, menu, data, task_name);
        else if (operation == PLANK_SUB_CMD_RENAME)
            exit_code = task::rename(out, menu, data, task_name, new_task_name);
        else if (operation == PLANK_SUB_CMD_COPY)
            exit_code = task::copy(out, data, task_name, new_task_name);
        else if (operation == PLANK_SUB_CMD_OPEN)
            exit_code = task::open(out, menu, data, task_name);
        else if (operation == PLANK_SUB_CMD_CLOSE)
            exit_code = task::close(out, menu, data);
        else if (operation == PLANK_SUB_CMD_SAVE_SPEC)
            exit_code = task::save_spec(out, data, path);
        else if (operation == PLANK_SUB_CMD_SWITCH)
            exit_code = task::switch_(out, menu, data, new_task_name);
    };
}

plank::exit_code task::add(std::ostream &out, cli_data &data, const std::string &task_name, cli_task_data from) {
    if (not cli_utils::check_name(out, task_name, task::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (data.is_defined_task(task_name)) {
        out << task::get_name() << ": redefinition of task "
            << cli_utils::quote(task_name) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.add_task_data(task_name, std::move(from));
    return plank::exit_code::all_good;
}

plank::exit_code task::remove(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data,
                              const std::string &task_name) {
    if (not cli_utils::check_name(out, task_name, task::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_defined_task(task_name)) {
        out << task::get_name() << ": undefined task "
            << cli_utils::quote(task_name) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    if (data.get_current_task() == task_name)
        task::close(out, menu, data);

    data.remove_task_data(task_name);

    return plank::exit_code::all_good;
}

plank::exit_code task::rename(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data,
                              const std::string &task_name, const std::string &new_task_name) {
    if (not cli_utils::check_name(out, task_name, task::get_name()) or
        not cli_utils::check_name(out, new_task_name, task::get_name()))
        return plank::exit_code::cli_cmd_error;

    if (task_name == new_task_name)
        return plank::exit_code::all_good;

    if (not data.is_defined_task(task_name))
        out << task::get_name() << ": undefined task "
            << cli_utils::quote(task_name) << "." << std::endl;
    else if (data.is_defined_task(new_task_name))
        out << task::get_name() << ": redefinition of task "
            << cli_utils::quote(new_task_name) << "." << std::endl;
    else {
        cli_task_data task_data = std::move(data.get_task_data(task_name));
        bool open_new_task = data.get_current_task() == task_name;

        task::remove(out, menu, data, task_name);
        task::add(out, data, new_task_name, std::move(task_data));

        if (open_new_task)
            task::open(out, menu, data, new_task_name);

        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code task::copy(std::ostream &out, plank::cli_data &data, const std::string &task_name,
                            const std::string &new_task_name) {
    if (not cli_utils::check_name(out, task_name, task::get_name()) or
        not cli_utils::check_name(out, new_task_name, task::get_name()))
        return plank::exit_code::cli_cmd_error;

    if (task_name == new_task_name)
        return plank::exit_code::all_good;

    if (not data.is_defined_task(task_name))
        out << task::get_name() << ": undefined task "
            << cli_utils::quote(task_name) << "." << std::endl;
    else if (data.is_defined_task(new_task_name))
        out << task::get_name() << ": redefinition of task "
            << cli_utils::quote(new_task_name) << "." << std::endl;
    else {
        cli_task_data data_copy = data.get_current_task_data();
        data.add_task_data(new_task_name, std::move(data_copy));

        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code task::open(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data,
                            const std::string &task_name) {
    if (not cli_utils::check_name(out, task_name, task::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (data.is_opened_task()) {
        out << task::get_name() << ": task "
            << cli_utils::quote(data.get_current_task())
            << " is already opened. Close it first, or use "
            << task::get_name() << " " << PLANK_SUB_CMD_SWITCH << "." << std::endl;

        return plank::exit_code::cli_cmd_error;
    }

    if (not data.is_defined_task(task_name))
        data.add_task_data(task_name, cli_task_data{});

    data.set_current_task(task_name);
    menu->set_prompt(PLANK_NAME + std::string{"/"} + task_name);

    return plank::exit_code::all_good;
}

plank::exit_code task::close(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    if (not data.is_opened_task()) {
        out << task::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.reset_current_task();
    menu->set_prompt(PLANK_NAME);

    return plank::exit_code::all_good;
}

plank::exit_code task::save_spec(std::ostream &out, cli_data &data, const std::string &path) {
    if (not data.is_opened_task()) {
        out << task::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    printer::specification_printer::print_specification_json(
            data.get_current_task_data().get_absolute_spec_paths(data.get_current_working_dir()),
            cli_utils::get_absolute_path(data.get_current_working_dir(), path));

    return plank::exit_code::all_good;
}

plank::exit_code task::switch_(std::ostream &out, std::unique_ptr<cli::Menu> &menu, plank::cli_data &data,
                               const std::string &new_task_name) {
    if (not cli_utils::check_name(out, new_task_name, task::get_name()))
        return plank::exit_code::cli_cmd_error;

    task::close(out, menu, data);
    task::open(out, menu, data, new_task_name);

    return plank::exit_code::all_good;
}
