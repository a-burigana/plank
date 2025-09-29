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

#include "../../../include/type-checker/common/relations_type_checker.h"
#include "../../../include/type-checker/common/formulas_type_checker.h"

using namespace epddl;
using namespace epddl::type_checker;

void relations_type_checker::check_agent_relation(const ast::agent_relation_ptr &r_i, context &context,
                                                  const type_ptr &types_tree) {
    const type_ptr &obs_group = types_tree->find(";obs-group"), &event = types_tree->find("event");

    context.check_type(r_i->get_obs_group(), obs_group);
    check_relation(r_i->get_relation(), context, types_tree, event);
}

void relations_type_checker::check_relation(const ast::relation_ptr &r, context &context, const type_ptr &types_tree,
                                            const type_ptr &node_type) {
    if (std::holds_alternative<ast::simple_relation_ptr>(r)) {
        context.check_type(std::get<ast::simple_relation_ptr>(r)->get_first_term(), node_type);
        context.check_type(std::get<ast::simple_relation_ptr>(r)->get_second_term(), node_type);
    } else if (std::holds_alternative<ast::and_relation_ptr>(r)) {
        for (const ast::relation_ptr &r_ : std::get<ast::and_relation_ptr>(r)->get_relation_list())
            check_relation(r_, context, types_tree, node_type);
    } else if (std::holds_alternative<ast::forall_relation_ptr>(r)) {
        formulas_type_checker::check_list_comprehension(std::get<ast::forall_relation_ptr>(r)->get_params(), context, types_tree);
        check_relation(std::get<ast::forall_relation_ptr>(r)->get_relation(), context, types_tree, node_type);
    }
}
