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
#include "../../../include/lib/epddl/utils/spec_paths_loader.h"
#include "../../../include/frontend/bfs-planner/search/planner.h"
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
    const auto cli =
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
    const auto [spec_paths, failed] =
        epddl::grounder::grounder_helper::get_specification_paths(
            domain_path, problem_path, libraries_paths, spec_paths_json_file);

    if (failed) return 1;

    try {
        const auto task = epddl::grounder::grounder_helper::build_ground_task(spec_paths);

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
    } catch (std::runtime_error &e) {
        std::cout << std::endl << e.what();
        return 1;
    } catch (...) {
        std::cout << std::endl << "Unknown exception was caught. Please contact the developers to fix this.";
        return 1;
    }

    return 0;
}
