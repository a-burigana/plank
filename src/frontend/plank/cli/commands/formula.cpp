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

#include "../../../../../include/frontend/plank/cli/commands/formula.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"
#include "../../../../../include/frontend/plank/printer/formula_printer.h"
#include "../../../../../include/lib/epddl/parser/common/formulas_parser.h"
#include "../../../../../include/lib/epddl/type-checker/common/formulas_and_lists_type_checker.h"
#include "../../../../../include/lib/epddl/grounder/formulas/formulas_and_lists_grounder.h"
#include <memory>
#include <string>

#define CLI_VAR_CHAR '$'

using namespace plank;
using namespace plank::commands;

using namespace epddl;
using namespace epddl::parser;

void formula::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(formula::get_name());

    menu->Insert(
        commands::formula::get_name(),
        commands::formula::run_cmd(data, exit_code),
        commands::formula::get_description(),
        {commands::formula::get_man_page()}
    );
}

std::string formula::get_name() {
    return PLANK_CMD_FORMULA;
}

std::string formula::get_description() {
    return "    Create and store formulas in the current task. Formulas can be created from existing ones by "
           "escaping formulas names with the '$' symbol. For instance, if the formula 'old-formula' was "
           "previously created, the command 'formula add new-formula \"(not $old-formula)\"' will create a "
           "formula called 'new-formula' that is the negation of 'old-formula'. Name escaping is resolved "
           "recursively, so we can e.g. create a third formula by escaping 'new-formula' in its body. Note "
           "that if the body of the EPDDL formula contains some whitespaces, we need to surround it with "
           "single or double quotes.\n\n"
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

std::string formula::get_man_page() {
    auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
    std::stringstream buffer;

    std::string str1, str2, str3, str4;

    buffer << make_man_page(formula::get_cli(str1, str2, str3, str4), formula::get_name(), fmt)
            .prepend_section("DESCRIPTION",
                             cli_utils::get_formatted_man_description(formula::get_description()));

    return buffer.str();
}

clipp::group formula::get_cli(std::string &operation, std::string &formula, std::string &formula_name,
                              std::string &new_formula_name) {
    return clipp::group(
        clipp::one_of(
            clipp::command(PLANK_SUB_CMD_ADD).set(operation)
                & PLANK_SUB_CMD_ADD % clipp::group(
                    clipp::group(
                        clipp::value("formula name", formula_name).doc("name of formula to add")
                        & clipp::value("formula", formula).doc("EPDDL formula")
                    )
                ),
            clipp::command(PLANK_SUB_CMD_ADD_GOAL).set(operation)
                & PLANK_SUB_CMD_ADD_GOAL % clipp::group(
                    clipp::value("formula name", formula_name).doc("name of formula")
                ),
            clipp::command(PLANK_SUB_CMD_REMOVE).set(operation)
                & PLANK_SUB_CMD_REMOVE %
                    clipp::group( clipp::value("formula name", formula_name).doc("name of formula to remove") ),
            clipp::command(PLANK_SUB_CMD_RENAME).set(operation)
                & PLANK_SUB_CMD_RENAME % (
                    clipp::value("formula name", formula_name).doc("name of formula to rename")
                        & clipp::value("new formula name", new_formula_name).doc("new name of formula")
                  ),
            clipp::command(PLANK_SUB_CMD_COPY).set(operation)
                & PLANK_SUB_CMD_COPY % (
                    clipp::value("formula name", formula_name).doc("name of formula to copy")
                        & clipp::value("new formula name", new_formula_name).doc("name of new formula"
                  ))
        )
    );
}

cmd_function<string_vector> formula::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation, formula, formula_name, new_formula_name;
        auto cli = formula::get_cli(operation, formula, formula_name, new_formula_name);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            std::cout << make_man_page(cli, formula::get_name(), fmt);
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        if (operation == PLANK_SUB_CMD_ADD)
            exit_code = formula::add(out, data, formula_name, formula);
        else if (operation == PLANK_SUB_CMD_ADD_GOAL)
            exit_code = formula::add_goal(out, data, formula_name);
        else if (operation == PLANK_SUB_CMD_REMOVE)
            exit_code = formula::remove(out, data, formula_name);
        else if (operation == PLANK_SUB_CMD_RENAME)
            exit_code = formula::rename(out, data, formula_name, new_formula_name);
        else if (operation == PLANK_SUB_CMD_COPY)
            exit_code = formula::copy(out, data, formula_name, new_formula_name);
    };
}

