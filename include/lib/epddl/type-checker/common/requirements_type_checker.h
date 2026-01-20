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

#ifndef PLANK_REQUIREMENTS_TYPE_CHECKER_H
#define PLANK_REQUIREMENTS_TYPE_CHECKER_H

#include "type-checker/context/context.h"
#include "ast/common/requirements_decl_ast.h"

namespace epddl::type_checker {
    class requirements_type_checker {
    public:
        static void check(const planning_specification &task, context &context,
                          spec_error_managers &err_managers);

    private:
        template<typename item_type>
        static void check_decl_requirements(const ast::ast_node_ptr &root, const std::list<item_type> &items,
                                            context &context, error_manager_ptr &err_manager) {
            for (const auto &item : items)
                if (std::holds_alternative<ast::requirements_decl_ptr>(item))
                    for (const auto &req : std::get<ast::requirements_decl_ptr>(item)->get_requirements())
                        context.requirements.add_requirement(req);

            context.requirements.expand_requirements();
            check_node_requirements(root, context, err_manager);
            context.requirements.clear_requirements();
        }

        static void check_node_requirements(const ast::ast_node_ptr &node, context &context,
                                            error_manager_ptr &err_manager);
    };
}

#endif //PLANK_REQUIREMENTS_TYPE_CHECKER_H
