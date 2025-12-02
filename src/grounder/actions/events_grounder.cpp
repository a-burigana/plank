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

#include "../../../include/grounder/actions/events_grounder.h"
#include "../../../include/grounder/language_grounder.h"
#include "../../../include/grounder/formulas/formulas_and_lists_grounder.h"
#include <memory>
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

std::pair<del::formula_ptr, del::event_post>
events_grounder::build_event(const ast::event_ptr &event, const ast::event_signature_ptr &sign,
                             const context &context, const type_ptr &types_tree, variables_assignment &assignment,
                             const del::atom_set &static_atoms, const del::language_ptr &language) {
    name_id_map vars_ids;

    // We associate to each variable in the parameters of the event declaration the id of its
    // corresponding actual parameter passed in the event signature
    if (event->get_params().has_value())
        for (auto [sign_term, event_var] = std::tuple{sign->get_params().begin(), event->get_params()->begin()};
             sign_term != sign->get_params().end(); ++sign_term, ++event_var)
            vars_ids[(*event_var)->get_var()->get_token().get_lexeme()] =
                    language_grounder::get_term_id(*sign_term, context.entities, assignment);

    // We internally rename the variables with fresh names to avoid clashes with action parameters variables
    typed_var_list typed_vars = events_grounder::build_reserved_params(event, context.events);
    combination combination;

    for (const auto &[var_name, id]: vars_ids)
        combination.emplace_back(id);

    assignment.push(typed_vars, combination);

    del::formula_ptr pre = events_grounder::build_event_precondition(
            event, context, types_tree, assignment, static_atoms, language);

    del::event_post post;

    assignment.pop();
    return {std::move(pre), std::move(post)};
}

del::formula_ptr
events_grounder::build_event_precondition(const ast::event_ptr &event, const context &context,
                                          const type_ptr &types_tree, variables_assignment &assignment,
                                          const del::atom_set &static_atoms, const del::language_ptr &language) {
    if (not event->get_precondition().has_value())
        return std::make_shared<del::true_formula>();

    return formulas_and_lists_grounder::build_formula(
            *event->get_precondition(), context, types_tree, assignment, static_atoms, language);
}

del::event_post
events_grounder::build_event_postconditions(const ast::event_ptr &event, const context &context,
                                            const type_ptr &types_tree, variables_assignment &assignment,
                                            const del::atom_set &static_atoms, const del::language_ptr &language) {
    if (not event->get_postconditions().has_value())
        return del::event_post{};

    auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
        ast::postcondition, bool, atom_conditions &>(
        [&](const ast::postcondition &post, const class context &context, const type_ptr &types_tree,
            const type_ptr &default_type, variables_assignment &assignment,
            const del::atom_set &static_atoms, const del::language_ptr &language, atom_conditions &conditions) {
            events_grounder::build_postcondition(post, context, types_tree, assignment, static_atoms, language,
                                                 conditions);
            return true;
        });

    atom_conditions conditions(language->get_atoms_number());

    formulas_and_lists_grounder::build_list<
            ast::postcondition, bool, atom_conditions &>(
            *event->get_postconditions(), ground_elem, context, types_tree,
            type_utils::find(types_tree, "object"), assignment, static_atoms, language, conditions);

    del::event_post post;

    for (del::atom p = 0; p < language->get_atoms_number(); ++p)
        if (conditions[p].size() == 1)
            post[p] = std::move(conditions[p].front());
        else if (conditions[p].size() > 1)
            post[p] = std::make_shared<del::and_formula>(std::move(conditions[p]));

    return post;
}

void events_grounder::build_postcondition(const ast::postcondition &post, const context &context,
                                          const type_ptr &types_tree, variables_assignment &assignment,
                                          const del::atom_set &static_atoms, const del::language_ptr &language,
                                          atom_conditions &conditions) {
    std::visit([&](auto &&arg) {
        events_grounder::build_postcondition(arg, context, types_tree, assignment,
                                             static_atoms, language, conditions);
    },post);
}

