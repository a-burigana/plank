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

#include "../../../external/clipp.h"
#include "../../../include/lib/epddl/error-manager/epddl_exception.h"
#include "../../../include/lib/epddl/parser/file_parser.h"
#include "../../../include/lib/epddl/type-checker/type_checker.h"
#include "../../../include/lib/epddl/grounder/grounder_helper.h"
#include "../../../include/lib/epddl/json-printer/planning_task_printer.h"
#include "../../../include/frontend/bfs-planner/search/planner.h"
#include "../../../include/frontend/bfs-planner/utils/spec_paths_loader.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char **argv) {
    std::cout << "BFS planner" << std::endl;

    std::string domain_path, problem_path, spec_paths_json_file, plan_file;
    std::vector<std::string> libraries_paths;

    // Parsing command line arguments
    clipp::group cli =
        clipp::group(
            clipp::one_of(
                clipp::group(
                    clipp::required("-d", "--domain")
                    & clipp::value("domain path", domain_path).doc("path to EPDDL domain"),
                    clipp::required("-p", "--problem")
                    & clipp::value("problem path", problem_path).doc("path to EPDDL problem"),
                    clipp::option("-l", "--libraries")
                    & clipp::opt_values("libraries paths", libraries_paths).doc("paths to EPDDL libraries")
                ),
                clipp::required("-s", "--spec")
                & clipp::value("specification path", spec_paths_json_file).doc("path to EPDDL specification")
            ),
            clipp::option("--plan-file")
            & clipp::value("plan file path", plan_file).doc("path to plan file")
        );

    if (not clipp::parse(argc, argv, cli)) {
        auto fmt = clipp::doc_formatting{}.first_column(4).doc_column(30).last_column(80);
        std::cout << make_man_page(cli, "bfs_planner", fmt)
            .prepend_section("DESCRIPTION",
                             "    A baseline BFS epistemic planner with bisimulation contractions.");
        return 1;
    }

    // Setting EPDDL specification paths
    epddl::parser::specification_paths spec_paths;

    // Loading from user files
    if (spec_paths_json_file.empty()) {
        // Removing accidental duplicates from library paths
        libraries_paths.erase(
                std::unique(libraries_paths.begin(), libraries_paths.end()),
                libraries_paths.end());

        spec_paths = epddl::parser::specification_paths{problem_path, domain_path, libraries_paths};
    } else {
        // Loading from JSON file
        if (not search::spec_paths_loader::load_specification_paths(spec_paths_json_file, spec_paths))
            return 1;
    }

    try {
        // Parsing...
        std::cout << "Parsing..." << std::flush;

        auto [spec, err_managers] =
                epddl::parser::file_parser::parse_planning_specification(spec_paths);

        std::cout << "done." << std::endl;

        // Type-checking...
        std::cout << "Type-checking..." << std::flush;
        epddl::type_checker::context context =
                epddl::type_checker::do_semantic_check(spec, err_managers);

        std::cout << "done." << std::endl;

        // Grounding...
        std::cout << "Grounding..." << std::flush;
        auto [task, _] = epddl::grounder::grounder_helper::ground(
                spec, context, err_managers);

        std::cout << "done." << std::endl;

        // Solving...
        std::cout << "Solving..." << std::endl;
        del::action_deque plan = search::planner::solve(task);

        // Printing...
        if (not plan_file.empty()) {
            std::ofstream plan_output;
            plan_output.open(plan_file);

            if (plan_output.is_open())
                search::planner::print_plan_json(plan_output, plan);
        }
    } catch (epddl::EPDDLException &e) {
        std::cout << std::endl << e.what();
        return 1;
    }

    return 0;
}
