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

#include "../../../../include/ast/domains/actions/obs_conditions_ast.h"

using namespace epddl::ast;

static_obs_condition::static_obs_condition(info info, identifier_ptr obs_type, term agent) :
        ast_node{std::move(info)},
        m_obs_type{std::move(obs_type)},
        m_agent{std::move(agent)} {
    add_child(m_obs_type);
    std::visit([&](auto &&arg) { add_child(arg); }, m_agent);
}

if_then_else_obs_condition::if_then_else_obs_condition(info info, if_obs_cond_ptr if_cond,
                                                       else_if_obs_cond_list else_if_conds,
                                                       std::optional<else_obs_cond_ptr> else_cond) :
        ast_node{std::move(info)},
        m_if_cond{std::move(if_cond)},
        m_else_if_conds{std::move(else_if_conds)},
        m_else_cond{std::move(else_cond)} {
    add_child(m_if_cond);
    for (const auto &cond : m_else_if_conds) add_child(cond);
    if (m_else_cond.has_value()) add_child(*m_else_cond);
}

if_obs_condition::if_obs_condition(info info, formula_ptr cond, static_obs_cond_ptr obs_cond) :
        ast_node{std::move(info)},
        m_cond{std::move(cond)},
        m_obs_cond{std::move(obs_cond)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_cond);
    add_child(m_obs_cond);
}

else_if_obs_condition::else_if_obs_condition(info info, formula_ptr cond, static_obs_cond_ptr obs_cond) :
        if_obs_condition(std::move(info), std::move(cond), std::move(obs_cond)) {}

else_obs_condition::else_obs_condition(info info, identifier_ptr obs_type, term agent) :
        static_obs_condition(std::move(info), std::move(obs_type), std::move(agent)) {}
