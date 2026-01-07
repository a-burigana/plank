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

#include "../../../../../include/del/semantics/states/bisimulations/contraction_builder.h"
#include "../../../../../include/del/semantics/states/bisimulations/partition_refinement.h"
#include "../../../../../include/del/semantics/states/state.h"

using namespace del;

state_ptr contraction_builder::calculate_standard_contraction(const state_ptr &s) {
    bpr_structures structures = partition_refinement::do_all_refinement_steps(s);
    return contraction_helper(s, structures);
}

state_ptr contraction_builder::contraction_helper(const state_ptr &s, bpr_structures &structures) {
    const block_vector &worlds_blocks = structures.worlds_blocks;
    world_id quotient_worlds_no = structures.Q.size();

    std::vector<world_id> contracted_worlds_map = std::vector<world_id>(s->get_worlds_number());
    relations quotient_r = relations(s->get_language()->get_agents_number());
    label_vector quotient_v = label_vector(quotient_worlds_no);
    world_bitset designated_worlds(quotient_worlds_no);

    for (world_id w = 0; w < quotient_worlds_no; ++w)
        for (const world_id v : *structures.Q[w])
            contracted_worlds_map[v] = w;

    for (del::agent ag = 0; ag < s->get_language()->get_agents_number(); ++ag) {
        quotient_r[ag] = agent_relation(quotient_worlds_no);

        for (world_id w = 0; w < quotient_worlds_no; ++w)
            quotient_r[ag][w] = world_bitset(quotient_worlds_no);
    }

    for (world_id x = 0; x < s->get_worlds_number(); ++x)
        for (del::agent ag = 0; ag < s->get_language()->get_agents_number(); ++ag)
            for (const world_id y : s->get_agent_possible_worlds(ag, x))
                quotient_r[ag][contracted_worlds_map[x]].push_back(contracted_worlds_map[y]);

    for (world_id w = 0; w < quotient_worlds_no; ++w)
        quotient_v[w] = s->get_label(structures.Q[w]->front());

    for (world_id wd : s->get_designated_worlds())
        designated_worlds.push_back(contracted_worlds_map[wd]);

    return std::make_shared<state>(s->get_language(), quotient_worlds_no,
                                   std::move(quotient_r), std::move(quotient_v),
                                   std::move(designated_worlds));
}
