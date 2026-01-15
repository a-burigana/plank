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

#include "../../../../include/frontend/plank/cli_commands/script.h"
#include "../../../../include/frontend/plank/cli_names.h"
#include "../../../../include/frontend/plank/cli_commands/cd.h"
#include "../../../../include/frontend/plank/cli_commands/clear.h"
#include "../../../../include/frontend/plank/cli_commands/export.h"
#include "../../../../include/frontend/plank/cli_commands/formula.h"
#include "../../../../include/frontend/plank/cli_commands/ground.h"
#include "../../../../include/frontend/plank/cli_commands/load.h"
#include "../../../../include/frontend/plank/cli_commands/ls.h"
#include "../../../../include/frontend/plank/cli_commands/parse.h"
#include "../../../../include/frontend/plank/cli_commands/pwd.h"
#include "../../../../include/frontend/plank/cli_commands/show.h"
#include "../../../../include/frontend/plank/cli_commands/state.h"
#include "../../../../include/frontend/plank/cli_commands/task.h"
#include "../../../../include/frontend/plank/cli_commands/validate.h"
#include "../../../../include/frontend/plank/cli_commands/version.h"
#include <ostream>

using namespace plank;
using namespace plank::commands;


void script::add_to_menu(cli::CliLocalTerminalSession &session, std::unique_ptr<cli::Menu> &menu, cli_data &data,
                         plank::exit_code &exit_code) {
    menu->Insert(
        commands::script::get_name(),
        commands::script::run_cmd(session, menu, data, exit_code),
        commands::script::get_help(),
        {commands::script::get_cmd_syntax()}
    );
}

std::string script::get_name() {
    return PLANK_CMD_SCRIPT;
}

std::string script::get_help() {
    return "Load and run plank scripts";
}

std::string script::get_cmd_syntax() {
    std::string str1, str2, str3, str4;
    std::string desc = clipp::usage_lines(script::get_cli(str1, str2, str3, str4)).str();

    return "\n\t" + cli_utils::ltrim(desc);
}

clipp::group script::get_cli(std::string &operation, std::string &script_name,
                             std::string &new_script_name, std::string &script_path) {
    return clipp::group(
        clipp::one_of(
            clipp::command(PLANK_SUB_CMD_ADD).set(operation)
                & clipp::value("script name", script_name)
                & clipp::value("script path", script_path),
            clipp::command(PLANK_SUB_CMD_REMOVE).set(operation)
                & clipp::value("script name", script_name),
            clipp::command(PLANK_SUB_CMD_RENAME).set(operation)
                & clipp::value("script name", script_name)
                & clipp::value("new script name", new_script_name),
            clipp::command(PLANK_SUB_CMD_RUN).set(operation)
                & clipp::value("script name", script_name)
        )
    );
}

cmd_function<string_vector> script::run_cmd(cli::CliLocalTerminalSession &session,
                                            std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string operation, script_path, script_name, new_script_name;

        auto cli_ = script::get_cli(operation, script_name, new_script_name, script_path);

        // Parsing arguments
        if (not clipp::parse(input_args, cli_)) {
            std::cout << make_man_page(cli_, script::get_name());
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        if (operation == PLANK_SUB_CMD_ADD)
            exit_code = script::add(out, data, script_name, script_path);
        else if (operation == PLANK_SUB_CMD_REMOVE)
            exit_code = script::remove(out, data, script_name);
        else if (operation == PLANK_SUB_CMD_RENAME)
            exit_code = script::rename(out, data, script_name, new_script_name);
        else if (operation == PLANK_SUB_CMD_RUN)
            exit_code = script::run(out, session, menu, data, script_name);
    };
}

