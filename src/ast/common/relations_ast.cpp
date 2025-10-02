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

#include "../../../include/ast/common/relations_ast.h"

using namespace epddl::ast;

agent_relation::agent_relation(info info, identifier_ptr obs_group, relation_ptr relation) :
        ast_node{std::move(info)},
        m_obs_group{std::move(obs_group)},
        m_relation{std::move(relation)} {
    add_child(m_obs_group);
    std::visit([&](auto &&arg) { add_child(arg); }, m_relation);
}

and_relation::and_relation(info info, relation_list relation_list) :
        ast_node{std::move(info)},
        m_relation_list{std::move(relation_list)} {
    for (const relation_ptr &r : m_relation_list)
        std::visit([&](auto &&arg) { add_child(arg); }, r);
}

forall_relation::forall_relation(info info, list_comprehension_ptr params, relation_ptr r) :
        ast_node{std::move(info)},
        m_params{std::move(params)},
        m_r{std::move(r)} {
    add_child(m_params);
    std::visit([&](auto &&arg) { add_child(arg); }, m_r);
}
