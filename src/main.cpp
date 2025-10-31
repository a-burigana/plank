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
#include "../include/error-manager/epddl_exception.h"
#include <iostream>

using namespace epddl;

void print_debug_tests(const type_checker::type_ptr &types_tree, const type_checker::context &context);

int main(int argc, char *argv[]) {
    std::vector<std::string> libraries_paths;
    std::string domain_path, problem_path;
    bool debug;

    auto cli = (
            clipp::option("-l", "--libraries") & clipp::values("libraries", libraries_paths),
            clipp::option("-d", "--domain")    & clipp::value ("domain",    domain_path),
            clipp::option("-p", "--problem")   & clipp::value ("problem",   problem_path),
            clipp::option("--debug").set(debug)
    );

    if (not parse(argc, argv, cli))
        std::cout << make_man_page(cli, argv[0]);

    try {
        std::list<ast::act_type_library_ptr> libraries;
        ast::domain_ptr domain;
        ast::problem_ptr problem;

        for (const std::string &library_path : libraries_paths)
            libraries.push_back(parser::parse_file<ast::act_type_library_ptr>(library_path));

        if (not domain_path.empty())
            domain = parser::parse_file<ast::domain_ptr>(domain_path);
        if (not problem_path.empty())
            problem = parser::parse_file<ast::problem_ptr>(problem_path);

        std::cout << "Parsing successful!" << std::endl;

        if (debug) {
            auto spec = type_checker::planning_specification{std::move(problem), std::move(domain), std::move(libraries)};
            const auto &[types_tree, context] = type_checker::do_semantic_check(spec);

            print_debug_tests(types_tree, context);
            std::cout << "Type checking successful!" << std::endl;
        }

//        del::planning_task task = grounder::grounder_helper::ground(spec, context);
//
//        std::cout << "Grounding successful!" << std::endl;
    } catch (EPDDLException &e) {
        std::cerr << e.what();
    }

    return 0;
}

void print_debug_tests(const type_checker::type_ptr &types_tree, const type_checker::context &context) {
    const type_checker::scope &scope = context.get_scopes().back();

    std::cout << "TYPES:" << std::endl;

    std::function<void(const type_checker::type_ptr &)> print_type = [&] (const type_checker::type_ptr &t) {
        if (not t->get_name().empty()) {
            std::cout << " ~ " << t->get_name();
            if (t->get_parent()) std::cout << " - " << t->get_parent()->get_name();
            std::cout << std::endl;
        }

        for (const auto &c : t->get_children()) print_type(c);
    };

    print_type(types_tree);

    std::cout << std::endl << "ENTITIES:" << std::endl;

    for (const auto &[entity, type] : scope.get_type_map())
        std::cout << " ~ " << entity << " - " << type_checker::context::to_string(type) << std::endl;

    std::cout << std::endl << "PREDICATES:" << std::endl;

    for (const auto &[atom, types] : context.get_predicate_signatures()) {
        bool is_static = context.get_static_predicates().at(atom);
        std::cout << " ~ " << (is_static ? ":static " : "") << atom << "( ";

        for (const type_checker::either_type &t : types)
            std::cout << type_checker::context::to_string(t) << " ";

        std::cout << ")" << std::endl;
    }
}
