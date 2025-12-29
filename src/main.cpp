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

#include "../include/utils/clipp.h"
#include "../include/parser/parse_file.h"
#include "../include/type-checker/type_checker.h"
#include "../include/grounder/grounder_helper.h"
#include "../include/printer/planning_task_printer.h"
#include "../include/error-manager/epddl_exception.h"
#include <iostream>
#include <filesystem>
#include <memory>

using namespace epddl;

int main(int argc, char *argv[]) {
    std::vector<std::string> libraries_paths;
    std::string domain_path, problem_path, json_path;

    auto cli = (
        clipp::option  ("-l", "--libraries") & clipp::values("libraries paths",  libraries_paths),
        clipp::required("-d", "--domain"    ) & clipp::value ("domain path",     domain_path),
        clipp::required("-p", "--problem"   ) & clipp::value ("problem path",    problem_path),
        clipp::option  ("-o", "--output"   ) & clipp::value ("JSON output path", json_path)
    );

    if (not parse(argc, argv, cli))
        std::cout << make_man_page(cli, argv[0]);
    else
        try {
            auto [spec, err_managers] =
                    parser::file_parser::parse_planning_specification(libraries_paths, domain_path, problem_path);

            type_checker::context context = type_checker::do_semantic_check(spec, err_managers);
            auto [task, info] = grounder::grounder_helper::ground(spec, context, err_managers);

            json_path = json_path.empty() ? problem_path : json_path;

            epddl::printer::planning_task_printer::print_planning_task_json(
                    task, info, std::filesystem::path(json_path));

        } catch (EPDDLException &e) {
            std::cerr << e.what();
        } catch (std::runtime_error &e) {
            std::cerr << e.what();
        }

    return 0;
}
