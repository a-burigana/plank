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

#ifndef PLANK_BOUNDED_BISIMULATION_TYPES_H
#define PLANK_BOUNDED_BISIMULATION_TYPES_H

#include <deque>
#include <list>
#include <memory>
#include <vector>
#include <set>
#include <unordered_map>
#include "../../../../utils/bit_deque.h"
#include "../states_types.h"

namespace del {
    using block_id         = unsigned long;
    using block            = bit_deque;
    using block_ptr        = std::shared_ptr<block>;
    using block_vector     = std::vector<block_ptr>;
//    using block_matrix     = std::vector<block_vector>;
    using partition        = std::deque<block_ptr>;
//    using partition_vector = std::vector<partition>;
    using split_blocks_map = std::unordered_map<block_ptr, block_ptr>;

    struct bpr_structures {
        partition Q;
        block_vector worlds_blocks;
        relations r_1;
        block_id count;
    };

    using bpr_structures_ptr = std::shared_ptr<bpr_structures>;
}

#endif //PLANK_BOUNDED_BISIMULATION_TYPES_H
