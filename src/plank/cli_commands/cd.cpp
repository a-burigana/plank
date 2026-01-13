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

#include "../../../include/plank/cli_commands/cd.h"
#include "../../../include/plank/cli_names.h"
#include "../../../include/plank/cli_utils.h"
#include <filesystem>

using namespace plank;
using namespace plank::commands;

namespace fs = std::filesystem;

void cd::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(cd::get_name());

    menu->Insert(
        commands::cd::get_name(),
        commands::cd::run_cmd(data, exit_code),
        commands::cd::get_help(),
        {commands::cd::get_cmd_syntax()}
    );
}

std::string cd::get_name() {
    return PLANK_CMD_CD;
}

std::string cd::get_help() {
    return "Change directory";
}

std::string cd::get_cmd_syntax() {
    std::string str;
    std::string desc = clipp::usage_lines(cd::get_cli(str)).str();

    return "  " + cli_utils::ltrim(desc);
}

clipp::group cd::get_cli(std::string &dir_path) {
    return clipp::group{
        clipp::opt_value("path to directory", dir_path)
    };
}

cmd_function<string_vector> cd::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string dir_path;
        auto cli = cd::get_cli(dir_path);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, cd::get_name());
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        if (dir_path.empty() or dir_path == ".") {
            exit_code = plank::exit_code::all_good;
            return;
        } else if (dir_path == "..") {
            data.set_current_working_dir(data.get_current_working_dir().parent_path());
            exit_code = plank::exit_code::all_good;
            return;
        } else if (dir_path == "~") {
            data.set_current_working_dir(getenv("HOME"));
            exit_code = plank::exit_code::all_good;
            return;
        }

        fs::path target = cli_utils::get_absolute_path(data.get_current_working_dir(), dir_path);

        if (fs::exists(target) and fs::is_directory(target))
            data.set_current_working_dir(target);
        else {
            std::cout << cd::get_name() << ": no such directory." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
        }

        exit_code = plank::exit_code::all_good;
    };
}
