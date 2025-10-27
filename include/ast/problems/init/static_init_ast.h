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
#include "../../common/lists_ast.h"
#include <memory>
#include <variant>

namespace epddl::ast {
    class static_init;
    using static_init_ptr = std::shared_ptr<static_init>;

    class static_init : public ast_node {
    public:
        explicit static_init(info info, list<predicate_ptr> predicates) :
                ast_node{std::move(info)},
                m_predicates{std::move(predicates)} {
            std::visit([&](auto &&arg) { add_child(arg); }, m_predicates);
        }

        [[nodiscard]] const list<predicate_ptr> &get_predicates() const { return m_predicates; }

    private:
        const list<predicate_ptr> m_predicates;
    };
}

#endif //EPDDL_STATIC_INIT_AST_H
