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

#include "../../include/printer/initial_state_printer.h"
#include "../../include/del/semantics/states/state.h"

using namespace epddl::printer;

json initial_state_printer::build_state_json(const del::state_ptr &state) {
    json worlds_json = json::array(), des_worlds_json = json::array();

    for (del::world_id w = 0; w < state->get_worlds_number(); ++w)
        worlds_json.emplace_back(state->get_world_name(w));

    for (del::world_id w_d : state->get_designated_worlds())
        des_worlds_json.emplace_back(state->get_world_name(w_d));

    json r_json = initial_state_printer::build_relations(state);
    json l_json = initial_state_printer::build_labels(state);

    return json::array({
        json::object({ {"worlds", std::move(worlds_json)} }),
        json::object({ {"relations", std::move(r_json)} }),
        json::object({ {"labels", std::move(l_json)} }),
        json::object({ {"designated", std::move(des_worlds_json)} })
    });
}

json initial_state_printer::build_relations(const del::state_ptr &state) {
    json r_json = json::array();

    for (del::agent i = 0; i < state->get_language()->get_agents_number(); ++i) {
        json r_i = json::array();

        for (del::world_id w = 0; w < state->get_worlds_number(); ++w) {
            json w_worlds = json::array();

            for (const del::world_id v: state->get_agent_possible_worlds(i, w))
                w_worlds.emplace_back(state->get_world_name(v));

            r_i.emplace_back(json::object({ {state->get_world_name(w), std::move(w_worlds)} }));
        }
        r_json.emplace_back(json::object({ {state->get_language()->get_agent_name(i), std::move(r_i)} }));
    }
    return r_json;
}

json initial_state_printer::build_labels(const del::state_ptr &state) {
    json l_json = json::array();

    for (del::world_id w = 0; w < state->get_worlds_number(); ++w) {
        json l_w_json = json::array();

        for (del::atom p = 0; p < state->get_language()->get_atoms_number(); ++p)
            if (state->get_label(w)[p])
                l_w_json.emplace_back(state->get_language()->get_atom_name(p));

        l_json.emplace_back(json::object({ {
            state->get_world_name(w),
            std::move(l_w_json)
        } }));
    }

    return l_json;
}