void
events_grounder::build_postcondition(const ast::literal_postcondition_ptr &post, const context &context,
                                     const type_ptr &types_tree, variables_assignment &assignment,
                                     const del::atom_set &static_atoms, const del::language_ptr &language,
                                     atom_conditions &conditions) {
    const ast::literal_ptr &l = post->get_literal();
    unsigned long p_id = language_grounder::get_predicate_id(l->get_predicate(), assignment, language);

    if (l->is_positive())
        conditions[p_id].emplace_back(std::make_shared<del::true_formula>());
    else
        conditions[p_id].emplace_back(std::make_shared<del::false_formula>());
}

void
events_grounder::build_postcondition(const ast::when_postcondition_ptr &post, const context &context,
                                     const type_ptr &types_tree, variables_assignment &assignment,
                                     const del::atom_set &static_atoms, const del::language_ptr &language,
                                     atom_conditions &conditions) {
    literal_list ground_literals =
            events_grounder::build_literals(post->get_literals(), context, types_tree,
                                            assignment, static_atoms, language);
    del::formula_ptr cond =
            formulas_and_lists_grounder::build_formula(post->get_cond(), context, types_tree,
                                                       assignment, static_atoms, language);
    del::formula_ptr not_cond = std::make_shared<del::not_formula>(cond);

    for (const auto &[is_positive, p] : ground_literals) {
        auto p_formula = std::make_shared<del::atom_formula>(p);

        if (is_positive)
            conditions[p].emplace_back(
                    std::make_shared<del::or_formula>(del::formula_deque{p_formula, cond}));
        else
            conditions[p].emplace_back(
                    std::make_shared<del::and_formula>(del::formula_deque{p_formula, not_cond}));
    }
}

void
events_grounder::build_postcondition(const ast::iff_postcondition_ptr &post, const context &context,
                                     const type_ptr &types_tree, variables_assignment &assignment,
                                     const del::atom_set &static_atoms, const del::language_ptr &language,
                                     atom_conditions &conditions) {
    literal_list ground_literals =
            events_grounder::build_literals(post->get_literals(), context, types_tree,
                                            assignment, static_atoms, language);
    del::formula_ptr cond =
            formulas_and_lists_grounder::build_formula(post->get_cond(), context, types_tree,
                                                       assignment, static_atoms, language);
    del::formula_ptr not_cond = std::make_shared<del::not_formula>(cond);

    for (const auto &[is_positive, p] : ground_literals)
        if (is_positive)
            conditions[p].emplace_back(cond);
        else
            conditions[p].emplace_back(not_cond);
}

events_grounder::literal_list
events_grounder::build_literals(const ast::list<ast::literal_ptr> &literals, const context &context,
                                const type_ptr &types_tree, variables_assignment &assignment,
                                const del::atom_set &static_atoms, const del::language_ptr &language) {
    auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
        ast::literal_ptr, literal>(
        [&](const ast::literal_ptr &l, const class context &context, const type_ptr &types_tree,
            const type_ptr &default_type, variables_assignment &assignment,
            const del::atom_set &static_atoms, const del::language_ptr &language) {
            del::atom p = language_grounder::get_predicate_id(l->get_predicate(), assignment, language);
            return literal{l->is_positive(), p};
        });

    return formulas_and_lists_grounder::build_list<
            ast::literal_ptr, literal>(
            literals, ground_elem, context, types_tree,
            type_utils::find(types_tree, "object"), assignment, static_atoms, language);
}

typed_var_list events_grounder::build_reserved_params(const ast::event_ptr &event,
                                                      const events_context &events) {
    typed_var_list typed_vars = events.get_formal_param_types_event(event->get_name());

    for (auto &[var_name, _] : typed_vars)
        var_name = events_grounder::build_reserved_name(var_name);

    return typed_vars;
}

std::string events_grounder::build_reserved_name(const std::string &name) {
    return ";" + name;
}
