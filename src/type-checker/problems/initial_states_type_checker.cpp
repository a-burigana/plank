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

#include "../../../include/type-checker/problems/initial_states_type_checker.h"
#include "../../../include/type-checker/common/formulas_type_checker.h"
#include "../../../include/type-checker/common/relations_type_checker.h"
#include <variant>

using namespace epddl;
using namespace epddl::type_checker;

void
initial_states_type_checker::check(const ast::initial_state_ptr &state, context &context, const type_ptr &types_tree) {
    std::visit([&](auto &&arg) {
        check_state(arg, context, types_tree);
    }, state->get_state());
}

void initial_states_type_checker::check_state(const ast::explicit_initial_state_ptr &state, context &context,
                                              const type_ptr &types_tree) {
    context.push();

    const type_ptr &world = type_utils::find(types_tree, "world");
    context.add_decl_list(state->get_worlds(), either_type{world}, types_tree);

    for (const ast::agent_relation_ptr<ast::identifier_ptr> &r_i: state->get_relations())
        relations_type_checker::check_agent_relation<ast::identifier_ptr>(r_i, context, types_tree);

    for (const ast::world_label_ptr &l: state->get_labels())
        initial_states_type_checker::check_world_label(l, context, types_tree);

    for (const ast::identifier_ptr &w_d: state->get_designated())
        context.check_type(w_d, world);

    context.pop();
}

void initial_states_type_checker::check_world_label(const ast::world_label_ptr &l, context &context,
                                                    const type_ptr &types_tree) {
    const type_ptr &world = type_utils::find(types_tree, "world");
    context.check_type(l->get_world_name(), world);

    auto check_elem = formulas_type_checker::check_function_t<ast::predicate_ptr>(
            [&] (const ast::predicate_ptr &p, class context &context, const type_ptr &types_tree) {
                context.check_predicate_signature(p->get_id(), p->get_terms());
            });

    formulas_type_checker::check_list(l->get_predicates(), check_elem, context, types_tree, type_utils::find(types_tree, "object"));
}

void initial_states_type_checker::check_state(const ast::finitary_S5_theory &state, context &context,
                                              const type_ptr &types_tree) {
    auto check_elem = formulas_type_checker::check_function_t<ast::finitary_S5_formula>(
            [&] (const ast::finitary_S5_formula &formula, class context &context, const type_ptr &types_tree) {
                initial_states_type_checker::check_formula(formula, context, types_tree);
            });

    formulas_type_checker::check_list(state, check_elem, context, types_tree, type_utils::find(types_tree, "object"));
}

void initial_states_type_checker::check_formula(const ast::finitary_S5_formula &formula, context &context,
                                                const type_ptr &types_tree) {
    std::visit([&](auto &&arg) { initial_states_type_checker::check_formula(arg, context, types_tree); }, formula);
}

void initial_states_type_checker::check_formula(const ast::prop_formula_ptr &formula, context &context, const type_ptr &types_tree) {
    formulas_type_checker::check_formula(formula->get_formula(), context, types_tree);
}

void initial_states_type_checker::check_formula(const ast::ck_formula_ptr &formula, context &context, const type_ptr &types_tree) {
    formulas_type_checker::check_formula(formula->get_formula(), context, types_tree);
}

void initial_states_type_checker::check_formula(const ast::ck_k_formula_ptr &formula, context &context, const type_ptr &types_tree) {
    context.check_type(formula->get_agent(), type_utils::find(types_tree, "agent"));
    formulas_type_checker::check_formula(formula->get_formula(), context, types_tree);
}

void initial_states_type_checker::check_formula(const ast::ck_kw_formula_ptr &formula, context &context, const type_ptr &types_tree) {
    context.check_type(formula->get_agent(), type_utils::find(types_tree, "agent"));
    formulas_type_checker::check_formula(formula->get_formula(), context, types_tree);
}

void initial_states_type_checker::check_formula(const ast::ck_not_kw_formula_ptr &formula, context &context, const type_ptr &types_tree) {
    context.check_type(formula->get_agent(), type_utils::find(types_tree, "agent"));
    formulas_type_checker::check_formula(formula->get_formula(), context, types_tree);
}
