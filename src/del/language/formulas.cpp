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

#include "../../../include/del/language/formulas.h"

using namespace del;

true_formula::true_formula() {
    m_type = formula_type::true_formula;
    m_modal_depth = 0;
}

false_formula::false_formula() {
    m_type = formula_type::false_formula;
    m_modal_depth = 0;
}

atom_formula::atom_formula(atom atom) :
        m_atom{atom} {
    m_type = formula_type::atom_formula;
    m_modal_depth = 0;
}

not_formula::not_formula(formula_ptr f) :
        m_f{std::move(f)} {
    m_type = formula_type::not_formula;
    m_modal_depth = formulas_utils::get_modal_depth(m_f);
}

and_formula::and_formula(formula_deque fs) :
        m_fs{std::move(fs)} {
    m_type = formula_type::and_formula;
    auto comp = [](const formula_ptr &f1, const formula_ptr &f2) { return formulas_utils::get_modal_depth(f1) < formulas_utils::get_modal_depth(f2); };

    m_modal_depth = m_fs.empty() ? 0 : formulas_utils::get_modal_depth(*std::max_element(m_fs.begin(), m_fs.end(), comp));
}

or_formula::or_formula(formula_deque fs) :
        m_fs{std::move(fs)} {
    m_type = formula_type::or_formula;
    auto comp = [](const formula_ptr &f1, const formula_ptr &f2) { return formulas_utils::get_modal_depth(f1) < formulas_utils::get_modal_depth(f2); };

    m_modal_depth = m_fs.empty() ? 0 : formulas_utils::get_modal_depth(*std::max_element(m_fs.begin(), m_fs.end(), comp));
}

imply_formula::imply_formula(formula_ptr f1, formula_ptr f2) :
        m_f1{std::move(f1)},
        m_f2{std::move(f2)} {
    m_type = formula_type::imply_formula;
    m_modal_depth = std::max(formulas_utils::get_modal_depth(m_f1), formulas_utils::get_modal_depth(m_f2));
}

box_formula::box_formula(agent_group ag, formula_ptr f) :
        m_ag{std::move(ag)},
        m_f{std::move(f)} {
    m_type = formula_type::box_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
}

diamond_formula::diamond_formula(agent_group ag, formula_ptr f) :
        m_ag{std::move(ag)},
        m_f{std::move(f)} {
    m_type = formula_type::diamond_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
}

kw_box_formula::kw_box_formula(agent_group ag, formula_ptr f) :
        m_ag{std::move(ag)},
        m_f{std::move(f)} {
    m_type = formula_type::kw_box_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
}

kw_diamond_formula::kw_diamond_formula(agent_group ag, formula_ptr f) :
        m_ag{std::move(ag)},
        m_f{std::move(f)} {
    m_type = formula_type::kw_diamond_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
}

c_box_formula::c_box_formula(agent_group ag, formula_ptr f) :
        m_ag{std::move(ag)},
        m_f{std::move(f)} {
    m_type = formula_type::c_box_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
}

c_diamond_formula::c_diamond_formula(agent_group ag, formula_ptr f) :
        m_ag{std::move(ag)},
        m_f{std::move(f)} {
    m_type = formula_type::c_diamond_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
}

unsigned long formulas_utils::get_modal_depth(const del::formula_ptr &f) {
    return std::visit([&](auto &&arg) -> unsigned long { return arg->get_modal_depth(); }, f);
}
