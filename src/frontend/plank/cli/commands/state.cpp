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

#include "../../../../../include/frontend/plank/cli/commands/state.h"
#include "../../../../../include/frontend/plank/cli/commands/formula.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"
#include "../../../../../include/frontend/plank/printer/formula_printer.h"
#include "../../../../../include/frontend/plank/printer/graphviz_printer.h"
#include "../../../../../include/lib/epddl/parser/common/formulas_parser.h"
#include "../../../../../include/lib/epddl/type-checker/common/formulas_and_lists_type_checker.h"
#include "../../../../../include/lib/epddl/grounder/formulas/formulas_and_lists_grounder.h"
#include "../../../../../include/lib/epddl/grounder/initial_state/initial_state_grounder.h"
#include "../../../../../include/lib/del/semantics/model_checker.h"
#include "../../../../../include/lib/del/semantics/update/updater.h"
#include "../../../../../include/lib/del/semantics/states/bisimulations/bisimulator.h"
#include <algorithm>
#include <filesystem>
#include <fstream>

using namespace plank;
using namespace plank::commands;

using namespace epddl;
using namespace epddl::parser;

void state::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(state::get_name());

    menu->Insert(
        commands::state::get_name(),
        commands::state::run_cmd(data, exit_code),
        commands::state::get_description(),
        {commands::state::get_man_page()}
    );
}

std::string state::get_name() {
    return PLANK_CMD_STATE;
}

