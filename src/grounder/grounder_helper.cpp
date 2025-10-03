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

#include "../../include/grounder/grounder_helper.h"
#include "../../include/grounder/language_grounder.h"
#include "../../include/grounder/initial_state/initial_state_grounder.h"
#include "../../include/grounder/actions/actions_grounder.h"
#include "../../include/grounder/formulas_grounder.h"

using namespace epddl;
using namespace epddl::grounder;

del::planning_task grounder_helper::ground(const planning_specification &spec, const context &context) {
    const del::language_ptr &language = language_grounder::build_language(spec, context);

    del::state_ptr initial_state = initial_state_grounder::build_initial_state(spec, context, language);
    del::action_deque actions = actions_grounder::build_actions(spec, context, language);
    del::formula_ptr goal = formulas_grounder::build_goal(spec, context, language);

    return del::planning_task{std::move(initial_state), std::move(actions), std::move(goal)};
}
