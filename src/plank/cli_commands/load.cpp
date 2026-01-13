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

#include "../../../include/plank/cli_commands/load.h"
#include "../../../include/plank/cli_names.h"
#include "../../../include/plank/cli_utils.h"
#include "../../../include/plank/cli_data/cli_data_loader.h"
#include <filesystem>
#include <fstream>

using namespace plank;
using namespace plank::commands;

namespace fs = std::filesystem;

void load::add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code) {
    data.add_script_cmd(load::get_name());

    menu->Insert(
        commands::load::get_name(),
        commands::load::run_cmd(data, exit_code),
        commands::load::get_help(),
        {commands::load::get_cmd_syntax()}
    );
}

std::string load::get_name() {
    return PLANK_CMD_LOAD;
}

std::string load::get_help() {
    return "Load an EPDDL domain, problem, action type library, or specification";
}

std::string load::get_cmd_syntax() {
    std::string str1, str2;
    std::string desc = clipp::usage_lines(load::get_cli(str1, str2)).str();

    return "  " + cli_utils::ltrim(desc);
}

clipp::group load::get_cli(std::string &file_type, std::string &path) {
    return clipp::group{
        clipp::one_of(
            clipp::command(PLANK_SUB_CMD_DOMAIN).set(file_type),
            clipp::command(PLANK_SUB_CMD_PROBLEM).set(file_type),
            clipp::command(PLANK_SUB_CMD_LIBRARY).set(file_type),
            clipp::command(PLANK_SUB_CMD_SPEC).set(file_type))
        &
        clipp::value("path to file", path)
    };
}

cmd_function<string_vector> load::run_cmd(cli_data &data, plank::exit_code &exit_code) {
    return [&](std::ostream &out, const string_vector &input_args) {
        std::string file_type, path;
        auto cli = load::get_cli(file_type, path);

        // Parsing arguments
        if (not clipp::parse(input_args, cli)) {
            std::cout << make_man_page(cli, load::get_name());
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        if (not data.is_opened_task()) {
            out << load::get_name() << ": no task is currently opened." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        fs::path file_path = cli_utils::get_absolute_path(data.get_current_working_dir(), path);
        std::ifstream file(file_path);
        bool good_path = file.good();

        if (not good_path) {
            out << load::get_name() << ": no such file " << cli_utils::quote(path) << "." << std::endl;
            exit_code = plank::exit_code::cli_cmd_error;
            return;
        }

        if (file_type == PLANK_SUB_CMD_PROBLEM)
            data.get_current_task_data().set_problem_path(file_path);
        else if (file_type == PLANK_SUB_CMD_DOMAIN)
            data.get_current_task_data().set_domain_path(file_path);
        else if (file_type == PLANK_SUB_CMD_LIBRARY)
            data.get_current_task_data().add_library_path(file_path);
        else if (file_type == PLANK_SUB_CMD_SPEC) {
            exit_code = load::load_specification(out, data, file_path);
            return;
        }

        file.close();
        exit_code = plank::exit_code::all_good;
    };
}

plank::exit_code load::load_specification(std::ostream &out, cli_data &data, const fs::path &path) {
    std::ifstream f(path);
    json spec = json::parse(f);
    bool bad_json = not spec.is_array();

    json problem_json, domain_json, libraries_json;

    for (const auto &[_, item_json] : spec.items()) {
        if (not item_json.is_object() or item_json.size() != 1)
            bad_json = true;
        else
            for (const auto &[key, value]: item_json.items())
                if (key == "problem")
                    problem_json = value;
                else if (key == "domain")
                    domain_json = value;
                else if (key == "action-type-libraries")
                    libraries_json = value;
                else
                    bad_json = true;

        if (bad_json) {
            out << load::get_name() << ": expected array of EPDDL components paths." << std::endl;
            return plank::exit_code::cli_cmd_error;
        }
    }

    auto spec_paths = epddl::parser::specification_paths{};

    if (load::load_component(out, "problem", problem_json, spec_paths) != plank::exit_code::all_good)
        return plank::exit_code::cli_cmd_error;

    if (load::load_component(out, "domain", domain_json, spec_paths) != plank::exit_code::all_good)
        return plank::exit_code::cli_cmd_error;

    if (load::load_libraries(out, libraries_json, spec_paths) != plank::exit_code::all_good)
        return plank::exit_code::cli_cmd_error;

    data.get_current_task_data().set_spec_paths(std::move(spec_paths));

    return plank::exit_code::all_good;
}

plank::exit_code load::load_path(std::ostream &out, const std::string &component, const json &component_json,
                                 const std::function<void(const std::string &)> &load_f) {
    if (not component_json.is_string()) {
        out << load::get_name() << ": expected " << component << " path." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    fs::path component_path = component_json;

    if (not fs::is_regular_file(component_path)) {
        out << load::get_name() << ": no such file"
            << cli_utils::quote(component_path.string()) << "." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    load_f(component_path.string());
    return plank::exit_code::all_good;
}

plank::exit_code load::load_component(std::ostream &out, const std::string &component, const json &component_json,
                                      epddl::parser::specification_paths &spec_paths) {
    if (component_json.empty()) {
        out << load::get_name() << ": missing " << component << " path." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    load::load_path(
        out, component, component_json,
        [&](const std::string &path) {
            if (component == "problem")
                spec_paths.problem_path = path;
            else
                spec_paths.domain_path = path;
        });

    return plank::exit_code::all_good;
}

plank::exit_code load::load_libraries(std::ostream &out, const json &libraries_json,
                                      epddl::parser::specification_paths &spec_paths) {
    if (libraries_json.empty()) {
        out << load::get_name() << ": missing action type libraries paths." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    if (not libraries_json.is_array()) {
        out << load::get_name() << ": expected array of action type libraries paths." << std::endl;
        return plank::exit_code::cli_cmd_error;
    }

    for (const auto &library_json : libraries_json)
        load::load_path(
            out, "action type library", library_json,
            [&](const std::string &path) {
                spec_paths.libraries_paths.emplace_back(path);
            });

    // Removing accidental duplicates from library paths
    spec_paths.libraries_paths.erase(
            std::unique(spec_paths.libraries_paths.begin(), spec_paths.libraries_paths.end()),
            spec_paths.libraries_paths.end());

    return plank::exit_code::all_good;
}
