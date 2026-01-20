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

#include "grounder/initial_state/initial_state_grounder.h"
#include "grounder/initial_state/explicit_initial_state_grounder.h"
#include "grounder/initial_state/finitary_s5_theory_grounder.h"
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

del::state_ptr initial_state_grounder::build_initial_state(const planning_specification &spec, grounder_info &info) {
    const auto &[problem, domain, libraries] = spec;

    for (const auto &item: problem->get_items()) {
        if (std::holds_alternative<ast::initial_state_ptr>(item)) {
            auto init = std::get<ast::initial_state_ptr>(item);

            if (std::holds_alternative<ast::explicit_initial_state_ptr>(init->get_state()))
                return explicit_initial_state_grounder::build_initial_state(
                        std::get<ast::explicit_initial_state_ptr>(init->get_state()), info);
            else if (std::holds_alternative<ast::finitary_S5_theory>(init->get_state()))
                return finitary_s5_theory_grounder::build_initial_state(
                        std::get<ast::finitary_S5_theory>(init->get_state()), info);
        }
    }
    return nullptr;
}
