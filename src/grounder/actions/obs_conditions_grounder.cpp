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

#include "../../../include/grounder/actions/obs_conditions_grounder.h"
#include "../../../include/grounder/formulas/formulas_and_lists_grounder.h"
#include <memory>
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

del::obs_conditions
obs_conditions_grounder::build_obs_conditions(const std::optional<ast::list<ast::obs_cond>> &obs_conditions,
                                              const context &context, const type_ptr &types_tree,
                                              variables_assignment &assignment, const del::atom_set &static_atoms,
                                              const del::language_ptr &language, const name_id_map &obs_types_ids) {
    del::obs_conditions conditions(language->get_agents_number());

    if (not obs_conditions.has_value()) {
        auto basic_conditions = del::agent_obs_conditions{};
        basic_conditions[0] = std::make_shared<del::true_formula>();

        for (del::agent i = 0; i < language->get_agents_number(); ++i)
            conditions[i] = basic_conditions;
    } else {
        auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
            ast::obs_cond, bool, del::obs_conditions &, const name_id_map &, del::obs_type &>(
            [&](const ast::obs_cond &obs, const class context &context, const type_ptr &types_tree,
                const type_ptr &default_type, variables_assignment &assignment,
                const del::atom_set &static_atoms, const del::language_ptr &language,
                del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                del::obs_type &default_t) {
                obs_conditions_grounder::build_obs_condition(obs, context, types_tree, assignment,
                                                             static_atoms, language, conditions,
                                                             obs_types_ids, default_t);
                return true;
            });

        for (del::agent i = 0; i < language->get_agents_number(); ++i)
            conditions[i] = del::agent_obs_conditions{};

        del::obs_type default_t = 0;

        formulas_and_lists_grounder::build_list<
                ast::obs_cond, bool, del::obs_conditions &, const name_id_map &, del::obs_type &>(
                *obs_conditions, ground_elem, context, types_tree, type_utils::find(types_tree, "agent"),
                assignment, static_atoms, language, conditions, obs_types_ids, default_t);

        for (del::agent i = 0; i < language->get_agents_number(); ++i)
            if (conditions[i].empty())
                conditions[i][default_t] = std::make_shared<del::true_formula>();
    }
    return conditions;
}

void
obs_conditions_grounder::build_obs_condition(const ast::obs_cond &obs_cond, const context &context,
                                             const type_ptr &types_tree, variables_assignment &assignment,
                                             const del::atom_set &static_atoms, const del::language_ptr &language,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::obs_type &default_t) {
    std::visit([&](auto &&arg) {
        obs_conditions_grounder::build_obs_condition(arg, context, types_tree, assignment, static_atoms,
                                                     language, conditions, obs_types_ids, default_t);
    }, obs_cond);
}

void
obs_conditions_grounder::build_obs_condition(const ast::static_obs_cond_ptr &obs_cond, const context &context,
                                             const type_ptr &types_tree, variables_assignment &assignment,
                                             const del::atom_set &static_atoms, const del::language_ptr &language,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::obs_type &default_t) {
    del::obs_type t = obs_types_ids.at(obs_cond->get_obs_type()->get_token().get_lexeme());
    del::agent i = language_grounder::get_term_id(obs_cond->get_agent(), context.entities, assignment);

    conditions[i][t] = std::make_shared<del::true_formula>();
}

void
obs_conditions_grounder::build_obs_condition(const ast::if_then_else_obs_cond_ptr &obs_cond, const context &context,
                                             const type_ptr &types_tree, variables_assignment &assignment,
                                             const del::atom_set &static_atoms, const del::language_ptr &language,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::obs_type &default_t) {
    del::formula_deque fs;

    obs_conditions_grounder::build_obs_condition(obs_cond->get_if_cond(), context, types_tree, assignment,
                                                 static_atoms, language, conditions, obs_types_ids, fs);

    for (const ast::else_if_obs_cond_ptr &ei_obs_cond : obs_cond->get_else_if_conds())
        obs_conditions_grounder::build_obs_condition(ei_obs_cond, context, types_tree, assignment,
                                                     static_atoms, language, conditions, obs_types_ids, fs);

    if (obs_cond->get_else_cond().has_value())
        obs_conditions_grounder::build_obs_condition(*obs_cond->get_else_cond(), context, types_tree, assignment,
                                                     static_atoms, language, conditions, obs_types_ids, fs);
}

void
obs_conditions_grounder::build_obs_condition(const ast::if_obs_cond_ptr &obs_cond, const context &context,
                                             const type_ptr &types_tree, variables_assignment &assignment,
                                             const del::atom_set &static_atoms, const del::language_ptr &language,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::formula_deque &fs) {
    const auto &static_obs_cond = obs_cond->get_obs_cond();
    del::obs_type t = obs_types_ids.at(static_obs_cond->get_obs_type()->get_token().get_lexeme());
    del::agent i = language_grounder::get_term_id(static_obs_cond->get_agent(), context.entities, assignment);

    del::formula_ptr cond = formulas_and_lists_grounder::build_formula(
            obs_cond->get_cond(), context, types_tree, assignment, static_atoms, language);

    conditions[i][t] = cond;
    fs.emplace_back(std::make_shared<del::not_formula>(cond));
}

void
obs_conditions_grounder::build_obs_condition(const ast::else_if_obs_cond_ptr &obs_cond, const context &context,
                                             const type_ptr &types_tree, variables_assignment &assignment,
                                             const del::atom_set &static_atoms, const del::language_ptr &language,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::formula_deque &fs) {
    const auto &static_obs_cond = obs_cond->get_obs_cond();
    del::obs_type t = obs_types_ids.at(static_obs_cond->get_obs_type()->get_token().get_lexeme());
    del::agent i = language_grounder::get_term_id(static_obs_cond->get_agent(), context.entities, assignment);

    del::formula_ptr cond = formulas_and_lists_grounder::build_formula(
            obs_cond->get_cond(), context, types_tree, assignment, static_atoms, language);

    del::formula_deque fs_ = fs;
    fs.emplace_back(cond);

    conditions[i][t] = std::make_shared<del::and_formula>(fs_);
    fs.emplace_back(std::make_shared<del::not_formula>(cond));
}

void
obs_conditions_grounder::build_obs_condition(const ast::else_obs_cond_ptr &obs_cond, const context &context,
                                             const type_ptr &types_tree, variables_assignment &assignment,
                                             const del::atom_set &static_atoms, const del::language_ptr &language,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::formula_deque &fs) {
    del::obs_type t = obs_types_ids.at(obs_cond->get_obs_type()->get_token().get_lexeme());
    del::agent i = language_grounder::get_term_id(obs_cond->get_agent(), context.entities, assignment);

    conditions[i][t] = std::make_shared<del::and_formula>(fs);
}

void
obs_conditions_grounder::build_obs_condition(const ast::default_obs_cond_ptr &obs_cond, const context &context,
                                             const type_ptr &types_tree, variables_assignment &assignment,
                                             const del::atom_set &static_atoms, const del::language_ptr &language,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::obs_type &default_t) {
    const std::string &t_name = obs_cond->get_obs_type()->get_token().get_lexeme();
    default_t = obs_types_ids.at(t_name);
}