plank::exit_code formula::add(std::ostream &out, cli_data &data, const std::string &formula_name,
                              const std::string &formula) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()))
        return plank::exit_code::cli_cmd_error;
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

        if (not current_task_data.is_set_info() and
            current_task_data.build_info(out, formula::get_name()) != plank::exit_code::all_good)
            return plank::exit_code::cli_cmd_error;

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
            current_task_data.add_formula(formula_name, f_ground);

            return plank::exit_code::all_good;
        } catch (EPDDLException &e) {
            out << std::endl << e.what();
            return plank::exit_code::cli_cmd_error;
        }
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code formula::add_goal(std::ostream &out, cli_data &data, const std::string &formula_name) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()))
        return plank::exit_code::cli_cmd_error;
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

        if (not current_task_data.is_set_info() and
            current_task_data.build_info(out, formula::get_name()) != plank::exit_code::all_good)
            return plank::exit_code::cli_cmd_error;

        out << "Grounding goal formula..." << std::flush;

        del::formula_ptr goal = epddl::grounder::formulas_and_lists_grounder::build_goal(
                data.get_current_task_data().get_specification(),
                current_task_data.get_info());

        out << "done." << std::endl;

        current_task_data.add_formula(formula_name, goal);
        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code formula::remove(std::ostream &out, cli_data &data, const std::string &formula_name) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_opened_task())
        out << formula::get_name() << ": no task is currently opened." << std::endl;
    else if (not data.get_current_task_data().is_defined_formula(formula_name))
        out << formula::get_name() << ": undefined formula "
            << cli_utils::quote(formula_name) << "." << std::endl;
    else {
        data.get_current_task_data().remove_formula(formula_name);
        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code formula::rename(std::ostream &out, cli_data &data, const std::string &formula_name,
                                 const std::string &new_formula_name) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()) or
        not cli_utils::check_name(out, new_formula_name, formula::get_name()))
        return plank::exit_code::cli_cmd_error;

    if (formula_name == new_formula_name)
        return plank::exit_code::all_good;

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

        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code formula::copy(std::ostream &out, cli_data &data, const std::string &formula_name,
                               const std::string &new_formula_name) {
    if (not cli_utils::check_name(out, formula_name, formula::get_name()) or
        not cli_utils::check_name(out, new_formula_name, formula::get_name()))
        return plank::exit_code::cli_cmd_error;

    if (formula_name == new_formula_name)
        return plank::exit_code::all_good;

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
                del::formula_ptr{});

        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

std::string formula::expand_cli_variables(std::ostream &out, cli_data &data, const std::string &formula) {
    std::string expanded_formula = formula, cli_var_name;
    size_t pos = 0, begin_var_name_pos, end_var_name_pos;

    if (formula.find(CLI_VAR_CHAR) == std::string::npos)
        return formula;

    while (pos < expanded_formula.size()) {
        if (expanded_formula[pos++] != CLI_VAR_CHAR)
            continue;

        begin_var_name_pos = pos - 1;

        while (cli_utils::is_name_char(expanded_formula[pos]))
            cli_var_name += std::string{expanded_formula[pos++]};

        end_var_name_pos = pos;

        if (not cli_utils::check_name(out, cli_var_name, formula::get_name()))
            return "";

        if (not data.get_current_task_data().is_defined_formula(cli_var_name)) {
            out << std::endl << formula::get_name() << ": undefined formula "
                << cli_utils::quote(cli_var_name) << "." << std::endl;
            return "";
        }

        std::string var_formula = printer::formula_printer::to_string(
                data.get_current_task_data().get_formula(cli_var_name),
                data.get_current_task_data().get_info().language);

        std::string expanded_var_formula = formula::expand_cli_variables(out, data, var_formula);

        if (expanded_var_formula.empty())
            return "";

        expanded_formula = expanded_formula.substr(0, begin_var_name_pos)
                .append(expanded_var_formula)
                .append(expanded_formula.substr(end_var_name_pos));

        pos = begin_var_name_pos + expanded_var_formula.size();
    }

    return expanded_formula;
}
