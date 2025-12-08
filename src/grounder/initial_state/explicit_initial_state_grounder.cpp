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

#include "../../../include/grounder/initial_state/explicit_initial_state_grounder.h"
#include "../../../include/grounder/formulas/formulas_and_lists_grounder.h"
#include "../../../include/grounder/relations/relations_grounder.h"
#include <memory>

using namespace epddl;
using namespace epddl::grounder;

del::state_ptr explicit_initial_state_grounder::build_initial_state(const ast::explicit_initial_state_ptr &state,
                                                                    grounder_info &info) {
    info.context.entities.push();
    info.context.entities.add_decl_list(state->get_worlds(),
                                        type_checker::either_type{info.context.types.get_type_id("world")});

    info.context.entities.update_typed_entities_sets(info.context.types);

    unsigned long worlds_no = state->get_worlds().size();
    type_checker::name_id_map worlds_ids;
    del::world_id id = 0;

    for (const ast::identifier_ptr &w: state->get_worlds())
        worlds_ids[w->get_token().get_lexeme()] = id++;

    name_id_map agents_ids = info.language->get_agents_name_map();

    del::relations r = relations_grounder::build_relations<ast::term>(
            state->get_relations(), info, worlds_ids, agents_ids, worlds_no);

    del::label_vector labels(worlds_no);

    for (const world_label_ptr &l : state->get_labels())
        labels[worlds_ids.at(l->get_world_name()->get_token().get_lexeme())] =
                explicit_initial_state_grounder::build_label(l, info);

    del::world_bitset designated{worlds_no};

    for (const ast::identifier_ptr &w_d: state->get_designated())
        designated.push_back(worlds_ids.at(w_d->get_token().get_lexeme()));

    info.context.entities.pop();
    return std::make_shared<del::state>(info.language, worlds_no, std::move(r),
                                        std::move(labels), std::move(designated));
}

del::label explicit_initial_state_grounder::build_label(const ast::world_label_ptr &l, grounder_info &info) {
    boost::dynamic_bitset<> ground_atoms(info.language->get_atoms_number());

    auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
            ast::predicate_ptr, del::atom>(
        [&](const ast::predicate_ptr &p, grounder_info &info, const type_ptr &default_type) {
            return language_grounder::get_predicate_id(p, info);
        });

    auto l_atoms = formulas_and_lists_grounder::build_list<ast::predicate_ptr, del::atom>(
            l->get_predicates(), ground_elem, info, info.context.types.get_type("object"));

    for (const del::atom p : l_atoms)
        ground_atoms.push_back(p);

    return del::label{std::move(ground_atoms)};
}
