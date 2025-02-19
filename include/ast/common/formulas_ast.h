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

#ifndef EPDDL_FORMULAS_AST_H
#define EPDDL_FORMULAS_AST_H

#include "../../ast/ast_node.h"
#include "../tokens/tokens_ast.h"
#include "typed_elem_ast.h"

namespace epddl::ast {
    class predicate;
    class literal;
    class predicate_formula;
    class eq_formula;
    class not_formula;
    class and_formula;
    class or_formula;
    class imply_formula;
    class modality;
    class box_formula;
    class diamond_formula;
    class forall_formula;
    class exists_formula;
    class in_formula;
    class ext_list_comprehension;
    class int_list_comprehension;

    using modality_ptr              = std::unique_ptr<modality>;

    using predicate_ptr             = std::unique_ptr<predicate>;
    using literal_ptr               = std::unique_ptr<literal>;
    using predicate_list            = std::list<predicate_ptr>;
    using literal_list              = std::list<literal_ptr>;

    using predicate_formula_ptr     = std::unique_ptr<predicate_formula>;
    using eq_formula_ptr            = std::unique_ptr<eq_formula>;
    using not_formula_ptr           = std::unique_ptr<not_formula>;
    using and_formula_ptr           = std::unique_ptr<and_formula>;
    using or_formula_ptr            = std::unique_ptr<or_formula>;
    using imply_formula_ptr         = std::unique_ptr<imply_formula>;
    using box_formula_ptr           = std::unique_ptr<box_formula>;
    using diamond_formula_ptr       = std::unique_ptr<diamond_formula>;
    using forall_formula_ptr        = std::unique_ptr<forall_formula>;
    using exists_formula_ptr        = std::unique_ptr<exists_formula>;
    using in_formula_ptr            = std::unique_ptr<in_formula>;

    using ext_list_comprehension_ptr = std::unique_ptr<ext_list_comprehension>;
    using int_list_comprehension_ptr = std::unique_ptr<int_list_comprehension>;
    using list_comprehension_ptr     = std::variant<ext_list_comprehension_ptr, int_list_comprehension_ptr>;

    using formula_ptr               = std::variant<predicate_formula_ptr, eq_formula_ptr, not_formula_ptr, and_formula_ptr, or_formula_ptr, imply_formula_ptr, box_formula_ptr, diamond_formula_ptr, forall_formula_ptr, exists_formula_ptr, in_formula_ptr>;
    using formula_list              = std::list<formula_ptr>;

    using term                      = std::variant<identifier_ptr, variable_ptr>;
    using term_list                 = std::list<term>;

    using single_modality_index_ptr = std::variant<identifier_ptr, variable_ptr>;
    using group_modality_index_ptr  = std::list<single_modality_index_ptr>;
    using modality_index_ptr        = std::variant<single_modality_index_ptr, group_modality_index_ptr, agent_group_token::all>;

    class predicate : public ast_node {
    public:
        explicit predicate(identifier_ptr name, term_list args) :
                m_name{std::move(name)},
                m_args{std::move(args)} {}

    private:
        const identifier_ptr m_name;
        const term_list m_args;
    };

    class literal : public ast_node {
    public:
        explicit literal(bool positive, predicate_ptr pred) :
                m_positive{positive},
                m_pred{std::move(pred)} {}

    private:
        const bool m_positive;
        const predicate_ptr m_pred;
    };

    class predicate_formula : public ast_node {
    public:
        explicit predicate_formula(predicate_ptr predicate) :
                m_predicate{std::move(predicate)} {}

    private:
        const predicate_ptr m_predicate;
    };

    class eq_formula : public ast_node {
    public:
        explicit eq_formula(term t1, term t2) :
                m_t1{std::move(t1)},
                m_t2{std::move(t2)} {}

    private:
        const term m_t1, m_t2;
    };

    class not_formula : public ast_node {
    public:
        explicit not_formula(formula_ptr f) :
                m_f{std::move(f)} {}

    private:
        const formula_ptr m_f;
    };

    class and_formula : public ast_node {
    public:
        explicit and_formula(formula_list fs) :
                m_fs{std::move(fs)} {}

    private:
        const formula_list m_fs;
    };

    class or_formula : public ast_node {
    public:
        explicit or_formula(formula_list fs) :
                m_fs{std::move(fs)} {}

    private:
        const formula_list m_fs;
    };

    class imply_formula : public ast_node {
    public:
        explicit imply_formula(formula_ptr f1, formula_ptr f2) :
                m_f1{std::move(f1)},
                m_f2{std::move(f2)}{}

    private:
        const formula_ptr m_f1, m_f2;
    };

    class modality : public ast_node {
    public:
        explicit modality(std::optional<modality_name_ptr> name, modality_index_ptr index) :
                m_name{std::move(name)},
                m_index{std::move(index)} {}

    private:
        const std::optional<modality_name_ptr> m_name;
        const modality_index_ptr m_index;
    };

    class box_formula : public ast_node {
    public:
        explicit box_formula(modality_ptr mod, formula_ptr f) :
                m_mod{std::move(mod)},
                m_f{std::move(f)} {}

    private:
        const modality_ptr m_mod;
        const formula_ptr m_f;
    };

    class diamond_formula : public ast_node {
    public:
        explicit diamond_formula(modality_ptr mod, formula_ptr f) :
                m_mod{std::move(mod)},
                m_f{std::move(f)} {}

    private:
        const modality_ptr m_mod;
        const formula_ptr m_f;
    };

    class ext_list_comprehension : public ast_node {
    public:
        explicit ext_list_comprehension(term_list terms) :
                m_terms{std::move(terms)} {}

    private:
        const term_list m_terms;
    };

    class int_list_comprehension : public ast_node {
    public:
        explicit int_list_comprehension(formal_param_list params, std::optional<formula_ptr> f) :
            m_params{std::move(params)},
            m_f{std::move(f)} {}

    private:
        const formal_param_list m_params;
        const std::optional<formula_ptr> m_f;
    };

    class in_formula : public ast_node {
    public:
        explicit in_formula(term_list terms, list_comprehension_ptr list) :
                m_terms{std::move(terms)},
                m_list{std::move(list)} {}

    private:
        const term_list m_terms;
        const list_comprehension_ptr m_list;
    };

    class forall_formula : public ast_node {
    public:
        explicit forall_formula(int_list_comprehension_ptr params, formula_ptr f) :
                m_params{std::move(params)},
                m_f{std::move(f)} {}

    private:
        const int_list_comprehension_ptr m_params;
        const formula_ptr m_f;
    };

    class exists_formula : public ast_node {
    public:
        explicit exists_formula(int_list_comprehension_ptr params, formula_ptr f) :
                m_params{std::move(params)},
                m_f{std::move(f)} {}

    private:
        const int_list_comprehension_ptr m_params;
        const formula_ptr m_f;
    };
}

#endif //EPDDL_FORMULAS_AST_H