plank::exit_code script::add(std::ostream &out, cli_data &data, const std::string &script_name,
                             const std::string &script_path) {
    if (not cli_utils::check_name(out, script_name, script::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (data.is_defined_script(script_name)) {
        out << script::get_name() << ": redefinition of script "
            << cli_utils::quote(script_name) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    fs::path file_path = cli_utils::get_absolute_path(data.get_current_working_dir(), script_path);
    std::ifstream file(file_path);
    bool good_path = file.good();

    if (not good_path) {
        out << script::get_name() << ": no such file " << cli_utils::quote(script_path) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.add_script_path(script_name, script_path);
    file.close();

    return plank::exit_code::all_good;
}

plank::exit_code script::remove(std::ostream &out, cli_data &data, const std::string &script_name) {
    if (not cli_utils::check_name(out, script_name, script::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_defined_script(script_name)) {
        out << script::get_name() << ": undefined script "
            << cli_utils::quote(script_name) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    data.remove_script(script_name);
    return plank::exit_code::all_good;
}

plank::exit_code script::rename(std::ostream &out, cli_data &data, const std::string &script_name,
                                const std::string &new_script_name) {
    if (not cli_utils::check_name(out, script_name, script::get_name()) or
        not cli_utils::check_name(out, new_script_name, script::get_name()))
        return plank::exit_code::cli_cmd_error;

    if (script_name == new_script_name)
        return plank::exit_code::all_good;

    if (not data.is_defined_script(script_name))
        out << script::get_name() << ": undefined script "
            << cli_utils::quote(script_name) << "." << std::endl;
    else if (data.is_defined_script(new_script_name))
        out << script::get_name() << ": redefinition of script "
            << cli_utils::quote(new_script_name) << "." << std::endl;
    else {
        data.add_script_path(
                new_script_name,
                data.get_script_path(script_name));
        data.remove_script(script_name);

        return plank::exit_code::all_good;
    }

    return plank::exit_code::cli_cmd_error;
}

plank::exit_code script::run(std::ostream &out, cli::CliLocalTerminalSession &session,
                             std::unique_ptr<cli::Menu> &menu, cli_data &data, const std::string &script_name) {
    if (not cli_utils::check_name(out, script_name, script::get_name()))
        return plank::exit_code::cli_cmd_error;
    else if (not data.is_defined_script(script_name)) {
        out << script::get_name() << ": undefined script "
            << cli_utils::quote(script_name) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    fs::path file_path = cli_utils::get_absolute_path(data.get_current_working_dir(), data.get_script_path(script_name));
    std::ifstream file(file_path);
    bool good_path = file.good();

    if (not good_path) {
        out << script::get_name() << ": no such file "
            << cli_utils::quote(data.get_script_path(script_name)) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    out << "Running script..." << std::endl;

    std::string line;
    plank::exit_code exit_code = plank::exit_code::all_good;

    while (exit_code == plank::exit_code::all_good and std::getline(file, line)) {
        std::vector<std::string> line_args;
        cli::detail::split(line_args, line);

        if (line_args.empty())
            continue;

        session.Prompt();
        out << line << std::endl;

        const std::string cmd = line_args.front();
        line_args.erase(line_args.begin());

        if (cmd == PLANK_CMD_HELP or cmd == PLANK_CMD_HISTORY or cmd == PLANK_CMD_QUIT or cmd == "!" or
            cmd == PLANK_CMD_SCRIPT) {
            out << PLANK_NAME << ": command " << cli_utils::quote(cmd)
                << " can not be used inside scripts." << std::endl;
            return plank::exit_code::cli_cmd_error;
        }

        if (not data.is_script_cmd(cmd)) {
            out << PLANK_NAME << ": no such command " << cli_utils::quote(cmd) << "." << std::endl;
            return plank::exit_code::cli_cmd_error;
        }

        if (cmd == cd::get_name())
            cd::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == clear::get_name())
            clear::run_cmd(menu, data, exit_code)(out, line_args);
        else if (cmd == export_::get_name())
            export_::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == formula::get_name())
            formula::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == ground::get_name())
            ground::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == load::get_name())
            load::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == ls::get_name())
            ls::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == parse::get_name())
            parse::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == pwd::get_name())
            pwd::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == show::get_name())
            show::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == state::get_name())
            state::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == task::get_name())
            task::run_cmd(menu, data, exit_code)(out, line_args);
        else if (cmd == validate::get_name())
            validate::run_cmd(data, exit_code)(out, line_args);
        else if (cmd == version::get_name())
            version::run_cmd(exit_code)(out, line_args);
    }

    file.close();

    out << "Script finished with exit code " << exit_code << std::endl;
    return exit_code;
}
