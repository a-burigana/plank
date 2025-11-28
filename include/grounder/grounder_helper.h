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

#ifndef EPDDL_GROUNDER_HELPER_H
#define EPDDL_GROUNDER_HELPER_H

#include <list>
#include <optional>
#include <string>
#include "../ast/common/formulas_ast.h"
#include "../del/semantics/planning_task.h"
#include "../type-checker/context/context.h"

using namespace epddl::type_checker;

namespace epddl::grounder {
    using power_set = std::list<std::list<std::string>>;

    class grounder_helper {
    public:
        [[nodiscard]] static del::planning_task ground(const planning_specification &spec, const context &context, const type_ptr &types_tree);

        [[nodiscard]] static power_set get_induced_power_set(const ast::formal_param_list &params,
                                                             const std::optional<ast::formula_ptr> &f = std::nullopt) {
            power_set combinations;

            return combinations;
        }
    };
}

#endif //EPDDL_GROUNDER_HELPER_H
