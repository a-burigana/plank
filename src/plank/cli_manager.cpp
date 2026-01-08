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

#include "../../include/plank/cli_manager.h"
#include "../../include/plank/cli_headers.h"
#include "../../include/parser/file_parser.h"
#include "../../include/type-checker/type_checker.h"
#include "../../include/grounder/grounder_helper.h"
#include "../../include/printer/tasks/planning_task_printer.h"
#include "../../include/error-manager/epddl_exception.h"
#include "../../include/utils/interactive-cli/filehistorystorage.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

using namespace plank;

int cli_manager::start(int argc, char *argv[]) {
    std::cout
        << PLANK_LOGO_ASCII << " "
        << PLANK_NAME << " "
        << PLANK_VERSION << " - "
        << PLANK_TAGLINE << std::endl;

    if (argc == 1)
        return cli_manager::start_interactive_cli();

    std::string operation, problem_path, domain_path, spec_path, json_path;
    string_vector libraries_paths, action_names;

    clipp::group plank_cli = cli_manager::get_plank_cli(
            operation, problem_path, domain_path, spec_path, json_path,
            libraries_paths, action_names);

    if (not clipp::parse(argc, argv, plank_cli))
        std::cout << make_man_page(plank_cli, argv[0]);
    else
        try {
            // Removing accidental duplicates from library paths
            libraries_paths.erase(
                    std::unique(libraries_paths.begin(), libraries_paths.end()),
                    libraries_paths.end());

            cli_data data;
            cli_task_data task_data;

            task_data.set_spec_paths(epddl::parser::specification_paths{problem_path, domain_path, libraries_paths});
            data.add_task_data("task", std::move(task_data));
            data.set_current_task("task");

            if (not spec_path.empty())
                commands::load::load_specification(std::cerr, data, spec_path);

            if (operation == PLANK_CMD_PARSE)
                data.get_current_task_data().parse(std::cerr);
            else if (operation == PLANK_CMD_GROUND or
                     operation == PLANK_CMD_EXPORT or
                     operation == PLANK_CMD_VALIDATE) {
                data.get_current_task_data().ground(std::cerr);

                if (operation == PLANK_CMD_EXPORT) {
                    std::cout << "Printing...";

                    json_path = json_path.empty() ? problem_path : json_path;

                    printer::planning_task_printer::print_planning_task_json(
                            data.get_current_task_data().get_task(),
                            data.get_current_task_data().get_info(),
                            std::filesystem::path(json_path));

                    std::cout << "done." << std::endl;
                } else if (operation == PLANK_CMD_VALIDATE)
                    return commands::validate::do_validation(std::cerr, data, action_names);
            }

            std::cout << PLANK_LOGO_ASCII << std::endl;
        } catch (epddl::EPDDLException &e) {
            std::cerr << std::endl << e.what();
            std::cout << PLANK_LOGO_ASCII << std::endl;

            return plank::exit_code::parser_error;
        } catch (std::runtime_error &e) {
            std::cerr << std::endl << e.what();
            std::cout << PLANK_LOGO_ASCII << std::endl;

            return plank::exit_code::file_not_found_error;
        } catch (...) {
            std::cerr << "Unknown exception was caught. Please report this to the developers." << std::endl;
            return plank::exit_code::unknown_error;
        }
    return plank::exit_code::all_good;
}

