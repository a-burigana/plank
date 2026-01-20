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

#include "../../../../../include/frontend/plank/cli/commands/version.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"

using namespace plank;
using namespace plank::commands;

void version::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(version::get_name());

    menu->Insert(
        commands::version::get_name(),
        commands::version::run_cmd(exit_code),
        commands::version::get_help(),
        {commands::version::get_cmd_syntax()}
    );
}

std::string version::get_name() {
    return PLANK_CMD_VERSION;
}

std::string version::get_help() {
    return "Print plank version";
}

std::string version::get_cmd_syntax() {
    std::string desc = clipp::usage_lines(version::get_cli()).str();

    return "  " + cli_utils::ltrim(desc);
}

clipp::group version::get_cli() {
    return clipp::group{};
}

cmd_function<string_vector> version::run_cmd(plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        auto cli = version::get_cli();

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, version::get_name());
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        out << PLANK_NAME << " - version " << PLANK_VERSION << std::endl;
        exit_code = plank::exit_code::all_good;
    };
}
