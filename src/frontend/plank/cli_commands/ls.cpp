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

#include "../../../../include/frontend/plank/cli_commands/ls.h"
#include "../../../../include/frontend/plank/cli_names.h"
#include "../../../../include/frontend/plank/cli_utils.h"
#include <filesystem>
#include <ostream>
#include <vector>

using namespace plank;
using namespace plank::commands;

namespace fs = std::filesystem;

void ls::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(ls::get_name());

    menu->Insert(
        commands::ls::get_name(),
        commands::ls::run_cmd(data, exit_code),
        commands::ls::get_help(),
        {commands::ls::get_cmd_syntax()}
    );
}

std::string ls::get_name() {
    return PLANK_CMD_LS;
}

std::string ls::get_help() {
    return "List directory contents";
}

std::string ls::get_cmd_syntax() {
    std::string str;
    std::string desc = clipp::usage_lines(ls::get_cli(str)).str();

    return "  " + cli_utils::ltrim(desc);
}

clipp::group ls::get_cli(std::string &path) {
    return clipp::group{
        clipp::option("-a"),
        clipp::opt_value("path to directory", path)
    };
}

cmd_function<string_vector> ls::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string path;
        auto cli = ls::get_cli(path);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, ls::get_name());
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        fs::path dir_path;

        if (path.empty())
            dir_path = data.get_current_working_dir();
        else if (path == "~")
            dir_path = getenv("HOME");
        else
            dir_path = cli_utils::get_absolute_path(data.get_current_working_dir(), path);

        if (not fs::is_directory(dir_path)) {
            out << ls::get_name() << ": no such directory." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        bool show_hidden = false;

        for (const std::string &arg : input_args)
            if (show_hidden = arg == "-a"; show_hidden)
                break;

        string_vector items = ls::get_directory_entries(dir_path, show_hidden);
        cli_utils::print_table(out, items);

        exit_code = plank::exit_code::all_good;
    };
}

std::string ls::format_entry(const fs::directory_entry &entry) {
    std::string name = entry.path().filename().string();

    if (fs::is_symlink(entry))
        name += "@";
    else if (fs::is_directory(entry))
        name += "/";

    return name;
}

string_vector ls::get_directory_entries(const fs::path &path, bool show_hidden) {
    string_vector entries;

    if (show_hidden) {
        entries.emplace_back(".");
        entries.emplace_back("..");
    }

    for (const fs::directory_entry &entry : fs::directory_iterator(path)) {
        auto entry_name = ls::format_entry(entry);

        if (not show_hidden and entry_name.front() == '.')
            continue;

        entries.emplace_back(entry_name);
    }

    std::sort(entries.begin(), entries.end());
    return entries;
}
