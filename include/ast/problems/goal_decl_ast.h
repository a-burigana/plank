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

#ifndef PLANK_GOAL_DECL_AST_H
#define PLANK_GOAL_DECL_AST_H

#include "../ast_node.h"
#include "../common/formulas_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class goal_decl;
    using goal_decl_ptr  = std::shared_ptr<goal_decl>;

    class goal_decl : public ast_node {
    public:
        explicit goal_decl(info info, formula_ptr goal) :
                ast_node{std::move(info)},
                m_goal{std::move(goal)} {
            std::visit([&](auto &&arg) { add_child(arg); }, m_goal);
        }

        [[nodiscard]] const formula_ptr &get_goal() const { return m_goal; }

    private:
        const formula_ptr m_goal;
    };
}

#endif //PLANK_GOAL_DECL_AST_H
