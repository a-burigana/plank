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

#include "../../../include/plank/cli_commands/ground.h"
#include "../../../include/plank/cli_names.h"
#include "../../../include/plank/cli_commands/parse.h"
#include "../../../include/grounder/grounder_helper.h"

using namespace plank;
using namespace plank::commands;

void ground::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data) {
    menu->Insert(
        commands::ground::get_name(),
        commands::ground::run_cmd(data),
        commands::ground::get_help(),
        {commands::ground::get_cmd_syntax()}
    );
}

std::string ground::get_name() {
    return PLANK_CMD_GROUND;
}

std::string ground::get_help() {
    return "Ground the current epistemic planning task";
}

std::string ground::get_cmd_syntax() {
    std::string desc = clipp::usage_lines(ground::get_cli()).str();

    return "  " + cli_utils::ltrim(desc);
}

clipp::group ground::get_cli() {
    return clipp::group{};
}

cmd_function<string_vector> ground::run_cmd(cli_data &data, bool check_syntax) {
    return [&](std::ostream &out, const string_vector &input_args) {
        if (check_syntax) {
            auto cli = ground::get_cli();

            // Parsing arguments
            if (not clipp::parse(input_args, cli)) {
                std::cout << make_man_page(cli, ground::get_name());
                return;
            }
        }

        if (not data.is_opened_task()) {
            out << ground::get_name() << ": no epistemic planning task is currently opened." << std::endl;
            return;
        }

        commands::parse::run_cmd(data, false)(out, input_args);
        cli_task_data &task_data = data.get_current_task_data();

        if (task_data.is_set_specification() and task_data.is_set_error_managers() and task_data.is_set_context()) {
            out << "Grounding..." << std::flush;

            try {
                auto [task, info] = epddl::grounder::grounder_helper::ground(
                    task_data.get_specification(),
                    task_data.get_context(),
                    task_data.get_error_managers());

                task_data.set_info(std::move(info));
                task_data.set_task(std::move(task));
            } catch (epddl::EPDDLException &e) {
                out << std::endl << e.what();
                return;
            }

            out << " done." << std::endl;
        }
    };
}
