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

#include "../../include/type-checker/type_checker_helper.h"
#include "../../include/type-checker/domains/domains_type_checker.h"
#include "../../include/type-checker/libraries/act_type_library_type_checker.h"
#include "../../include/type-checker/problems/problems_type_checker.h"
#include "../../include/type-checker/common/requirements_type_checker.h"
#include <memory>
#include <string>
#include <variant>

using namespace epddl::type_checker;

context type_checker_helper::do_semantic_check(const planning_specification &spec,
                                               spec_error_managers &err_managers) {
    const auto &[problem, domain, libraries] = spec;
    context context = build_context(spec, err_managers);

    for (const ast::act_type_library_ptr &library : libraries)
        act_type_library_type_checker::check(library, context,
                                             err_managers.libraries_err_managers.at(
                                                     library->get_name()->get_token().get_lexeme()));

    domains_type_checker::check(domain, context, err_managers.domain_err_manager);
    problems_type_checker::check(problem, context, err_managers.problem_err_manager);
    requirements_type_checker::check(spec, context);

    return context;
}

context type_checker_helper::build_context(const planning_specification &spec,
                                           spec_error_managers &err_managers) {
    const auto &[problem, domain, libraries] = spec;

    auto types_context = build_types_context(domain, err_managers.domain_err_manager);
    auto entities_context = build_entities(spec, types_context, err_managers.domain_err_manager,
                                           err_managers.problem_err_manager);
    entities_context.build_typed_entities_sets(types_context);

    if (entities_context.get_entities_with_type(types_context, "agent").empty())
        err_managers.problem_err_manager->throw_error(error_type::empty_agent_set, problem->get_info());

    auto predicates_context = build_predicate_signatures(
            spec, types_context, entities_context, err_managers.domain_err_manager);
    auto events_context = build_event_signatures(
            spec, types_context, entities_context, err_managers.domain_err_manager);
    auto action_types_context = build_action_type_signatures(
            spec, types_context, entities_context, err_managers.libraries_err_managers);
    auto actions_context = build_action_signatures(
            spec, types_context, entities_context, err_managers.domain_err_manager);

    return context{components_names_context{},
                   std::move(types_context),
                   std::move(entities_context),
                   std::move(predicates_context),
                   std::move(events_context),
                   std::move(actions_context),
                   std::move(action_types_context),
                   requirements_context{}};
}

types_context type_checker_helper::build_types_context(const domain_ptr &domain,
                                                       error_manager_ptr &domain_err_manager) {
    types_context types_context{domain_err_manager};

    const std::string
        root        = ROOT_TYPE_NAME,
        entity      = "entity",
        object      = "object",
        agent       = "agent",
        agent_group = "agent-group",
        world       = "world",
        event       = "event",
        obs_type    = "obs-type";

    types_context.add_reserved_type_decl(root);
    types_context.add_reserved_type_decl(entity,      root);
    types_context.add_reserved_type_decl(object,      entity);
    types_context.add_reserved_type_decl(agent,       entity);
    types_context.add_reserved_type_decl(agent_group, entity);
    types_context.add_reserved_type_decl(world,       root, false);
    types_context.add_reserved_type_decl(event,       root, false);
    types_context.add_reserved_type_decl(obs_type,    root, false);

    ast::typed_identifier_list domain_types;

    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::types_decl_ptr>(item)) {
            const auto &types = std::get<ast::types_decl_ptr>(item)->get_types();
            domain_types.insert(domain_types.end(), types.begin(), types.end());
        }
    }

    domain_err_manager->push_error_info(error_manager::get_error_info(
            decl_type::domain_decl, domain->get_name()->get_token().get_lexeme()));
    domain_err_manager->push_error_info(error_manager::get_error_info(decl_type::types_decl));

    for (const auto &type_decl : domain_types)
        types_context.add_type_decl(domain_err_manager,
                                    type_decl->get_id(), type_decl->get_type());

    domain_err_manager->pop_error_info();
    domain_err_manager->pop_error_info();

    return types_context;
}

