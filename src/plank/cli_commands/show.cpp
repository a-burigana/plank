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

#include "../../../include/plank/cli_commands/show.h"
#include "../../../include/plank/cli_commands/parse.h"
#include "../../../include/plank/cli_commands/ground.h"
#include "../../../include/plank/cli_names.h"
#include "../../../include/printer/formula_printer.h"
#include "../../../include/grounder/grounder_helper.h"

using namespace plank;
using namespace plank::commands;

void show::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    menu->Insert(
        commands::show::get_name(),
        commands::show::run_cmd(data),
        commands::show::get_help(),
        {commands::show::get_cmd_syntax()}
    );
}

std::string show::get_name() {
    return PLANK_CMD_SHOW;
}

std::string show::get_help() {
    return "Show required session data";
}

std::string show::get_cmd_syntax() {
    std::string str;
    bool b1, b2;
    std::string desc = clipp::usage_lines(show::get_cli(str, b1, b2)).str();

    return "  " + cli_utils::ltrim(desc);
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
                & clipp::option("-t", "--types").set(show_types)
                & clipp::option("-g", "--ground").set(ground),
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
                & clipp::option("-g", "--ground").set(ground)
        )
    );
}

cmd_function<string_vector> show::run_cmd(cli_data &data) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation;
        bool ground = false, show_types = false;

        auto cli = show::get_cli(operation, ground, show_types);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, show::get_name());
            return;
        }

        if (operation == PLANK_SUB_CMD_TASKS)
            show::show_tasks(out, data);
        else if (operation == PLANK_SUB_CMD_STATES)
            show::show_states(out, data);
        else if (operation == PLANK_SUB_CMD_ACTIONS)
            show::show_actions(out, data, ground);
        else if (operation == PLANK_SUB_CMD_FORMULAS)
            show::show_formulas(out, data, ground);
        else if (operation == PLANK_SUB_CMD_TYPES)
            show::show_types(out, data, ground, show_types);
        else if (operation == PLANK_SUB_CMD_PREDICATES)
            show::show_predicates(out, data, ground);
        else if (operation == PLANK_SUB_CMD_ENTITIES)
            show::show_entities(out, data, ground, show_types);
        else if (operation == PLANK_SUB_CMD_OBJECTS)
            show::show_objects(out, data, ground, show_types);
        else if (operation == PLANK_SUB_CMD_AGENTS)
            show::show_agents(out, data, ground, show_types);
        else if (operation == PLANK_SUB_CMD_AGENT_GROUPS)
            show::show_agent_groups(out, data, ground, show_types);
    };
}

void show::show_tasks(std::ostream &out, cli_data &data) {
    cli_utils::print_table(out, data.get_tasks_names());
}

void show::show_states(std::ostream &out, cli_data &data) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return;
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
            << "; " << current_task_data.get_state_description(state_name) << std::endl;
}

void show::show_actions(std::ostream &out, cli_data &data, bool ground) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    if (ground or not data.get_current_task_data().is_set_task())
        commands::ground::run_cmd(data, false)(out, {});

    string_vector actions_names;

    for (const auto &[action_name, _] : data.get_current_task_data().get_task().actions)
        actions_names.emplace_back(action_name);

    cli_utils::print_table(out, actions_names);
}

void show::show_formulas(std::ostream &out, cli_data &data, bool ground) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    show::build_info(out, data, ground);
    cli_task_data &current_task_data = data.get_current_task_data();

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
}

void show::show_types(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    show::build_info(out, data, ground);
    epddl::type_checker::context &context = data.get_current_task_data().get_info().context;

    string_vector types_names;
    size_t max_length = 0;

    for (size_t t = 0; t < context.types.get_types_size(); ++t) {
        types_names.emplace_back(context.types.get_type_name(t));

        if (cli_utils::get_column_width(types_names.back()) > max_length)
            max_length = cli_utils::get_column_width(types_names.back());
    }

    if (show_types)
        for (std::string &type_name : types_names) {
            out << std::left << std::setw(static_cast<int>(max_length)) << type_name;
            out << "- " << context.types.get_parent(type_name)->get_name() << std::endl;
        }
    else
        cli_utils::print_table(out, types_names);
}

void show::show_predicates(std::ostream &out, cli_data &data, bool ground) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    show::build_info(out, data, ground);
    cli_utils::print_table(out, data.get_current_task_data().get_info().language->get_atoms_names());
}

void show::show_entities(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    show::show_entities_with_type(out, data, "entity", ground, show_types);
}

void show::show_objects(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    show::show_entities_with_type(out, data, "object", ground, show_types);
}

void show::show_agents(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    show::show_entities_with_type(out, data, "agent", ground, show_types);
}

void show::show_agent_groups(std::ostream &out, cli_data &data, bool ground, bool show_types) {
    if (not data.is_opened_task()) {
        out << show::get_name() << ": no task is currently opened." << std::endl;
        return;
    }

    show::show_entities_with_type(out, data, "agent-group", ground, show_types);
}

void show::show_entities_with_type(std::ostream &out, cli_data &data, const std::string &type, bool ground,
                                   bool show_types) {
    show::build_info(out, data, ground);
    cli_task_data &current_task_data = data.get_current_task_data();

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
}

void show::build_info(std::ostream &out, cli_data &data, bool ground) {
    cli_task_data &current_task_data = data.get_current_task_data();

    if (ground or
        not current_task_data.is_set_specification() or
        not current_task_data.is_set_error_managers() or
        not current_task_data.is_set_context())
        commands::parse::run_cmd(data, false)(out, {});

    if (ground or not current_task_data.is_set_info()) {
        out << "Grounding task language..." << std::flush;

        epddl::grounder::grounder_info info = epddl::grounder::grounder_helper::build_info(
                current_task_data.get_specification(),
                current_task_data.get_context(),
                current_task_data.get_error_managers());

        out << " done" << std::endl;
        current_task_data.set_info(std::move(info));
    }
}
