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

#ifndef EPDDL_PREDICATES_DECL_AST_H
#define EPDDL_PREDICATES_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/typed_elem_ast.h"
#include <memory>

namespace epddl::ast {
    class predicate_decl;
    class domain_predicates;

    using predicate_decl_ptr    = std::shared_ptr<predicate_decl>;
    using predicate_decl_list   = std::list<predicate_decl_ptr>;
    using domain_predicates_ptr = std::shared_ptr<domain_predicates>;

    class predicate_decl : public ast_node {
    public:
        explicit predicate_decl(info info, identifier_ptr name, formal_param_list params, bool is_fact) :
                ast_node{std::move(info)},
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_is_fact{is_fact} {
            add_child(m_name);
            for (const formal_param &param : m_params) add_child(param);
        }

        [[nodiscard]] const identifier_ptr &get_name() const { return m_name; }
        [[nodiscard]] const formal_param_list &get_params() const { return m_params; }
        [[nodiscard]] bool is_fact() const { return m_is_fact; }

    private:
        const identifier_ptr m_name;
        const formal_param_list m_params;
        const bool m_is_fact;
    };

    class domain_predicates : public ast_node {
    public:
        explicit domain_predicates(info info, predicate_decl_list preds) :
                ast_node{std::move(info)},
                m_preds{std::move(preds)} {
            for (const predicate_decl_ptr &p : m_preds)
                add_child(p);
        }

        [[nodiscard]] const predicate_decl_list &get_predicate_decl_list() const { return m_preds; }

    private:
        const predicate_decl_list m_preds;
    };
}

#endif //EPDDL_PREDICATES_DECL_AST_H
