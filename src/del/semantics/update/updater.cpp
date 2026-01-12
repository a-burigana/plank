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

#include <memory>
#include <queue>
#include <utility>
#include "../../../../include/del/language/formulas.h"
#include "../../../../include/del/semantics/update/updater.h"
#include "../../../../include/del/semantics/model_checker.h"
#include "../../../../include/del/semantics/states/bisimulations/bisimulator.h"

using namespace del;

state_deque updater::product_update(const state_ptr &s, const action_deque &actions, bool do_contractions) {
    state_deque results = {s};

    for (const action_ptr &a : actions) {
        if (not updater::is_applicable(results.back(), a))
            break;

        state_ptr result = updater::product_update(results.back(), a);

        if (do_contractions)
            result = bisimulator::contract(result);

        results.emplace_back(std::move(result));
    }

    return results;
}

bool updater::is_applicable(const state_ptr &s, const action_ptr &a) {
    const auto check = [&](const world_id wd) { return is_applicable_world(s, a, wd); };
    return std::all_of(s->get_designated_worlds().begin(), s->get_designated_worlds().end(), check);
}

bool updater::is_applicable_world(const state_ptr &s, const action_ptr &a, const world_id wd) {
    const auto check = [&](const event_id ed) { return model_checker::holds_in(s, wd, a->get_precondition(ed)); };
    return std::any_of(a->get_designated_events().begin(), a->get_designated_events().end(), check);
}

state_ptr updater::product_update(const state_ptr &s, const action_ptr &a) {
    updated_worlds_map w_map;
    updated_edges_vector r_map(s->get_language()->get_agents_number());
    agents_obs_type_map agents_obs_type = updater::calculate_agents_obs_type(s, a);

    auto [worlds_number, designated_worlds] = calculate_worlds(s, a, w_map, r_map, agents_obs_type);
    relations r = calculate_relations(s, a, worlds_number, w_map, r_map, agents_obs_type);
    label_vector labels = calculate_labels(s, a, worlds_number, w_map);

    return std::make_shared<state>(s->get_language(), worlds_number, std::move(r), std::move(labels), std::move(designated_worlds));
}

agents_obs_type_map updater::calculate_agents_obs_type(const state_ptr &s, const action_ptr &a) {
    agents_obs_type_map agents_obs_type(s->get_language()->get_agents_number());

    for (agent i = 0; i < s->get_language()->get_agents_number(); ++i)
        for (const auto &[t, cond] : a->get_agent_obs_conditions(i))
            if (model_checker::satisfies(s, cond))
                agents_obs_type[i] = t;

    return agents_obs_type;
}

std::pair<world_id, world_bitset>
updater::calculate_worlds(const state_ptr &s, const action_ptr &a, updated_worlds_map &w_map,
                          updated_edges_vector &r_map, const agents_obs_type_map &agents_obs_type) {
    world_id worlds_number = 0;
    world_set designated_worlds;

    std::unordered_set<updated_world> to_expand;
    std::unordered_set<updated_world> visited;

    for (agent i = 0; i < s->get_language()->get_agents_number(); ++i)
        r_map[i] = updated_world_pair_deque{};

    for (const world_id wd : s->get_designated_worlds())
        for (const event_id ed : a->get_designated_events())
            if (model_checker::holds_in(s, wd, a->get_precondition(ed)))
                to_expand.emplace(wd, ed);

    while (not to_expand.empty()) {
        const auto first = to_expand.begin();
        const auto &[w, e] = *first;
        w_map[updated_world{w, e}] = worlds_number++;
        visited.emplace(w, e);

        if (s->is_designated(w) and a->is_designated(e))
            designated_worlds.emplace(worlds_number-1);

        for (agent i = 0; i < s->get_language()->get_agents_number(); ++i) {
            const world_bitset &i_worlds = s->get_agent_possible_worlds(i, w);
            const event_bitset &i_events = a->get_obs_type_possible_events(agents_obs_type[i], e);

            for (const world_id v : i_worlds) {
                for (const event_id f : i_events) {
                    if (model_checker::holds_in(s, v, a->get_precondition(f))) {
                        updated_world w_ = {w, e}, v_ = {v, f};
                        r_map[i].emplace_back(w_, v_);

                        if (visited.find(v_) == visited.end())
                            to_expand.emplace(v_);
                    }
                }
            }
        }
        to_expand.erase(first);
    }
    return {worlds_number, world_bitset{worlds_number, designated_worlds}};
}

relations updater::calculate_relations(const state_ptr &s, const action_ptr &a, const world_id worlds_number,
                                       const updated_worlds_map &w_map, const updated_edges_vector &r_map,
                                       const agents_obs_type_map &agents_obs_type) {
    relations r = relations(s->get_language()->get_agents_number());

    for (agent i = 0; i < s->get_language()->get_agents_number(); ++i) {
        r[i] = agent_relation(worlds_number);

        for (world_id w = 0; w < worlds_number; ++w)
            r[i][w] = world_bitset(worlds_number);
    }

    for (agent i = 0; i < s->get_language()->get_agents_number(); ++i) {
        for (const auto &[w_, v_] : r_map[i]) {
            const auto &[w, e] = w_;
            const auto &[v, f] = v_;

            if (s->has_edge(i, w, v) and a->has_edge(agents_obs_type[i], e, f))
                r[i][w_map.at(w_)].push_back(w_map.at(v_));
        }
    }
    return r;
}

label_vector updater::calculate_labels(const state_ptr &s, const action_ptr &a, const world_id worlds_number,
                                       const updated_worlds_map &w_map) {
    label_vector labels = label_vector(worlds_number);

    for (const auto &[w_, w_id] : w_map) {
        const auto &[w, e] = w_;
        labels[w_id] = a->is_ontic(e) ? update_world(s, w, a, e) : s->get_label(w);
    }
    return labels;
}

label updater::update_world(const state_ptr &s, const world_id &w, const action_ptr &a, const event_id &e) {
    auto bitset = s->get_label(w).get_bitset();

    for (const auto &[p, post] : a->get_postconditions(e))
        bitset[p] = model_checker::holds_in(s, w, post);

    return label{std::move(bitset)};
}
