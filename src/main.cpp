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
#include "../include/error-manager/epddl_exception.h"
#include <iostream>

using namespace epddl;

int main(int argc, char *argv[]) {
    std::vector<std::string> libraries_paths;
    std::string domain_path, problem_path;

    auto cli = (
            clipp::option("-l", "--libraries") & clipp::values("libraries", libraries_paths),
            clipp::required("-d", "--domain")  & clipp::value("domain", domain_path),
            clipp::required("-p", "--problem") & clipp::value("problem", problem_path)
    );

    if (not parse(argc, argv, cli))
        std::cout << make_man_page(cli, argv[0]);

    try {
        std::list<ast::act_type_library_ptr> libraries;
        ast::domain_ptr domain;
        ast::problem_ptr problem;

        for (const std::string &library_path : libraries_paths)
            libraries.push_back(parser::parse_file<ast::act_type_library_ptr>(library_path));

        domain = parser::parse_file<ast::domain_ptr>(domain_path);
        problem = parser::parse_file<ast::problem_ptr>(problem_path);

        std::cout << "Parsing successful!" << std::endl;

        auto task = type_checker::planning_specification{std::move(problem), std::move(domain), std::move(libraries)};
        type_checker::do_semantic_check(task);

        std::cout << "Type checking successful!" << std::endl;
    } catch (EPDDLException &e) {
        std::cerr << e.what();
    }

    return 0;
}


