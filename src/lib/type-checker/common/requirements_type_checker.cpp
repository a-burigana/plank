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

#include "../../../../include/lib/type-checker/common/requirements_type_checker.h"
#include <algorithm>
#include <iostream>

using namespace epddl;
using namespace epddl::type_checker;

void requirements_type_checker::check(const planning_specification &task, context &context,
                                      spec_error_managers &err_managers) {
    const auto &[problem, domain, libraries] = task;

    for (const ast::act_type_library_ptr &library: libraries)
        check_decl_requirements<ast::act_type_library_item>(
                library, library->get_items(), context,
                err_managers.libraries_err_managers.at(library->get_name()->get_token().get_lexeme()));

    check_decl_requirements<ast::domain_item>(
            domain, domain->get_items(), context,
            err_managers.domain_err_manager);

    check_decl_requirements<ast::problem_item>(
            problem, problem->get_items(), context,
            err_managers.problem_err_manager);
}

void requirements_type_checker::check_node_requirements(const ast::ast_node_ptr &node, context &context,
                                                        error_manager_ptr &err_manager) {
    const ast::info &info = node->get_info();
    const auto &[req, msg] = info.m_requirements;

    if (not req.empty() and not context.requirements.is_declared_requirement(req))
        err_manager->print_warning(error_type::missing_requirement, info, {"Warning: " + msg});

    for (const ast::ast_node_ptr &child : node->get_children())
        check_node_requirements(child, context, err_manager);
}
