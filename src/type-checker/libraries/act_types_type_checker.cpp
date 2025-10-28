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

#include "../../../include/type-checker/libraries/act_types_type_checker.h"
#include "../../../include/type-checker/common/relations_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void act_types_type_checker::check(const ast::action_type_ptr &action_type, context &context, const type_ptr &types_tree) {
    context.push();

    const type_ptr &obs_group = types_tree->find(";obs-group"), &event = types_tree->find("event");
    context.add_decl_list(action_type->get_obs_groups(), either_type{obs_group}, types_tree);
    context.add_decl_list(action_type->get_events(), either_type{event}, types_tree);

    for (const ast::agent_relation_ptr<ast::variable_ptr> &q_i : action_type->get_relations())
        relations_type_checker::check_agent_relation<ast::variable_ptr>(q_i, context, types_tree);

    for (const ast::variable_ptr &e_d : action_type->get_designated())
        context.check_type(e_d, event);

    context.pop();
}
