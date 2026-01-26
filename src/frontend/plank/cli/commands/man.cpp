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

#include "../../../../../include/frontend/plank/cli/commands/man.h"
#include "../../../../../include/frontend/plank/cli/commands/cd.h"
#include "../../../../../include/frontend/plank/cli/commands/clear.h"
#include "../../../../../include/frontend/plank/cli/commands/export.h"
#include "../../../../../include/frontend/plank/cli/commands/formula.h"
#include "../../../../../include/frontend/plank/cli/commands/ground.h"
#include "../../../../../include/frontend/plank/cli/commands/load.h"
#include "../../../../../include/frontend/plank/cli/commands/ls.h"
#include "../../../../../include/frontend/plank/cli/commands/parse.h"
#include "../../../../../include/frontend/plank/cli/commands/pwd.h"
#include "../../../../../include/frontend/plank/cli/commands/script.h"
#include "../../../../../include/frontend/plank/cli/commands/show.h"
#include "../../../../../include/frontend/plank/cli/commands/state.h"
#include "../../../../../include/frontend/plank/cli/commands/task.h"
#include "../../../../../include/frontend/plank/cli/commands/validate.h"
#include "../../../../../include/frontend/plank/cli/commands/version.h"
#include "../../../../../include/frontend/plank/cli/cli_names.h"
#include "../../../../../include/frontend/plank/cli/cli_utils.h"
#include <filesystem>
#include <sstream>

using namespace plank;
using namespace plank::commands;

namespace fs = std::filesystem;

void man::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    menu->Insert(
        commands::man::get_name(),
        commands::man::run_cmd(data, exit_code),
        commands::man::get_description(),
        {commands::man::get_man_page()}
    );
}

std::string man::get_name() {
    return PLANK_CMD_MAN;
}

std::string man::get_description() {
    return "    Print command manual.";
}

std::string man::get_man_page() {
    auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
    std::stringstream buffer;

    std::string str;

    buffer << make_man_page(man::get_cli(str), man::get_name(), fmt)
                   .prepend_section("DESCRIPTION",
                                    cli_utils::get_formatted_man_description(man::get_description()));

    return buffer.str();
}

clipp::group man::get_cli(std::string &cmd) {
    return clipp::group{
        clipp::opt_value("command", cmd)
    };
}

cmd_function<string_vector> man::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string cmd;
        auto cli = man::get_cli(cmd);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            std::cout << make_man_page(cli, man::get_name(), fmt);
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        if (cmd.empty() or cmd == PLANK_CMD_MAN)
            out << man::get_man_page();
        else if (cmd == PLANK_CMD_CD)
            out << cd::get_man_page();
        else if (cmd == PLANK_CMD_CLEAR)
            out << clear::get_man_page();
        else if (cmd == PLANK_CMD_EXPORT)
            out << export_::get_man_page();
        else if (cmd == PLANK_CMD_FORMULA)
            out << formula::get_man_page();
        else if (cmd == PLANK_CMD_GROUND)
            out << ground::get_man_page();
        else if (cmd == PLANK_CMD_LOAD)
            out << load::get_man_page();
        else if (cmd == PLANK_CMD_LS)
            out << ls::get_man_page();
        else if (cmd == PLANK_CMD_PARSE)
            out << parse::get_man_page();
        else if (cmd == PLANK_CMD_PWD)
            out << pwd::get_man_page();
        else if (cmd == PLANK_CMD_SCRIPT)
            out << script::get_man_page();
        else if (cmd == PLANK_CMD_SHOW)
            out << show::get_man_page();
        else if (cmd == PLANK_CMD_STATE)
            out << state::get_man_page();
        else if (cmd == PLANK_CMD_TASK)
            out << task::get_man_page();
        else if (cmd == PLANK_CMD_VALIDATE)
            out << validate::get_man_page();
        else if (cmd == PLANK_CMD_VERSION)
            out << version::get_man_page();
        else if (cmd == "!") {
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            out << make_man_page(
                    clipp::group{clipp::value("history index").doc("numeric index of command to run")}, cmd, fmt)
                    .prepend_section("DESCRIPTION", "    Execute command by history index.");
        } else if (cmd == PLANK_CMD_HISTORY) {
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            out << make_man_page(clipp::group{}, cmd, fmt)
                    .prepend_section("DESCRIPTION", "    Show command history.");
        } else if (cmd == PLANK_CMD_QUIT) {
            auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
            out << make_man_page(clipp::group{}, cmd, fmt)
                    .prepend_section("DESCRIPTION", "    Quit current session.");
        } else {
            out << man::get_name() << ": no such command "
                << cli_utils::quote(cmd) << "." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        exit_code = plank::exit_code::all_good;
    };
}