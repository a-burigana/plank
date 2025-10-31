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

std::pair<type_ptr, context> type_checker_helper::do_semantic_check(const planning_specification &spec) {
    const auto &[problem, domain, libraries] = spec;

    auto types_tree = build_type_tree(spec);
    context context = build_context(spec, types_tree);

//    for (const ast::act_type_library_ptr &library : libraries)
//        act_type_library_type_checker::check(library, context, types_tree);
//
//    domains_type_checker::check(domain, context, types_tree);
//    problems_type_checker::check(problem, context, types_tree);
//    requirements_type_checker::check(spec, context);

    return {types_tree, context};
}

type_ptr type_checker_helper::build_type_tree(const planning_specification &spec) {
    const auto &[problem, domain, libraries] = spec;

    auto root        = std::make_shared<type>("", nullptr);

    auto entity      = std::make_shared<type>("entity", root);
    auto object      = std::make_shared<type>("object", entity);
    auto agent       = std::make_shared<type>("agent", entity);

    auto world       = std::make_shared<type>("world", root, false);
    auto event       = std::make_shared<type>("event", root, false);

    // Internal types
    auto agent_group = std::make_shared<type>(";agent-group", root, false);
    auto obs_group   = std::make_shared<type>(";obs-group", root, false);

    entity->add_child(std::move(object));
    entity->add_child(std::move(agent));

    root->add_child(std::move(entity));
    root->add_child(std::move(world));
    root->add_child(std::move(event));
    root->add_child(std::move(agent_group));
    root->add_child(std::move(obs_group));

    ast::typed_identifier_list domain_types;

    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::types_decl_ptr>(item)) {
            const auto &types = std::get<ast::types_decl_ptr>(item)->get_types();
            domain_types.insert(domain_types.end(), types.begin(), types.end());
        }
    }

    const type_ptr &object_ = type_utils::find(type_utils::find(root, "entity"), "object");

    for (const auto &type_decl : domain_types) {
        auto &declared_type_id = type_decl->get_id();
        auto &super_type_id = type_decl->get_type();

        const type_ptr &node_type = type_utils::find(root, declared_type_id);
        const type_ptr &node_super_type = super_type_id.has_value()
                ? type_utils::find(root, (*super_type_id))
                : object_;

        if (node_type) {
            const std::string node_type_str = node_type->is_reserved() ? "reserved type" : "type";
            const token &type_tok = node_type->get_identifier()->get_token();

            throw EPDDLException{std::string{""},
                                 declared_type_id->get_token().get_row(),
                                 declared_type_id->get_token().get_col(),
                                 std::string{"Redeclaration of " + node_type_str + " '"
                                             + node_type->get_identifier()->get_token().get_lexeme() + "'."
                                             + (node_type->is_reserved()
                                                ? ""
                                                : " Previous declaration at "
                                                  + std::to_string(type_tok.get_row()) + ":"
                                                  + std::to_string(type_tok.get_col()) + ".")}};
        }

        if (not node_super_type)
            // Note that node_super_type == nullptr only if super_type_id != object.
            // Therefore, we use the position of the token (*super_type_id)->get_token()
            throw EPDDLException{std::string{""},
                                 (*super_type_id)->get_token().get_row(),
                                 (*super_type_id)->get_token().get_col(),
                                 std::string{"Use of undeclared type '" + (*super_type_id)->get_token().get_lexeme() + "'."}};

        if (not node_super_type->is_specializable())
            throw EPDDLException{std::string{""},
                                 (*super_type_id)->get_token().get_row(),
                                 (*super_type_id)->get_token().get_col(),
                                 std::string{"Specialization of non-specializable type '" + (*super_type_id)->get_token().get_lexeme() + "'."}};

        node_super_type->add_child(std::move(std::make_shared<type>(type_decl->get_id(), node_super_type)));
    }

    return root;
}

context type_checker_helper::build_context(const planning_specification &spec, const type_ptr &types_tree) {
    context context;

    build_entities(spec, context, types_tree);
    build_predicate_signatures(spec, context, types_tree);
    build_event_signatures(spec, context, types_tree);
    build_action_signatures(spec, context, types_tree);
    build_action_type_signatures(spec, context, types_tree);

    return context;
}

void type_checker_helper::build_entities(const planning_specification &spec, context &context, const type_ptr &types_tree) {
    const auto &[problem, domain, libraries] = spec;

    const type_ptr &object = type_utils::find(types_tree, "object");
    const type_ptr &agent  = type_utils::find(types_tree, "agent");
    const type_ptr &agent_group  = type_utils::find(types_tree, ";agent-group");

    // We add domain constants...
    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::constants_decl_ptr>(item)) {
            const auto &constants = std::get<ast::constants_decl_ptr>(item)->get_constants();
            context.add_decl_list(constants, object, types_tree);
        }
    }
    // ... and problem objects, agents and agent groups to the context
    for (const auto &item: problem->get_items()) {
        if (std::holds_alternative<ast::objects_decl_ptr>(item)) {
            const auto &objects = std::get<ast::objects_decl_ptr>(item)->get_objects();
            context.add_decl_list(objects, object, types_tree);
        } else if (std::holds_alternative<ast::agents_decl_ptr>(item)) {
            const auto &agents = std::get<ast::agents_decl_ptr>(item)->get_agents();
            context.add_decl_list(agents, agent, types_tree);
        } else if (std::holds_alternative<ast::agent_groups_decl_ptr>(item)) {
            const auto &agent_groups = std::get<ast::agent_groups_decl_ptr>(item)->get_agent_groups();

            for (const ast::agent_group_decl_ptr &group : agent_groups)
                context.add_agent_group(group, types_tree);
        }
    }
}

void type_checker_helper::build_predicate_signatures(const planning_specification &spec, context &context,
                                                     const type_ptr &types_tree) {
    const auto &[problem, domain, libraries] = spec;

    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::domain_predicates_ptr>(item)) {
            const auto &predicates = std::get<ast::domain_predicates_ptr>(item)->get_predicate_decl_list();

            for (const auto &predicate_decl : predicates)
                context.add_decl_predicate(predicate_decl, types_tree);
        }
    }
}

void type_checker_helper::build_event_signatures(const planning_specification &spec, context &context,
                                                 const type_ptr &types_tree) {
    const auto &[problem, domain, libraries] = spec;

    for (const auto &item: domain->get_items())
        if (std::holds_alternative<ast::event_ptr>(item))
            context.add_decl_event(std::get<ast::event_ptr>(item), types_tree);
}

void type_checker_helper::build_action_type_signatures(const planning_specification &spec, context &context,
                                                       const type_ptr &types_tree) {
    const auto &[problem, domain, libraries] = spec;

    // Adding default action type, corresponding to atomic public actions
    context.add_decl_action_type("basic", types_tree);

    for (const ast::act_type_library_ptr &library : libraries)
        for (const auto &item : library->get_items())
            if (std::holds_alternative<ast::action_type_ptr>(item))
                context.add_decl_action_type(std::get<ast::action_type_ptr>(item), types_tree);
}

void type_checker_helper::build_action_signatures(const planning_specification &spec, context &context,
                                                  const type_ptr &types_tree) {
    const auto &[problem, domain, libraries] = spec;

    for (const auto &item: domain->get_items())
        if (std::holds_alternative<ast::action_ptr>(item))
            context.add_decl_action(std::get<ast::action_ptr>(item), types_tree);
}
