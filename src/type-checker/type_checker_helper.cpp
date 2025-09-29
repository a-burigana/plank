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
#include "../../include/error-manager/epddl_exception.h"
#include <memory>
#include <string>
#include <variant>

using namespace epddl::type_checker;

void type_checker_helper::do_semantic_check(const planning_task &task) {
    auto types_tree = build_type_tree(task);
    auto context = build_context(task, types_tree);
}

type_ptr type_checker_helper::build_type_tree(const planning_task &task) {
    const auto &[problem, domain, libraries] = task;

    auto root        = std::make_shared<type>("", nullptr);

    auto entity      = std::make_shared<type>("entity", root);
    auto object      = std::make_shared<type>("object", entity);
    auto agent       = std::make_shared<type>("agent", entity);
//    auto agent_group = std::make_shared<type>("agent-group", entity, false);

    auto world       = std::make_shared<type>("world", root, false);
    auto event       = std::make_shared<type>("event", root, false);

    ast::typed_identifier_list domain_types;

    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::types_decl_ptr>(item)) {
            const auto &types = std::get<ast::types_decl_ptr>(item)->get_types();
            domain_types.insert(domain_types.end(), types.begin(), types.end());
        }
    }

    for (const auto &type_decl : domain_types) {
        auto &declared_type_id = type_decl->get_id();
        auto &super_type_id = type_decl->get_type();

        auto node_type       = root->find(declared_type_id);
        auto node_super_type = super_type_id.has_value()
                ? root->find((*super_type_id))
                : object;

        const token &type_tok = node_type->get_identifier()->get_token();
        const std::string node_type_str = node_type->is_reserved() ? "reserved type" : "type";

        if (node_type)
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

        if (not node_super_type)
            // Note that node_super_type == nullptr only if super_type_id != object.
            // Therefore, we use the position of the token (*super_type_id)->get_token()
            throw EPDDLException{std::string{""},
                                 (*super_type_id)->get_token().get_row(),
                                 (*super_type_id)->get_token().get_col(),
                                 std::string{"Use of undeclared type '" + type_tok.get_lexeme() + "'."}};

        if (not node_super_type->is_specializable())
            throw EPDDLException{std::string{""},
                                 (*super_type_id)->get_token().get_row(),
                                 (*super_type_id)->get_token().get_col(),
                                 std::string{"Specialization of non-specializable type '" + type_tok.get_lexeme() + "'."}};

        std::make_shared<type>(type_decl->get_id(), node_super_type);
    }

    return root;
}

context type_checker_helper::build_context(const epddl::type_checker::planning_task &task,
                                           const epddl::type_checker::type_ptr &types_tree) {
    context context;
    build_entities(task, context, types_tree);
    build_predicate_signatures(task, context, types_tree);

    return context;
}

void type_checker_helper::build_entities(const planning_task &task, context &context, const type_ptr &types_tree) {
    const auto &[problem, domain, libraries] = task;

    const type_ptr &object = types_tree->find("object");
    const type_ptr &agent  = types_tree->find("agent");

    // Lists of pairs (entity, default_type), where default_type is the default type of the declared entity,
    // which we must know in case it was declared with no explicit type. The default type is 'object' for
    // constants and objects, and 'agent' for agents
//    std::list<std::pair<ast::typed_identifier_ptr, type_ptr>> domain_entities, problem_entities;
    ast::typed_identifier_list domain_constants, problem_objects, problem_agents;

    // We add constants, objects and agents declarations to the list of entities...
    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::constants_decl_ptr>(item)) {
            const auto &constants = std::get<ast::constants_decl_ptr>(item)->get_constants();
            domain_constants.insert(domain_constants.end(), constants.begin(), constants.end());
        }
    }

    for (const auto &item: problem->get_items()) {
        if (std::holds_alternative<ast::objects_decl_ptr>(item)) {
            const auto &objects = std::get<ast::objects_decl_ptr>(item)->get_objects();
            problem_objects.insert(problem_objects.end(), objects.begin(), objects.end());
        } else if (std::holds_alternative<ast::agents_decl_ptr>(item)) {
            const auto &agents = std::get<ast::agents_decl_ptr>(item)->get_agents();
            problem_agents.insert(problem_agents.end(), agents.begin(), agents.end());
        }
    }

    // ...and we sort the list wrt. the order in which entities are declared
//    entities.sort([](const auto &x, const auto &y) -> bool {
//        return x.first->get_id()->get_token().get_col() < y.first->get_id()->get_token().get_col() or
//               x.first->get_id()->get_token().get_row() < y.first->get_id()->get_token().get_row();
//    });

    context.add_decl_list(domain_constants, object, types_tree);
    context.add_decl_list(problem_objects,  object, types_tree);
    context.add_decl_list(problem_agents,   agent,  types_tree);
    // todo: make sure that objects and agents are inserted in the order they are declared in (right now this is not the case)
    // todo: also make sure that the correct types are associated to all entities, e.g., if x y - z are defined, then
    //       both x and y are of type z
}

void type_checker_helper::build_predicate_signatures(const planning_task &task, context &context,
                                                     const type_ptr &types_tree) {
    const auto &[problem, domain, libraries] = task;

    for (const auto &item: domain->get_items()) {
        if (std::holds_alternative<ast::domain_predicates_ptr>(item)) {
            const auto &predicates = std::get<ast::domain_predicates_ptr>(item)->get_predicate_decl_list();

            for (const auto &predicate_decl : predicates)
                context.add_decl_predicate(predicate_decl, types_tree);
        }
    }
}
