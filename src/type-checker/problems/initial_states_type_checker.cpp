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
#include "../../../include/type-checker/common/formulas_and_lists_type_checker.h"
#include "../../../include/type-checker/common/relations_type_checker.h"
#include <variant>

using namespace epddl;
using namespace epddl::type_checker;

void
initial_states_type_checker::check(const ast::initial_state_ptr &state, context &context) {
    std::visit([&](auto &&arg) {
        check_state(arg, context);
    }, state->get_state());
}

void initial_states_type_checker::check_state(const ast::explicit_initial_state_ptr &state, context &context) {
    context.entities.push();

    const type_ptr &world = context.types.get_type("world");
    context.entities.add_decl_list(state->get_worlds(), either_type{context.types.get_type_id(world)});
    context.entities.update_typed_entities_sets(context.types);
    context.entities.update_typed_entities_sets(context.types);

    for (const ast::agent_relation_ptr<ast::term> &r_i: state->get_relations())
        relations_type_checker::check_agent_relation<ast::term>(r_i, context);

    for (const ast::world_label_ptr &l: state->get_labels())
        initial_states_type_checker::check_world_label(l, context);

    for (const ast::identifier_ptr &w_d: state->get_designated())
        context.entities.check_type(context.types, w_d, world);

    context.entities.pop();
}

void initial_states_type_checker::check_world_label(const ast::world_label_ptr &l, context &context) {
    const type_ptr &world = context.types.get_type("world");
    context.entities.check_type(context.types, l->get_world_name(), world);

    auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::predicate_ptr>(
            [&] (const ast::predicate_ptr &p, class context &context, const type_ptr &default_type) {
                context.predicates.check_predicate_signature(context.types, context.entities, p->get_id(), p->get_terms());
            });

    formulas_and_lists_type_checker::check_list(l->get_predicates(), check_elem, context, context.types.get_type("object"));
}

void initial_states_type_checker::check_state(const ast::finitary_S5_theory &state, context &context) {
    auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::finitary_S5_formula>(
            [&] (const ast::finitary_S5_formula &formula, class context &context, const type_ptr &default_type) {
                initial_states_type_checker::check_formula(formula, context);
            });

    formulas_and_lists_type_checker::check_list(state, check_elem, context, context.types.get_type("entity"));
}

void initial_states_type_checker::check_formula(const ast::finitary_S5_formula &formula, context &context) {
    std::visit([&](auto &&arg) { initial_states_type_checker::check_formula(arg, context); }, formula);
    // todo: check for inconsistent theories -> for all ck_formula_ptr and ck_k_formula_ptr, collect all literals
    //       and check if both p and -p are included there.
}

void initial_states_type_checker::check_formula(const ast::prop_formula_ptr &formula, context &context) {
    formulas_and_lists_type_checker::check_formula(formula->get_formula(), context);
}

void initial_states_type_checker::check_formula(const ast::ck_formula_ptr &formula, context &context) {
    formulas_and_lists_type_checker::check_formula(formula->get_formula(), context);
}

void initial_states_type_checker::check_formula(const ast::ck_k_formula_ptr &formula, context &context) {
    context.entities.check_type(context.types, formula->get_agent(), context.types.get_type("agent"));
    formulas_and_lists_type_checker::check_formula(formula->get_formula(), context);
}

void initial_states_type_checker::check_formula(const ast::ck_kw_formula_ptr &formula, context &context) {
    context.entities.check_type(context.types, formula->get_agent(), context.types.get_type("agent"));
    formulas_and_lists_type_checker::check_formula(formula->get_formula(), context);
}

void initial_states_type_checker::check_formula(const ast::ck_not_kw_formula_ptr &formula, context &context) {
    context.entities.check_type(context.types, formula->get_agent(), context.types.get_type("agent"));
    formulas_and_lists_type_checker::check_formula(formula->get_formula(), context);
}
