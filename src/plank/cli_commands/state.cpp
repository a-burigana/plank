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

#include "../../../include/plank/cli_commands/state.h"
#include "../../../include/plank/cli_commands/ground.h"
#include "../../../include/plank/cli_names.h"
#include "../../../include/plank/cli_commands/parse.h"
#include "../../../include/grounder/grounder_helper.h"
#include "../../../include/grounder/initial_state/initial_state_grounder.h"
#include "../../../include/del/semantics/model_checker.h"
#include "../../../include/del/semantics/update/updater.h"
#include "../../../include/del/semantics/states/bisimulations/bisimulator.h"
#include "../../../include/printer/graphviz_printer.h"
#include <algorithm>
#include <filesystem>
#include <fstream>

using namespace plank;
using namespace plank::commands;

void state::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    menu->Insert(
            commands::state::get_name(),
            commands::state::run_cmd(data),
            commands::state::get_help(),
            {commands::state::get_cmd_syntax()}
    );
}

std::string state::get_name() {
    return PLANK_CMD_STATE;
}

std::string state::get_help() {
    return "Create and manipulate epistemic states";
}

std::string state::get_cmd_syntax() {
    std::string str1, str2, str3, str4, str5;
    string_vector vec1;
    bool b1, b2;
    std::string desc = clipp::usage_lines(state::get_cli(
            str1, str2, str3, str4, str5, vec1, b1, b2)).str();

    return "\n\t" + cli_utils::ltrim(desc);
}

clipp::group
state::get_cli(std::string &operation, std::string &state_name, std::string &path, std::string &new_state_name,
               std::string &formula, string_vector &actions_names, bool &contract, bool &ground) {
    return clipp::group(
        clipp::one_of(
            clipp::command(PLANK_SUB_CMD_ADD_INIT).set(operation)
                & clipp::value("state name", state_name),
            clipp::command(PLANK_SUB_CMD_REMOVE).set(operation)
                & clipp::value("state name", state_name),
            clipp::command(PLANK_SUB_CMD_RENAME).set(operation)
                & clipp::value("state name", state_name)
                & clipp::value("new state name", new_state_name),
            clipp::command(PLANK_SUB_CMD_COPY).set(operation)
                & clipp::value("state name", state_name)
                & clipp::value("new state name", new_state_name),
            clipp::command(PLANK_SUB_CMD_CHECK).set(operation)
                & clipp::value("state name", state_name)
                & clipp::value("formula (name)", formula),
            clipp::command(PLANK_SUB_CMD_APPLICABLE).set(operation)
                & clipp::group(
                    clipp::group(
                        clipp::value("state name", state_name)
                            & clipp::values("action(s) name(s)", actions_names)
                        ),
                    clipp::group(clipp::option("-g", "--ground").set(ground))
                ),
            clipp::command(PLANK_SUB_CMD_UPDATE).set(operation)
                & clipp::group(
                    clipp::group(
                        clipp::value("state name", state_name)
                            & clipp::values("action(s) name(s)", actions_names)
                        ),
                    clipp::group(
                        clipp::option("-a", "--assign")
                            & clipp::value("new state name", new_state_name)
                        ),
                    clipp::option("-c", "--contract").set(contract),
                    clipp::group(
                        clipp::option("-p", "--pdf")
                            & clipp::value("path to directory", path)
                        ),
                    clipp::group(clipp::option("-g", "--ground").set(ground))
                ),
            clipp::command(PLANK_SUB_CMD_CONTRACT).set(operation)
                & clipp::group(
                    clipp::value("state name", state_name),
                    clipp::group(
                        clipp::option("-a", "--assign")
                            & clipp::value("new state name", new_state_name)
                        ),
                    clipp::group(
                        clipp::option("-p", "--pdf")
                            & clipp::value("path to directory", path)
                        )
                )
        )
    );
}