int cli_manager::start_interactive_cli() {
    auto plank_menu = std::make_unique<cli::Menu>(PLANK_NAME);
    cli::SetColor();

    cli_data data;
    cli::Cli cli(std::move(plank_menu), cli_manager::get_history());

    // Filesystem commands
    commands::cd      ::add_to_menu(cli.get_root_menu(), data);
    commands::ls      ::add_to_menu(cli.get_root_menu(), data);
    commands::pwd     ::add_to_menu(cli.get_root_menu(), data);

    // Main commands
    commands::load    ::add_to_menu(cli.get_root_menu(), data);
    commands::clear   ::add_to_menu(cli.get_root_menu(), data);
    commands::task    ::add_to_menu(cli.get_root_menu(), data);
    commands::state   ::add_to_menu(cli.get_root_menu(), data);
    commands::formula ::add_to_menu(cli.get_root_menu(), data);

    commands::ground  ::add_to_menu(cli.get_root_menu(), data);
    commands::parse   ::add_to_menu(cli.get_root_menu(), data);
    commands::validate::add_to_menu(cli.get_root_menu(), data);

    // Utility commands
    commands::export_ ::add_to_menu(cli.get_root_menu(), data);
    commands::show    ::add_to_menu(cli.get_root_menu(), data);
    commands::version ::add_to_menu(cli.get_root_menu());

    cli::LoopScheduler scheduler;
    cli::CliLocalTerminalSession input(cli, scheduler, std::cout, data);

    cli.WrongCommandHandler([&](std::ostream &out, const std::string &cmd) {
        cli_manager::run_wrong_command_handler(out, cmd);
    });

    cli.ExitAction([&](auto& out){
        out << PLANK_LOGO_ASCII;
        scheduler.Stop();
    });

    scheduler.Run();

    return plank::exit_code::all_good;
}

std::unique_ptr<cli::FileHistoryStorage> cli_manager::get_history() {
    const fs::path history_path =
            (fs::path{getenv("HOME")} / PLANK_DIR_PATH / PLANK_HISTORY_FILENAME).lexically_normal();

    if (not fs::exists(history_path.parent_path()))
        fs::create_directories(history_path.parent_path());

    return std::make_unique<cli::FileHistoryStorage>(history_path.string(), 100);
}

clipp::group cli_manager::get_plank_cli(std::string &operation, std::string &problem_path, std::string &domain_path,
                                        std::string &spec_path, std::string &json_path,
                                        string_vector &libraries_paths, string_vector &action_names) {
    clipp::group paths_cli =
        clipp::one_of(
            clipp::group(
                clipp::required("-p", "--problem")
                & clipp::value("problem path", problem_path),
                clipp::required("-d", "--domain")
                & clipp::value("domain path", domain_path),
                clipp::option("-l", "--libraries")
                & clipp::values("libraries paths", libraries_paths)
            ),
            clipp::required("-s", "--spec") & clipp::value("EPDDL specification path", spec_path)
        );

    return
        clipp::one_of(
            clipp::group(
                clipp::command(PLANK_CMD_PARSE).set(operation)
                & paths_cli
            ),
            clipp::group(
                clipp::command(PLANK_CMD_GROUND).set(operation)
                & paths_cli
            ),
            clipp::group(
                clipp::command(PLANK_CMD_EXPORT).set(operation)
                & clipp::group(
                    paths_cli,
                    clipp::required("-o", "--output")
                    & clipp::value("JSON output path", json_path)
                )
            ),
            clipp::group(
                clipp::command(PLANK_CMD_VALIDATE).set(operation)
                & clipp::group(
                    paths_cli,
                    clipp::required("-a", "--actions")
                    & clipp::values("actions", action_names)
                )
            )
        );
}

void cli_manager::run_wrong_command_handler(std::ostream &out, const std::string &cmd) {
    clipp::arg_list cmd_args;
    cli::detail::split(cmd_args, cmd);

    out << "Syntax error: ";

    if (cmd_args.front() == commands::clear::get_name())
        std::cout << commands::clear::get_cmd_syntax();
//    else if (cmd_args.front() == PLANK_CMD_EXIT)
//    else if (cmd_args.front() == PLANK_CMD_HELP)
    else if (cmd_args.front() == commands::ground::get_name())
        std::cout << commands::ground::get_cmd_syntax();
    else if (cmd_args.front() == commands::load::get_name())
        std::cout << commands::load::get_cmd_syntax();
    else if (cmd_args.front() == commands::parse::get_name())
        std::cout << commands::parse::get_cmd_syntax();
    else if (cmd_args.front() == commands::validate::get_name())
        std::cout << commands::validate::get_cmd_syntax();
    else if (cmd_args.front() == commands::version::get_name())
        std::cout << commands::version::get_cmd_syntax();
    else
        out << "Unknown command: " << cmd_args.front() << "." << std::endl;
}
