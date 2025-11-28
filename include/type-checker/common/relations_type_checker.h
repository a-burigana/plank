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

#ifndef EPDDL_RELATIONS_TYPE_CHECKER_H
#define EPDDL_RELATIONS_TYPE_CHECKER_H

#include "../context/context.h"
#include "../../ast/common/relations_ast.h"
#include "formulas_and_lists_type_checker.h"

namespace epddl::type_checker {
    class relations_type_checker {
    public:
        template<typename node_type>
        static void check_agent_relation(const ast::agent_relation_ptr<node_type> &r_i, context &context,
                                         const type_ptr &types_tree) {
            static_assert(std::is_same_v<node_type, ast::term> or std::is_same_v<node_type, ast::variable_ptr>);

            const type_ptr
                &ag_obs_type = std::is_same_v<node_type, ast::term>
                        ? type_utils::find(types_tree, "agent")
                        : type_utils::find(types_tree, "obs-type"),
                &world_event = std::is_same_v<node_type, ast::term>
                        ? type_utils::find(types_tree, "world")
                        : type_utils::find(types_tree, "event");

            auto check_elem = formulas_and_lists_type_checker::check_function_t<ast::simple_relation_ptr<node_type>>(
                    [&] (const ast::simple_relation_ptr<node_type> &r, class context &context, const type_ptr &types_tree) {
                        context.entities.check_type(r->get_first_node(),  world_event);
                        context.entities.check_type(r->get_second_node(), world_event);
                    });

            context.entities.check_type(r_i->get_obs_group(), ag_obs_type);
            formulas_and_lists_type_checker::check_list(r_i->get_relation(), check_elem, context, types_tree, world_event);
        }
    };
}

#endif //EPDDL_RELATIONS_TYPE_CHECKER_H
