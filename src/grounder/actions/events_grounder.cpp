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

std::pair<del::preconditions, del::postconditions>
events_grounder::build_pre_post(const ast::action_ptr &action, grounder_info &info) {
    del::preconditions pre;
    del::postconditions post;

    for (const ast::event_signature_ptr &e : action->get_signature()->get_events()) {
        auto [e_pre, e_post] = events_grounder::build_event_pre_post(
                info.context.events.get_event_decl(e->get_name()), e, info);

        pre.emplace_back(std::move(e_pre));
        post.emplace_back(std::move(e_post));
    }

    return {std::move(pre), std::move(post)};
}

std::pair<del::formula_ptr, del::event_post>
events_grounder::build_event_pre_post(const ast::event_ptr &event, const ast::event_signature_ptr &sign,
                                      grounder_info &info) {
    if (event->get_params().has_value()) {
        info.context.entities.push();
        info.context.entities.add_decl_list(info.context.types, info.err_managers.domain_err_manager,
                *event->get_params(), info.context.types.get_type("entity"), true);

        info.context.entities.update_typed_entities_sets(info.context.types);

        name_id_map vars_ids;

        // We associate to each variable in the parameters of the event declaration the id of its
        // corresponding actual parameter passed in the event signature
        for (auto [sign_term, event_var] = std::tuple{sign->get_params().begin(), event->get_params()->begin()};
             sign_term != sign->get_params().end(); ++sign_term, ++event_var) {
            // We internally rename the variables with fresh names to avoid clashes with action parameters variables
            const std::string &var_name = (*event_var)->get_var()->get_token().get_lexeme();
            vars_ids[scope::get_fresh_variable_name(var_name)] =
                    language_grounder::get_term_id(*sign_term, info);
        }

        typed_var_list typed_vars = events_grounder::get_fresh_params_name(event, info.context.events);
        combination combination;

        for (const auto &[var_name, id]: vars_ids)
            combination.emplace_back(id);

        info.assignment.push(typed_vars, combination);
    }

    del::formula_ptr pre = events_grounder::build_event_precondition(event, info);
    del::event_post post = events_grounder::build_event_postconditions(event, info);

    if (event->get_params().has_value()) {
        info.assignment.pop();
        info.context.entities.pop();
    }
    return {std::move(pre), std::move(post)};
}

del::formula_ptr
events_grounder::build_event_precondition(const ast::event_ptr &event, grounder_info &info) {
    if (not event->get_precondition().has_value())
        return std::make_shared<del::true_formula>();

    return formulas_and_lists_grounder::build_formula(*event->get_precondition(), info);
}

del::event_post
events_grounder::build_event_postconditions(const ast::event_ptr &event, grounder_info &info) {
    if (not event->get_postconditions().has_value())
        return del::event_post{};

    auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
        ast::postcondition, bool, atom_conditions &>(
        [&](const ast::postcondition &post, grounder_info &info, const type_ptr &default_type,
                atom_conditions &conditions) {
            events_grounder::build_postcondition(post, info, conditions);
            return true;
        });

    atom_conditions conditions(info.language->get_atoms_number());

    formulas_and_lists_grounder::build_list<
            ast::postcondition, bool, atom_conditions &>(
            *event->get_postconditions(), ground_elem, info,
            info.context.types.get_type("object"), conditions);

    del::event_post post;

    for (del::atom p = 0; p < info.language->get_atoms_number(); ++p)
        if (conditions[p].size() == 1)
            post[p] = std::move(conditions[p].front());
        else if (conditions[p].size() > 1)
            post[p] = std::make_shared<del::and_formula>(std::move(conditions[p]));

    return post;
}

void events_grounder::build_postcondition(const ast::postcondition &post, grounder_info &info,
                                          atom_conditions &conditions) {
    std::visit([&](auto &&arg) {
        events_grounder::build_postcondition(arg, info, conditions);
    }, post);
}

void events_grounder::build_postcondition(const ast::literal_postcondition_ptr &post, grounder_info &info,
                                          atom_conditions &conditions) {
    const ast::literal_ptr &l = post->get_literal();
    unsigned long p_id = language_grounder::get_predicate_id(l->get_predicate(), info);

    if (l->is_positive())
        conditions[p_id].emplace_back(std::make_shared<del::true_formula>());
    else
        conditions[p_id].emplace_back(std::make_shared<del::false_formula>());
}

void events_grounder::build_postcondition(const ast::when_postcondition_ptr &post, grounder_info &info,
                                          atom_conditions &conditions) {
    literal_list ground_literals =
            events_grounder::build_literals(post->get_literals(), info);
    del::formula_ptr cond =
            formulas_and_lists_grounder::build_formula(post->get_cond(), info);
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

void events_grounder::build_postcondition(const ast::iff_postcondition_ptr &post, grounder_info &info,
                                          atom_conditions &conditions) {
    literal_list ground_literals = events_grounder::build_literals(post->get_literals(), info);
    del::formula_ptr cond = formulas_and_lists_grounder::build_formula(post->get_cond(), info);
    del::formula_ptr not_cond = std::make_shared<del::not_formula>(cond);

    for (const auto &[is_positive, p] : ground_literals)
        if (is_positive)
            conditions[p].emplace_back(cond);
        else
            conditions[p].emplace_back(not_cond);
}

events_grounder::literal_list
events_grounder::build_literals(const ast::list<ast::literal_ptr> &literals, grounder_info &info) {
    auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
        ast::literal_ptr, literal>(
        [&](const ast::literal_ptr &l, grounder_info &info, const type_ptr &default_type) {
            del::atom p = language_grounder::get_predicate_id(l->get_predicate(), info);
            return literal{l->is_positive(), p};
        });

    return formulas_and_lists_grounder::build_list<
            ast::literal_ptr, literal>(literals, ground_elem, info, info.context.types.get_type("object"));
}

typed_var_list events_grounder::get_fresh_params_name(const ast::event_ptr &event,
                                                      const events_context &events) {
    const typed_var_list &typed_vars = events.get_formal_param_types_event(event->get_name());
    typed_var_list fresh_type_vars;

    for (auto &[var_name, var_type] : typed_vars)
        fresh_type_vars.emplace_back(scope::get_fresh_variable_name(var_name), var_type);

    return fresh_type_vars;
}
