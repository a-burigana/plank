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
    auto context = build_initial_context(task, types_tree);
}

types_tree_ptr type_checker_helper::build_type_tree(const planning_task &task) {
    const auto &[problem, domain, libraries] = task;

    auto root        = std::make_shared<types_tree>("", nullptr);

    auto entity      = std::make_shared<types_tree>("entity", root);
    auto world       = std::make_shared<types_tree>("world",  root, false);
    auto event       = std::make_shared<types_tree>("event",  root, false);

    auto object      = std::make_shared<types_tree>("object",      entity);
    auto agent       = std::make_shared<types_tree>("agent",       entity);
    auto agent_group = std::make_shared<types_tree>("agent-group", entity, false);

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

        auto type_node       = root->find(declared_type_id->get_token().get_lexeme());
        auto super_type_node = super_type_id.has_value()
                ? root->find((*super_type_id)->get_token().get_lexeme())
                : object;

        if (type_node)
            throw EPDDLException{std::string{""},
                                 declared_type_id->get_token().get_row(),
                                 declared_type_id->get_token().get_col(),
                                 std::string{"Redeclaration of type '"
                                             + type_node->get_token()->get_lexeme() + "'. Previous declaration at "
                                             + std::to_string(type_node->get_token()->get_row()) + ":"
                                             + std::to_string(type_node->get_token()->get_col()) + "."}};

        if (not super_type_node)
            // Note that super_type_node == nullptr only if super_type_id != object.
            // Therefore, we use the position of the token (*super_type_id)->get_token()
            throw EPDDLException{std::string{""},
                                 (*super_type_id)->get_token().get_row(),
                                 (*super_type_id)->get_token().get_col(),
                                 std::string{"Use of undeclared type '"
                                             + type_node->get_token()->get_lexeme() + "'."}};

        if (not super_type_node->is_specializable())
            throw EPDDLException{std::string{""},
                                 (*super_type_id)->get_token().get_row(),
                                 (*super_type_id)->get_token().get_col(),
                                 std::string{"Specialization of non-specializable type '"
                                             + type_node->get_token()->get_lexeme() + "'."}};

        std::make_shared<types_tree>(type_decl->get_id()->get_token_ptr(), super_type_node);
    }

    return root;
}

context type_checker_helper::build_initial_context(const planning_task &task, const types_tree_ptr &types_tree) {
    const auto &[problem, domain, libraries] = task;

    scope initial_scope;

    identifier_map id_map;
    variable_map var_map;

    ast::typed_identifier_list problem_objects, problem_agents;

    for (const auto &item: problem->get_items()) {
        if (std::holds_alternative<ast::objects_decl_ptr>(item)) {
            const auto &objects = std::get<ast::objects_decl_ptr>(item)->get_objects();
            problem_objects.insert(problem_objects.end(), objects.begin(), objects.end());
        } else if (std::holds_alternative<ast::agents_decl_ptr>(item)) {
            const auto &agents = std::get<ast::agents_decl_ptr>(item)->get_agents();
            problem_agents.insert(problem_objects.end(), agents.begin(), agents.end());
        }
    }

    for (const auto &obj_decl : problem_objects) {
        auto &declared_obj_id = obj_decl->get_id();
        auto &type_id = obj_decl->get_type();

        auto type_node = type_id.has_value()
                ? types_tree->find((*type_id)->get_token().get_lexeme())
                : types_tree->find("object");

        initial_scope.add_identifier_decl(declared_obj_id, type_node);
    }

    for (const auto &ag_decl : problem_agents) {
        auto &declared_ag_id = ag_decl->get_id();
        auto &type_id = ag_decl->get_type();

        auto type_node = type_id.has_value()
                         ? types_tree->find((*type_id)->get_token().get_lexeme())
                         : types_tree->find("agent");

        initial_scope.add_identifier_decl(declared_ag_id, type_node);
    }

    // todo: implement constants and add them to initial context (before objects and agents)
    //       if a constant is declared with no explicit type, we assume it's an object

    context context;
    context.push(std::move(initial_scope));

    return context;
}
