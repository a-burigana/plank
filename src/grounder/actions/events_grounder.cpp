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

    for (const auto &[var_name, id] : vars_ids)
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
        ast::postcondition, std::pair<del::atom, del::formula_ptr>>(
        [&](const ast::postcondition &post, const class context &context, const type_ptr &types_tree,
            const type_ptr &default_type, variables_assignment &assignment,
            const del::atom_set &static_atoms, const del::language_ptr &language) {
            return events_grounder::build_postcondition(post, context, types_tree, assignment, static_atoms, language);
        });

    auto post_pairs = formulas_and_lists_grounder::build_list<
            ast::postcondition, std::pair<del::atom, del::formula_ptr>>(
            *event->get_postconditions(), ground_elem, context, types_tree,
            type_utils::find(types_tree, "object"), assignment, static_atoms, language);

    del::event_post post;

    for (auto &[p, p_post] : post_pairs)
        post[p] = std::move(p_post);

    return post;
}

std::pair<del::atom, del::formula_ptr>
events_grounder::build_postcondition(const ast::postcondition &post, const context &context, const type_ptr &types_tree,
                                     variables_assignment &assignment, const del::atom_set &static_atoms,
                                     const del::language_ptr &language) {

    return std::pair<del::atom, del::formula_ptr>{0, del::formula_ptr{}};
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
