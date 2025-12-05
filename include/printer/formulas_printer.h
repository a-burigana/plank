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

#ifndef EPDDL_FORMULAS_PRINTER_H
#define EPDDL_FORMULAS_PRINTER_H

#include "../utils/json.hpp"
#include "../del/language/language.h"
#include "../del/language/formulas.h"

using namespace nlohmann;

namespace epddl::printer {
    class formulas_printer {
    public:
        static json build_formula_json(const del::language_ptr &language, const del::formula_ptr &f);

    private:
        static json build_formula_json(const del::language_ptr &language, const del::true_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::false_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::atom_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::not_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::and_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::or_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::imply_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::box_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::diamond_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::kw_box_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::kw_diamond_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::c_box_formula_ptr &f);
        static json build_formula_json(const del::language_ptr &language, const del::c_diamond_formula_ptr &f);

        static json build_agent_set_json(const del::language_ptr &language, const del::agent_set &ags,
                                         bool simplify_singleton = true);
    };
}

#endif //EPDDL_FORMULAS_PRINTER_H
