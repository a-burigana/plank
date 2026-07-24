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

#ifndef PLANK_PLANNER_H
#define PLANK_PLANNER_H

#include <fstream>
#include <ostream>
#include <memory>
#include "search_space.h"
#include "del/semantics/planning_task.h"
#include "del/semantics/states/state.h"
#include "del/semantics/update/updater.h"
#include "del/semantics/states/bisimulations/bisimulator.h"
#include "search_types.h"
#include "../utils/storages_handler.h"

using visited_states_set = std::unordered_set<del::state_id>;

namespace search {
    class planner {
    public:
        static del::action_deque solve(const del::planning_task &task);

        static void print_plan(std::ostream &out, const del::action_deque &plan);
        static void print_plan_json(std::ofstream &out, const del::action_deque &plan);

    private:
        static del::action_deque bfs(const del::planning_task &task, visited_states_set &visited_states,
                                     utils::storages_handler_ptr &storages_handler, unsigned long long &node_count);

        static del::action_deque extract_plan(node_ptr n);


        static node_ptr update_node(const node_ptr &n, const del::action_ptr &a, unsigned long long &node_count,
                                    visited_states_set &visited_states, utils::storages_handler_ptr &storages_handler);

        static node_ptr init_node(unsigned long long &node_count, del::state_ptr s, visited_states_set &visited_states,
                                  utils::storages_handler_ptr &storages_handler, del::action_ptr a = nullptr,
                                  const node_ptr &n = nullptr);

        static bool is_visited_state(del::state_id s_id, const visited_states_set &visited_states);
    };
}

#endif //PLANK_PLANNER_H
