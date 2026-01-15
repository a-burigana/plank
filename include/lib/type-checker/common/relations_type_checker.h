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

#ifndef PLANK_RELATIONS_TYPE_CHECKER_H
#define PLANK_RELATIONS_TYPE_CHECKER_H

#include "../context/context.h"
#include "../../ast/common/relations_ast.h"
#include "formulas_and_lists_type_checker.h"

namespace epddl::type_checker {
    class relations_type_checker {
    public:
        template<typename node_type>
        static void check_agent_relation(const ast::agent_relation_ptr<node_type> &r_i, context &context,
                                         error_manager_ptr &err_manager) {
            static_assert(std::is_same_v<node_type, ast::term> or std::is_same_v<node_type, ast::variable_ptr>);

            const type_ptr
                &ag_obs_type = std::is_same_v<node_type, ast::term>
                        ? context.types.get_type("agent")
                        : context.types.get_type("obs-type"),
                &world_event = std::is_same_v<node_type, ast::term>
                        ? context.types.get_type("world")
                        : context.types.get_type("event");

            auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::simple_relation_ptr<node_type>>(
                    [&] (const ast::simple_relation_ptr<node_type> &r, class context &context,
                         error_manager_ptr &err_manager, const type_ptr &default_type) {
                        context.entities.check_type(context.types, err_manager,
                                                    r->get_first_node(),  world_event);
                        context.entities.check_type(context.types, err_manager,
                                                    r->get_second_node(), world_event);
                    });

            context.entities.check_type(context.types, err_manager, r_i->get_obs_type(), ag_obs_type);
            formulas_and_lists_type_checker::check_list(
                    r_i->get_relation(), check_elem, context, err_manager, world_event);
        }
    };
}

#endif //PLANK_RELATIONS_TYPE_CHECKER_H
