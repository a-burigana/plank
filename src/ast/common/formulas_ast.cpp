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

#include "../../../include/ast/common/formulas_ast.h"

using namespace epddl::ast;

//in_formula::in_formula(info info, term term, list_ptr list) :
//        ast_node{std::move(info)},
//        m_term{std::move(term)},
//        m_list{std::move(list)} {
//    std::visit([&](auto &&arg) { add_child(arg); }, m_term);
//    std::visit([&](auto &&arg) { add_child(arg); }, m_list);
//}

not_formula::not_formula(ast::info info, formula_ptr f) :
        ast_node{std::move(info)},
        m_f{std::move(f)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

and_formula::and_formula(info info, formula_list fs) :
        ast_node{std::move(info)},
        m_fs{std::move(fs)} {
    for (const formula_ptr& f : m_fs)
        std::visit([&](auto &&arg) { add_child(arg); }, f);
}

or_formula::or_formula(info info, formula_list fs) :
        ast_node{std::move(info)},
        m_fs{std::move(fs)} {
    for (const formula_ptr& f : m_fs)
        std::visit([&](auto &&arg) { add_child(arg); }, f);
}

imply_formula::imply_formula(info info, formula_ptr f1, formula_ptr f2) :
        ast_node{std::move(info)},
        m_f1{std::move(f1)},
        m_f2{std::move(f2)} {
    std::visit([&](auto &&arg) { add_child(arg); }, m_f1);
    std::visit([&](auto &&arg) { add_child(arg); }, m_f2);
}

box_formula::box_formula(info info, modality_ptr mod, formula_ptr f) :
        ast_node{std::move(info)},
        m_mod{std::move(mod)},
        m_f{std::move(f)} {
    add_child(m_mod);
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

diamond_formula::diamond_formula(info info, modality_ptr mod, formula_ptr f) :
        ast_node{std::move(info)},
        m_mod{std::move(mod)},
        m_f{std::move(f)} {
    add_child(m_mod);
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

forall_formula::forall_formula(info info, list_comprehension_ptr params, formula_ptr f) :
        ast_node{std::move(info)},
        m_params{std::move(params)},
        m_f{std::move(f)} {
    add_child(m_params);
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

exists_formula::exists_formula(info info, list_comprehension_ptr params, formula_ptr f) :
        ast_node{std::move(info)},
        m_params{std::move(params)},
        m_f{std::move(f)} {
    add_child(m_params);
    std::visit([&](auto &&arg) { add_child(arg); }, m_f);
}

modality::modality(info info, std::optional<modality_name_ptr> name, modality_index_ptr index) :
        ast_node{std::move(info)},
        m_name{std::move(name)},
        m_index{std::move(index)} {
    if (m_name.has_value()) add_child(*m_name);

    if (std::holds_alternative<term>(m_index))
        std::visit([&](auto &&arg) { add_child(arg); }, std::get<term>(m_index));
    else if (std::holds_alternative<list_ptr>(m_index))
        std::visit([&](auto &&arg) { add_child(arg); }, std::get<list_ptr>(m_index));
    else if (std::holds_alternative<all_group_modality_ptr>(m_index))
        add_child((std::get<all_group_modality_ptr>(m_index)));
}

and_list::and_list(info info, list_list lists) :
        ast_node{std::move(info)},
        m_lists{std::move(lists)} {
    for (const list_ptr &list : m_lists)
        std::visit([&](auto &&arg) { add_child(arg); }, list);
}

forall_list::forall_list(info info, list_comprehension_ptr list_compr, list_ptr list) :
        ast_node{std::move(info)},
        m_list_compr{std::move(list_compr)},
        m_list{std::move(list)} {
    add_child(m_list_compr);
    std::visit([&](auto &&arg) { add_child(arg); }, m_list);
}
