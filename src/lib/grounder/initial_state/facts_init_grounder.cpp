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

#include "../../../../include/lib/grounder/initial_state/facts_init_grounder.h"
#include "../../../../include/lib/grounder/formulas/formulas_and_lists_grounder.h"
#include "../../../../include/lib/grounder/language_grounder.h"
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

del::atom_set facts_init_grounder::build_facts(const planning_specification &spec, grounder_info &info) {
    const auto &[problem, domain, libraries] = spec;
    ast::facts_init_ptr init;

    for (const ast::problem_item &item: problem->get_items())
        if (std::holds_alternative<ast::facts_init_ptr>(item))
            init = std::get<ast::facts_init_ptr>(item);

    del::atom_set facts{info.language->get_atoms_number()};

    if (init)
        for (const ast::predicate_ptr &fact : init->get_facts())
            facts.push_back(language_grounder::get_predicate_id(fact, info));

    return facts;
}
