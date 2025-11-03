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

#ifndef EPDDL_FORMULAS_GROUNDER_H
#define EPDDL_FORMULAS_GROUNDER_H

#include "../type-checker/context.h"
#include "../del/language/language.h"
#include "../del/language/formulas.h"

using namespace epddl::type_checker;

namespace epddl::grounder {
    class formulas_grounder {
    public:
        static del::formula_ptr build_goal(const planning_specification &spec, const context &context,
                                           const del::language_ptr &language);

        static del::formula_ptr build_formula(const ast::formula_ptr &f, const context &context, const del::language_ptr &language);

    private:
        static del::formula_ptr build_formula(const ast::true_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::false_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::predicate_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::not_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::and_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::or_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::imply_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::box_formula_ptr &f, const context &context, const del::language_ptr &language);
        static del::formula_ptr build_formula(const ast::diamond_formula_ptr &f, const context &context, const del::language_ptr &language);
    };
}

#endif //EPDDL_FORMULAS_GROUNDER_H
