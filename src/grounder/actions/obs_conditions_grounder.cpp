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
#include "../../../include/error-manager/epddl_exception.h"
#include <algorithm>
#include <memory>
#include <optional>
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

del::obs_conditions
obs_conditions_grounder::build_obs_conditions(const ast::action_ptr &action, grounder_info &info) {
    const auto &obs_conditions = action->get_obs_conditions();
    del::obs_conditions conditions(info.language->get_agents_number());

    if (not obs_conditions.has_value()) {
        auto basic_conditions = del::agent_obs_conditions{};
        basic_conditions[0] = std::make_shared<del::true_formula>();

        for (del::agent i = 0; i < info.language->get_agents_number(); ++i)
            conditions[i] = basic_conditions;
    } else {
        info.context.entities.push();
        auto action_obs_types = info.context.action_types.get_obs_types(action->get_signature()->get_name());
        info.context.entities.add_decl_list(action_obs_types,
                                            type_checker::either_type{info.context.types.get_type_id("obs-type")});

        info.context.entities.update_typed_entities_sets(info.context.types);

        name_id_map obs_types_ids;
        del::obs_type id = 0;

        for (const ast::identifier_ptr &obs_type_name : action_obs_types)
            obs_types_ids[obs_type_name->get_token().get_lexeme()] = id++;

//        name_vector obs_types_names(obs_types_ids.size());
//
//        for (const auto &[name, t_id] : obs_types_ids)
//            obs_types_names[t_id] = name;

        std::optional<del::obs_type> default_t = std::nullopt;
        obs_conditions_grounder::check_default_obs_cond(*obs_conditions, info, conditions,
                                                        obs_types_ids, default_t);
        obs_conditions_grounder::check_missing_else_cond(*obs_conditions, info, default_t);

        auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
            ast::obs_cond, bool, del::obs_conditions &, const name_id_map &>(
            [&](const ast::obs_cond &obs, grounder_info &info, const type_ptr &default_type,
                del::obs_conditions &conditions, const name_id_map &obs_types_ids) {
                obs_conditions_grounder::build_obs_condition(obs, info, conditions, obs_types_ids);
                return true;
            });

        formulas_and_lists_grounder::build_list<
                ast::obs_cond, bool, del::obs_conditions &, const name_id_map &>(
                *obs_conditions, ground_elem, info, info.context.types.get_type("agent"),
                conditions, obs_types_ids);

        obs_conditions_grounder::assign_default_obs_cond(*obs_conditions, info, conditions, default_t);
        info.context.entities.pop();
    }
    return conditions;
}

void
obs_conditions_grounder::build_obs_condition(const ast::obs_cond &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids) {
    std::visit([&](auto &&arg) {
        obs_conditions_grounder::build_obs_condition(arg, info, conditions, obs_types_ids);
    }, obs_cond);
}

void
obs_conditions_grounder::build_obs_condition(const ast::static_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids) {
    del::obs_type t = obs_types_ids.at(obs_cond->get_obs_type()->get_token().get_lexeme());
    del::agent i = language_grounder::get_term_id(obs_cond->get_agent(), info);

    conditions[i][t] = std::make_shared<del::true_formula>();
}

void
obs_conditions_grounder::build_obs_condition(const ast::if_then_else_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids) {
    del::formula_deque fs;

    obs_conditions_grounder::build_obs_condition(obs_cond->get_if_cond(), info, conditions, obs_types_ids, fs);

    for (const ast::else_if_obs_cond_ptr &ei_obs_cond : obs_cond->get_else_if_conds())
        obs_conditions_grounder::build_obs_condition(ei_obs_cond, info, conditions, obs_types_ids, fs);

    if (obs_cond->get_else_cond().has_value())
        obs_conditions_grounder::build_obs_condition(*obs_cond->get_else_cond(), info, conditions, obs_types_ids, fs);
}

void
obs_conditions_grounder::build_obs_condition(const ast::if_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::formula_deque &fs) {
    const auto &static_obs_cond = obs_cond->get_obs_cond();
    del::obs_type t = obs_types_ids.at(static_obs_cond->get_obs_type()->get_token().get_lexeme());
    del::agent i = language_grounder::get_term_id(static_obs_cond->get_agent(), info);

    del::formula_ptr cond = formulas_and_lists_grounder::build_formula(obs_cond->get_cond(), info);

    conditions[i][t] = cond;
    fs.emplace_back(std::make_shared<del::not_formula>(cond));
}

