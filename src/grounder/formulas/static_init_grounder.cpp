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

#include "../../../include/grounder/formulas/static_init_grounder.h"
#include "../../../include/grounder/formulas/formulas_and_lists_grounder.h"
#include "../../../include/grounder/language_grounder.h"
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

del::atom_set static_init_grounder::build_static_atom_set(const planning_specification &spec, grounder_info &info) {
    const auto &[problem, domain, libraries] = spec;
    ast::static_init_ptr init;

    for (const ast::problem_item &item: problem->get_items())
        if (std::holds_alternative<ast::static_init_ptr>(item))
            init = std::get<ast::static_init_ptr>(item);

    del::atom_set static_atoms{info.language->get_atoms_number()};
    variables_assignment assignment{info.context.entities};

    if (init) {
        auto ground_elem = formulas_and_lists_grounder::grounding_function_t<ast::predicate_ptr, unsigned long>(
            [&](const ast::predicate_ptr &p, grounder_info &info, const type_ptr &default_type) {
                return language_grounder::get_predicate_id(p, info);
            });

        auto atoms_ids = formulas_and_lists_grounder::build_list<ast::predicate_ptr, unsigned long>(
                init->get_predicates(), ground_elem, info, type_utils::find(info.types_tree, "entities"));

        for (const unsigned long p: atoms_ids)
            static_atoms.push_back(p);
    }
    return static_atoms;
}
