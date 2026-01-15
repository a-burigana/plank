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

#include "../../../../include/lib/del/language/formulas.h"
#include <algorithm>
#include <type_traits>

using namespace del;

true_formula::true_formula() {
    m_type = formula_type::true_formula;
    m_modal_depth = 0;
    m_size = 1;
}

bool true_formula::operator==(const true_formula &rhs) const {
    return true;
}

bool true_formula::operator!=(const true_formula &rhs) const {
    return false;
}

false_formula::false_formula() {
    m_type = formula_type::false_formula;
    m_modal_depth = 0;
    m_size = 1;
}

bool false_formula::operator==(const false_formula &rhs) const {
    return true;
}

bool false_formula::operator!=(const false_formula &rhs) const {
    return false;
}

atom_formula::atom_formula(atom atom) :
        m_atom{atom} {
    m_type = formula_type::atom_formula;
    m_modal_depth = 0;
    m_size = 1;
}

bool atom_formula::operator==(const atom_formula &rhs) const {
    return m_atom == rhs.m_atom;
}

bool atom_formula::operator!=(const atom_formula &rhs) const {
    return not(*this == rhs);
}

not_formula::not_formula(formula_ptr f) :
        m_f{std::move(f)} {
    m_type = formula_type::not_formula;
    m_modal_depth = formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

bool not_formula::operator==(const not_formula &rhs) const {
    return formulas_utils::are_equal(m_f, rhs.m_f);
}

bool not_formula::operator!=(const not_formula &rhs) const {
    return not(*this == rhs);
}

and_formula::and_formula(formula_deque fs) :
        m_fs{std::move(fs)} {
    m_type = formula_type::and_formula;
    auto comp = [](const formula_ptr &f1, const formula_ptr &f2) {
        return formulas_utils::get_modal_depth(f1) < formulas_utils::get_modal_depth(f2);
    };

    m_modal_depth = m_fs.empty() ? 0 : formulas_utils::get_modal_depth(
            *std::max_element(m_fs.begin(), m_fs.end(), comp));
    m_size = 1;

    for (const formula_ptr &f: m_fs)
        m_size += formulas_utils::get_size(f);
}

bool and_formula::operator==(const and_formula &rhs) const {
    return formulas_utils::are_equal(m_fs, rhs.m_fs);
}

bool and_formula::operator!=(const and_formula &rhs) const {
    return not (*this == rhs);
}

or_formula::or_formula(formula_deque fs) :
        m_fs{std::move(fs)} {
    m_type = formula_type::or_formula;
    auto comp = [](const formula_ptr &f1, const formula_ptr &f2) { return formulas_utils::get_modal_depth(f1) < formulas_utils::get_modal_depth(f2); };

    m_modal_depth = m_fs.empty() ? 0 : formulas_utils::get_modal_depth(*std::max_element(m_fs.begin(), m_fs.end(), comp));
    m_size = 1;

    for (const formula_ptr &f : m_fs)
        m_size += formulas_utils::get_size(f);
}

bool or_formula::operator==(const or_formula &rhs) const {
    return formulas_utils::are_equal(m_fs, rhs.m_fs);
}

bool or_formula::operator!=(const or_formula &rhs) const {
    return not (*this == rhs);
}

imply_formula::imply_formula(formula_ptr f1, formula_ptr f2) :
        m_f1{std::move(f1)},
        m_f2{std::move(f2)} {
    m_type = formula_type::imply_formula;
    m_modal_depth = std::max(formulas_utils::get_modal_depth(m_f1), formulas_utils::get_modal_depth(m_f2));
    m_size = 1 + formulas_utils::get_size(m_f1) + formulas_utils::get_size(m_f2);
}

bool imply_formula::operator==(const imply_formula &rhs) const {
    return
        formulas_utils::are_equal(m_f1, rhs.m_f1) and
        formulas_utils::are_equal(m_f2, rhs.m_f2);
}

bool imply_formula::operator!=(const imply_formula &rhs) const {
    return not(*this == rhs);
}

box_formula::box_formula(agent_set ags, formula_ptr f) :
        m_ags{std::move(ags)},
        m_f{std::move(f)} {
    m_type = formula_type::box_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

bool box_formula::operator==(const box_formula &rhs) const {
    return
        m_ags == rhs.m_ags and
        formulas_utils::are_equal(m_f, rhs.m_f);
}

bool box_formula::operator!=(const box_formula &rhs) const {
    return not(*this == rhs);
}

diamond_formula::diamond_formula(agent_set ags, formula_ptr f) :
        m_ags{std::move(ags)},
        m_f{std::move(f)} {
    m_type = formula_type::diamond_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

bool diamond_formula::operator==(const diamond_formula &rhs) const {
    return
        m_ags == rhs.m_ags and
        formulas_utils::are_equal(m_f, rhs.m_f);
}

bool diamond_formula::operator!=(const diamond_formula &rhs) const {
    return not(*this == rhs);
}

kw_box_formula::kw_box_formula(agent_set ags, formula_ptr f) :
        m_ags{std::move(ags)},
        m_f{std::move(f)} {
    m_type = formula_type::kw_box_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

bool kw_box_formula::operator==(const kw_box_formula &rhs) const {
    return
        m_ags == rhs.m_ags and
        formulas_utils::are_equal(m_f, rhs.m_f);
}

bool kw_box_formula::operator!=(const kw_box_formula &rhs) const {
    return not(*this == rhs);
}

kw_diamond_formula::kw_diamond_formula(agent_set ags, formula_ptr f) :
        m_ags{std::move(ags)},
        m_f{std::move(f)} {
    m_type = formula_type::kw_diamond_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

bool kw_diamond_formula::operator==(const kw_diamond_formula &rhs) const {
    return
        m_ags == rhs.m_ags and
        formulas_utils::are_equal(m_f, rhs.m_f);
}

bool kw_diamond_formula::operator!=(const kw_diamond_formula &rhs) const {
    return not(*this == rhs);
}

c_box_formula::c_box_formula(agent_set ags, formula_ptr f) :
        m_ags{std::move(ags)},
        m_f{std::move(f)} {
    m_type = formula_type::c_box_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

bool c_box_formula::operator==(const c_box_formula &rhs) const {
    return
        m_ags == rhs.m_ags and
        formulas_utils::are_equal(m_f, rhs.m_f);
}

bool c_box_formula::operator!=(const c_box_formula &rhs) const {
    return not(*this == rhs);
}

c_diamond_formula::c_diamond_formula(agent_set ags, formula_ptr f) :
        m_ags{std::move(ags)},
        m_f{std::move(f)} {
    m_type = formula_type::c_diamond_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

bool c_diamond_formula::operator==(const c_diamond_formula &rhs) const {
    return
        m_ags == rhs.m_ags and
        formulas_utils::are_equal(m_f, rhs.m_f);
}

bool c_diamond_formula::operator!=(const c_diamond_formula &rhs) const {
    return not(*this == rhs);
}

unsigned long formulas_utils::get_modal_depth(const del::formula_ptr &f) {
    return std::visit([&](auto &&arg) -> unsigned long { return arg->get_modal_depth(); }, f);
}

unsigned long formulas_utils::get_size(const del::formula_ptr &f) {
    return std::visit([&](auto &&arg) -> unsigned long { return arg->get_size(); }, f);
}

formula_type formulas_utils::get_type(const del::formula_ptr &f) {
    return std::visit([&](auto &&arg) -> formula_type { return arg->get_type(); }, f);
}

bool formulas_utils::are_equal(const formula_ptr &f1, const formula_ptr &f2) {
    return std::visit([&](auto &&arg1) {
        using arg1_type = std::remove_reference_t<decltype(arg1)>;

        return std::visit([&](auto &&arg2) {
            using arg2_type = std::remove_reference_t<decltype(arg2)>;

            if constexpr (std::is_same_v<arg1_type, arg2_type>)
                return *arg1 == *arg2;
            else
                return false;
        }, f2);
    }, f1);
}

bool formulas_utils::are_equal(const del::formula_deque &fs1, const del::formula_deque &fs2) {
    return formulas_utils::covers(fs1, fs2) and formulas_utils::covers(fs2, fs1);
}

bool formulas_utils::covers(const del::formula_deque &fs1, const del::formula_deque &fs2) {
    return std::all_of(fs1.begin(), fs1.end(), [&](const formula_ptr &f) {
        return std::any_of(fs2.begin(), fs2.end(), [&](const formula_ptr & rf) {
            return formulas_utils::are_equal(f, rf);
        });
    });
}