void
obs_conditions_grounder::build_obs_condition(const ast::else_if_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::formula_deque &fs) {
    const auto &static_obs_cond = obs_cond->get_obs_cond();
    del::obs_type t = obs_types_ids.at(static_obs_cond->get_obs_type()->get_token().get_lexeme());
    del::agent i = language_grounder::get_term_id(static_obs_cond->get_agent(), info);

    del::formula_ptr cond = formulas_and_lists_grounder::build_formula(obs_cond->get_cond(), info);

    del::formula_deque fs_ = fs;
    fs.emplace_back(cond);

    conditions[i][t] = std::make_shared<del::and_formula>(fs_);
    fs.emplace_back(std::make_shared<del::not_formula>(cond));
}

void
obs_conditions_grounder::build_obs_condition(const ast::else_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                             del::formula_deque &fs) {
    del::obs_type t = obs_types_ids.at(obs_cond->get_obs_type()->get_token().get_lexeme());
    del::agent i = language_grounder::get_term_id(obs_cond->get_agent(), info);

    conditions[i][t] = std::make_shared<del::and_formula>(fs);
}

void
obs_conditions_grounder::build_obs_condition(const ast::default_obs_cond_ptr &obs_cond, grounder_info &info,
                                             del::obs_conditions &conditions, const name_id_map &obs_types_ids) {
}

void
obs_conditions_grounder::assign_obs_condition(const ast::obs_cond &obs_cond, grounder_info &info,
                                              del::obs_conditions &conditions, const name_vector &obs_types_names,
                                              del::agent i, del::obs_type t, const del::formula_ptr &f) {
    ast::info token_info = std::visit([&](auto &&arg) { return arg->get_info(); }, obs_cond);

    if (conditions[i].find(t) == conditions[i].end())
        conditions[i][t] = f;
    else
        throw EPDDLException(token_info, "Redeclaration of observability condition for agent '" +
                                          info.language->get_agent_name(i) + "' and observability type '" +
                                          obs_types_names[t] + "'.");
}

void
obs_conditions_grounder::check_default_obs_cond(const ast::list<ast::obs_cond> &obs_conditions, grounder_info &info,
                                                del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                                                std::optional<del::obs_type> &default_t) {
    auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
        ast::obs_cond, bool, std::optional<del::obs_type> &>(
        [&](const ast::obs_cond &obs, grounder_info &info, const type_ptr &default_type,
            std::optional<del::obs_type> &default_t) {
            if (std::holds_alternative<ast::default_obs_cond_ptr>(obs)) {
                const auto &default_obs = std::get<ast::default_obs_cond_ptr>(obs);

                if (default_t.has_value())
                    throw EPDDLException(default_obs->get_info(),
                                         "Redeclaration of default observability condition.");

                const std::string &t_name = default_obs->get_obs_type()->get_token().get_lexeme();
                default_t = obs_types_ids.at(t_name);
            }
            return true;
        });

    formulas_and_lists_grounder::build_list<ast::obs_cond, bool, std::optional<del::obs_type> &>(
            obs_conditions, ground_elem, info,
            info.context.types.get_type("agent"), default_t);
}

void
obs_conditions_grounder::assign_default_obs_cond(const ast::list<ast::obs_cond> &obs_conditions, grounder_info &info,
                                                 del::obs_conditions &conditions,
                                                 std::optional<del::obs_type> &default_t) {
    bool missing_default_cond = default_t == std::nullopt;
    ast::info token_info = std::visit([&](auto &&arg) { return arg->get_info(); }, obs_conditions);

    for (del::agent i = 0; i < info.language->get_agents_number(); ++i)
        if (conditions[i].empty()) {
            if (not missing_default_cond)
                conditions[i][*default_t] = std::make_shared<del::true_formula>();
            else
                throw EPDDLException(token_info, "Missing observability conditions for agent '" +
                                                  info.language->get_agent_name(i) + "'.");
        }
}

void
obs_conditions_grounder::check_missing_else_cond(const ast::list<ast::obs_cond> &obs_conditions, grounder_info &info,
                                                 std::optional<del::obs_type> &default_t) {
    bool missing_default_cond = default_t == std::nullopt;

    auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
        ast::obs_cond, bool>(
        [&](const ast::obs_cond &obs, grounder_info &info, const type_ptr &default_type) {
            if (std::holds_alternative<ast::if_then_else_obs_cond_ptr>(obs)) {
                const auto &ite_obs = std::get<ast::if_then_else_obs_cond_ptr>(obs);

                if (not ite_obs->get_else_cond().has_value() and missing_default_cond)
                    throw EPDDLException(ite_obs->get_info(),
                                         "Ill-formed if-then-else observability condition: missing else statement or default condition.");
            }
            return true;
        });

    formulas_and_lists_grounder::build_list<
            ast::obs_cond, bool>(obs_conditions, ground_elem, info, info.context.types.get_type("agent"));
}
