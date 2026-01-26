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

#include "../../../../../include/frontend/plank/cli/commands/validate.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"
#include "../../../../../include/frontend/plank/cli/cli_utils.h"
#include "../../../../../include/frontend/plank/cli/commands/ground.h"
#include "../../../../../include/lib/del/semantics/model_checker.h"
#include "../../../../../include/lib/del/semantics/update/updater.h"
#include <ios>

using namespace plank;
using namespace plank::commands;

void validate::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(validate::get_name());

    menu->Insert(
        commands::validate::get_name(),
        commands::validate::run_cmd(data, exit_code),
        commands::validate::get_description(),
        {commands::validate::get_man_page()}
    );
}

std::string validate::get_name() {
    return PLANK_CMD_VALIDATE;
}

std::string validate::get_description() {
    return "   Validate an action sequence in the current task. If no actions are provided, the goal "
           "formula is checked on the initial epistemic state.\n\n"
           "    This command might trigger the grounding of the logical language, i.e., the computation "
           "of the set of agents and the set of ground predicates of the task. In this event, and if a mismatch "
           "is found in such sets (e.g., some new agents have been added, or some predicates have been removed "
           "in the specification), then all existing states and formulas would no longer be compatible with the "
           "new logical language, as they are based on a different language. Should this happen, a message is "
           "prompted to the user asking to choose between two options:\n"
           " 1. Accept the new logical language and delete all existing states and formulas in the current task.\n"
           " 2. Discard the new language and maintain all data.\n"
           "If the second option is chosen, then all modifications of the specification are not imported, "
           "and the EPDDL files are not modified.";
}

std::string validate::get_man_page() {
    auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
    std::stringstream buffer;

    string_vector vec;
    bool b;

    buffer << make_man_page(validate::get_cli(vec, b), validate::get_name(), fmt)
            .prepend_section("DESCRIPTION",
                             cli_utils::get_formatted_man_description(validate::get_description()));

    return buffer.str();
}

clipp::group validate::get_cli(string_vector &actions_names, bool &ground) {
    return clipp::group(
        clipp::opt_values("action(s) name(s)", actions_names).doc("action sequence to validate"),
        clipp::option("-g", "--ground").set(ground).doc("force grounding before validation")
    );
}

cmd_function<string_vector> validate::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        string_vector actions_names;
        bool ground = false;

        auto cli = validate::get_cli(actions_names, ground);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            std::cout << make_man_page(cli, validate::get_name(), fmt);
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        for (const std::string &action_name : actions_names)
            if (not cli_utils::check_name(out, action_name, validate::get_name())) {
                exit_code = plank::exit_code::cli_cmd_error;
                return;
            }

        if (not data.is_opened_task()) {
            out << validate::get_name() << ": no task is currently opened." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        cli_task_data &current_task_data = data.get_current_task_data();

        if ((ground or not current_task_data.is_set_task()) and
            current_task_data.ground(out, validate::get_name()) != plank::exit_code::all_good) {
                exit_code = plank::exit_code::cli_cmd_error;
                return;
            }

        exit_code = validate::do_validation(out, data, actions_names);
    };
}

plank::exit_code validate::do_validation(std::ostream &out, plank::cli_data &data,
                                         const plank::string_vector &actions_names) {
    const auto &[s0, _, actions_map, goal] =
            data.get_current_task_data().get_task();

    if (actions_names.empty()) {
        out << std::boolalpha << del::model_checker::satisfies(s0, goal) << std::endl;
        return plank::exit_code::all_good;
    }

    del::action_deque actions;

    for (const std::string &action_name : actions_names)
        if (auto it = actions_map.find(action_name); it == actions_map.end()) {
            out << validate::get_name() << ": undefined action "
                << cli_utils::quote(action_name) << "." << std::endl;
            return plank::exit_code::elem_not_found_error;
        } else
            actions.emplace_back(it->second);

    const del::state_deque results = del::updater::product_update(s0, actions);
    const size_t applied_actions = results.size() - 1;

    if (applied_actions < actions.size()) {
        std::string where = "init";

        for (size_t i = 0; i < applied_actions; ++i)
            where.append(" (X) ").append(actions[i]->get_name());

        out << "false (" << actions[applied_actions-1]->get_name()
            << " is not applicable in " << where << ")" << std::endl;
    } else
        out << std::boolalpha << del::model_checker::satisfies(results.back(), goal) << std::endl;

    return plank::exit_code::all_good;
}
