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

#include "../../../include/lib/grounder/grounder_helper.h"
#include "../../../include/lib/grounder/grounder_info.h"
#include "../../../include/lib/grounder/language_grounder.h"
#include "../../../include/lib/grounder/initial_state/initial_state_grounder.h"
#include "../../../include/lib/grounder/actions/actions_grounder.h"
#include "../../../include/lib/grounder/formulas/formulas_and_lists_grounder.h"
#include "../../../include/lib/grounder/initial_state/facts_init_grounder.h"

using namespace epddl;
using namespace epddl::grounder;

std::pair<del::planning_task, grounder_info>
grounder_helper::ground(const planning_specification &spec, context &context, spec_error_managers err_managers) {
    grounder_info info = grounder_helper::build_info(spec, context, std::move(err_managers));

    del::state_ptr initial_state = initial_state_grounder::build_initial_state(spec, info);
    del::action_map actions = actions_grounder::build_actions(spec, info);
    del::formula_ptr goal = formulas_and_lists_grounder::build_goal(spec, info);
    del::planning_task task = del::planning_task{std::move(initial_state), std::move(actions), std::move(goal)};

    return {std::move(task), std::move(info)};
}

grounder_info grounder_helper::build_info(const planning_specification &spec, context &context,
                                          spec_error_managers err_managers) {
    del::language_ptr language = language_grounder::build_language(context);
    variables_assignment assignment;
    del::atom_set empty{language->get_atoms_number()};

    grounder_info info{std::move(context), std::move(assignment),
                       empty, std::move(language), std::move(err_managers)};

    info.facts = facts_init_grounder::build_facts(spec, info);

    return info;
}
