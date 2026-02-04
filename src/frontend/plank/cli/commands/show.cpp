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

#include "../../../../../include/frontend/plank/cli/commands/show.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"
#include "../../../../../include/frontend/plank/printer/formula_printer.h"

using namespace plank;
using namespace plank::commands;

void show::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(show::get_name());

    menu->Insert(
        commands::show::get_name(),
        commands::show::run_cmd(data, exit_code),
        commands::show::get_description(),
        {commands::show::get_man_page()}
    );
}

std::string show::get_name() {
    return PLANK_CMD_SHOW;
}

std::string show::get_description() {
    return "    Show required session data.\n\n"
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

std::string show::get_man_page() {
    auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
    std::stringstream buffer;

    std::string str;
    bool b1, b2;

    buffer << make_man_page(show::get_cli(str, b1, b2), show::get_name(), fmt)
            .prepend_section("DESCRIPTION",
                             cli_utils::get_formatted_man_description(show::get_description()));

    return buffer.str();
}

clipp::group show::get_cli(std::string &operation, bool &ground, bool &show_types) {
    return clipp::group(
        clipp::one_of(
            clipp::command(PLANK_SUB_CMD_TASKS).set(operation),
            clipp::command(PLANK_SUB_CMD_STATES).set(operation),
            clipp::command(PLANK_SUB_CMD_ACTIONS).set(operation)
                & clipp::option("-g", "--ground").set(ground),
            clipp::command(PLANK_SUB_CMD_FORMULAS).set(operation)
                & clipp::option("-g", "--ground").set(ground),
            clipp::command(PLANK_SUB_CMD_TYPES).set(operation)
                & clipp::option("-t", "--types").set(show_types).doc("show super-types or entity types")
                & clipp::option("-g", "--ground").set(ground).doc("force grounding before showing data"),
            clipp::command(PLANK_SUB_CMD_PREDICATES).set(operation)
                & clipp::option("-g", "--ground").set(ground),
            clipp::command(PLANK_SUB_CMD_ENTITIES).set(operation)
                & clipp::option("-t", "--types").set(show_types)
                & clipp::option("-g", "--ground").set(ground),
            clipp::command(PLANK_SUB_CMD_OBJECTS).set(operation)
                & clipp::option("-t", "--types").set(show_types)
                & clipp::option("-g", "--ground").set(ground),
            clipp::command(PLANK_SUB_CMD_AGENTS).set(operation)
                & clipp::option("-t", "--types").set(show_types)
                & clipp::option("-g", "--ground").set(ground),
            clipp::command(PLANK_SUB_CMD_AGENT_GROUPS).set(operation)
                & clipp::option("-t", "--types").set(show_types)
                & clipp::option("-g", "--ground").set(ground),
            clipp::command(PLANK_SUB_CMD_SCRIPTS).set(operation)
        )
    );
}

cmd_function<string_vector> show::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation;
        bool ground = false, show_types = false;

        auto cli = show::get_cli(operation, ground, show_types);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            std::cout << make_man_page(cli, show::get_name(), fmt);
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        if (operation == PLANK_SUB_CMD_TASKS)
            exit_code = show::show_tasks(out, data);
        else if (operation == PLANK_SUB_CMD_STATES)
            exit_code = show::show_states(out, data);
        else if (operation == PLANK_SUB_CMD_ACTIONS)
            exit_code = show::show_actions(out, data, ground);
        else if (operation == PLANK_SUB_CMD_FORMULAS)
            exit_code = show::show_formulas(out, data, ground);
        else if (operation == PLANK_SUB_CMD_TYPES)
            exit_code = show::show_types(out, data, ground, show_types);
        else if (operation == PLANK_SUB_CMD_PREDICATES)
            exit_code = show::show_predicates(out, data, ground);
        else if (operation == PLANK_SUB_CMD_ENTITIES)
            exit_code = show::show_entities(out, data, ground, show_types);
        else if (operation == PLANK_SUB_CMD_OBJECTS)
            exit_code = show::show_objects(out, data, ground, show_types);
        else if (operation == PLANK_SUB_CMD_AGENTS)
            exit_code = show::show_agents(out, data, ground, show_types);
        else if (operation == PLANK_SUB_CMD_AGENT_GROUPS)
            exit_code = show::show_agent_groups(out, data, ground, show_types);
        else if (operation == PLANK_SUB_CMD_SCRIPTS)
            exit_code = show::show_scripts(out, data);
    };
}

plank::exit_code show::show_tasks(std::ostream &out, cli_data &data) {
    cli_utils::print_table(out, data.get_tasks_names());
    return plank::exit_code::all_good;
}

plank::exit_code show::show_states(std::ostream &out, cli_data &data) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    cli_task_data &current_task_data = data.get_current_task_data();
    size_t column_width = 0;

    for (const std::string &state_name : current_task_data.get_states_names())
        if (state_name.size() > column_width)
            column_width = state_name.size();

    for (const std::string &state_name : current_task_data.get_states_names())
        out << std::left
            << std::setw(static_cast<int>(column_width + 4))
            << state_name
            << ": " << current_task_data.get_state_description(state_name) << std::endl;

    return plank::exit_code::all_good;
}

