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

#include "../../../../include/lib/del/semantics/model_checker.h"
#include "del/language/formulas.h"
#include "del/language/language_types.h"
#include "del/semantics/states/states_types.h"

using namespace plank::del;

bool model_checker::satisfies(const state_ptr &s, const formula_ptr &f) {
    return std::all_of(s->get_designated_worlds().begin(), s->get_designated_worlds().end(),
        [&](const world_id wd) {
            return model_checker::holds_in(s, wd, f);
    });
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const formula_ptr &f) {
    return std::visit([&](auto &&arg) {
        return model_checker::holds_in(s, w, arg);
    }, *f);
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const true_formula &f) {
    return true;
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const false_formula &f) {
    return false;
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const atom_formula &f) {
    return s->get_label(w)[f.get_atom()];
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const not_formula &f) {
    return not model_checker::holds_in(s, w, f.get_formula());
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const and_formula &f) {
    auto check =
            [&](const formula_ptr &f_) { return model_checker::holds_in(s, w, f_); };
    return std::all_of(f.get_formulas().begin(), f.get_formulas().end(), check);
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const or_formula &f) {
    auto check =
            [&](const formula_ptr &f_) { return model_checker::holds_in(s, w, f_); };
    return std::any_of(f.get_formulas().begin(), f.get_formulas().end(), check);
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const imply_formula &f) {
    return not model_checker::holds_in(s, w, f.get_first_formula()) or
    model_checker::holds_in(s, w, f.get_second_formula());
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const box_formula &f) {
    return std::all_of(f.get_mod_index().begin(), f.get_mod_index().end(), [&](const agent &ag) {
        const auto &worlds = s->get_agent_possible_worlds(ag, w);
        return std::all_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
            return model_checker::holds_in(s, v, f.get_formula());
        });
    });
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const diamond_formula &f) {
    return std::all_of(f.get_mod_index().begin(), f.get_mod_index().end(), [&](const agent &ag) {
        const auto &worlds = s->get_agent_possible_worlds(ag, w);
        return std::any_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
            return model_checker::holds_in(s, v, f.get_formula());
        });
    });
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const kw_box_formula &f) {
    return std::all_of(f.get_mod_index().begin(), f.get_mod_index().end(), [&](const agent &ag) {
        const auto &worlds = s->get_agent_possible_worlds(ag, w);
        return
            std::all_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
                return model_checker::holds_in(s, v, f.get_formula());
            })
            or
            std::all_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
                return not model_checker::holds_in(s, v, f.get_formula());
            });
    });
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const kw_diamond_formula &f) {
    return std::all_of(f.get_mod_index().begin(), f.get_mod_index().end(), [&](const agent &ag) {
        const auto &worlds = s->get_agent_possible_worlds(ag, w);
        return
            std::any_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
                return model_checker::holds_in(s, v, f.get_formula());
            })
            and
            std::any_of(worlds.begin(), worlds.end(), [&](const world_id &v) {
                return not model_checker::holds_in(s, v, f.get_formula());
            });
    });
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const c_box_formula &f) {
    const formula_ptr &f_ = f.get_formula();
    const agent_set &ags = f.get_mod_index();

    boost::dynamic_bitset<> visited(s->get_worlds_number()), to_visit(s->get_worlds_number());

    // Initializing worlds to visit
    for (const agent i : ags)
        for (const world_id v : s->get_agent_possible_worlds(i, w))
            to_visit[v] = true;

    // While there still are worlds left to visit
    while (to_visit.any()) {
        const world_id v = to_visit.find_first();

        if (not holds_in(s, v, f_))     // If f_ does not hold in v, then ([C. ags] f_) does not hold in w
            return false;

        visited[v] = true;              // We mark v as visited
        to_visit[v] = false;            // and no longer to visit

        for (const agent i: ags)              // We update the worlds to visit
            for (const world_id u: s->get_agent_possible_worlds(i, v))
                if (not visited[u])
                    to_visit[u] = true;
    }
    return true;        // If we reach this point, then all worlds reachable via ags from w satisfy f_
}

bool model_checker::holds_in(const state_ptr &s, const world_id w, const c_diamond_formula &f) {
    const formula_ptr &f_ = f.get_formula();
    const agent_set &ags = f.get_mod_index();

    boost::dynamic_bitset<> visited(s->get_worlds_number()), to_visit(s->get_worlds_number());

    // Initializing worlds to visit
    for (const agent i : ags)
        for (const world_id v : s->get_agent_possible_worlds(i, w))
            to_visit[v] = true;

    // While there still are worlds left to visit
    while (to_visit.any()) {
        const world_id v = to_visit.find_first();

        if (holds_in(s, v, f_))         // If f_ holds in v, then (<C. ags> f_) holds in w
            return true;

        visited[v] = true;              // We mark v as visited
        to_visit[v] = false;            // and no longer to visit

        for (const agent i: ags)              // We update the worlds to visit
            for (const world_id u: s->get_agent_possible_worlds(i, v))
                if (not visited[u])
                    to_visit[u] = true;
    }
    return false;        // If we reach this point, then no world reachable via ags from w satisfies f_
}

bool model_checker::satisfies_prop_formula(const label &l, const formula_ptr &f) {
    return std::visit([&](auto &&arg) {
        return model_checker::satisfies_prop_formula(l, arg);
    }, *f);
}

bool model_checker::satisfies_prop_formula(const label &l, const true_formula &f) {
    return true;
}

bool model_checker::satisfies_prop_formula(const label &l, const false_formula &f) {
    return false;
}

bool model_checker::satisfies_prop_formula(const label &l, const atom_formula &f) {
    return l[f.get_atom()];
}

bool model_checker::satisfies_prop_formula(const label &l, const not_formula &f) {
    return not model_checker::satisfies_prop_formula(l, f.get_formula());
}

bool model_checker::satisfies_prop_formula(const label &l, const and_formula &f) {
    auto check =
            [&](const formula_ptr &f_) { return model_checker::satisfies_prop_formula(l, f_); };
    return std::all_of(f.get_formulas().begin(), f.get_formulas().end(), check);
}

bool model_checker::satisfies_prop_formula(const label &l, const or_formula &f) {
    auto check =
            [&](const formula_ptr &f_) { return model_checker::satisfies_prop_formula(l, f_); };
    return std::any_of(f.get_formulas().begin(), f.get_formulas().end(), check);
}

bool model_checker::satisfies_prop_formula(const label &l, const imply_formula &f) {
    return not model_checker::satisfies_prop_formula(l, f.get_first_formula()) or
        model_checker::satisfies_prop_formula(l, f.get_second_formula());
}

bool model_checker::satisfies_prop_formula(const label &l, const box_formula &f) {
    return false;
}

bool model_checker::satisfies_prop_formula(const label &l, const diamond_formula &f) {
    return false;
}

bool model_checker::satisfies_prop_formula(const label &l, const kw_box_formula &f) {
    return false;
}

bool model_checker::satisfies_prop_formula(const label &l, const kw_diamond_formula &f) {
    return false;
}

bool model_checker::satisfies_prop_formula(const label &l, const c_box_formula &f) {
    return false;
}

bool model_checker::satisfies_prop_formula(const label &l, const c_diamond_formula &f) {
    return false;
}
