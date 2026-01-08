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

#include "../../../include/plank/cli_commands/validate.h"
#include "../../../include/plank/cli_names.h"
#include "../../../include/plank/cli_utils.h"
#include "../../../include/plank/cli_commands/ground.h"
#include "../../../include/del/semantics/model_checker.h"
#include "../../../include/del/semantics/update/updater.h"
#include <ios>

using namespace plank;
using namespace plank::commands;

void validate::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    menu->Insert(
            commands::validate::get_name(),
            commands::validate::run_cmd(data),
            commands::validate::get_help(),
            {commands::validate::get_cmd_syntax()}
    );
}

std::string validate::get_name() {
    return PLANK_CMD_VALIDATE;
}

std::string validate::get_help() {
    return "Validate an action sequence";
}

std::string validate::get_cmd_syntax() {
    string_vector vec;
    bool b;
    std::string desc = clipp::usage_lines(validate::get_cli(vec, b)).str();

    return "  " + cli_utils::ltrim(desc);
}

clipp::group validate::get_cli(string_vector &actions_names, bool &ground) {
    return clipp::group(
        clipp::values("action(s) name(s)", actions_names),
        clipp::option("-g", "--ground").set(ground).doc("Force grounding")
    );
}

cmd_function<string_vector> validate::run_cmd(cli_data &data) {
    return [&](std::ostream &out, const string_vector &input_args) {
        string_vector actions_names;
        bool ground = false;

        auto cli = validate::get_cli(actions_names, ground);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, validate::get_name());
            return;
        }

        for (const std::string &action_name : actions_names)
            if (not cli_utils::check_name(out, action_name, validate::get_name()))
                return;

        if (not data.is_opened_task()) {
            out << validate::get_name() << ": no task is currently opened." << std::endl;
            return;
        }

        cli_task_data &current_task_data = data.get_current_task_data();

        if (ground or not current_task_data.is_set_task())
            if (current_task_data.ground(out) != plank::exit_code::all_good)
                return;

        validate::do_validation(out, data, actions_names);
    };
}

plank::exit_code validate::do_validation(std::ostream &out, plank::cli_data &data,
                                         const plank::string_vector &actions_names) {
    const auto &[s0, actions_map, goal] =
            data.get_current_task_data().get_task();

    del::action_deque actions;

    for (const std::string &action_name : actions_names)
        if (auto it = actions_map.find(action_name); it == actions_map.end()) {
            out << validate::get_name() << ": undefined action "
                << cli_utils::quote(action_name) << "." << std::endl;
            return plank::exit_code::elem_not_found_error;
        } else
            actions.emplace_back(it->second);

    auto [index, result] = del::updater::product_update(s0, actions);

    if (index < actions.size()) {
        std::string where = "init";

        if (index > 0)
            for (size_t i = 0; i < index - 1; ++i)
                where += " * " + actions[i]->get_name();

        out << "false (" << actions[index]->get_name()
            << " is not applicable in " << where << ")" << std::endl;
    } else
        out << std::boolalpha << del::model_checker::satisfies(result, goal) << std::endl;

    return plank::exit_code::all_good;
}
