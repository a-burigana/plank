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

#include "../../../../include/lib/grounder/actions/obs_conditions_grounder.h"
#include "../../../../include/lib/grounder/formulas/formulas_and_lists_grounder.h"
#include "../../../../include/lib/error-manager/epddl_exception.h"
#include <algorithm>
#include <memory>
#include <optional>
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

del::obs_conditions
obs_conditions_grounder::build_obs_conditions(const ast::action_ptr &action, grounder_info &info,
                                              const std::string &ground_action_name) {
    const auto &obs_conditions = action->get_obs_conditions();
    del::obs_conditions conditions(info.language->get_agents_number());

    if (not obs_conditions.has_value()) {
        auto basic_conditions = del::agent_obs_conditions{};
        basic_conditions[0] = std::make_shared<del::true_formula>();

        for (del::agent i = 0; i < info.language->get_agents_number(); ++i)
            conditions[i] = basic_conditions;
    } else {
        info.context.entities.push();
        auto action_obs_types = info.context.action_types.get_obs_types(
                info.err_managers.domain_err_manager, action->get_signature()->get_name());

        info.context.entities.add_decl_list(info.err_managers.domain_err_manager, action_obs_types,
                                            type_checker::either_type{info.context.types.get_type_id("obs-type")});

        info.context.entities.update_typed_entities_sets(info.context.types);

        name_vector obs_types_names;
        name_id_map obs_types_ids;

        for (const ast::identifier_ptr &obs_type_name : action_obs_types) {
            obs_types_names.emplace_back(obs_type_name->get_token().get_lexeme());
            obs_types_ids[obs_type_name->get_token().get_lexeme()] = obs_types_names.size() - 1;
        }

        const std::string
            &action_name = action->get_name()->get_token().get_lexeme(),
            &default_t_name = info.context.actions.get_default_obs_type(action_name);

        auto default_t = default_t_name.empty()
                ? std::optional<del::obs_type>{std::nullopt}
                : obs_types_ids.at(default_t_name);

        info.err_managers.domain_err_manager->push_error_info(
                error_manager::get_error_info(decl_type::ground_action, ground_action_name));

        auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
            ast::obs_cond, bool, del::obs_conditions &, const name_id_map &>(
            [&](const ast::obs_cond &obs, grounder_info &info, const type_ptr &default_type,
                del::obs_conditions &conditions, const name_id_map &obs_types_ids) {
                obs_conditions_grounder::build_obs_condition(obs, info, conditions, obs_types_ids,
                                                             obs_types_names, default_t);
                return true;
            });

        formulas_and_lists_grounder::build_list<
                ast::obs_cond, bool, del::obs_conditions &, const name_id_map &>(
                *obs_conditions, ground_elem, info, info.context.types.get_type("agent"),
                conditions, obs_types_ids);

        obs_conditions_grounder::assign_default_obs_cond(info, conditions, default_t);

        info.err_managers.domain_err_manager->pop_error_info();
        info.context.entities.pop();
    }
    return conditions;
}

void
obs_conditions_grounder::build_obs_condition(const ast::obs_cond &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             const name_vector &obs_types_names,
                                             const std::optional<del::obs_type> default_t) {
    std::visit([&](auto &&arg) {
        obs_conditions_grounder::build_obs_condition(arg, info, conditions, obs_types_ids,
                                                     obs_types_names, default_t);
    }, obs_cond);
}

void
obs_conditions_grounder::build_obs_condition(const ast::static_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             const name_vector &obs_types_names,
                                             const std::optional<del::obs_type> default_t) {
    del::obs_type t = obs_types_ids.at(obs_cond->get_obs_type()->get_token().get_lexeme());
    del::agent i = language_grounder::get_term_id(obs_cond->get_agent(), info);

    obs_conditions_grounder::assign_obs_cond(info, conditions, i, t,
                                             std::make_shared<del::true_formula>(), obs_types_names);
}

void
obs_conditions_grounder::build_obs_condition(const ast::if_then_else_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             const name_vector &obs_types_names,
                                             const std::optional<del::obs_type> default_t) {
    del::formula_deque fs;
    del::agent i = language_grounder::get_term_id(obs_cond->get_agent(), info);;

    obs_conditions_grounder::build_obs_condition(obs_cond->get_if_cond(), info, conditions, i,
                                                 obs_types_ids, obs_types_names, default_t, fs);

    for (const ast::else_if_obs_cond_ptr &ei_obs_cond : obs_cond->get_else_if_conds())
        obs_conditions_grounder::build_obs_condition(ei_obs_cond, info, conditions, i,
                                                     obs_types_ids, obs_types_names, default_t, fs);

    obs_conditions_grounder::build_obs_condition(obs_cond->get_else_cond(), info, conditions, i,
                                                 obs_types_ids, obs_types_names, default_t, fs);
}

