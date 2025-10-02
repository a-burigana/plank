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
#include "../../../include/type-checker/problems/initial_states_type_checker.h"
#include "../../../include/type-checker/problems/static_init_type_checker.h"
#include "../../../include/type-checker/common/formulas_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;


void problems_type_checker::check(const ast::problem_ptr &problem, context &context, const type_ptr &types_tree) {
    for (const auto &item: problem->get_items())
        if (std::holds_alternative<ast::initial_state_ptr>(item))
            initial_states_type_checker::check(std::get<ast::initial_state_ptr>(item), context, types_tree);
        else if (std::holds_alternative<ast::static_init_ptr>(item))
            static_init_type_checker::check(std::get<ast::static_init_ptr>(item), context, types_tree);
        else if (std::holds_alternative<ast::goal_decl_ptr>(item))
            formulas_type_checker::check_formula(std::get<ast::goal_decl_ptr>(item)->get_goal(), context, types_tree);
}
