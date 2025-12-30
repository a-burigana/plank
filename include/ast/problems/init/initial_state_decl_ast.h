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

#ifndef PLANK_INITIAL_STATE_DECL_AST_H
#define PLANK_INITIAL_STATE_DECL_AST_H

#include "explicit_inititial_state_ast.h"
#include "finitary_s5_theory_ast.h"
#include "../../common/formulas_ast.h"
#include "finitary_s5_theory_ast.h"
#include <variant>

namespace epddl::ast {
    class initial_state;
    using initial_state_ptr = std::shared_ptr<initial_state>;
    using initial_state_repr = std::variant<explicit_initial_state_ptr, finitary_S5_theory>;

    class initial_state : public ast_node {
    public:
        explicit initial_state(info info, initial_state_repr state) :
                ast_node{std::move(info)},
                m_state{std::move(state)} {
            if (std::holds_alternative<explicit_initial_state_ptr>(m_state))
                add_child(std::get<explicit_initial_state_ptr>(m_state));
            else if (std::holds_alternative<finitary_S5_theory>(m_state)) {
                const auto &theory = std::get<finitary_S5_theory>(m_state);
                std::visit([&](auto &&arg) { add_child(arg); }, theory);
            }
        }

        [[nodiscard]] const initial_state_repr &get_state() const { return m_state; }

    private:
        const initial_state_repr m_state;
    };
}

#endif //PLANK_INITIAL_STATE_DECL_AST_H
