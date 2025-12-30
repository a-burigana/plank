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

#ifndef PLANK_FORMULAS_AST_H
#define PLANK_FORMULAS_AST_H

#include "../../ast/ast_node.h"
#include "../tokens/tokens_ast.h"
#include "typed_elem_ast.h"
#include <cstddef>

namespace epddl::ast {
    class true_formula;
    class false_formula;
    class predicate;
    class literal;
    class eq_formula;
    class neq_formula;
//    class in_formula;

    class predicate_formula;
    class not_formula;
    class and_formula;
    class or_formula;
    class imply_formula;
    class box_formula;
    class diamond_formula;
    class forall_formula;
    class exists_formula;

    class modality;
    class all_group_modality;

    class simple_agent_group;

    template<typename Elem> class singleton_list;
    template<typename Elem> class and_list;
    template<typename Elem> class forall_list;

    class list_comprehension;

    using modality_ptr              = std::shared_ptr<modality>;
    using all_group_modality_ptr    = std::shared_ptr<all_group_modality>;

    using true_formula_ptr          = std::shared_ptr<true_formula>;
    using false_formula_ptr         = std::shared_ptr<false_formula>;
    using predicate_ptr             = std::shared_ptr<predicate>;
    using literal_ptr               = std::shared_ptr<literal>;
    using eq_formula_ptr            = std::shared_ptr<eq_formula>;
    using neq_formula_ptr           = std::shared_ptr<neq_formula>;
//    using in_formula_ptr            = std::shared_ptr<in_formula>;

    using predicate_list            = std::list<predicate_ptr>;
    using literal_list              = std::list<literal_ptr>;

    using predicate_formula_ptr     = std::shared_ptr<predicate_formula>;
    using not_formula_ptr           = std::shared_ptr<not_formula>;
    using and_formula_ptr           = std::shared_ptr<and_formula>;
    using or_formula_ptr            = std::shared_ptr<or_formula>;
    using imply_formula_ptr         = std::shared_ptr<imply_formula>;
    using box_formula_ptr           = std::shared_ptr<box_formula>;
    using diamond_formula_ptr       = std::shared_ptr<diamond_formula>;
    using forall_formula_ptr        = std::shared_ptr<forall_formula>;
    using exists_formula_ptr        = std::shared_ptr<exists_formula>;

    using simple_agent_group_ptr = std::shared_ptr<simple_agent_group>;

    template<typename Elem> using singleton_list_ptr = std::shared_ptr<singleton_list<Elem>>;
    template<typename Elem> using and_list_ptr       = std::shared_ptr<and_list<Elem>>;
    template<typename Elem> using forall_list_ptr    = std::shared_ptr<forall_list<Elem>>;

    template<typename Elem> using list      = std::variant<singleton_list_ptr<Elem>, and_list_ptr<Elem>, forall_list_ptr<Elem>>;
    template<typename Elem> using list_list = std::list<list<Elem>>;

    using list_comprehension_ptr = std::shared_ptr<list_comprehension>;

    using formula_ptr            = std::variant<true_formula_ptr, false_formula_ptr, predicate_formula_ptr,
                                                eq_formula_ptr, neq_formula_ptr, not_formula_ptr,
                                                and_formula_ptr, or_formula_ptr, imply_formula_ptr, box_formula_ptr,
                                                diamond_formula_ptr, forall_formula_ptr, exists_formula_ptr>;   //, in_formula_ptr
    using formula_list           = std::list<formula_ptr>;

    using term                   = std::variant<identifier_ptr, variable_ptr>;
    using term_list              = std::list<term>;

    using modality_index_ptr     = std::variant<term, list<simple_agent_group_ptr>, all_group_modality_ptr>;

    class true_formula : public ast_node {
    public:
        explicit true_formula(info info) :
            ast_node{std::move(info)} {}
    };

    class false_formula : public ast_node {
    public:
        explicit false_formula(info info) :
            ast_node{std::move(info)} {}
    };

    class predicate : public ast_node {
    public:
        explicit predicate(info info, identifier_ptr name, term_list args) :
                ast_node{std::move(info)},
                m_name{std::move(name)},
                m_args{std::move(args)} {
            add_child(m_name);
            for (const term &t : m_args) std::visit([&](auto &&arg) { add_child(arg); }, t);
        }

        [[nodiscard]] const identifier_ptr &get_id() const { return m_name; }
        [[nodiscard]] const term_list &get_terms() const { return m_args; }

    private:
        const identifier_ptr m_name;
        const term_list m_args;
    };

    class literal : public ast_node {
    public:
        explicit literal(info info, bool positive, predicate_ptr predicate) :
                ast_node{std::move(info)},
                m_positive{positive},
                m_predicate{std::move(predicate)} {
            add_child(m_predicate);
        }

