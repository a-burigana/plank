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

#ifndef EPDDL_PARSE_FILE_H
#define EPDDL_PARSE_FILE_H

#include "../ast/planning_specification.h"
#include "libraries/act_type_library_parser.h"
#include "domains/domain_parser.h"
#include "problems/problem_parser.h"
#include <algorithm>
#include <cassert>
#include <memory>

namespace epddl::parser {
    class file_parser {
    public:
        struct specification_paths {
            const std::string problem_path;
            const std::string domain_path;
            const std::vector<std::string> libraries_paths;
        };

        static std::pair<ast::planning_specification, spec_error_managers>
        parse_planning_specification(const specification_paths &spec_paths) {
            const auto &[problem_path, domain_path, libraries_paths] = spec_paths;

            std::list<ast::act_type_library_ptr> libraries;
            ast::domain_ptr domain;
            ast::problem_ptr problem;
            error_manager_map err_manager_map;

            for (const std::string &library_path: libraries_paths) {
                auto lib = file_parser::parse_file<ast::act_type_library_ptr>(
                        library_path, err_manager_map);

                bool redeclared_library = std::any_of(libraries.begin(), libraries.end(),
                                                      [&](const auto &library) {
                    return library->get_name()->get_token().get_lexeme() == lib->get_name()->get_token().get_lexeme();
                });

                if (redeclared_library)
                    error_manager::throw_error(library_path, error_type::library_declaration,
                                               {lib->get_name()->get_token().get_lexeme()});

                libraries.push_back(std::move(lib));
            }

            if (not domain_path.empty())
                domain = file_parser::parse_file<ast::domain_ptr>(domain_path, err_manager_map);
            if (not problem_path.empty())
                problem = file_parser::parse_file<ast::problem_ptr>(problem_path, err_manager_map);

            ast::planning_specification spec = {std::move(problem), std::move(domain), std::move(libraries)};
            spec_error_managers err_managers = file_parser::get_specification_error_managers(spec, err_manager_map);

            return {std::move(spec), std::move(err_managers)};
        }

    private:
        template<typename decl_type>
        static decl_type parse_file(const std::string &path, error_manager_map &err_manager_map) {
            assert((std::is_same_v<decl_type, ast::act_type_library_ptr> or
                    std::is_same_v<decl_type, ast::domain_ptr> or
                    std::is_same_v<decl_type, ast::problem_ptr>));

            error_manager_ptr err_manager = std::make_shared<error_manager>(path);

            parser_helper helper{path, err_manager};
            decl_type decl;

            if constexpr (std::is_same_v<decl_type, ast::act_type_library_ptr>)
                decl = act_type_library_parser::parse(helper);
            else if constexpr (std::is_same_v<decl_type, ast::domain_ptr>)
                decl = domain_parser::parse(helper);
            else if constexpr (std::is_same_v<decl_type, ast::problem_ptr>)
                decl = problem_parser::parse(helper);

            err_manager_map[decl->get_name()->get_token().get_lexeme()] = err_manager;
            return decl;
        }

        static spec_error_managers get_specification_error_managers(const planning_specification &spec,
                                                                    error_manager_map &err_manager_map) {
            const auto &[problem, domain, libraries] = spec;

            error_manager_ptr problem_err_manager, domain_err_manager;
            error_manager_map libraries_err_managers;

            for (const auto &[name, err_manager] : err_manager_map) {
                if (name == problem->get_name()->get_token().get_lexeme())
                    problem_err_manager = err_manager;
                else if (name == domain->get_name()->get_token().get_lexeme())
                    domain_err_manager = err_manager;
                else
                    libraries_err_managers[name] = err_manager;
            }

            return spec_error_managers{std::move(problem_err_manager), std::move(domain_err_manager),
                                       std::move(libraries_err_managers)};
        }
    };
}

#endif //EPDDL_PARSE_FILE_H
