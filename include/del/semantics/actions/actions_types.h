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

#ifndef EPDDL_ACTIONS_TYPES_H
#define EPDDL_ACTIONS_TYPES_H

#include <memory>
#include <vector>
#include <set>
#include <deque>
#include <unordered_set>
#include "../../language/language_types.h"
#include "../../utils/bit_deque.h"
#include "../../formulas/formula.h"

namespace del {
    class formula;
    class action;
    using action_ptr   = std::shared_ptr<action>;
    using action_deque = std::deque<del::action_ptr>;

    using event_id               = unsigned long long;
    using event_bitset           = bit_deque;
    using event_set              = std::unordered_set<event_id>;

    using action_agent_relations = std::vector<event_bitset>;
    using action_relations       = std::vector<action_agent_relations>;

    using preconditions  = std::vector<del::formula_ptr>;
    using event_post     = std::unordered_map<del::atom, del::formula_ptr>;
    using postconditions = std::vector<event_post>;
}

#endif //EPDDL_ACTIONS_TYPES_H
