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

#include "../../../../../include/frontend/plank/cli/commands/ground.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"

using namespace plank;
using namespace plank::commands;

void ground::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(ground::get_name());

    menu->Insert(
        commands::ground::get_name(),
        commands::ground::run_cmd(data, exit_code),
        commands::ground::get_description(),
        {commands::ground::get_man_page()}
    );
}

std::string ground::get_name() {
    return PLANK_CMD_GROUND;
}

std::string ground::get_description() {
    return "    Compute a ground epistemic planning task from the current EPDDL specification. Parsing and "
           "type-checking are automatically performed prior to grounding. No options are required.\n\n"
           "    This command will trigger the grounding of the logical language, i.e., the computation "
           "of the set of agents and the set of ground predicates of the task. If a mismatch "
           "is found in such sets (e.g., some new agents have been added, or some predicates have been removed "
           "in the specification), then all existing states and formulas would no longer be compatible with the "
           "new logical language, as they are based on a different language. Should this happen, a message is "
           "prompted to the user asking to choose between two options:\n"
           " 1. Accept the new logical language and delete all existing states and formulas in the current task.\n"
           " 2. Discard the new language and maintain all data.\n"
           "If the second option is chosen, then all modifications of the specification are not imported, "
           "and the EPDDL files are not modified.";
}

std::string ground::get_man_page() {
    auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
    std::stringstream buffer;

    buffer << make_man_page(ground::get_cli(), ground::get_name(), fmt)
            .prepend_section("DESCRIPTION",
                             cli_utils::get_formatted_man_description(ground::get_description()));

    return buffer.str();
}

clipp::group ground::get_cli() {
    return clipp::group{};
}

cmd_function<string_vector> ground::run_cmd(cli_data &data, plank::exit_code &exit_code, bool check_syntax) {
    return [&](std::ostream &out, const string_vector &input_args) {
        if (check_syntax) {
            auto cli = ground::get_cli();

            // Parsing arguments
            if (not clipp::parse(input_args, cli)) {
                auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
                std::cout << make_man_page(cli, ground::get_name(), fmt);
                exit_code = plank::exit_code::cli_cmd_error;
                return;
            }
        }

        if (not data.is_opened_task()) {
            out << ground::get_name() << ": no task is currently opened." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
        } else
            exit_code = data.get_current_task_data().ground(out, ground::get_name());
    };
}