entities_context type_checker_helper::build_entities(const planning_specification &spec, types_context &types_context,
                                                     error_manager_ptr &domain_err_manager,
                                                     error_manager_ptr &problem_err_manager) {
    const auto &[problem, domain, libraries] = spec;
    entities_context entities_context;

    const type_ptr &entity      = types_context.get_type("entity");
    const type_ptr &object      = types_context.get_type("object");
    const type_ptr &agent       = types_context.get_type("agent");
    const type_ptr &agent_group = types_context.get_type("agent-group");

    // We add domain constants...
    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::constants_decl_ptr>(item)) {
            const auto &constants = std::get<ast::constants_decl_ptr>(item)->get_constants();

            domain_err_manager->push_error_info(error_manager::get_error_info(
                    decl_type::domain_decl, domain->get_name()->get_token().get_lexeme()));
            domain_err_manager->push_error_info(error_manager::get_error_info(decl_type::constants_decl));

            entities_context.add_decl_list(types_context, domain_err_manager,
                                           constants, object, entity);

            domain_err_manager->pop_error_info();
            domain_err_manager->pop_error_info();
        }
    }
    // ... and problem objects, agents and agent groups to the context
    for (const auto &item: problem->get_items()) {
        if (std::holds_alternative<ast::objects_decl_ptr>(item)) {
            const auto &objects = std::get<ast::objects_decl_ptr>(item)->get_objects();

            problem_err_manager->push_error_info(error_manager::get_error_info(
                    decl_type::problem_decl, problem->get_name()->get_token().get_lexeme()));
            problem_err_manager->push_error_info(error_manager::get_error_info(decl_type::objects_decl));

            entities_context.add_decl_list(types_context, problem_err_manager,
                                           objects, object, object);

            problem_err_manager->pop_error_info();
            problem_err_manager->pop_error_info();
        } else if (std::holds_alternative<ast::agents_decl_ptr>(item)) {
            const auto &agents = std::get<ast::agents_decl_ptr>(item)->get_agents();

            problem_err_manager->push_error_info(error_manager::get_error_info(
                    decl_type::problem_decl, problem->get_name()->get_token().get_lexeme()));
            problem_err_manager->push_error_info(error_manager::get_error_info(decl_type::agents_decl));

            entities_context.add_decl_list(types_context, problem_err_manager,
                                           agents, agent, agent);
            problem_err_manager->pop_error_info();
            problem_err_manager->pop_error_info();
        } else if (std::holds_alternative<ast::agent_groups_decl_ptr>(item)) {
            const auto &agent_groups = std::get<ast::agent_groups_decl_ptr>(item)->get_agent_groups();

            problem_err_manager->push_error_info(error_manager::get_error_info(
                    decl_type::problem_decl, problem->get_name()->get_token().get_lexeme()));

            for (const ast::agent_group_decl_ptr &group : agent_groups) {
                problem_err_manager->push_error_info(error_manager::get_error_info(
                        decl_type::agent_group_decl,
                        group->get_group_name()->get_token().get_lexeme()));

                entities_context.add_agent_group(types_context, problem_err_manager, group);
                problem_err_manager->pop_error_info();
                problem_err_manager->pop_error_info();
            }
        }
    }

    return entities_context;
}

predicates_context type_checker_helper::build_predicate_signatures(const planning_specification &spec,
                                                                   types_context &types_context,
                                                                   entities_context &entities_context,
                                                                   error_manager_ptr &domain_err_manager) {
    const auto &[problem, domain, libraries] = spec;
    predicates_context predicates_context{domain_err_manager};

    domain_err_manager->push_error_info(error_manager::get_error_info(
            decl_type::domain_decl, domain->get_name()->get_token().get_lexeme()));

    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::domain_predicates_ptr>(item)) {
            const auto &predicates = std::get<ast::domain_predicates_ptr>(item)->get_predicate_decl_list();

            for (const auto &predicate_decl : predicates) {
                domain_err_manager->push_error_info(error_manager::get_error_info(
                        decl_type::predicate_decl,
                        predicate_decl->get_name()->get_token().get_lexeme()));
                predicates_context.add_decl_predicate(types_context, entities_context, predicate_decl);
                domain_err_manager->pop_error_info();
            }
        }
    }

    domain_err_manager->pop_error_info();
    return predicates_context;
}

