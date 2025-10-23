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

#include "../../../../include/ast/problems/init/static_init_ast.h"

using namespace epddl::ast;

and_static_literal_list::and_static_literal_list(info info, static_literal_list list) :
        ast_node{std::move(info)},
        m_list{std::move(list)} {
    for (const static_literals &l : m_list)
        std::visit([&](auto &&arg) { add_child(arg); }, l);
}

forall_static_literal_list::forall_static_literal_list(info info, list_comprehension_ptr list_compr,
                                                       static_literals literal) :
        ast_node{std::move(info)},
        m_list_compr{std::move(list_compr)},
        m_literal{std::move(literal)} {
    add_child(m_list_compr);
    std::visit([&](auto &&arg) { add_child(arg); }, m_literal);
}

static_init::static_init(info info, static_literals literals) :
        ast_node{std::move(info)},
        m_literals{std::move(literals)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_literals);
}
