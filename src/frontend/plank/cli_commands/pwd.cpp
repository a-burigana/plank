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

#include "../../../../include/frontend/plank/cli_commands/pwd.h"
#include "../../../../include/frontend/plank/cli_names.h"

using namespace plank;
using namespace plank::commands;


void pwd::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(pwd::get_name());

    menu->Insert(
        commands::pwd::get_name(),
        commands::pwd::run_cmd(data, exit_code),
        commands::pwd::get_help(),
        {commands::pwd::get_cmd_syntax()}
    );
}

std::string pwd::get_name() {
    return PLANK_CMD_PWD;
}

std::string pwd::get_help() {
    return "Print working directory";
}

std::string pwd::get_cmd_syntax() {
    std::string desc = clipp::usage_lines(pwd::get_cli()).str();

    return "  " + cli_utils::ltrim(desc);
}

clipp::group pwd::get_cli() {
    return clipp::group{};
}

cmd_function<string_vector> pwd::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        auto cli = pwd::get_cli();

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, pwd::get_name());
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        out << data.get_current_working_dir().string() << std::endl;
        exit_code = plank::exit_code::all_good;
    };
}
