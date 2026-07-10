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

#include "../../../../../include/lib/del/semantics/states/state.h"
#include "../../../../../include/lib/del/semantics/model_checker.h"
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace plank::del;

state::state(language_ptr language, const unsigned long long worlds_number, relations relations,
             label_vector valuation, world_bitset designated_worlds, const unsigned long long state_id) :
        m_language{std::move(language)},
        m_worlds_number{worlds_number},
        m_relations{std::move(relations)},
        m_labels{std::move(valuation)},
        m_designated_worlds{std::move(designated_worlds)},
        m_state_id{state_id} {
    calculate_state_depth();
}

state::state(language_ptr language, const unsigned long long worlds_number, relations relations,
             label_vector valuation, world_bitset designated_worlds, name_vector worlds_names,
             const unsigned long long state_id) :
        m_language{std::move(language)},
        m_worlds_number{worlds_number},
        m_relations{std::move(relations)},
        m_labels{std::move(valuation)},
        m_designated_worlds{std::move(designated_worlds)},
        m_worlds_names{std::move(worlds_names)},
        m_state_id{state_id} {
    calculate_state_depth();
}

unsigned long long state::get_worlds_number() const {
    return m_worlds_number;
}

unsigned long long state::get_depth() const {
    return m_state_depth;
}

unsigned long long state::get_depth(const world_id x) const {
    return m_worlds_depth[x];
}

const world_bitset &state::get_agent_possible_worlds(const agent ag, const world_id w) const {
    return m_relations[ag].at(w);
}

bool state::has_edge(const agent ag, const world_id w, const world_id v) const {
    return (*m_relations[ag][w])[v];
}

const label &state::get_label(const world_id w) const {
    return m_labels[w];
}

const world_bitset &state::get_designated_worlds() const {
    return m_designated_worlds;
}

unsigned long long state::get_id() const {
    return m_state_id;
}

bool state::is_designated(const world_id w) const {
    return std::find(m_designated_worlds.begin(), m_designated_worlds.end(), w) != m_designated_worlds.end();
}

language_ptr state::get_language() const {
    return m_language;
}

const std::string &state::get_world_name(const world_id w) const {
    return m_worlds_names[w];
}

void state::calculate_state_depth() {
    m_worlds_depth = std::vector<world_id>(m_worlds_number);
    m_state_depth = 0;

    std::queue<world_id> to_visit;
    boost::dynamic_bitset<> assigned(m_worlds_number);

    for (const world_id wd : m_designated_worlds) {
        m_worlds_depth[wd] = 0;     // The designated worlds have depth 0
        assigned[wd] = true;
        to_visit.push(wd);
    }

    while (not to_visit.empty()) {
        const world_id current = to_visit.front();
        to_visit.pop();

        if (m_worlds_depth[current] > m_state_depth)
            m_state_depth = m_worlds_depth[current];

        for (agent ag = 0; ag < m_language->get_agents_number(); ++ag)
            for (const world_id v : m_relations[ag][current])
                if (not assigned[v]) {
                    m_worlds_depth[v] = m_worlds_depth[current] + 1;
                    assigned[v] = true;
                    to_visit.push(v);
                }
    }
}

bool state::operator<(const state &rhs) const {
    return m_state_id < rhs.m_state_id;
}

bool state::operator>(const state &rhs) const {
    return rhs < *this;
}

bool state::operator<=(const state &rhs) const {
    return rhs >= *this;
}

bool state::operator>=(const state &rhs) const {
    return !(*this < rhs);
}

bool state::operator==(const state &rhs) const {
    return m_state_id == rhs.m_state_id;
}

bool state::operator!=(const state &rhs) const {
    return !(rhs == *this);
}