events_context type_checker_helper::build_event_signatures(const planning_specification &spec,
                                                           types_context &types_context,
                                                           entities_context &entities_context,
                                                           error_manager_ptr &domain_err_manager) {
    const auto &[problem, domain, libraries] = spec;
    events_context events_context{domain_err_manager};

    domain_err_manager->push_error_info(error_manager::get_error_info(
            decl_type::domain_decl, domain->get_name()->get_token().get_lexeme()));

    for (const auto &item: domain->get_items())
        if (std::holds_alternative<ast::event_ptr>(item)) {
            auto event_decl = std::get<ast::event_ptr>(item);
            const std::string
                event_name = event_decl->get_name()->get_token().get_lexeme(),
                err_info = error_manager::get_error_info(decl_type::event_params_decl, event_name);

            domain_err_manager->push_error_info(err_info);
            events_context.add_decl_event(types_context, entities_context, event_decl);
            domain_err_manager->pop_error_info();
        }

    domain_err_manager->pop_error_info();
    return events_context;
}

action_types_context type_checker_helper::build_action_type_signatures(const planning_specification &spec,
                                                                       types_context &types_context,
                                                                       entities_context &entities_context,
                                                                       error_manager_map &library_err_managers) {
    const auto &[problem, domain, libraries] = spec;
    action_types_context action_types_context;

    // Adding default action type, corresponding to atomic public actions
    action_types_context.add_decl_action_type(types_context, "basic");

    for (const ast::act_type_library_ptr &library : libraries) {
        const std::string &library_name = library->get_name()->get_token().get_lexeme();
        error_manager_ptr lib_err_manager = library_err_managers.at(library_name);

        // We already checked for duplicate library names, so we can safely assume each library has a unique name
        lib_err_manager->push_error_info(error_manager::get_error_info(
                decl_type::library_decl, library_name));

        for (const auto &item: library->get_items())
            if (std::holds_alternative<ast::action_type_ptr>(item)) {
                auto action_type_decl = std::get<ast::action_type_ptr>(item);
                const std::string action_type_name = action_type_decl->get_name()->get_token().get_lexeme();

                action_types_context.add_decl_action_type(types_context, entities_context, lib_err_manager,
                                                          library->get_name(), action_type_decl);
            }

        lib_err_manager->pop_error_info();
    }
    return action_types_context;
}

actions_context type_checker_helper::build_action_signatures(const planning_specification &spec,
                                                             types_context &types_context,
                                                             entities_context &entities_context,
                                                             error_manager_ptr &domain_err_manager) {
    const auto &[problem, domain, libraries] = spec;
    actions_context actions_context{domain_err_manager};

    domain_err_manager->push_error_info(error_manager::get_error_info(
            decl_type::domain_decl, domain->get_name()->get_token().get_lexeme()));

    for (const auto &item: domain->get_items())
        if (std::holds_alternative<ast::action_ptr>(item)) {
            auto action_decl = std::get<ast::action_ptr>(item);
            const std::string
                action_name = action_decl->get_name()->get_token().get_lexeme(),
                err_info = error_manager::get_error_info(decl_type::action_params_decl, action_name);

            domain_err_manager->push_error_info(err_info);
            actions_context.add_decl_action(types_context, entities_context, action_decl);
            domain_err_manager->pop_error_info();
        }

    domain_err_manager->pop_error_info();
    return actions_context;
}
