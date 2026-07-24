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

#include "epddl/grounder/initial_state/explicit_initial_state_grounder.h"
#include "epddl/grounder/formulas/formulas_and_lists_grounder.h"
#include "epddl/grounder/relations/relations_grounder.h"
#include <memory>

using namespace plank;
using namespace plank::epddl;
using namespace plank::epddl::grounder;

del::state_ptr explicit_initial_state_grounder::build_initial_state(const ast::explicit_initial_state_ptr &state,
                                                                    grounder_info &info) {
    info.context.entities.push();
    info.context.entities.add_decl_list(info.err_managers.problem_err_manager, state->get_worlds(),
                                        type_checker::either_type{info.context.types.get_type_id("world")});

    info.context.entities.update_typed_entities_sets(info.context.types);

    unsigned long worlds_no = state->get_worlds().size();
    name_vector world_names;
    name_id_map worlds_ids;
    del::world_id id = 0;

    for (const ast::identifier_ptr &w: state->get_worlds()) {
        worlds_ids[w->get_token().get_lexeme()] = id++;
        world_names.emplace_back(w->get_token().get_lexeme());
    }

    const name_id_map agents_ids = info.language->get_agents_name_map();

    del::relations r = relations_grounder::build_relations<ast::term>(
            state->get_relations(), info, worlds_ids, agents_ids,
            info.language->get_agents_number(), worlds_no);
    del::label_id_vector labels =
            explicit_initial_state_grounder::build_label_id_vector(state, worlds_ids, worlds_no, info);
    del::world_bitset designated{worlds_no};

    for (const ast::identifier_ptr &w_d: state->get_designated())
        designated.push_back(worlds_ids.at(w_d->get_token().get_lexeme()));

    info.context.entities.pop();
    return std::make_shared<del::state>(info.language, info.label_storage, worlds_no, std::move(r),
                                        std::move(labels), std::move(designated),
                                        std::move(world_names));
}

del::label_id_vector
explicit_initial_state_grounder::build_label_id_vector(const ast::explicit_initial_state_ptr &state,
                                                    const name_id_map &worlds_ids, del::world_id worlds_no,
                                                    grounder_info &info) {
    boost::dynamic_bitset<> facts_bitset(info.language->get_atoms_number());

    for (del::atom p = 0; p < info.language->get_atoms_number(); ++p)
        if (info.language->is_fact(p))
            facts_bitset[p] = info.facts.get_bitset()[p];

    del::label_id_vector labels(worlds_no);
    std::unordered_set<std::string> visited_worlds;

    for (const world_label_ptr &l : state->get_labels()) {
        labels[worlds_ids.at(l->get_world_name()->get_token().get_lexeme())] =
                explicit_initial_state_grounder::build_label(l, facts_bitset, info);

        visited_worlds.emplace(l->get_world_name()->get_token_ptr()->get_lexeme());
    }

    // We initialize all labels of non-visited worlds with the initialized facts. In this way,
    // if a label is not declared for a world 'w', we still correctly set its label
    const del::label_id facts_id = info.label_storage->emplace(del::label{facts_bitset});

    for (const ast::identifier_ptr &w : state->get_worlds())
        if (visited_worlds.find(w->get_token_ptr()->get_lexeme()) == visited_worlds.end())
            labels[worlds_ids.at(w->get_token_ptr()->get_lexeme())] = facts_id;

    return labels;
}

del::label_id explicit_initial_state_grounder::build_label(const ast::world_label_ptr &l,
                                                           const boost::dynamic_bitset<> &facts_bitset,
                                                           grounder_info &info) {
    boost::dynamic_bitset<> ground_atoms = facts_bitset;

    const auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
            ast::predicate_ptr, del::atom>(
        [&](const ast::predicate_ptr &p, grounder_info &info, const type_ptr &default_type) {
            return language_grounder::get_predicate_id(p, info);
        });

    const auto l_atoms = formulas_and_lists_grounder::build_list<ast::predicate_ptr, del::atom>(
            l->get_predicates(), ground_elem, info, info.context.types.get_type("object"));

    for (const del::atom p : l_atoms)
        ground_atoms[p] = true;

    return info.label_storage->emplace(del::label{std::move(ground_atoms)});
}
