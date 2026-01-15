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

#ifndef PLANK_BOUNDED_PARTITION_REFINEMENT_H
#define PLANK_BOUNDED_PARTITION_REFINEMENT_H

#include <vector>
#include <list>
#include <map>
#include <memory>
#include <deque>
#include <set>
#include <boost/dynamic_bitset.hpp>
#include "bisimulation_types.h"
#include "../states_types.h"

namespace del {
    class state;

    class partition_refinement {
    public:
        static bpr_structures do_all_refinement_steps(const state_ptr &s);

    private:
        static void refinement_step_helper(const state_ptr &s, bpr_structures &structures);

        static void do_refinement_step(const state_ptr &s, bpr_structures &structures);

        static void refine(const state_ptr &s, partition &Q, const block_ptr &B,
                           const relations &r_1, block_vector &worlds_blocks, block_id &count);

        static block calculate_preimages(const state_ptr &s, const block &B_copy, const relations &r_1, del::agent ag);

        static void split(const state_ptr &s, partition &Q, const block &block_preimage,
                          block_vector &worlds_blocks, block_id &count);

        // Initialization of structures
        static bpr_structures init_structures(const state_ptr &s);

        static void init_partitions_helper(const state_ptr &s, std::map<const label, block_ptr> &partition,
                                           world_id w, block_vector &worlds_blocks, block_id &count);

        static relations init_preimage(const state_ptr &s);

    };
}

#endif //PLANK_BOUNDED_PARTITION_REFINEMENT_H
