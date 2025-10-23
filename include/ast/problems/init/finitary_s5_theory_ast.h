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

#ifndef EPDDL_FINITARY_S5_THEORY_AST_H
#define EPDDL_FINITARY_S5_THEORY_AST_H

#include "../../ast_node.h"
#include "../../common/formulas_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class prop_formula;
    class ck_formula;
    class ck_k_formula;
    class ck_kw_formula;
    class ck_not_kw_formula;

    class and_theory;
    class forall_theory;

    using prop_formula_ptr        = std::shared_ptr<prop_formula>;
    using ck_formula_ptr          = std::shared_ptr<ck_formula>;
    using ck_k_formula_ptr        = std::shared_ptr<ck_k_formula>;
    using ck_kw_formula_ptr       = std::shared_ptr<ck_kw_formula>;
    using ck_not_kw_formula_ptr   = std::shared_ptr<ck_not_kw_formula>;

    using and_theory_ptr          = std::shared_ptr<and_theory>;
    using forall_theory_ptr       = std::shared_ptr<forall_theory>;

    using finitary_S5_formula     = std::variant<prop_formula_ptr, ck_formula_ptr, ck_k_formula_ptr, ck_kw_formula_ptr, ck_not_kw_formula_ptr>;
    using finitary_S5_theory      = std::variant<finitary_S5_formula, and_theory_ptr, forall_theory_ptr>;
    using finitary_S5_theory_list = std::list<finitary_S5_theory>;


    class prop_formula : public ast_node {
    public:
        explicit prop_formula(ast::info info, formula_ptr f);

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const formula_ptr m_f;
    };

    class ck_formula : public ast_node {
    public:
        explicit ck_formula(ast::info info, formula_ptr f);

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const formula_ptr m_f;
    };

    class ck_k_formula : public ast_node {
    public:
        explicit ck_k_formula(info info, term agent, formula_ptr f);

        [[nodiscard]] const term &get_agent() const { return m_agent; }
        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const term m_agent;
        const formula_ptr m_f;
    };

    class ck_kw_formula : public ast_node {
    public:
        explicit ck_kw_formula(info info, term agent, formula_ptr f);

        [[nodiscard]] const term &get_agent() const { return m_agent; }
        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const term m_agent;
        const formula_ptr m_f;
    };

    class ck_not_kw_formula : public ast_node {
    public:
        explicit ck_not_kw_formula(info info, term agent, formula_ptr f);

        [[nodiscard]] const term &get_agent() const { return m_agent; }
        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const term m_agent;
        const formula_ptr m_f;
    };

    class and_theory : public ast_node {
    public:
        explicit and_theory(ast::info info, finitary_S5_theory_list list);

        [[nodiscard]] const finitary_S5_theory_list &get_formula() const { return m_list; }

    private:
        const finitary_S5_theory_list m_list;
    };

    class forall_theory : public ast_node {
    public:
        explicit forall_theory(info info, list_comprehension_ptr list_compr, finitary_S5_theory theory);

        [[nodiscard]] const list_comprehension_ptr &get_list_compr() const { return m_list_compr; }
        [[nodiscard]] const finitary_S5_theory &get_terms() const { return m_theory; }

    private:
        const list_comprehension_ptr m_list_compr;
        const finitary_S5_theory m_theory;
    };
}

#endif //EPDDL_FINITARY_S5_THEORY_AST_H
