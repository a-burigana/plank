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

#ifndef EPDDL_STATIC_INIT_AST_H
#define EPDDL_STATIC_INIT_AST_H

#include "../../ast_node.h"
#include "../../common/formulas_ast.h"
#include <memory>
#include <variant>

namespace epddl::ast {
    class and_static_literal_list;
    class forall_static_literal_list;
    class static_init;

    using and_static_literal_list_ptr    = std::shared_ptr<and_static_literal_list>;
    using forall_static_literal_list_ptr = std::shared_ptr<forall_static_literal_list>;
    using static_literals                = std::variant<literal_ptr, and_static_literal_list_ptr, forall_static_literal_list_ptr>;
    using static_literal_list            = std::list<static_literals>;

    using static_init_ptr = std::shared_ptr<static_init>;

    class and_static_literal_list : public ast_node {
    public:
        explicit and_static_literal_list(info info, static_literal_list list);

        [[nodiscard]] const static_literal_list &get_literals() const { return m_list; }

    private:
        const static_literal_list m_list;
    };

    class forall_static_literal_list : public ast_node {
    public:
        explicit forall_static_literal_list(info info, list_comprehension_ptr list_compr, static_literals literal);

        [[nodiscard]] const list_comprehension_ptr &get_list_compr() const { return m_list_compr; }
        [[nodiscard]] const static_literals &get_literal() const { return m_literal; }

    private:
        const list_comprehension_ptr m_list_compr;
        const static_literals m_literal;
    };

    class static_init : public ast_node {
    public:
        explicit static_init(info info, static_literals literals);

        [[nodiscard]] const static_literals &get_literals() const { return m_literals; }

    private:
        const static_literals m_literals;
    };
}

#endif //EPDDL_STATIC_INIT_AST_H
