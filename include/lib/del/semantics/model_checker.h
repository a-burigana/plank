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

namespace plank::del {
    class model_checker {
    public:
        static bool satisfies(const state_ptr &s, const formula_ptr &f);
        static bool holds_in(const state_ptr &s, world_id w, const formula_ptr &f);

        static bool satisfies_prop_formula(const label &l, const formula_ptr &f);

    private:
        static bool holds_in(const state_ptr &s, world_id w, const true_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const false_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const atom_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const not_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const and_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const or_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const imply_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const box_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const diamond_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const kw_box_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const kw_diamond_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const c_box_formula &f);
        static bool holds_in(const state_ptr &s, world_id w, const c_diamond_formula &f);

        static bool satisfies_prop_formula(const label &l, const true_formula &f);
        static bool satisfies_prop_formula(const label &l, const false_formula &f);
        static bool satisfies_prop_formula(const label &l, const atom_formula &f);
        static bool satisfies_prop_formula(const label &l, const not_formula &f);
        static bool satisfies_prop_formula(const label &l, const and_formula &f);
        static bool satisfies_prop_formula(const label &l, const or_formula &f);
        static bool satisfies_prop_formula(const label &l, const imply_formula &f);
        static bool satisfies_prop_formula(const label &l, const box_formula &f);
        static bool satisfies_prop_formula(const label &l, const diamond_formula &f);
        static bool satisfies_prop_formula(const label &l, const kw_box_formula &f);
        static bool satisfies_prop_formula(const label &l, const kw_diamond_formula &f);
        static bool satisfies_prop_formula(const label &l, const c_box_formula &f);
        static bool satisfies_prop_formula(const label &l, const c_diamond_formula &f);

    };
}

#endif //PLANK_MODEL_CHECKER_H
