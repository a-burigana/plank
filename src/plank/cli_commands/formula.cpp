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

#include "../../../include/plank/cli_commands/formula.h"
#include "../../../include/plank/cli_commands/parse.h"
#include "../../../include/plank/cli_names.h"
#include "../../../include/grounder/grounder_helper.h"
#include "../../../include/grounder/formulas/formulas_and_lists_grounder.h"

using namespace plank;
using namespace plank::commands;


void formula::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    menu->Insert(
        commands::formula::get_name(),
        commands::formula::run_cmd(data),
        commands::formula::get_help(),
        {commands::formula::get_cmd_syntax()}
    );
}

std::string formula::get_name() {
    return PLANK_CMD_FORMULA;
}

std::string formula::get_help() {
    return "Print working directory";
}

std::string formula::get_cmd_syntax() {
    std::string str1, str2, str3, str4;
    bool b;
    std::string desc = clipp::usage_lines(formula::get_cli(str1, str2, str3, str4, b)).str();

    return "  " + cli_utils::ltrim(desc);
}

clipp::group formula::get_cli(std::string &operation, std::string &formula, std::string &formula_name,
                              std::string &new_formula_name, bool &ground) {
    return clipp::group(
        clipp::one_of(
            clipp::command(PLANK_SUB_CMD_ADD).set(operation)
                & clipp::group(
                    clipp::group(
                        clipp::value("formula name", formula_name)
                            & clipp::value("formula", formula)
                    ),
                    clipp::option("-g", "--ground").set(ground)
                ),
            clipp::command(PLANK_SUB_CMD_ADD_GOAL).set(operation)
                & clipp::value("formula name", formula_name),
            clipp::command(PLANK_SUB_CMD_REMOVE).set(operation)
                & clipp::value("formula name", formula_name),
            clipp::command(PLANK_SUB_CMD_RENAME).set(operation)
                & clipp::value("formula name", formula_name)
                & clipp::value("new formula name", new_formula_name),
            clipp::command(PLANK_SUB_CMD_COPY).set(operation)
                & clipp::value("formula name", formula_name)
                & clipp::value("new formula name", new_formula_name)
        )
    );
}

cmd_function<string_vector> formula::run_cmd(cli_data &data) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation, formula, formula_name, new_formula_name;
        bool ground;
        auto cli = formula::get_cli(operation, formula, formula_name, new_formula_name, ground);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, formula::get_name());
            return;
        }

        if (operation == PLANK_SUB_CMD_ADD)
            formula::add(out, data, formula_name, formula, ground);
        else if (operation == PLANK_SUB_CMD_ADD_GOAL)
            formula::add_goal(out, data, formula_name);
        else if (operation == PLANK_SUB_CMD_REMOVE)
            formula::remove(out, data, formula_name);
        else if (operation == PLANK_SUB_CMD_RENAME)
            formula::rename(out, data, formula_name, new_formula_name);
        else if (operation == PLANK_SUB_CMD_COPY)
            formula::copy(out, data, formula_name, new_formula_name);
    };
}

void formula::add(std::ostream &out, cli_data &data, const std::string &formula_name, const std::string &formula,
                  bool ground) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()))
        return;
    else if (not data.is_opened_task())
        out << formula::get_name() << ": no task is currently opened." << std::endl;
    else if (data.get_current_task_data().is_defined_formula(formula_name))
        out << formula::get_name() << ": redefinition of formula "
            << cli_utils::quote(formula_name) << "." << std::endl;
    else if (not data.get_current_task_data().is_loaded_domain())
        out << formula::get_name() << ": no domain was loaded." << std::endl;
    else if (not data.get_current_task_data().is_loaded_problem())
        out << formula::get_name() << ": no problem was loaded." << std::endl;
    else {
        cli_task_data &current_task_data = data.get_current_task_data();

        if (current_task_data.build_info(out, true) != plank::exit_code::all_good)
            return;

        out << "Grounding formula..." << std::flush;

        del::formula_ptr goal = epddl::grounder::formulas_and_lists_grounder::build_goal(
                data.get_current_task_data().get_specification(),
                current_task_data.get_info());

        current_task_data.add_formula(formula_name, goal);

        out << " done." << std::endl;
    }
}

void formula::add_goal(std::ostream &out, cli_data &data, const std::string &formula_name) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()))
        return;
    else if (not data.is_opened_task())
        out << formula::get_name() << ": no task is currently opened." << std::endl;
    else if (data.get_current_task_data().is_defined_formula(formula_name))
        out << formula::get_name() << ": redefinition of formula "
            << cli_utils::quote(formula_name) << "." << std::endl;
    else if (not data.get_current_task_data().is_loaded_domain())
        out << formula::get_name() << ": no domain was loaded." << std::endl;
    else if (not data.get_current_task_data().is_loaded_problem())
        out << formula::get_name() << ": no problem was loaded." << std::endl;
    else {
        cli_task_data &current_task_data = data.get_current_task_data();

        if (current_task_data.build_info(out, true) != plank::exit_code::all_good)
            return;

        out << "Grounding goal formula..." << std::flush;

        del::formula_ptr goal = epddl::grounder::formulas_and_lists_grounder::build_goal(
                data.get_current_task_data().get_specification(),
                current_task_data.get_info());

        current_task_data.add_formula(formula_name, goal);

        out << " done." << std::endl;
    }
}

void formula::remove(std::ostream &out, cli_data &data, const std::string &formula_name) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()))
        return;
    else if (not data.is_opened_task())
        out << formula::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_formula(formula_name))
        out << formula::get_name() << ": undefined formula "
            << cli_utils::quote(formula_name) << "." << std::endl;
    else
        data.get_current_task_data().remove_formula(formula_name);
}

void formula::rename(std::ostream &out, cli_data &data, const std::string &formula_name,
                   const std::string &new_formula_name) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()) or
        not cli_utils::check_name(out, new_formula_name, formula::get_name()) or
        formula_name == new_formula_name)
        return;

    if (not data.is_opened_task())
        out << formula::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_formula(formula_name))
        out << formula::get_name() << ": undefined formula "
            << cli_utils::quote(formula_name) << "." << std::endl;
    else if (data.get_current_task_data().is_defined_formula(new_formula_name))
        out << formula::get_name() << ": redefinition of formula "
            << cli_utils::quote(new_formula_name) << "." << std::endl;
    else {
        data.get_current_task_data().add_formula(
                new_formula_name,
                data.get_current_task_data().get_formula(formula_name));
        data.get_current_task_data().remove_formula(formula_name);
    }
}

void formula::copy(std::ostream &out, cli_data &data, const std::string &formula_name,
                 const std::string &new_formula_name) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()) or
        not cli_utils::check_name(out, new_formula_name, formula::get_name()) or
        formula_name == new_formula_name)
        return;

    if (not data.is_opened_task())
        out << formula::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_formula(formula_name))
        out << formula::get_name() << ": undefined formula "
            << cli_utils::quote(formula_name) << "." << std::endl;
    else if (data.get_current_task_data().is_defined_formula(new_formula_name))
        out << formula::get_name() << ": redefinition of formula "
            << cli_utils::quote(new_formula_name) << "." << std::endl;
    else
        data.get_current_task_data().add_formula(
                new_formula_name,
                del::formula_ptr{});
}
