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

#ifndef EPDDL_EVENT_POSTCONDITIONS_AST_H
#define EPDDL_EVENT_POSTCONDITIONS_AST_H

#include "../../tokens/tokens_ast.h"
#include "../../common/formulas_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class literal_postcondition;
    class when_postcondition;
    class iff_postcondition;
    class forall_postcondition;
    class and_postcondition;

    using literal_postcondition_ptr  = std::shared_ptr<literal_postcondition>;
    using when_postcondition_ptr     = std::shared_ptr<when_postcondition>;
    using iff_postcondition_ptr      = std::shared_ptr<iff_postcondition>;
    using forall_postcondition_ptr   = std::shared_ptr<forall_postcondition>;
    using and_postcondition_ptr      = std::shared_ptr<and_postcondition>;

    using postconditions             = std::variant<literal_postcondition_ptr, when_postcondition_ptr, iff_postcondition_ptr,
                                                    forall_postcondition_ptr, and_postcondition_ptr>;
    using postconditions_list        = std::list<postconditions>;

    class literal_postcondition : public ast_node {
    public:
        explicit literal_postcondition(info info, literal_ptr literal) :
                ast_node{std::move(info)},
                m_literal{std::move(literal)} {}

        [[nodiscard]] const literal_ptr &get_literal() const { return m_literal; }

    private:
        const literal_ptr m_literal;
    };

    class when_postcondition : public ast_node {
    public:
        explicit when_postcondition(info info, formula_ptr cond, literal_list literals) :
                ast_node{std::move(info)},
                m_cond{std::move(cond)},
                m_literals{std::move(literals)} {}

        [[nodiscard]] const formula_ptr &get_cond() const { return m_cond; }
        [[nodiscard]] const literal_list &get_literals() const { return m_literals; }

    private:
        const formula_ptr m_cond;
        const literal_list m_literals;
    };

    class iff_postcondition : public ast_node {
    public:
        explicit iff_postcondition(info info, formula_ptr cond, literal_list literals) :
                ast_node{std::move(info)},
                m_cond{std::move(cond)},
                m_literals{std::move(literals)} {}

        [[nodiscard]] const formula_ptr &get_cond() const { return m_cond; }
        [[nodiscard]] const literal_list &get_literals() const { return m_literals; }

    private:
        const formula_ptr m_cond;
        const literal_list m_literals;
    };

    class forall_postcondition : public ast_node {
    public:
        explicit forall_postcondition(info info, list_comprehension_ptr params, postconditions post) :
                ast_node{std::move(info)},
                m_params{std::move(params)},
                m_post{std::move(post)} {}

        [[nodiscard]] const list_comprehension_ptr &get_params() const { return m_params; }
        [[nodiscard]] const postconditions &get_post() const { return m_post; }

    private:
        const list_comprehension_ptr m_params;
        const postconditions m_post;
    };

    class and_postcondition : public ast_node {
    public:
        explicit and_postcondition(info info, postconditions_list post_list) :
                ast_node{std::move(info)},
                m_post_list{std::move(post_list)} {}

        [[nodiscard]] const postconditions_list &get_post_list() const { return m_post_list; }

    private:
        const postconditions_list m_post_list;
    };
}

#endif //EPDDL_EVENT_POSTCONDITIONS_AST_H
