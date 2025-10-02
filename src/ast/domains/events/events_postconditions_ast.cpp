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

#include "../../../../include/ast/domains/events/event_postconditions_ast.h"

using namespace epddl::ast;

literal_postcondition::literal_postcondition(info info, literal_ptr literal) :
        ast_node{std::move(info)},
        m_literal{std::move(literal)} {
    add_child(m_literal);
}

when_postcondition::when_postcondition(info info, formula_ptr cond, literal_list literals) :
        ast_node{std::move(info)},
        m_cond{std::move(cond)},
        m_literals{std::move(literals)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_cond);
    for (const literal_ptr &l : m_literals) add_child(l);
}

iff_postcondition::iff_postcondition(info info, formula_ptr cond, literal_list literals) :
        ast_node{std::move(info)},
        m_cond{std::move(cond)},
        m_literals{std::move(literals)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_cond);
    for (const literal_ptr &l : m_literals) add_child(l);
}

forall_postcondition::forall_postcondition(info info, list_comprehension_ptr params, postconditions post) :
        ast_node{std::move(info)},
        m_params{std::move(params)},
        m_post{std::move(post)} {
    add_child(m_params);
    std::visit([&](auto &&arg) { add_child(arg); }, m_post);
}

and_postcondition::and_postcondition(info info, postconditions_list post_list) :
        ast_node{std::move(info)},
        m_post_list{std::move(post_list)} {
    for (const postconditions &post : m_post_list)
        std::visit([&](auto &&arg) { add_child(arg); }, post);
}
