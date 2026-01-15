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

#ifndef PLANK_INITIAL_STATES_TYPE_CHECKER_H
#define PLANK_INITIAL_STATES_TYPE_CHECKER_H

#include "../context/context.h"
#include "../../ast/problems/init/initial_state_decl_ast.h"

namespace epddl::type_checker {
    class initial_states_type_checker {
    public:
        static void check(const ast::initial_state_ptr &state, context &context, error_manager_ptr &err_manager);

    private:
        static void check_state(const ast::explicit_initial_state_ptr &state, context &context,
                                error_manager_ptr &err_manager);
        static void check_state(const ast::finitary_S5_theory &state, context &context,
                                error_manager_ptr &err_manager);

        static void check_world_label(const ast::world_label_ptr &l, context &context, error_manager_ptr &err_manager);

        static void check_formula(const ast::finitary_S5_formula &formula, context &context,
                                  error_manager_ptr &err_manager);

        static void check_formula(const ast::prop_formula_ptr &formula, context &context,
                                  error_manager_ptr &err_manager);
        static void check_formula(const ast::ck_formula_ptr &formula, context &context,
                                  error_manager_ptr &err_manager);
        static void check_formula(const ast::ck_k_formula_ptr &formula, context &context,
                                  error_manager_ptr &err_manager);
        static void check_formula(const ast::ck_kw_formula_ptr &formula, context &context,
                                  error_manager_ptr &err_manager);
        static void check_formula(const ast::ck_not_kw_formula_ptr &formula, context &context,
                                  error_manager_ptr &err_manager);
    };
}

#endif //PLANK_INITIAL_STATES_TYPE_CHECKER_H