std::string state::get_description() {
    return "    Create and manipulate epistemic states. There are different ways to create "
           "a new epistemic state:\n"
           " - Import the initial state of the current task.\n"
           " - Update an existing state.\n"
           " - Compute the bisimulation contraction of an existing state.\n\n"
           "    States can be updated with one or more epistemic actions. The user can "
           "choose to export the state resulting from the last update, or all updates, to a graphviz "
           "(https://graphviz.org/) image file. Graphic representation of epistemic states contain:\n"
           " - A graph with circled nodes representing possible worlds (labelled with their name), doubly "
           "circled nodes representing designated worlds, and labelled edges representing agents' "
           "accessibility relations.\n\n"
           "    One can also check whether one or more epistemic actions are applicable in a state, or "
           "if an EPDDL formula holds in a state.\n\n"
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

std::string state::get_man_page() {
    auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
    std::stringstream buffer;

    std::string str1, str2, str3, str4, str5, str6;
    string_vector vec1;
    bool b1, b2, b3;

    std::string desc = clipp::usage_lines(state::get_cli(
            str1, str2, str3, str4, str5, str6, vec1, b1, b2, b3)).str();

    buffer << make_man_page(state::get_cli(str1, str2, str3, str4, str5, str6, vec1, b1, b2, b3),
                            state::get_name(), fmt)
            .prepend_section("DESCRIPTION",
                             cli_utils::get_formatted_man_description(state::get_description()));

    return buffer.str();
}

clipp::group
state::get_cli(std::string &operation, std::string &state_name, std::string &path, std::string &new_state_name,
               std::string &formula, std::string &export_file_ext, string_vector &actions_names,
               bool &contract, bool &ground, bool &export_all) {
    return clipp::group(
        clipp::one_of(
            clipp::command(PLANK_SUB_CMD_ADD_INIT).set(operation)
                & PLANK_SUB_CMD_ADD_INIT % clipp::group(
                    clipp::value("state name", state_name).doc("name of initial state to add"),
                    clipp::option("-g", "--ground").set(ground).doc("force initial state grounding before adding state")
                ),
            clipp::command(PLANK_SUB_CMD_REMOVE).set(operation)
                & PLANK_SUB_CMD_REMOVE % clipp::group(
                    clipp::value("state name", state_name).doc("name of state to remove")
                ),
            clipp::command(PLANK_SUB_CMD_RENAME).set(operation)
                & PLANK_SUB_CMD_RENAME % clipp::group(
                    clipp::value("state name", state_name).doc("name of state to rename")
                    & clipp::value("new state name", new_state_name).doc("new name of name")
                ),
            clipp::command(PLANK_SUB_CMD_COPY).set(operation)
                & PLANK_SUB_CMD_COPY % clipp::group(
                    clipp::value("state name", state_name).doc("name of state to copy")
                    & clipp::value("new state name", new_state_name).doc("name of new name")
                ),
            clipp::command(PLANK_SUB_CMD_CHECK).set(operation)
                & PLANK_SUB_CMD_CHECK % clipp::group(
                    clipp::value("state name", state_name).doc("name of state to check formula on")
                    & clipp::value("formula (name)", formula).doc("EPDDL formula or name of existing formula")
                ),
            clipp::command(PLANK_SUB_CMD_APPLICABLE).set(operation)
                & PLANK_SUB_CMD_APPLICABLE % clipp::group(
                    clipp::group(
                        clipp::value("state name", state_name).doc("name of state to check formula on")
                            & clipp::values("action(s) name(s)", actions_names).doc("action sequence to check")
                        ),
                    clipp::option("-g", "--ground").set(ground).doc("force grounding before applicability check")
                ),
            clipp::command(PLANK_SUB_CMD_UPDATE).set(operation)
                & PLANK_SUB_CMD_UPDATE % clipp::group(
                    clipp::group(
                        clipp::value("state name", state_name).doc("name of state to update")
                            & clipp::values("action(s) name(s)", actions_names).doc("action sequence to apply")
                        ),
                    clipp::group(
                        clipp::option("-a", "--add").doc("add new state from last update")
                            & clipp::value("new state name", new_state_name).doc("name of new state")
                        ),
                    clipp::option("-c", "--contract").set(contract).doc("apply bisimulation contraction after each update"),
                    clipp::option("-g", "--ground").set(ground).doc("force grounding before update"),
                    clipp::group(
                        clipp::option("--all").set(export_all).doc("export all states"),
                        clipp::group(
                            clipp::option("-e", "--export").doc("export computed state(s)")
                            & clipp::group(
                                clipp::value("path to directory", path).doc("target directory for exportation"),
                                clipp::one_of(
                                    clipp::option(PLANK_CMD_FLAG_PDF).set(export_file_ext).doc("export state(s) to .pdf"),
                                    clipp::option(PLANK_CMD_FLAG_PNG).set(export_file_ext).doc("export state(s) to .png"),
                                    clipp::option(PLANK_CMD_FLAG_JPG).set(export_file_ext).doc("export state(s) to .jpg"),
                                    clipp::option(PLANK_CMD_FLAG_SVG).set(export_file_ext).doc("export state(s) to .svg"),
                                    clipp::option(PLANK_CMD_FLAG_EPS).set(export_file_ext).doc("export state(s) to .eps"),
                                    clipp::option(PLANK_CMD_FLAG_PS) .set(export_file_ext).doc("export state(s) to .ps")
                                )
                            )
                        )
                    )
                ),
            clipp::command(PLANK_SUB_CMD_CONTRACT).set(operation)
                & PLANK_SUB_CMD_CONTRACT % clipp::group(
                    clipp::value("state name", state_name).doc("name of state to contract"),
                    clipp::group(
                        clipp::option("-a", "--add").doc("add new state from contraction")
                            & clipp::value("new state name", new_state_name).doc("name of new state")
                        ),
                    clipp::group(
                        clipp::option("-e", "--export").doc("export computed state")
                        & clipp::group(
                            clipp::value("path to directory", path).doc("target directory for exportation"),
                            clipp::one_of(
                                clipp::option(PLANK_CMD_FLAG_PDF).set(export_file_ext).doc("export state to .pdf"),
                                clipp::option(PLANK_CMD_FLAG_PNG).set(export_file_ext).doc("export state to .png"),
                                clipp::option(PLANK_CMD_FLAG_JPG).set(export_file_ext).doc("export state to .jpg"),
                                clipp::option(PLANK_CMD_FLAG_SVG).set(export_file_ext).doc("export state to .svg"),
                                clipp::option(PLANK_CMD_FLAG_EPS).set(export_file_ext).doc("export state to .eps"),
                                clipp::option(PLANK_CMD_FLAG_PS) .set(export_file_ext).doc("export state to .ps")
                            )
                        )
                    )
                )
        )
    );
}

cmd_function<string_vector> state::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation, state_name, path, new_state_name, formula, export_file_ext = PLANK_CMD_FLAG_PDF;
        string_vector actions_names;
        bool contract, ground, export_all;

        auto cli = state::get_cli(
                operation, state_name, path, new_state_name,
                formula, export_file_ext, actions_names, contract, ground, export_all);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            std::cout << make_man_page(cli, state::get_name(), fmt);
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        fs::path file_path = cli_utils::get_absolute_path(data.get_current_working_dir(), path);
        std::ifstream file(file_path);

        if (operation == PLANK_SUB_CMD_ADD_INIT)
            exit_code = state::add_init(out, data, state_name, ground);
        else if (operation == PLANK_SUB_CMD_REMOVE)
            exit_code = state::remove(out, data, state_name);
        else if (operation == PLANK_SUB_CMD_RENAME)
            exit_code = state::rename(out, data, state_name, new_state_name);
        else if (operation == PLANK_SUB_CMD_COPY)
            exit_code = state::copy(out, data, state_name, new_state_name);
        else if (operation == PLANK_SUB_CMD_CHECK)
            exit_code = state::check(out, data, state_name, formula);
        else if (operation == PLANK_SUB_CMD_APPLICABLE)
            exit_code = state::applicable(out, data, state_name, actions_names, ground);
        else if (operation == PLANK_SUB_CMD_UPDATE)
            exit_code = state::update(out, data, state_name, actions_names, new_state_name,
                          contract, ground, export_all, path, export_file_ext);
        else if (operation == PLANK_SUB_CMD_CONTRACT)
            exit_code = state::contract(out, data, state_name, new_state_name, path, export_file_ext);
    };
}

