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

#ifndef PLANK_MODEL_CHECKER_H
#define PLANK_MODEL_CHECKER_H

#include "states/state.h"
#include "states/states_types.h"
#include "../language/formulas.h"

namespace del {
    class model_checker {
    public:
        static bool satisfies(const state_ptr &s, const del::formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::formula_ptr &f);

        static bool satisfies_prop_formula(const label &l, const del::formula_ptr &f);

    private:
        static bool holds_in(const state_ptr &s, world_id w, const del::atom_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::not_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::and_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::or_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::imply_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::box_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::diamond_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::kw_box_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::kw_diamond_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::c_box_formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const del::c_diamond_formula_ptr &f);

        static bool satisfies_prop_formula(const label &l, const del::atom_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::not_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::and_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::or_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::imply_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::box_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::diamond_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::kw_box_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::kw_diamond_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::c_box_formula_ptr &f);
        static bool satisfies_prop_formula(const label &l, const del::c_diamond_formula_ptr &f);

    };
}

#endif //PLANK_MODEL_CHECKER_H
