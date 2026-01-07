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

#include "../../../../../include/del/semantics/states/bisimulations/bisimulator.h"
#include "../../../../../include/del/semantics/states/bisimulations/partition_refinement.h"
#include "../../../../../include/del/semantics/states/bisimulations/contraction_builder.h"
#include <algorithm>
#include <memory>

using namespace del;

state_ptr bisimulator::contract(const state_ptr &s) {
    return contraction_builder::calculate_standard_contraction(s);
}

/*
bool bisimulator::are_bisimilar(const state &s, const state &t, unsigned long k, del::storages_handler_ptr handler) {
    state u = disjoint_union(s, t);
    unsigned long offset = s.get_worlds_number();

    auto [is_bisim, structures] = partition_refinement::do_refinement_steps(u, k);
    auto worlds_blocks = structures.worlds_blocks;

    for (auto wd: s.get_designated_worlds())
        if (std::all_of(t->get_designated_worlds().begin(), t->get_designated_worlds().end(),
                    [&](world_id vd) -> bool {
                        auto block_wd = worlds_blocks[wd][k];
                        return std::find(block_wd->begin(), block_wd->end(), offset + vd) == block_wd->end();}))
            return false;

    for (auto vd: t->get_designated_worlds())
        if (std::all_of(s.get_designated_worlds().begin(), s.get_designated_worlds().end(),
                        [&](world_id wd) -> bool {
                            auto block_vd = worlds_blocks[offset + vd][k];
                            return std::find(block_vd->begin(), block_vd->end(), wd) == block_vd->end();}))
            return false;

    return true;
}
*/

state_ptr bisimulator::disjoint_union(const state_ptr &s, const state_ptr &t) {
    unsigned long worlds_number = s->get_worlds_number() + t->get_worlds_number(), offset = s->get_worlds_number();

    relations r = relations(s->get_language()->get_agents_number());

    for (del::agent ag = 0; ag < s->get_language()->get_agents_number(); ++ag) {
        r[ag] = agent_relation(worlds_number);

        for (world_id w = 0; w < s->get_worlds_number(); ++w) {
            r[ag][w] = world_bitset(worlds_number);

            for (auto v: s->get_agent_possible_worlds(ag, w))
                r[ag][w].push_back(v);
        }

        for (world_id w = 0; w < t->get_worlds_number(); ++w) {
            r[ag][offset + w] = world_bitset(worlds_number);

            for (auto v: t->get_agent_possible_worlds(ag, w))
                r[ag][offset + w].push_back(offset + v);
        }
    }

    label_vector ls = label_vector(worlds_number);

    for (world_id w = 0; w < s->get_worlds_number(); ++w)
        ls[w] = s->get_label(w);

    for (world_id w = 0; w < t->get_worlds_number(); ++w)
        ls[offset + w] = t->get_label(w);

    world_bitset designated = world_bitset(worlds_number);

    for (auto w: s->get_designated_worlds())
        designated.push_back(w);

    for (auto w: t->get_designated_worlds())
        designated.push_back(offset + w);

    return std::make_shared<state>(s->get_language(), worlds_number, std::move(r),
                                   std::move(ls), std::move(designated));
}
