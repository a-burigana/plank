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

#include "../../../../include/frontend/bfs-planner/signatures/signature_calculator.h"

using namespace search::utils;

signature_set_id
signature_calculator::calculate_state_id(const del::state_ptr &s, storages_handler_ptr &handler) {
    auto worlds_signatures = signature_matrix(s->get_depth()+1);
    signature_set designated_signatures;

    for (auto &h_signatures : worlds_signatures)
        h_signatures = signature_vector(s->get_worlds_number());

    for (const del::world_id wd : s->get_designated_worlds())
        designated_signatures.emplace(calculate_world_signature(s, wd, s->get_depth(), handler, worlds_signatures));

    return handler->get_signature_set_storage().emplace(std::move(designated_signatures));
}

signature_id
signature_calculator::calculate_world_signature(const del::state_ptr &s, const del::world_id x, const unsigned long h,
                                                storages_handler_ptr &handler, signature_matrix &worlds_signatures) {
    auto xs = agents_signature_set(s->get_language()->get_agents_number());

    for (del::agent ag = 0; ag < s->get_language()->get_agents_number(); ++ag)
        xs[ag] = 0;

    if (h > 0)
        for (del::agent ag = 0; ag < s->get_language()->get_agents_number(); ++ag) {
            signature_set x_ag;

            for (const del::world_id y : s->get_agent_possible_worlds(ag, x)) {
                if (handler->get_signature_storage().is_null(worlds_signatures[h-1][y]))    // We check that we did not already calculate y's (h-1)-signature
                    worlds_signatures[h-1][y] = calculate_world_signature(s, y, h-1, handler, worlds_signatures);

                x_ag.emplace(worlds_signatures[h-1][y]);
            }
            xs[ag] = handler->get_signature_set_storage().emplace(std::move(x_ag));     // xss[h][ag] is the numerical id referring to the set of
        }                                                                                       // (h-1)-signatures of the worlds y such that x R_ag y

    del::label x_label = s->get_label(x);
    const label_id x_label_id = handler->get_label_storage().emplace(std::move(x_label));

    auto sign_x_h = signature{x_label_id, std::move(xs)};               // We create the h-signature of x (h being x's bound),

    return handler->get_signature_storage().emplace(std::move(sign_x_h));       // we add it to the storage, and we return it
}