cmd_function<string_vector> state::run_cmd(cli_data &data) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation, state_name, path, new_state_name, formula;
        string_vector actions_names;
        bool contract, ground;

        auto cli = state::get_cli(
                operation, state_name, path, new_state_name,
                formula, actions_names, contract, ground);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, state::get_name());
            return;
        }

        fs::path file_path = (data.get_current_working_dir() / path).lexically_normal();
        std::ifstream file(file_path);

        if (operation == PLANK_SUB_CMD_ADD_INIT)
            state::add(out, data, state_name);
        else if (operation == PLANK_SUB_CMD_REMOVE)
            state::remove(out, data, state_name);
        else if (operation == PLANK_SUB_CMD_RENAME)
            state::rename(out, data, state_name, new_state_name);
        else if (operation == PLANK_SUB_CMD_COPY)
            state::copy(out, data, state_name, new_state_name);
        else if (operation == PLANK_SUB_CMD_CHECK)
            state::check(out, data, state_name, formula);
        else if (operation == PLANK_SUB_CMD_APPLICABLE)
            state::applicable(out, data, state_name, actions_names, ground);
        else if (operation == PLANK_SUB_CMD_UPDATE)
            state::update(out, data, state_name, actions_names, new_state_name, contract, ground, path);
        else if (operation == PLANK_SUB_CMD_CONTRACT)
            state::contract(out, data, state_name, new_state_name, path);
    };
}

void state::add(std::ostream &out, cli_data &data, const std::string &state_name) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return;
    else if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": redefinition of state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else if (not data.get_current_task_data().is_loaded_domain())
        out << state::get_name() << ": no domain was loaded." << std::endl;
    else if (not data.get_current_task_data().is_loaded_problem())
        out << state::get_name() << ": no problem was loaded." << std::endl;
    else {
        cli_task_data &current_task_data = data.get_current_task_data();
        commands::parse::run_cmd(data, false)(out, {});

        if (current_task_data.is_set_specification() and
            current_task_data.is_set_error_managers() and
            current_task_data.is_set_context()) {
            out << "Grounding initial state..." << std::flush;

            epddl::grounder::grounder_info info = epddl::grounder::grounder_helper::build_info(
                    current_task_data.get_specification(),
                    current_task_data.get_context(),
                    current_task_data.get_error_managers());

            del::state_ptr s0 = epddl::grounder::initial_state_grounder::build_initial_state(
                    current_task_data.get_specification(),
                    info);

            current_task_data.set_info(info);
            current_task_data.add_state(
                    state_name, s0,
                    "Initial state of problem " +
                    cli_utils::quote(info.context.components_names.get_problem_name()));

            out << " done." << std::endl;
        }
    }
}

void state::remove(std::ostream &out, cli_data &data, const std::string &state_name) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return;
    else if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else
        data.get_current_task_data().remove_state(state_name);
}

void state::rename(std::ostream &out, cli_data &data, const std::string &state_name,
                   const std::string &new_state_name) {
    if (not cli_utils::check_name(out, state_name, state::get_name()) or
        not cli_utils::check_name(out, new_state_name, state::get_name()) or
        state_name == new_state_name)
        return;

    if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else if (data.get_current_task_data().is_defined_state(new_state_name))
        out << state::get_name() << ": redefinition of state "
            << cli_utils::quote(new_state_name) << "." << std::endl;
    else {
        data.get_current_task_data().add_state(
                new_state_name,
                data.get_current_task_data().get_state(state_name),
                data.get_current_task_data().get_state_description(state_name));
        data.get_current_task_data().remove_state(state_name);
    }
}

void state::copy(std::ostream &out, plank::cli_data &data, const std::string &state_name,
                 const std::string &new_state_name) {
    if (not cli_utils::check_name(out, state_name, state::get_name()) or
        not cli_utils::check_name(out, new_state_name, state::get_name()) or
        state_name == new_state_name)
        return;

    if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else if (data.get_current_task_data().is_defined_state(new_state_name))
        out << state::get_name() << ": redefinition of state "
            << cli_utils::quote(new_state_name) << "." << std::endl;
    else
        data.get_current_task_data().add_state(
                new_state_name,
                data.get_current_task_data().get_state(state_name),
                "Copy of " + cli_utils::quote(state_name));
}

void state::check(std::ostream &out, cli_data &data, const std::string &state_name,
                  const std::string &formula) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return;
    else if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else {
        const del::state_ptr &s = data.get_current_task_data().get_state(state_name);
        bool holds_formula = false;

        if (data.get_current_task_data().is_defined_formula(formula))
            holds_formula = del::model_checker::satisfies(s, data.get_current_task_data().get_formula(formula));
        else {
            // todo: parse, ground and check formula
        }

        out << std::boolalpha << holds_formula << std::endl;
    }
}

