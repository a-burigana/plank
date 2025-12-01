// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano_
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

#include "../../../include/del/semantics/model_checker.h"

using namespace del;

bool model_checker::holds_in(const state &s, world_id w, const del::formula_ptr &f) {
    return std::visit([&](auto &&arg) {
        return model_checker::holds_in(s, w, arg);
    }, f);
}

bool model_checker::holds_in(const state &s, world_id w, const del::atom_formula_ptr &f) {
    return s.get_label(w)[f->get_atom()];
}

bool model_checker::holds_in(const state &s, world_id w, const del::not_formula_ptr &f) {
    return not model_checker::holds_in(s, w, f->get_formula());
}

bool model_checker::holds_in(const state &s, world_id w, const del::and_formula_ptr &f) {
    auto check = [&](const del::formula_ptr &f) { return model_checker::holds_in(s, w, f); };
    return std::all_of(f->get_formulas().begin(), f->get_formulas().end(), check);
}

bool model_checker::holds_in(const state &s, world_id w, const del::or_formula_ptr &f) {
    auto check = [&](const del::formula_ptr &f) { return model_checker::holds_in(s, w, f); };
    return std::any_of(f->get_formulas().begin(), f->get_formulas().end(), check);
}

bool model_checker::holds_in(const state &s, world_id w, const del::imply_formula_ptr &f) {
    return not model_checker::holds_in(s, w, f->get_first_formula()) or model_checker::holds_in(s, w, f->get_second_formula());
}

bool model_checker::holds_in(const state &s, world_id w, const del::box_formula_ptr &f) {
    return std::all_of(f->get_mod_index().begin(), f->get_mod_index().end(), [&](const del::agent &ag) {
        const auto &worlds = s.get_agent_possible_worlds(ag, w);
        return std::all_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
            return model_checker::holds_in(s, v, f->get_formula());
        });
    });
}

bool model_checker::holds_in(const state &s, world_id w, const del::diamond_formula_ptr &f) {
    return std::all_of(f->get_mod_index().begin(), f->get_mod_index().end(), [&](const del::agent &ag) {
        const auto &worlds = s.get_agent_possible_worlds(ag, w);
        return std::any_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
            return model_checker::holds_in(s, v, f->get_formula());
        });
    });
}

bool model_checker::holds_in(const state &s, world_id w, const del::kw_box_formula_ptr &f) {
    return std::all_of(f->get_mod_index().begin(), f->get_mod_index().end(), [&](const del::agent &ag) {
        const auto &worlds = s.get_agent_possible_worlds(ag, w);
        return
            std::all_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
                return model_checker::holds_in(s, v, f->get_formula());
            })
            or
            std::all_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
                return not model_checker::holds_in(s, v, f->get_formula());
            });
    });
}

bool model_checker::holds_in(const state &s, world_id w, const del::kw_diamond_formula_ptr &f) {
    return std::all_of(f->get_mod_index().begin(), f->get_mod_index().end(), [&](const del::agent &ag) {
        const auto &worlds = s.get_agent_possible_worlds(ag, w);
        return
            std::any_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
                return model_checker::holds_in(s, v, f->get_formula());
            })
            and
            std::any_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
                return not model_checker::holds_in(s, v, f->get_formula());
            });
    });
}

bool model_checker::holds_in(const state &s, world_id w, const del::c_box_formula_ptr &f) {
    return false;
}

bool model_checker::holds_in(const state &s, world_id w, const del::c_diamond_formula_ptr &f) {
    return false;
}
