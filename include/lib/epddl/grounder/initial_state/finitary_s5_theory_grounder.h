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

#ifndef PLANK_FINITARY_S5_THEORY_GROUNDER_H
#define PLANK_FINITARY_S5_THEORY_GROUNDER_H

#include "grounder/grounder_info.h"
#include "type-checker/context/context.h"
#include "../../../del/semantics/states/state.h"
#include "../../../del/semantics/states/finitary_s5_theory.h"
#include "ast/problems/init/finitary_s5_theory_ast.h"

using namespace epddl::type_checker;

namespace epddl::grounder {
    class finitary_s5_theory_grounder {
    public:
        static del::finitary_s5_theory_ptr build_finitary_s5_theory(const ast::finitary_S5_theory &init,
                                                                    grounder_info &info);
        static del::state_ptr build_initial_state(const ast::finitary_S5_theory &init, grounder_info &info);

    private:
        static std::pair<del::label_vector, del::world_bitset>
        compute_labels_and_designated(const ast::finitary_S5_theory &init, const del::finitary_s5_theory_ptr &theory,
                                      grounder_info &info);
        static del::relations
        compute_relations(const ast::finitary_S5_theory &init, const del::finitary_s5_theory_ptr &theory,
                          const del::label_vector &l, grounder_info &info, del::world_id worlds_no);

        static bool agree_on_formula(const del::label &l1, const del::label &l2, const del::formula_ptr &f);
        static boost::dynamic_bitset<> next_bitset(const boost::dynamic_bitset<> &current);
        static boost::dynamic_bitset<> next_bitset(const boost::dynamic_bitset<> &current,
                                                   const boost::dynamic_bitset<> &fixed_bits);

        static std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<>>
        compute_fixed_literal_set(const del::formula_deque &fs, const grounder_info &info);
        static std::optional<std::pair<del::atom, bool>>
        is_literal(const del::formula_ptr &f);

        static void check_worlds(error_manager_ptr &err_manager, const ast::finitary_S5_theory &init,
                                 del::world_id worlds_no, del::world_id designated_no);
    };
}

#endif //PLANK_FINITARY_S5_THEORY_GROUNDER_H
