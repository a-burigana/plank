// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano_
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

#ifndef EPDDL_STATES_TYPES_H
#define EPDDL_STATES_TYPES_H

#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <boost/dynamic_bitset.hpp>
#include "../../language/label.h"
#include "../../language/language_types.h"
#include "../../../utils/bit_deque.h"

namespace del {
    class state;
    using state_ptr = std::shared_ptr<state>;

    using state_id          = unsigned long long;
    using state_deque       = std::deque<state_ptr>;
    using state_set         = std::set<state_ptr>;

    using world_id          = unsigned long long;
    using world_bitset      = bit_deque;
    using world_set         = std::unordered_set<world_id>;
    using world_deque       = std::deque<world_id>;

    using agent_relation    = std::vector<world_bitset>;
    using relations         = std::vector<agent_relation>;

    using label_vector      = std::vector<label>;
}

#endif //EPDDL_STATES_TYPES_H
