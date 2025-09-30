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

#include "../../../include/type-checker/domains/actions_type_checker.h"
#include "../../../include/type-checker/common/formulas_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void actions_type_checker::check(const ast::action_ptr &action, context &context, const type_ptr &types_tree) {
    context.push();

    const type_ptr &object = types_tree->find("object");
    formulas_type_checker::check_list_comprehension(action->get_params(), context, types_tree);

    check_action_signature(action->get_signature(), context, types_tree);

    if (action->get_obs_conditions().has_value())
        check_obs_conditions(*action->get_obs_conditions(), context, types_tree);

    context.pop();
}

void actions_type_checker::check_action_signature(const ast::action_signature_ptr &signature, context &context,
                                                  const type_ptr &types_tree) {
    either_type_list action_type_types = context.get_formal_param_types_action_type(signature->get_name());

    if (action_type_types.size() != signature->get_events().size())
        context::throw_arguments_number_error(signature->get_name(), action_type_types, signature->get_events(), "action type");

    for (const ast::event_signature_ptr &e : signature->get_events())
        context.check_event_signature(e->get_name(), e->get_params());
}

void actions_type_checker::check_obs_conditions(const ast::obs_cond &obs_cond, context &context,
                                                const type_ptr &types_tree) {
    // todo: finish here
}