        [[nodiscard]] const predicate_ptr &get_predicate() const { return m_predicate; }
        [[nodiscard]] bool is_positive() const { return m_positive; }

    private:
        const bool m_positive;
        const predicate_ptr m_predicate;
    };

    class predicate_formula : public ast_node {
    public:
        explicit predicate_formula(info info, predicate_ptr predicate) :
                ast_node{std::move(info)},
                m_predicate{std::move(predicate)} {
            add_child(m_predicate);
        }

        [[nodiscard]] const predicate_ptr &get_predicate() const { return m_predicate; }

    private:
        const predicate_ptr m_predicate;
    };

    class eq_formula : public ast_node {
    public:
        explicit eq_formula(info info, term t1, term t2) :
                ast_node{std::move(info)},
                m_t1{std::move(t1)},
                m_t2{std::move(t2)} {
            std::visit([&](auto &&arg) { add_child(arg); }, m_t1);
            std::visit([&](auto &&arg) { add_child(arg); }, m_t2);
        }

        [[nodiscard]] const term &get_first_term() const { return m_t1; }
        [[nodiscard]] const term &get_second_term() const { return m_t2; }

    private:
        const term m_t1, m_t2;
    };

    class neq_formula : public ast_node {
    public:
        explicit neq_formula(info info, term t1, term t2) :
                ast_node{std::move(info)},
                m_t1{std::move(t1)},
                m_t2{std::move(t2)} {
            std::visit([&](auto &&arg) { add_child(arg); }, m_t1);
            std::visit([&](auto &&arg) { add_child(arg); }, m_t2);
        }

        [[nodiscard]] const term &get_first_term() const { return m_t1; }
        [[nodiscard]] const term &get_second_term() const { return m_t2; }

    private:
        const term m_t1, m_t2;
    };

//    class in_formula : public ast_node {
//    public:
//        explicit in_formula(info info, term term, list_ptr list);
//
//        [[nodiscard]] const term &get_term() const { return m_term; }
//        [[nodiscard]] const list_ptr &get_list() const { return m_list; }
//
//    private:
//        const term m_term;
//        const list_ptr m_list;
//    };

    class not_formula : public ast_node {
    public:
        explicit not_formula(ast::info info, formula_ptr f);

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const formula_ptr m_f;
    };

    class and_formula : public ast_node {
    public:
        explicit and_formula(info info, formula_list fs);

        [[nodiscard]] const formula_list &get_formulas() const { return m_fs; }

    private:
        const formula_list m_fs;
    };

    class or_formula : public ast_node {
    public:
        explicit or_formula(info info, formula_list fs);

        [[nodiscard]] const formula_list &get_formulas() const { return m_fs; }

    private:
        const formula_list m_fs;
    };

    class imply_formula : public ast_node {
    public:
        explicit imply_formula(info info, formula_ptr f1, formula_ptr f2);

        [[nodiscard]] const formula_ptr &get_first_formula() const { return m_f1; }
        [[nodiscard]] const formula_ptr &get_second_formula() const { return m_f2; }

    private:
        const formula_ptr m_f1, m_f2;
    };

    class box_formula : public ast_node {
    public:
        explicit box_formula(info info, modality_ptr mod, formula_ptr f);

        [[nodiscard]] const modality_ptr &get_modality() const { return m_mod; }
        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const modality_ptr m_mod;
        const formula_ptr m_f;
    };

    class diamond_formula : public ast_node {
    public:
        explicit diamond_formula(info info, modality_ptr mod, formula_ptr f);

        [[nodiscard]] const modality_ptr &get_modality() const { return m_mod; }
        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const modality_ptr m_mod;
        const formula_ptr m_f;
    };

    class forall_formula : public ast_node {
    public:
        explicit forall_formula(info info, list_comprehension_ptr params, formula_ptr f);

        [[nodiscard]] const list_comprehension_ptr &get_list_compr() const { return m_params; }
        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const list_comprehension_ptr m_params;
        const formula_ptr m_f;
    };

    class exists_formula : public ast_node {
    public:
        explicit exists_formula(info info, list_comprehension_ptr params, formula_ptr f);

        [[nodiscard]] const list_comprehension_ptr &get_list_compr() const { return m_params; }
        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

    private:
        const list_comprehension_ptr m_params;
        const formula_ptr m_f;
    };

    class all_group_modality : public ast_node {
    public:
        explicit all_group_modality(info info) :
                ast_node{std::move(info)} {}
    };

    class modality : public ast_node {
    public:
        explicit modality(info info, std::optional<modality_name_ptr> name, modality_index_ptr index);