plank::exit_code state::add_init(std::ostream &out, cli_data &data, const std::string &state_name, bool ground) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return plank::exit_code::cli_cmd_error;
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

        if ((ground or not current_task_data.is_set_info()) and
            current_task_data.build_info(out, state::get_name()) != plank::exit_code::all_good)
            return plank::exit_code::cli_cmd_error;

        out << "Grounding initial state..." << std::flush;

        del::state_ptr s0 = epddl::grounder::initial_state_grounder::build_initial_state(
                current_task_data.get_specification(),
                current_task_data.get_info());

        current_task_data.add_state(
                state_name, s0,
                "Initial state of problem " +
                cli_utils::quote(current_task_data.get_info().context.components_names.get_problem_name()));

        out << "done." << std::endl;
        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code state::remove(std::ostream &out, cli_data &data, const std::string &state_name) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else {
        data.get_current_task_data().remove_state(state_name);
        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code state::rename(std::ostream &out, cli_data &data, const std::string &state_name,
                               const std::string &new_state_name) {
    if (not cli_utils::check_name(out, state_name, state::get_name()) or
        not cli_utils::check_name(out, new_state_name, state::get_name()))
        return plank::exit_code::cli_cmd_error;

    if (state_name == new_state_name)
        return plank::exit_code::all_good;

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

        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code state::copy(std::ostream &out, plank::cli_data &data, const std::string &state_name,
                             const std::string &new_state_name) {
    if (not cli_utils::check_name(out, state_name, state::get_name()) or
        not cli_utils::check_name(out, new_state_name, state::get_name()))
        return plank::exit_code::cli_cmd_error;

    if (state_name == new_state_name)
        return plank::exit_code::all_good;

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
                "Copy of " + cli_utils::quote(state_name));

        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code state::check(std::ostream &out, cli_data &data, const std::string &state_name,
                              const std::string &formula) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else {
        cli_task_data &current_task_data = data.get_current_task_data();
        const del::state_ptr &s = data.get_current_task_data().get_state(state_name);
        bool holds_formula;

        if (cli_utils::check_name(out, formula, state::get_name(), true)) {
            if (data.get_current_task_data().is_defined_formula(formula))
                holds_formula = del::model_checker::satisfies(s, data.get_current_task_data().get_formula(formula));
            else {
                out << state::get_name() << ": undefined formula "
                    << cli_utils::quote(formula) << "." << std::endl;
                return plank::exit_code::cli_cmd_error;
            }
        } else {
            try {
                out << "Grounding formula..." << std::flush;

                std::string expanded_formula = formula::expand_cli_variables(out, data, formula);

                if (expanded_formula.empty())
                    return plank::exit_code::cli_cmd_error;

                error_manager_ptr err_manager = std::make_shared<epddl::error_manager>(true);

                parser_helper helper{expanded_formula, err_manager, false};
                ast::formula_ptr f = formulas_parser::parse_formula(helper, formula_type::cli_user_formula);

                type_checker::formulas_and_lists_type_checker::check_formula(
                        f, current_task_data.get_info().context, err_manager);
                del::formula_ptr f_ground = grounder::formulas_and_lists_grounder::build_formula(
                        f, current_task_data.get_info());

                out << "done." << std::endl;

                holds_formula = del::model_checker::satisfies(s, f_ground);
            } catch (EPDDLException &e) {
                out << std::endl << e.what();
                return plank::exit_code::cli_cmd_error;
            }
        }

        out << std::boolalpha << holds_formula << std::endl;
        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code state::applicable(std::ostream &out, cli_data &data, const std::string &state_name,
                                   const string_vector &actions_names, bool ground) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_opened_task()) {
        out << state::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    cli_task_data &current_task_data = data.get_current_task_data();

    if ((ground or not current_task_data.is_set_task()) and
        current_task_data.ground(out, state::get_name()) != plank::exit_code::all_good)
            return plank::exit_code::cli_cmd_error;

    del::action_deque actions = state::check_state_actions(out, data, state_name, actions_names);

    if (actions.empty())
        return plank::exit_code::cli_cmd_error;

    const del::state_ptr &s = data.get_current_task_data().get_state(state_name);
    const del::state_deque results = del::updater::product_update(s, actions);
    const size_t applied_actions = results.size() - 1;

    if (applied_actions < actions.size()) {
        std::string where = state_name;

        for (size_t i = 0; i < applied_actions; ++i)
            where.append(" (X) ").append(actions[i]->get_name());

        out << "false (" << actions[applied_actions]->get_name()
            << " is not applicable in " << where << ")" << std::endl;
    } else
        out << "true" << std::endl;

    return plank::exit_code::all_good;
}

plank::exit_code state::update(std::ostream &out, cli_data &data, const std::string &state_name,
                               const string_vector &actions_names, const std::string &new_state_name,
                               bool contract, bool ground, bool export_all, const std::string &dir_path,
                               const std::string &export_file_ext) {
    if (not cli_utils::check_name(out, state_name, state::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_opened_task()) {
        out << state::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    cli_task_data &current_task_data = data.get_current_task_data();

    if ((ground or not current_task_data.is_set_task()) and
        current_task_data.ground(out, state::get_name()) != plank::exit_code::all_good)
            return plank::exit_code::cli_cmd_error;

    del::action_deque actions = state::check_state_actions(out, data, state_name, actions_names);

    if (actions.empty())
        return plank::exit_code::cli_cmd_error;

    if (data.get_current_task_data().is_defined_state(new_state_name)) {
        out << state::get_name() << ": redefinition of state "
            << cli_utils::quote(new_state_name) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    fs::path pdf_path = cli_utils::get_absolute_path(data.get_current_working_dir(), dir_path);

    const del::state_ptr &s = data.get_current_task_data().get_state(state_name);
    const del::state_deque results = del::updater::product_update(s, actions, contract);
    const size_t applied_actions = results.size() - 1;

    if (not dir_path.empty() and export_all) {
        printer::graphviz::print_state(results.front(), pdf_path, state_name, export_file_ext);
        std::string result_name = state_name;

        for (size_t i = 1; i <= applied_actions; ++i) {
            result_name.append("(X)").append(actions[i-1]->get_name());
            printer::graphviz::print_state(results[i], pdf_path, result_name, export_file_ext);
        }
    }

    if (applied_actions < actions.size()) {
        std::string where = state_name;

        for (size_t i = 0; i < applied_actions; ++i)
            where.append(" (X) ").append(actions[i]->get_name());

        out << state::get_name() << ": "
            << cli_utils::quote(actions[applied_actions]->get_name())
            << " is not applicable in " << cli_utils::quote(where) << "." << std::endl;
        return plank::exit_code::all_good;
    }

    data.get_current_task_data().add_state(
            new_state_name, results.back(),
            state::to_string_product(state_name, actions_names, contract));

    if (not dir_path.empty() and not export_all) {
        std::string result_name = state_name;

        for (size_t i = 0; i < applied_actions; ++i)
            result_name.append("(X)").append(actions[i]->get_name());

        printer::graphviz::print_state(results.back(), pdf_path, result_name, export_file_ext);
    }

    return plank::exit_code::all_good;
}

plank::exit_code state::contract(std::ostream &out, cli_data &data, const std::string &state_name,
                                 const std::string &new_state_name, const std::string &dir_path,
                                 const std::string &export_file_ext) {
    if (not cli_utils::check_name(out, state_name, state::get_name()) or
        not cli_utils::check_name(out, new_state_name, state::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_opened_task())
        out << state::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_state(state_name))
        out << state::get_name() << ": undefined state "
            << cli_utils::quote(state_name) << "." << std::endl;
    else if (data.get_current_task_data().is_defined_state(new_state_name))
        out << state::get_name() << ": redefinition of state "
            << cli_utils::quote(new_state_name) << "." << std::endl;
    else {
        fs::path pdf_path = cli_utils::get_absolute_path(data.get_current_working_dir(), dir_path);

        const del::state_ptr &s = data.get_current_task_data().get_state(state_name);
        del::state_ptr contr = del::bisimulator::contract(s);

        data.get_current_task_data().add_state(
                new_state_name, contr,
                "Bisimulation contraction of " + cli_utils::quote(state_name));

        if (not dir_path.empty())
            printer::graphviz::print_state(contr, pdf_path, new_state_name, export_file_ext);

        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
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
        const auto &[s0, _, actions_map, goal] =
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
        desc += " (X) " + action_name;

    return prefix + (contract ? cli_utils::quote(desc) : desc);
}
