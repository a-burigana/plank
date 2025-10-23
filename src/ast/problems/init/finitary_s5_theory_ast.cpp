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

#include "../../../../include/ast/problems/init/finitary_s5_theory_ast.h"

using namespace epddl::ast;

prop_formula::prop_formula(ast::info info, formula_ptr f) :
        ast_node{std::move(info)},
        m_f{std::move(f)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

ck_formula::ck_formula(ast::info info, formula_ptr f) :
        ast_node{std::move(info)},
        m_f{std::move(f)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

ck_k_formula::ck_k_formula(info info, term agent, formula_ptr f) :
        ast_node{std::move(info)},
        m_agent{std::move(agent)},
        m_f{std::move(f)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_agent);
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

ck_kw_formula::ck_kw_formula(info info, term agent, formula_ptr f) :
        ast_node{std::move(info)},
        m_agent{std::move(agent)},
        m_f{std::move(f)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_agent);
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

ck_not_kw_formula::ck_not_kw_formula(info info, term agent, formula_ptr f) :
        ast_node{std::move(info)},
        m_agent{std::move(agent)},
        m_f{std::move(f)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_agent);
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

and_theory::and_theory(info info, finitary_S5_theory_list list) :
        ast_node{std::move(info)},
        m_list{std::move(list)} {
    for (const finitary_S5_theory &theory : m_list)
        if (std::holds_alternative<finitary_S5_formula>(theory))
            std::visit([&](auto &&arg) { add_child(arg); }, std::get<finitary_S5_formula>(theory));
        else if (std::holds_alternative<and_theory_ptr>(theory))
            add_child(std::get<and_theory_ptr>(theory));
        else if (std::holds_alternative<forall_theory_ptr>(theory))
            add_child(std::get<forall_theory_ptr>(theory));
}

forall_theory::forall_theory(info info, list_comprehension_ptr list_compr, finitary_S5_theory theory) :
        ast_node{std::move(info)},
        m_list_compr{std::move(list_compr)},
        m_theory{std::move(theory)} {
    add_child(list_compr);

    if (std::holds_alternative<finitary_S5_formula>(m_theory))
        std::visit([&](auto &&arg) { add_child(arg); }, std::get<finitary_S5_formula>(m_theory));
    else if (std::holds_alternative<and_theory_ptr>(m_theory))
        add_child(std::get<and_theory_ptr>(m_theory));
    else if (std::holds_alternative<forall_theory_ptr>(m_theory))
        add_child(std::get<forall_theory_ptr>(m_theory));
}
