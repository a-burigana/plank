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

using namespace plank::del;

true_formula::true_formula() {
    m_type = formula_type::true_formula;
    m_modal_depth = 0;
    m_size = 1;
}

false_formula::false_formula() {
    m_type = formula_type::false_formula;
    m_modal_depth = 0;
    m_size = 1;
}

atom_formula::atom_formula(const atom atom) :
        m_atom{atom} {
    m_type = formula_type::atom_formula;
    m_modal_depth = 0;
    m_size = 1;
}

not_formula::not_formula(const formula_id f_id, const formula_storage_ptr &storage) :
    m_f_id{f_id} {
    m_f = storage->get(m_f_id);

    m_type = formula_type::not_formula;
    m_modal_depth = formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

and_formula::and_formula(formula_id_deque fs_ids, const formula_storage_ptr &storage) :
        m_fs_ids{std::move(fs_ids)} {
    for (const formula_id &f_id : m_fs_ids)
        m_fs.emplace_back(storage->get(f_id));

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

or_formula::or_formula(formula_id_deque fs_ids, const formula_storage_ptr &storage) :
        m_fs_ids{std::move(fs_ids)} {
    for (const formula_id &f_id : m_fs_ids)
        m_fs.emplace_back(storage->get(f_id));

    m_type = formula_type::or_formula;

    auto comp = [](const formula_ptr &f1, const formula_ptr &f2) {
        return formulas_utils::get_modal_depth(f1) < formulas_utils::get_modal_depth(f2);
    };

    m_modal_depth = m_fs.empty() ? 0 : formulas_utils::get_modal_depth(
        *std::max_element(m_fs.begin(), m_fs.end(), comp));
    m_size = 1;

    for (const formula_ptr &f : m_fs)
        m_size += formulas_utils::get_size(f);
}

imply_formula::imply_formula(const formula_id f1_id, const formula_id f2_id, const formula_storage_ptr &storage) :
        m_f1_id{f1_id},
        m_f2_id{f2_id} {
    m_f1 = storage->get(m_f1_id);
    m_f2 = storage->get(m_f2_id);

    m_type = formula_type::imply_formula;
    m_modal_depth = std::max(formulas_utils::get_modal_depth(m_f1), formulas_utils::get_modal_depth(m_f2));
    m_size = 1 + formulas_utils::get_size(m_f1) + formulas_utils::get_size(m_f2);
}

box_formula::box_formula(agent_set ags, const formula_id f_id, const formula_storage_ptr &storage) :
        m_ags{std::move(ags)},
        m_f_id{f_id} {
    m_f = storage->get(m_f_id);

    m_type = formula_type::box_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

diamond_formula::diamond_formula(agent_set ags, const formula_id f_id, const formula_storage_ptr &storage) :
        m_ags{std::move(ags)},
        m_f_id{f_id} {
    m_f = storage->get(m_f_id);

    m_type = formula_type::diamond_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

kw_box_formula::kw_box_formula(agent_set ags, const formula_id f_id, const formula_storage_ptr &storage) :
        m_ags{std::move(ags)},
        m_f_id{f_id} {
    m_f = storage->get(m_f_id);

    m_type = formula_type::kw_box_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

kw_diamond_formula::kw_diamond_formula(agent_set ags, const formula_id f_id, const formula_storage_ptr &storage) :
        m_ags{std::move(ags)},
        m_f_id{f_id} {
    m_f = storage->get(m_f_id);

    m_type = formula_type::kw_diamond_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

c_box_formula::c_box_formula(agent_set ags, const formula_id f_id, const formula_storage_ptr &storage) :
        m_ags{std::move(ags)},
        m_f_id{f_id} {
    m_f = storage->get(m_f_id);

    m_type = formula_type::c_box_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}

c_diamond_formula::c_diamond_formula(agent_set ags, const formula_id f_id, const formula_storage_ptr &storage) :
        m_ags{std::move(ags)},
        m_f_id{f_id} {
    m_f = storage->get(m_f_id);

    m_type = formula_type::c_diamond_formula;
    m_modal_depth = 1 + formulas_utils::get_modal_depth(m_f);
    m_size = 1 + formulas_utils::get_size(m_f);
}


unsigned long formulas_utils::get_modal_depth(const formula_ptr &f) {
    return std::visit([&](auto &&arg) -> unsigned long { return arg.get_modal_depth(); }, *f);
}

unsigned long formulas_utils::get_size(const formula_ptr &f) {
    return std::visit([&](auto &&arg) -> unsigned long { return arg.get_size(); }, *f);
}

formula_type formulas_utils::get_type(const formula_ptr &f) {
    return std::visit([&](auto &&arg) -> formula_type { return arg.get_type(); }, *f);
}

bool formulas_utils::are_equal(const formula_ptr &f1, const formula_ptr &f2) {
    return std::visit([&](auto &&arg1) {
        using arg1_type = std::remove_reference_t<decltype(arg1)>;

        return std::visit([&](auto &&arg2) {
            using arg2_type = std::remove_reference_t<decltype(arg2)>;

            if constexpr (std::is_same_v<arg1_type, arg2_type>)
                return arg1 == arg2;
            else
                return false;
        }, *f2);
    }, *f1);
}

bool formulas_utils::are_equal(const formula_deque &fs1, const formula_deque &fs2) {
    return formulas_utils::covers(fs1, fs2) and formulas_utils::covers(fs2, fs1);
}

bool formulas_utils::covers(const formula_deque &fs1, const formula_deque &fs2) {
    return std::all_of(fs1.begin(), fs1.end(), [&](const formula_ptr &f) {
        return std::any_of(fs2.begin(), fs2.end(), [&](const formula_ptr & rf) {
            return formulas_utils::are_equal(f, rf);
        });
    });
}

agent_set formulas_utils::get_mod_index(const formula_ptr &f) {
    return std::visit([&](auto &&arg) -> agent_set {
        return get_mod_index(arg);
    }, *f);
}

agent_set formulas_utils::get_mod_index(const true_formula &f) {
    return agent_set{};
}

agent_set formulas_utils::get_mod_index(const false_formula &f) {
    return agent_set{};
}

agent_set formulas_utils::get_mod_index(const atom_formula &f) {
    return agent_set{};
}

agent_set formulas_utils::get_mod_index(const not_formula &f) {
    return agent_set{};
}

agent_set formulas_utils::get_mod_index(const and_formula &f) {
    return agent_set{};
}

agent_set formulas_utils::get_mod_index(const or_formula &f) {
    return agent_set{};
}

agent_set formulas_utils::get_mod_index(const imply_formula &f) {
    return agent_set{};
}

agent_set formulas_utils::get_mod_index(const box_formula &f) {
    return f.get_mod_index();
}

agent_set formulas_utils::get_mod_index(const diamond_formula &f) {
    return f.get_mod_index();
}

agent_set formulas_utils::get_mod_index(const kw_box_formula &f) {
    return f.get_mod_index();
}

agent_set formulas_utils::get_mod_index(const kw_diamond_formula &f) {
    return f.get_mod_index();
}

agent_set formulas_utils::get_mod_index(const c_box_formula &f) {
    return f.get_mod_index();
}

agent_set formulas_utils::get_mod_index(const c_diamond_formula &f) {
    return f.get_mod_index();
}
