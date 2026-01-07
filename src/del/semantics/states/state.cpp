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

#include "../../../../include/del/semantics/states/state.h"
#include "../../../../include/del/semantics/model_checker.h"
#include "../../../../include/del/language/formulas.h"
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace del;
using namespace del;

state::state(language_ptr language, unsigned long long worlds_number, relations relations,
             label_vector valuation, world_bitset designated_worlds, name_vector worlds_names,
             unsigned long long state_id) :
        m_language{std::move(language)},
        m_worlds_number{worlds_number},
        m_relations{std::move(relations)},
        m_labels{std::move(valuation)},
        m_designated_worlds{std::move(designated_worlds)},
        m_worlds_names{std::move(worlds_names)},
        m_state_id{state_id} {}

unsigned long long state::get_worlds_number() const {
    return m_worlds_number;
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

const std::string &state::get_world_name(del::world_id w) const {
    return m_worlds_names[w];
}

bool state::operator<(const state &rhs) const {
    return m_state_id < rhs.m_state_id;
}

bool state::operator>(const state &rhs) const {
    return rhs < *this;
}

bool state::operator<=(const state &rhs) const {
    return !(rhs < *this);
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