void state::applicable(std::ostream &out, cli_data &data, const std::string &state_name,
                       const string_vector &actions_names, bool ground) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return;
    else if (not data.is_opened_task()) {
        out << state::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    cli_task_data &current_task_data = data.get_current_task_data();

    if (ground or not current_task_data.is_set_task())
        commands::ground::run_cmd(data, false)(out, {});

    del::action_deque actions = state::check_state_actions(out, data, state_name, actions_names);

    if (actions.empty())
        return;

    const del::state_ptr &s = data.get_current_task_data().get_state(state_name);
    auto [index, result] = del::updater::product_update(s, actions);

    if (index < actions.size()) {
        std::string where = state_name;

        if (index > 0)
            for (size_t i = 0; i < index - 1; ++i)
                where += " * " + actions[i]->get_name();

        out << "false (" << actions[index]->get_name()
            << " is not applicable in " << where << ")" << std::endl;
    } else
        out << "true" << std::endl;
}

void state::update(std::ostream &out, cli_data &data, const std::string &state_name,
                   const string_vector &actions_names, const std::string &new_state_name,
                   bool contract, bool ground, const std::string &dir_path) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return;
    else if (not data.is_opened_task()) {
        out << state::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    cli_task_data &current_task_data = data.get_current_task_data();

    if (ground or not current_task_data.is_set_task())
        commands::ground::run_cmd(data, false)(out, {});

    del::action_deque actions = state::check_state_actions(out, data, state_name, actions_names);

    if (actions.empty())
        return;

    if (data.get_current_task_data().is_defined_state(new_state_name)) {
        out << state::get_name() << ": redefinition of state "
            << cli_utils::quote(new_state_name) << "." << std::endl;
        return;
    }

    fs::path pdf_path = (data.get_current_working_dir() / dir_path).lexically_normal();

    if (not dir_path.empty() and
        not cli_utils::check_directory_path(out, data.get_current_working_dir(), dir_path, state::get_name()))
        return;

    const del::state_ptr &s = data.get_current_task_data().get_state(state_name);
    auto [index, result] = del::updater::product_update(s, actions, contract);

    if (index < actions.size()) {
        out << state::get_name() << ": action " << actions[index]->get_name() << " is not applicable." << std::endl;
        return;
    }

    data.get_current_task_data().add_state(
            new_state_name, result,
            state::to_string_product(state_name, actions_names, contract));

    if (not dir_path.empty())
        printer::graphviz::print_state(result, pdf_path, new_state_name);
}

void state::contract(std::ostream &out, cli_data &data, const std::string &state_name,
                     const std::string &new_state_name, const std::string &dir_path) {
    if (not cli_utils::check_name(out, state_name, state::get_name()) or
        not cli_utils::check_name(out, new_state_name, state::get_name()))
        return;
    else if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else if (data.get_current_task_data().is_defined_state(new_state_name))
        out << state::get_name() << ": redefinition of state "
            << cli_utils::quote(new_state_name) << "." << std::endl;
    else {
        fs::path pdf_path = (data.get_current_working_dir() / dir_path).lexically_normal();

        if (not dir_path.empty() and
            not cli_utils::check_directory_path(out, data.get_current_working_dir(), dir_path, state::get_name()))
            return;

        const del::state_ptr &s = data.get_current_task_data().get_state(state_name);
        del::state_ptr contr = del::bisimulator::contract(s);

        data.get_current_task_data().add_state(
                new_state_name, contr,
                "Bisimulation contraction of " + cli_utils::quote(state_name));

        if (not dir_path.empty())
            printer::graphviz::print_state(contr, pdf_path, new_state_name);
    }
}

del::action_deque state::check_state_actions(std::ostream &out, plank::cli_data &data, const std::string &state_name,
                                             const plank::string_vector &actions_names) {
    del::action_deque actions;

    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return {};

    for (const std::string &action_name : actions_names)
        if (not cli_utils::check_name(out, action_name, state::get_name()))
            return {};

    if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else {
        const auto &[s0, actions_map, goal] =
                data.get_current_task_data().get_task();

        for (const std::string &action_name: actions_names)
            if (auto it = actions_map.find(action_name); it == actions_map.end()) {
                out << state::get_name() << ": undefined action "
                    << cli_utils::quote(action_name) << "." << std::endl;
                return del::action_deque{};
            } else
                actions.emplace_back(it->second);
    }

    return actions;
}

std::string state::to_string_product(const std::string &state_name, const string_vector &actions_names,
                                     bool contract) {
    std::string prefix = contract ? "Bisimulation contraction of " : "";
    std::string desc = state_name;

    for (const auto &action_name : actions_names)
        desc += " * " + action_name;

    return prefix + (contract ? cli_utils::quote(desc) : desc);
}
