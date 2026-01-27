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

#include <memory>
#include <ostream>
#include <utility>
#include <iostream>
#include "../../../../include/frontend/bfs-planner/search/planner.h"
#include "../../../../include/frontend/bfs-planner/utils/time_utils.h"
#include "../../../../include/lib/del/semantics/model_checker.h"
#include "../../../../external/json.hpp"

using namespace search;
using namespace nlohmann;

del::action_deque planner::solve(const del::planning_task &task) {
    unsigned long long node_count = 0;
    del::action_deque plan;

    auto start = std::chrono::high_resolution_clock::now();

    // If the initial state satisfies the goal, we immediately terminate
    bool is_init_goal = del::model_checker::satisfies(task.initial_state, task.goal);

    if (not is_init_goal)
        plan = bfs(task, node_count);

    auto runtime = static_cast<double>(since(start).count()) / 1000;
    std::cout << "Runtime: " << runtime << "." << std::endl;

    // If an empty action sequence is returned by the BFS search, then the task has no solution
    if (plan.empty() and not is_init_goal)
        std::cout << "No plan found." << std::endl;
    else {
        std::cout << "Plan found:" << std::endl;
        print_plan(std::cout, plan);
    }
    return plan;
}

void planner::print_plan(std::ostream &out, const del::action_deque &plan) {
    size_t count = 0;

    for (const del::action_ptr &action : plan)
        out << count++ << ". " << action->get_name() << std::endl;
}

void planner::print_plan_json(std::ofstream &out, const del::action_deque &plan) {
    json plan_json = json::array();

    for (const del::action_ptr &action : plan)
        plan_json.emplace_back(action->get_name());

    out << plan_json.dump(2) << std::endl;
}

del::action_deque planner::bfs(const del::planning_task &task, unsigned long long &node_count) {
    del::state_ptr s0 = task.initial_state;
    node_deque frontier;

    frontier.emplace_back(init_node(node_count, del::bisimulator::contract(task.initial_state)));

    while (not frontier.empty()) {
        node_ptr n = frontier.front();

        for (const auto &[a_name, a] : task.actions) {
            if (del::updater::is_applicable(n->get_state(), a)) {
                node_ptr n_ = update_node(n, a, node_count);
                n->add_child(n_);

                if (del::model_checker::satisfies(n_->get_state(), task.goal))
                    return extract_plan(n_);

                frontier.push_back(n_);
            }
        }

        frontier.pop_front();
    }
    return {};
}

node_ptr planner::update_node(const node_ptr &n, const del::action_ptr &a, unsigned long long &id) {
    del::state_ptr update = del::updater::product_update(n->get_state(), a);
    return init_node(id, del::bisimulator::contract(update), a, n);
}

search::node_ptr planner::init_node(unsigned long long &id, del::state_ptr s, del::action_ptr a,
                                    const node_ptr &n) {
    return std::make_shared<node>(id++, std::move(s), std::move(a), n);
}

del::action_deque planner::extract_plan(node_ptr n) {
    del::action_deque plan;

    do {
        if (n->get_action())
            plan.push_front(n->get_action());
        n = n->get_parent();
    } while (n);

    return plan;
}
