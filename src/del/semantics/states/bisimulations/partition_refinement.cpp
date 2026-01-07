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

#include "../../../../../include/del/semantics/states/bisimulations/partition_refinement.h"
#include "../../../../../include/del/semantics/states/state.h"
#include <memory>
#include <utility>

using namespace del;

bpr_structures partition_refinement::do_all_refinement_steps(const state_ptr &s) {
    bpr_structures structures = init_structures(s);

    refinement_step_helper(s, structures);
    return std::move(structures);
}

void partition_refinement::refinement_step_helper(const state_ptr &s, bpr_structures &structures) {
    size_t old_size;

    do {
        old_size = structures.Q.size();
        do_refinement_step(s, structures);
    } while (structures.Q.size() != old_size);   // If no block was split, then we are done
}

void partition_refinement::do_refinement_step(const state_ptr &s, bpr_structures &structures) {
    partition Q_copy = structures.Q;

    for (const block_ptr &B : Q_copy)                      // We refine Q wrt. all of its blocks
        refine(s, structures.Q, B, structures.r_1, structures.worlds_blocks, structures.count);
}

void partition_refinement::refine(const state_ptr &s, partition &Q, const block_ptr &B, const relations &r_1,
                                  block_vector &worlds_blocks, block_id &count) {
    // [From STEP 3] Copy the elements of B into a temporary set B'. (This facilitates splitting B with respect to
    // itself during the refinement.)
    block B_copy = *B;

    for (del::agent ag = 0; ag < s->get_language()->get_agents_number(); ++ag) {
        block B_preimage = calculate_preimages(s, B_copy, r_1, ag);

        // [STEP 4] Refine Q with respect to B
        if (not B_preimage.empty())
            split(s, Q, B_preimage, worlds_blocks, count);
    }
}

block partition_refinement::calculate_preimages(const state_ptr &s, const block &B_copy, const relations &r_1,
                                                const del::agent ag) {
//    boost::dynamic_bitset<> B_preimage(s.get_worlds_number());
//
//    for (const world_id y: B_)
//        B_preimage |= s.get_agent_possible_worlds(ag, y);   // todo: this way we don't use r_1!!!!!
//
//    return block{B_preimage};
    block B_preimage = block(s->get_worlds_number());

    for (const world_id y : B_copy)
        for (const world_id x : r_1[ag][y])
            // [From STEP 3] Compute R^-1(B).
            B_preimage.push_back(x);

    return B_preimage;
}

void partition_refinement::split(const state_ptr &s, partition &Q, const block &block_preimage,
                                 block_vector &worlds_blocks, block_id &count) {
    split_blocks_map split_blocks;
    // [From STEP 4] For each block D of Q containing some element of R^-1(B), split D into D_1 = D \cap R^-1(B)
    // and D_2 = D \ D_1. Do this by scanning the elements of R^-1(B) [i.e., block_preimage].
    // [From STEP 6] Proceed exactly as in Step 4 but scan R^-1(B) \ R^-1(S \ B) (computed in step 5) instead of R^-1(B).
    for (const world_id x: block_preimage) {
        // To process an element x \in R^-1(B), determine the block D of Q containing it...
        block_ptr D = worlds_blocks[x];

        // ...and create an associated block D' if one does not already exist.
        if (split_blocks.find(D) == split_blocks.end())
            split_blocks[D] = Q.emplace_back(std::make_shared<block>(block{s->get_worlds_number(), count++}));

        // We move x from D to D'
        block_ptr D_ = split_blocks[D];
        D_->push_back(x);
        D->remove(x);
        worlds_blocks[x] = D_;
    }
    // After the scanning, process the list of split blocks. For each such block D with associated block D'...
    for (auto &[D, D_]: split_blocks)
        if (D->empty())
            Q.erase(std::find(Q.begin(), Q.end(), D));
}

bpr_structures partition_refinement::init_structures(const state_ptr &s) {
    partition Q;
    block_vector worlds_blocks;
    relations r_1 = init_preimage(s);
    block_id count = 0;
    std::map<const label, block_ptr> initial_partition;

    worlds_blocks = block_vector(s->get_worlds_number());

    // Initializing initial partition. Here we split worlds depending on their propositional valuation.
    // In each q_block we insert worlds sharing the same valuation.
    for (world_id x = 0; x < s->get_worlds_number(); ++x)
        init_partitions_helper(s, initial_partition, x, worlds_blocks, count);
    // Complexity: O(|P|*|W|)

    // Initializing Q
    for (auto &[val, block] : initial_partition) {
        for (const world_id w : *block)
            worlds_blocks[w] = block;

        Q.push_back(block);
    }
    // Complexity: O(|W|)

    return bpr_structures{std::move(Q), std::move(worlds_blocks), std::move(r_1), count};
}   // Complexity: O(|P|*|W|)

void partition_refinement::init_partitions_helper(const state_ptr &s, std::map<const label, block_ptr> &partition,
                                                  world_id w, block_vector &worlds_blocks, block_id &count) {
    const auto it = partition.find(s->get_label(w));

    if (it == partition.end()) {
        block_ptr b = std::make_shared<block>(block{s->get_worlds_number(), world_set{w}, count++});
        worlds_blocks[w] = b;
        partition.emplace(s->get_label(w), std::move(b));
    } else {
        block_ptr &b = it->second;
        b->push_back(w);
        worlds_blocks[w] = b;
    }
}   // Complexity: O(|P|)

relations partition_refinement::init_preimage(const state_ptr &s) {
    relations r_1 = relations(s->get_language()->get_agents_number());

    for (del::agent ag = 0; ag < s->get_language()->get_agents_number(); ++ag) {
        agent_relation r_ag = agent_relation(s->get_worlds_number());

        for (world_id w = 0; w < s->get_worlds_number(); ++w)    // Initializing world sets
            r_ag[w] = world_bitset(s->get_worlds_number());

        for (world_id w = 0; w < s->get_worlds_number(); ++w)
            for (const world_id v: s->get_agent_possible_worlds(ag, w))
                r_ag[v].push_back(w);

        r_1[ag] = std::move(r_ag);
    }
    return r_1;
}   // Complexity: O(|R|)
