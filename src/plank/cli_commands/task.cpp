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

#include "../../../include/plank/cli_commands/task.h"
#include "../../../include/plank/cli_names.h"
#include "../../../include/plank/cli_utils.h"
#include "../../../include/printer/specification_printer.h"
#include <filesystem>
#include <fstream>

using namespace plank;
using namespace plank::commands;

void task::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    menu->Insert(
        commands::task::get_name(),
        commands::task::run_cmd(menu, data),
        commands::task::get_help(),
        {commands::task::get_cmd_syntax()}
    );
}

std::string task::get_name() {
    return PLANK_CMD_TASK;
}

std::string task::get_help() {
    return "Create and manipulate epistemic planning tasks";
}

std::string task::get_cmd_syntax() {
    std::string str1, str2, str3, str4;
    std::string desc = clipp::usage_lines(task::get_cli(str1, str2, str3, str4)).str();

    return "\n\t" + cli_utils::ltrim(desc);
}

clipp::group
task::get_cli(std::string &operation, std::string &task_name, std::string &path, std::string &new_task_name) {
    return clipp::group{
        clipp::one_of(
        clipp::command(PLANK_SUB_CMD_ADD).set(operation)
                & clipp::value("task name", task_name),
            clipp::command(PLANK_SUB_CMD_REMOVE).set(operation)
                & clipp::value("task name", task_name),
            clipp::command(PLANK_SUB_CMD_RENAME).set(operation)
                & clipp::value("task name", task_name)
                & clipp::value("new task name", new_task_name),
            clipp::command(PLANK_SUB_CMD_COPY).set(operation)
                & clipp::value("task name", task_name)
                & clipp::value("new task name", new_task_name),
            clipp::command(PLANK_SUB_CMD_OPEN).set(operation)
                & clipp::value("task name", task_name),
            clipp::command(PLANK_SUB_CMD_CLOSE).set(operation),
            clipp::command(PLANK_SUB_CMD_SAVE).set(operation)
                & clipp::value("path", path)
        )
    };
}

cmd_function<string_vector> task::run_cmd(std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation, task_name, path, new_task_name;
        auto cli = task::get_cli(operation, task_name, path, new_task_name);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, task::get_name());
            return;
        }

        fs::path file_path = (data.get_current_working_dir() / path).lexically_normal();
        std::ifstream file(file_path);

        if (operation == PLANK_SUB_CMD_ADD)
            task::add(out, data, task_name);
        else if (operation == PLANK_SUB_CMD_REMOVE)
            task::remove(out, menu, data, task_name);
        else if (operation == PLANK_SUB_CMD_RENAME)
            task::rename(out, menu, data, task_name, new_task_name);
        else if (operation == PLANK_SUB_CMD_COPY)
            task::copy(out, data, task_name, new_task_name);
        else if (operation == PLANK_SUB_CMD_OPEN)
            task::open(out, menu, data, task_name);
        else if (operation == PLANK_SUB_CMD_CLOSE)
            task::close(out, menu, data);
        else if (operation == PLANK_SUB_CMD_SAVE)
            task::save(out, data, path);
        else if (operation == PLANK_SUB_CMD_SWITCH)
            task::switch_(out, menu, data, task_name);
    };
}

void task::add(std::ostream &out, cli_data &data, const std::string &task_name, cli_task_data from) {
    if (not cli_utils::check_name(out, task_name, task::get_name()))
        return;
    else if (data.is_defined_task(task_name))
        out << task::get_name() << ": redefinition of task "
            << cli_utils::quote(task_name) << "." << std::endl;
    else
        data.add_task_data(task_name, std::move(from));
}

void task::remove(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data, const std::string &task_name) {
    if (not cli_utils::check_name(out, task_name, task::get_name()))
        return;
    else if (not data.is_defined_task(task_name))
        out << task::get_name() << ": undefined task "
            << cli_utils::quote(task_name) << "." << std::endl;
    else {
        if (data.get_current_task() == task_name)
            task::close(out, menu, data);

        data.remove_task_data(task_name);
    }
}

void task::rename(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data,
                  const std::string &task_name, const std::string &new_task_name) {
    if (not cli_utils::check_name(out, task_name, task::get_name()) or
        not cli_utils::check_name(out, new_task_name, task::get_name()) or
        task_name == new_task_name)
        return;

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
    }
}

void task::copy(std::ostream &out, plank::cli_data &data, const std::string &task_name,
                const std::string &new_task_name) {
    if (not cli_utils::check_name(out, task_name, task::get_name()) or
        not cli_utils::check_name(out, new_task_name, task::get_name()) or
        task_name == new_task_name)
        return;

    if (not data.is_defined_task(task_name))
        out << task::get_name() << ": undefined task "
            << cli_utils::quote(task_name) << "." << std::endl;
    else if (data.is_defined_task(new_task_name))
        out << task::get_name() << ": redefinition of task "
            << cli_utils::quote(new_task_name) << "." << std::endl;
    else {
        cli_task_data data_copy = data.get_current_task_data();
        data.add_task_data(new_task_name, std::move(data_copy));
    }
}

void task::open(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data, const std::string &task_name) {
    if (not cli_utils::check_name(out, task_name, task::get_name()))
        return;
    else if (data.is_opened_task()) {
        out << task::get_name() << ": task "
            << cli_utils::quote(data.get_current_task())
            << " is already opened. Close it first, or use "
            << task::get_name() << " " << PLANK_SUB_CMD_SWITCH << std::endl;

        return;
    }

    if (not data.is_defined_task(task_name))
        data.add_task_data(task_name, cli_task_data{});

    data.set_current_task(task_name);
    menu->set_prompt(PLANK_NAME + std::string{"/"} + task_name);
}

void task::close(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    if (not data.is_opened_task())
        out << task::get_name() << ": no task is currently opened." << std::endl;
    else {
        data.reset_current_task();
        menu->set_prompt(PLANK_NAME);
    }
}

void task::save(std::ostream &out, cli_data &data, const std::string &path) {
    if (not data.is_opened_task())
        out << task::get_name() << ": no task is currently opened." << std::endl;
    else
        printer::specification_printer::print_specification_json(
                data.get_current_task_data().get_absolute_spec_paths(data.get_current_working_dir()),
                cli_utils::get_absolute_path(data.get_current_working_dir(), path));
}

void task::switch_(std::ostream &out, std::unique_ptr<cli::Menu> &menu, plank::cli_data &data,
                   const std::string &task_name) {
    if (not cli_utils::check_name(out, task_name, task::get_name()))
        return;

    task::close(out, menu, data);
    task::open(out, menu, data, task_name);
}
