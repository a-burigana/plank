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

#ifndef EPDDL_EVENT_DECL_AST_H
#define EPDDL_EVENT_DECL_AST_H

#include "../../ast_node.h"
#include "../../tokens/tokens_ast.h"
#include "../../common/parameters_ast.h"
#include "event_postconditions_ast.h"
#include <optional>

namespace epddl::ast {
    class event;
    using event_ptr = std::shared_ptr<ast::event>;

    class event : public ast_node {
    public:
        explicit event(identifier_ptr name, std::optional<parameters_ptr> params,
                        std::optional<formula_ptr> precondition, std::optional<postconditions> postconditions) :
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_precondition{std::move(precondition)},
                m_postconditions{std::move(postconditions)} {}

    private:
        const identifier_ptr m_name;
        const std::optional<parameters_ptr> m_params;
        const std::optional<formula_ptr> m_precondition;
        const std::optional<postconditions> m_postconditions;
    };
}

#endif //EPDDL_EVENT_DECL_AST_H