plank::exit_code show::show_actions(std::ostream &out, cli_data &data, bool ground) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    if ((ground or not data.get_current_task_data().is_set_task()) and
        data.get_current_task_data().ground(out, show::get_name()) != plank::exit_code::all_good)
            return plank::exit_code::cli_cmd_error;

    cli_utils::print_table(out, data.get_current_task_data().get_task().actions_names);
    return plank::exit_code::all_good;
}

plank::exit_code show::show_formulas(std::ostream &out, cli_data &data, bool ground) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    cli_task_data &current_task_data = data.get_current_task_data();

    if ((ground or not current_task_data.is_set_info()) and
        current_task_data.build_info(out, show::get_name()) != plank::exit_code::all_good)
        return plank::exit_code::cli_cmd_error;

    string_vector formulas_names;
    size_t max_length = 0;

    for (const std::string &formula_name : current_task_data.get_formulas_names()) {
        formulas_names.emplace_back(formula_name);

        if (cli_utils::get_column_width(formula_name) > max_length)
            max_length = cli_utils::get_column_width(formula_name);
    }

    for (const std::string &formula_name : current_task_data.get_formulas_names()) {
        out << std::left << std::setw(static_cast<int>(max_length)) << formula_name;
        out << "= " << printer::formula_printer::to_string(
                current_task_data.get_formula(formula_name),
                current_task_data.get_info().language) << std::endl;
    }

    return plank::exit_code::all_good;
}

plank::exit_code show::show_types(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    } else if ((ground or not data.get_current_task_data().is_set_info()) and
               data.get_current_task_data().build_info(out, show::get_name()) != plank::exit_code::all_good)
        return plank::exit_code::cli_cmd_error;

    epddl::type_checker::context &context = data.get_current_task_data().get_info().context;

    string_vector types_names;
    size_t max_length = 0;

    for (size_t t = 0; t < context.types.get_types_size(); ++t)
        if (const auto &type_name = context.types.get_type_name(t); type_name != ROOT_TYPE_NAME) {
            types_names.emplace_back(type_name);

            if (cli_utils::get_column_width(types_names.back()) > max_length)
                max_length = cli_utils::get_column_width(types_names.back());
        }

    if (show_types)
        for (std::string &type_name: types_names)
            if (const auto &parent_type_name = context.types.get_parent(type_name)->get_name();
                    parent_type_name != ROOT_TYPE_NAME) {
                out << std::left << std::setw(static_cast<int>(max_length)) << type_name;
                out << "- " << parent_type_name << std::endl;
            } else
                out << type_name << std::endl;
    else
        cli_utils::print_table(out, types_names);

    return plank::exit_code::all_good;
}

plank::exit_code show::show_predicates(std::ostream &out, cli_data &data, bool ground) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    } else if ((ground or not data.get_current_task_data().is_set_info()) and
               data.get_current_task_data().build_info(out, show::get_name()) != plank::exit_code::all_good)
        return plank::exit_code::cli_cmd_error;

    cli_utils::print_table(out, data.get_current_task_data().get_info().language->get_atoms_names());
    return plank::exit_code::all_good;
}

plank::exit_code show::show_entities(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    return show::show_entities_with_type(out, data, "entity", ground, show_types);
}

plank::exit_code show::show_objects(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    return show::show_entities_with_type(out, data, "object", ground, show_types);
}

plank::exit_code show::show_agents(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    return show::show_entities_with_type(out, data, "agent", ground, show_types);
}

plank::exit_code show::show_agent_groups(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    return show::show_entities_with_type(out, data, "agent-group", ground, show_types);
}

plank::exit_code show::show_scripts(std::ostream &out, plank::cli_data &data) {
    size_t column_width = 0;

    for (const std::string &script_name : data.get_scripts_names())
        if (script_name.size() > column_width)
            column_width = script_name.size();

    for (const std::string &script_name : data.get_scripts_names())
        out << std::left
            << std::setw(static_cast<int>(column_width + 4))
            << script_name
            << ": " << data.get_script_path(script_name) << std::endl;

    return plank::exit_code::all_good;
}

plank::exit_code show::show_entities_with_type(std::ostream &out, cli_data &data, const std::string &type,
                                               bool ground, bool show_types) {
    cli_task_data &current_task_data = data.get_current_task_data();

    if ((ground or not current_task_data.is_set_info()) and
        current_task_data.build_info(out, show::get_name()) != plank::exit_code::all_good)
        return plank::exit_code::cli_cmd_error;

    epddl::type_checker::context &context = current_task_data.get_info().context;
    const bit_deque &entities = context.entities.get_entities_with_type(context.types, type);

    string_vector entities_names;
    size_t max_length = 0;

    for (const size_t e : entities) {
        entities_names.emplace_back(context.entities.get_entity_name(e));

        if (cli_utils::get_column_width(entities_names.back()) > max_length)
            max_length = cli_utils::get_column_width(entities_names.back());
    }

    if (show_types)
        for (std::string &entity_name : entities_names) {
            out << std::left << std::setw(static_cast<int>(max_length)) << entity_name;
            out << "- " << context.types.to_string_type(
                    context.entities.get_type(entity_name)) << std::endl;
        }
    else
        cli_utils::print_table(out, entities_names);

    return plank::exit_code::all_good;
}
