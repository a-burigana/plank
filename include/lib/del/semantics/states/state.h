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

#ifndef PLANK_STATE_H
#define PLANK_STATE_H

#include <set>
#include <map>
#include <ostream>
#include <vector>
#include "states_types.h"
#include "../../language/language.h"
#include "../../../utils/label_storage.h"

namespace plank::del {
    class state {
    public:
        state(language_ptr language, plank::utils::label_storage_ptr label_storage, world_id worlds_number, relations relations,
              label_id_vector labels_ids, world_bitset designated_worlds, unsigned long long state_id);

        state(language_ptr language, plank::utils::label_storage_ptr label_storage, world_id worlds_number, relations relations,
              label_id_vector labels_ids, world_bitset designated_worlds, name_vector worlds_names = {});

        state(const state&) = default;
        state& operator=(const state&) = default;

        state(state&&) = default;
        state& operator=(state&&) = default;

        ~state() = default;

        [[nodiscard]] world_id get_worlds_number() const;
        [[nodiscard]] unsigned long long get_depth() const;
        [[nodiscard]] unsigned long long get_depth(world_id x) const;

        [[nodiscard]] const world_bitset &get_worlds();
        [[nodiscard]] const world_bitset &get_agent_possible_worlds(agent ag, world_id w) const;
        [[nodiscard]] bool has_edge(agent ag, world_id w, world_id v) const;
        [[nodiscard]] const label &get_label(world_id w) const;
        [[nodiscard]] label_id get_label_id(world_id w) const;
        [[nodiscard]] const world_bitset &get_designated_worlds() const;
        [[nodiscard]] unsigned long long get_id() const;
        [[nodiscard]] bool is_designated(world_id w) const;

        [[nodiscard]] language_ptr get_language() const;
        [[nodiscard]] const std::string &get_world_name(world_id w) const;

        [[nodiscard]] plank::utils::label_storage_ptr &get_label_storage();

        bool operator< (const state &rhs) const;
        bool operator<=(const state &rhs) const;
        bool operator> (const state &rhs) const;
        bool operator>=(const state &rhs) const;
        bool operator==(const state &rhs) const;
        bool operator!=(const state &rhs) const;

    private:
        language_ptr m_language;
        unsigned long long m_worlds_number;
        world_bitset m_worlds;
        relations m_relations;
        label_id_vector m_labels_ids;
        world_bitset m_designated_worlds;
        name_vector m_worlds_names;
        unsigned long long m_state_id;
        unsigned long m_state_depth{};
        std::vector<world_id> m_worlds_depth;

        plank::utils::label_storage_ptr m_label_storage;

        void calculate_state_depth();
    };
}

#endif //PLANK_STATE_H