void
obs_conditions_grounder::build_obs_condition(const ast::if_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const del::agent i,
                                             const name_id_map &obs_types_ids, const name_vector &obs_types_names,
                                             const std::optional<del::obs_type> default_t, del::formula_deque &fs) {
    del::obs_type t = obs_types_ids.at(obs_cond->get_obs_type()->get_token().get_lexeme());
    del::formula_ptr cond = formulas_and_lists_grounder::build_formula(obs_cond->get_cond(), info);

    obs_conditions_grounder::assign_obs_cond(info, conditions, i, t,
                                             cond, obs_types_names);
    fs.emplace_back(std::make_shared<del::not_formula>(cond));
}

void
obs_conditions_grounder::build_obs_condition(const ast::else_if_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const del::agent i,
                                             const name_id_map &obs_types_ids, const name_vector &obs_types_names,
                                             const std::optional<del::obs_type> default_t, del::formula_deque &fs) {
    del::obs_type t = obs_types_ids.at(obs_cond->get_obs_type()->get_token().get_lexeme());

    del::formula_ptr cond = formulas_and_lists_grounder::build_formula(obs_cond->get_cond(), info);

    del::formula_deque fs_ = fs;
    fs.emplace_back(cond);

    obs_conditions_grounder::assign_obs_cond(info, conditions, i, t,
                                             std::make_shared<del::and_formula>(fs_), obs_types_names);
    fs.emplace_back(std::make_shared<del::not_formula>(cond));
}

void
obs_conditions_grounder::build_obs_condition(const std::optional<ast::else_obs_cond_ptr> &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const del::agent i,
                                             const name_id_map &obs_types_ids, const name_vector &obs_types_names,
                                             const std::optional<del::obs_type> default_t, del::formula_deque &fs) {
    del::formula_ptr else_cond = fs.size() == 1
            ? fs.front()
            : std::make_shared<del::and_formula>(fs);

    if (obs_cond.has_value()) {
        del::obs_type t = obs_types_ids.at((*obs_cond)->get_obs_type()->get_token().get_lexeme());
        obs_conditions_grounder::assign_obs_cond(info, conditions,
                                                 i, t,else_cond, obs_types_names);
    } else if (default_t.has_value())
        obs_conditions_grounder::assign_obs_cond(info, conditions,
                                                 i, *default_t,else_cond, obs_types_names);
}

void
obs_conditions_grounder::build_obs_condition(const ast::default_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             const name_vector &obs_types_names,
                                             const std::optional<del::obs_type> default_t) {
}

void
obs_conditions_grounder::assign_obs_cond(grounder_info &info, del::obs_conditions &conditions,
                                         del::agent i, del::obs_type t, const del::formula_ptr &cond,
                                         const name_vector &obs_types_names) {
    if (conditions[i].find(t) == conditions[i].end())
        conditions[i][t] = cond;
    else if (not del::formulas_utils::are_equal(conditions[i].at(t), cond)) {
        info.err_managers.domain_err_manager->throw_error(
                error_type::agent_obs_cond_redeclaration,
                std::vector<std::string>{info.language->get_agent_name(i),
                                         obs_types_names[t]});
    }
}

void
obs_conditions_grounder::assign_default_obs_cond(grounder_info &info, del::obs_conditions &conditions,
                                                 std::optional<del::obs_type> &default_t) {
    bool missing_default_cond = default_t == std::nullopt;

    for (del::agent i = 0; i < info.language->get_agents_number(); ++i)
        if (conditions[i].empty()) {
            if (not missing_default_cond and                                   // Checking that we have not already assigned
                conditions[i].find(*default_t) == conditions[i].end())      //  this due to a missing else-condition
                conditions[i][*default_t] = std::make_shared<del::true_formula>();
            else {
                if (missing_default_cond)
                    info.err_managers.domain_err_manager->throw_error(
                            error_type::missing_agent_obs_cond_no_default,
                            std::vector<std::string>{info.language->get_agent_name(i)});
                else
                    info.err_managers.domain_err_manager->throw_error(
                            error_type::missing_agent_obs_cond,
                            std::vector<std::string>{info.language->get_agent_name(i)});
            }
        }
}
