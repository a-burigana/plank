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

#ifndef EPDDL_MODEL_CHECKER_H
#define EPDDL_MODEL_CHECKER_H

#include "states/state.h"
#include "states/states_types.h"
#include "../formulas/all_formulas.h"

namespace del {
    class model_checker {
    public:
        static bool holds_in(const state &s, world_id w, const del::formula &f, const del::label_storage &l_storage);

    private:
        static bool holds_in(const state &s, world_id w, const del::atom_formula &f, const del::label_storage &l_storage);
        static bool holds_in(const state &s, world_id w, const del::not_formula &f, const del::label_storage &l_storage);
        static bool holds_in(const state &s, world_id w, const del::and_formula &f, const del::label_storage &l_storage);
        static bool holds_in(const state &s, world_id w, const del::or_formula &f, const del::label_storage &l_storage);
        static bool holds_in(const state &s, world_id w, const del::imply_formula &f, const del::label_storage &l_storage);
        static bool holds_in(const state &s, world_id w, const del::box_formula &f, const del::label_storage &l_storage);
        static bool holds_in(const state &s, world_id w, const del::diamond_formula &f, const del::label_storage &l_storage);
    };
}

#endif //EPDDL_MODEL_CHECKER_H
