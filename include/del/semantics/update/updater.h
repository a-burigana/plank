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

#ifndef PLANK_UPDATER_H
#define PLANK_UPDATER_H

#include <unordered_set>
#include <unordered_map>
#include "../../language/language.h"
#include "../states/state.h"
#include "../actions/action.h"
#include "boost/dynamic_bitset.hpp"

namespace del {
    using agents_obs_type_map = std::vector<obs_type>;

    class updater {
    public:
        struct updated_world {
            world_id m_w;
            event_id m_e;

            updated_world(world_id w, event_id e) : m_w{w}, m_e{e} {}

            bool operator==(const updated_world &rhs) const { return m_w == rhs.m_w and m_e == rhs.m_e; }
            bool operator!=(const updated_world &rhs) const { return !(rhs == *this); }
        };

        static std::pair<size_t, state_ptr>
        product_update(const state_ptr &s, const action_deque &actions, bool do_contractions = false);

        static bool is_applicable(const state_ptr &s, const action_ptr &a);
        static state_ptr product_update(const state_ptr &s, const action_ptr &a);

    private:
        using updated_world_pair       = std::pair<const updated_world, const updated_world>;
        using updated_worlds_map       = std::unordered_map<updated_world, world_id>;
        using updated_world_pair_deque = std::deque<updated_world_pair>;
        using updated_edges_vector     = std::vector<updated_world_pair_deque>;

        static bool is_applicable_world(const state_ptr &s, const action_ptr &a, world_id wd);

        static agents_obs_type_map calculate_agents_obs_type(const state_ptr &s, const action_ptr &a);

        static std::pair<world_id, world_bitset>
        calculate_worlds(const state_ptr &s, const action_ptr &a, updated_worlds_map &w_map,
                         updated_edges_vector &r_map);

        static relations calculate_relations(const state_ptr &s, const action_ptr &a, world_id worlds_number,
                                             const updated_worlds_map &w_map, const updated_edges_vector &r_map);

        static label_vector calculate_labels(const state_ptr &s, const action_ptr &a, world_id worlds_number,
                                             const updated_worlds_map &w_map);

        static label update_world(const state_ptr &s, const world_id &w, const action_ptr &a, const event_id &e);
    };
}

template<>
struct std::hash<del::updater::updated_world> {
    std::size_t operator()(const del::updater::updated_world& uw) const noexcept {
        std::size_t hw = std::hash<del::world_id>{}(uw.m_w);
        std::size_t he = std::hash<del::event_id>{}(uw.m_e);
        return hw ^ (he << 1);
    }
};

#endif //PLANK_UPDATER_H