        [[nodiscard]] const std::optional<modality_name_ptr> &get_modality_name() const { return m_name; }
        [[nodiscard]] const modality_index_ptr &get_modality_index() const { return m_index; }

    private:
        const std::optional<modality_name_ptr> m_name;
        const modality_index_ptr m_index;
    };

//    class list_name : public ast_node {
//    public:
//        explicit list_name(info info, identifier_ptr name) :
//                ast_node{std::move(info)},
//                m_name{std::move(name)} {
//            add_child(m_name);
//        }
//
//        [[nodiscard]] const identifier_ptr &get_name() const { return m_name; }
//
//    private:
//        const identifier_ptr m_name;
//    };

    class simple_agent_group : public ast_node {
    public:
        explicit simple_agent_group(info info, term_list terms) :
                ast_node{std::move(info)},
                m_terms{std::move(terms)} {
            for (const term &t : m_terms)
                std::visit([&](auto &&arg) { add_child(arg); }, t);
        }

        [[nodiscard]] const term_list &get_terms() const { return m_terms; }

    private:
        const term_list m_terms;
    };

//    class and_agent_group : public ast_node {
//    public:
//        explicit and_agent_group(info info, agent_group_list lists);
//
//        [[nodiscard]] const agent_group_list &get_term_lists() const { return m_lists; }
//
//    private:
//        const agent_group_list m_lists;
//    };
//
//    class forall_agent_group : public ast_node {
//    public:
//        explicit forall_agent_group(info info, list_comprehension_ptr list_compr, agent_group_ptr list);
//
//        [[nodiscard]] const list_comprehension_ptr &get_list_compr() const { return m_list_compr; }
//        [[nodiscard]] const agent_group_ptr &get_terms() const { return m_list; }
//
//    private:
//        const list_comprehension_ptr m_list_compr;
//        const agent_group_ptr m_list;
//    };

    template<typename Elem>
    class singleton_list : public ast_node {
    public:
        explicit singleton_list(info info, Elem elem);

        [[nodiscard]] const Elem &get_elem() const { return m_elem; }

    private:
        const Elem m_elem;
    };

    template<typename Elem>
    class and_list : public ast_node {
    public:
        explicit and_list(info info, list_list<Elem> list);

        [[nodiscard]] const list_list<Elem> &get_list() const { return m_list; }

    private:
        const list_list<Elem> m_list;
    };

    template<typename Elem>
    class forall_list : public ast_node {
    public:
        explicit forall_list(info info, list_comprehension_ptr list_compr, list<Elem> list);

        [[nodiscard]] const list_comprehension_ptr &get_list_compr() const { return m_list_compr; }
        [[nodiscard]] const list<Elem> &get_list() const { return m_list; }

    private:
        const list_comprehension_ptr m_list_compr;
        const list<Elem> m_list;
    };

    class list_comprehension : public ast_node {
    public:
        explicit list_comprehension(info info, formal_param_list params, std::optional<formula_ptr> f) :
                ast_node{std::move(info)},
                m_params{std::move(params)},
                m_f{std::move(f)} {
            for (const formal_param &param : m_params) add_child(param);
            if (m_f.has_value()) std::visit([&](auto &&arg) { add_child(arg); }, *m_f);
        }

        [[nodiscard]] const formal_param_list &get_formal_params() const { return m_params; }
        [[nodiscard]] const std::optional<formula_ptr> &get_condition() const { return m_f; }

    private:
        const formal_param_list m_params;
        const std::optional<formula_ptr> m_f;
    };
}

using namespace epddl::ast;

template<typename Test, template<typename...> class Ref>
struct is_specialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref>: std::true_type {};

template<typename Elem>
singleton_list<Elem>::singleton_list(info info, Elem elem) :
        ast_node{std::move(info)},
        m_elem{std::move(elem)} {
    if constexpr (is_specialization<Elem, std::variant>::value)
        std::visit([&](auto &&arg) { add_child(arg); }, m_elem);
    else
        add_child(m_elem);
}

template<typename Elem>
and_list<Elem>::and_list(info info, list_list<Elem> list) :
        ast_node{std::move(info)},
        m_list{std::move(list)} {
    for (const ast::list<Elem> &l : m_list)
        std::visit([&](auto &&arg) { add_child(arg); }, l);
}

template<typename Elem>
forall_list<Elem>::forall_list(info info, list_comprehension_ptr list_compr, list<Elem> list) :
        ast_node{std::move(info)},
        m_list_compr{std::move(list_compr)},
        m_list{std::move(list)} {
    add_child(m_list_compr);
    std::visit([&](auto &&arg) { add_child(arg); }, m_list);
}

#endif //PLANK_FORMULAS_AST_H
