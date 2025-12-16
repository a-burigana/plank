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

#include "../../../include/type-checker/problems/problems_type_checker.h"
#include "../../../include/type-checker/problems/agent_groups_type_checker.h"
#include "../../../include/type-checker/problems/initial_states_type_checker.h"
#include "../../../include/type-checker/problems/public_static_init_type_checker.h"
#include "../../../include/type-checker/common/formulas_and_lists_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void problems_type_checker::check(const ast::problem_ptr &problem, context &context) {
    bool defined_init = false, defined_static_init = false, defined_goal;
    context.components_names.set_problem_name(problem);
    context.components_names.assert_declared_domain(problem->get_domain()->get_name());

    for (const auto &item: problem->get_items())
        if (std::holds_alternative<ast::agent_groups_decl_ptr>(item))
            agent_groups_type_checker::check(std::get<ast::agent_groups_decl_ptr>(item), context);
        else if (std::holds_alternative<ast::initial_state_ptr>(item)) {
            if (defined_init)
                throw EPDDLException(std::get<ast::initial_state_ptr>(item)->get_info(),
                                     "Redeclaration of initial state initialization.");

            initial_states_type_checker::check(std::get<ast::initial_state_ptr>(item), context);
            defined_init = true;
        } else if (std::holds_alternative<ast::public_static_init_ptr>(item)) {
            if (defined_static_init)
                throw EPDDLException(std::get<ast::public_static_init_ptr>(item)->get_info(),
                                     "Redeclaration of static predicates initialization.");

            public_static_init_type_checker::check(std::get<ast::public_static_init_ptr>(item), context);
            defined_static_init = true;
        } else if (std::holds_alternative<ast::goal_decl_ptr>(item)) {
            formulas_and_lists_type_checker::check_formula(std::get<ast::goal_decl_ptr>(item)->get_goal(), context);
            defined_goal = true;
        }

    if (not defined_init)
        throw EPDDLException(problem->get_info(), "Missing initial state declaration.");

    if (not defined_goal)
        throw EPDDLException(problem->get_info(), "Missing goal declaration.");
}
