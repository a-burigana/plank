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

#include "../../../../../include/frontend/plank/cli/commands/parse.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"

using namespace plank;
using namespace plank::commands;

void parse::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(parse::get_name());

    menu->Insert(
        commands::parse::get_name(),
        commands::parse::run_cmd(data, exit_code),
        commands::parse::get_description(),
        {commands::parse::get_man_page()}
    );
}

std::string parse::get_name() {
    return PLANK_CMD_PARSE;
}

std::string parse::get_description() {
    return "    Parse and type-check the current EPDDL specification. No options are required.";
}

std::string parse::get_man_page() {
    auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
    std::stringstream buffer;

    buffer << make_man_page(parse::get_cli(), parse::get_name(), fmt)
            .prepend_section("DESCRIPTION",
                             cli_utils::get_formatted_man_description(parse::get_description()));

    return buffer.str();
}

clipp::group parse::get_cli() {
    return clipp::group{};
}

cmd_function<string_vector> parse::run_cmd(cli_data &data, plank::exit_code &exit_code, bool check_syntax) {
    return [&](std::ostream &out, const string_vector &input_args) {
        if (check_syntax) {
            auto cli = parse::get_cli();

            // Parsing arguments
            if (not clipp::parse(input_args, cli)) {
                auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
                std::cout << make_man_page(cli, parse::get_name(), fmt);
                exit_code = plank::exit_code::cli_cmd_error;
                return;
            }
        }

        if (not data.is_opened_task()) {
            out << parse::get_name() << ": no task is currently opened." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        if (not data.get_current_task_data().is_loaded_domain()) {
            out << parse::get_name() << ": no domain was loaded." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        } else if (not data.get_current_task_data().is_loaded_problem()) {
            out << parse::get_name() << ": no problem was loaded." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        exit_code = data.get_current_task_data().parse(out, parse::get_name());
    };
}
