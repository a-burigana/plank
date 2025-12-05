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

context type_checker_helper::do_semantic_check(const planning_specification &spec) {
    const auto &[problem, domain, libraries] = spec;

    types_context types_context = build_types_context(spec);
    context context = build_context(spec, types_context);

    for (const ast::act_type_library_ptr &library : libraries)
        act_type_library_type_checker::check(library, context);

    domains_type_checker::check(domain, context);
    problems_type_checker::check(problem, context);
    requirements_type_checker::check(spec, context);

    return context;
}

types_context type_checker_helper::build_types_context(const planning_specification &spec) {
    const auto &[problem, domain, libraries] = spec;
    types_context types_context;

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
    types_context.add_reserved_type_decl(agent_group, root);
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

    for (const auto &type_decl : domain_types)
        types_context.add_type_decl(type_decl->get_id(), type_decl->get_type());

    return types_context;
}

context type_checker_helper::build_context(const planning_specification &spec, types_context types_context) {
    context context;
    context.types = std::move(types_context);

    build_entities(spec, context);
    context.entities.build_typed_entities_sets(context.types);

    build_predicate_signatures(spec, context);
    build_action_type_signatures(spec, context);
    build_event_signatures(spec, context);
    build_action_signatures(spec, context);

    return context;
}

void type_checker_helper::build_entities(const planning_specification &spec, context &context) {
    const auto &[problem, domain, libraries] = spec;

    const type_ptr &entity      = context.types.get_type("entity");
    const type_ptr &object      = context.types.get_type("object");
    const type_ptr &agent       = context.types.get_type("agent");
    const type_ptr &agent_group = context.types.get_type("agent-group");

    // We add domain constants...
    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::constants_decl_ptr>(item)) {
            const auto &constants = std::get<ast::constants_decl_ptr>(item)->get_constants();
            context.entities.add_decl_list(context.types, constants, object, entity);
        }
    }
    // ... and problem objects, agents and agent groups to the context
    for (const auto &item: problem->get_items()) {
        if (std::holds_alternative<ast::objects_decl_ptr>(item)) {
            const auto &objects = std::get<ast::objects_decl_ptr>(item)->get_objects();
            context.entities.add_decl_list(context.types, objects, object, object);
        } else if (std::holds_alternative<ast::agents_decl_ptr>(item)) {
            const auto &agents = std::get<ast::agents_decl_ptr>(item)->get_agents();
            context.entities.add_decl_list(context.types, agents, agent, agent);
        } else if (std::holds_alternative<ast::agent_groups_decl_ptr>(item)) {
            const auto &agent_groups = std::get<ast::agent_groups_decl_ptr>(item)->get_agent_groups();

            for (const ast::agent_group_decl_ptr &group : agent_groups)
                context.entities.add_agent_group(context.types, group);
        }
    }
}

void type_checker_helper::build_predicate_signatures(const planning_specification &spec, context &context) {
    const auto &[problem, domain, libraries] = spec;

    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::domain_predicates_ptr>(item)) {
            const auto &predicates = std::get<ast::domain_predicates_ptr>(item)->get_predicate_decl_list();

            for (const auto &predicate_decl : predicates)
                context.predicates.add_decl_predicate(context.types, context.entities, predicate_decl);
        }
    }
}

void type_checker_helper::build_event_signatures(const planning_specification &spec, context &context) {
    const auto &[problem, domain, libraries] = spec;

    for (const auto &item: domain->get_items())
        if (std::holds_alternative<ast::event_ptr>(item))
            context.events.add_decl_event(context.types, context.entities,
                                          std::get<ast::event_ptr>(item));
}

void type_checker_helper::build_action_type_signatures(const planning_specification &spec, context &context) {
    const auto &[problem, domain, libraries] = spec;

    // Adding default action type, corresponding to atomic public actions
    context.action_types.add_decl_action_type(context.types, "basic");

    for (const ast::act_type_library_ptr &library : libraries)
        for (const auto &item : library->get_items())
            if (std::holds_alternative<ast::action_type_ptr>(item))
                context.action_types.add_decl_action_type(context.types, context.entities,
                                                          std::get<ast::action_type_ptr>(item));
}

void type_checker_helper::build_action_signatures(const planning_specification &spec, context &context) {
    const auto &[problem, domain, libraries] = spec;

    for (const auto &item: domain->get_items())
        if (std::holds_alternative<ast::action_ptr>(item))
            context.actions.add_decl_action(context.types, context.entities,
                                            std::get<ast::action_ptr>(item));
}
