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

#include "../../../include/grounder/initial_state/finitary_s5_theory_grounder.h"
#include "../../../include/grounder/formulas/formulas_and_lists_grounder.h"
#include "../../../include/del/semantics/model_checker.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <variant>

using namespace epddl;
using namespace epddl::grounder;

del::finitary_s5_theory_ptr
finitary_s5_theory_grounder::build_finitary_s5_theory(const ast::finitary_S5_theory &init, grounder_info &info) {
    del::formula_deque type_1_formulas, type_2_formulas;
    del::formula_map type_3_formulas(info.language->get_agents_number());

    auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
        ast::finitary_S5_formula, bool>(
        [&](const ast::finitary_S5_formula &f, grounder_info &info, const type_ptr &default_type) {
            if (std::holds_alternative<ast::prop_formula_ptr>(f)) {
                const ast::formula_ptr &f_ = std::get<ast::prop_formula_ptr>(f)->get_formula();
                type_1_formulas.emplace_back(formulas_and_lists_grounder::build_formula(f_, info));
            } else if (std::holds_alternative<ast::ck_formula_ptr>(f)) {
                const ast::formula_ptr &f_ = std::get<ast::ck_formula_ptr>(f)->get_formula();
                type_2_formulas.emplace_back(formulas_and_lists_grounder::build_formula(f_, info));
            } else if (std::holds_alternative<ast::ck_k_formula_ptr>(f)) {
                const ast::formula_ptr &f_ = std::get<ast::ck_k_formula_ptr>(f)->get_formula();
                type_2_formulas.emplace_back(formulas_and_lists_grounder::build_formula(f_, info));
            } else if (std::holds_alternative<ast::ck_kw_formula_ptr>(f)) {
                const auto &kw_f = std::get<ast::ck_kw_formula_ptr>(f);
                const del::agent i = language_grounder::get_agent_id(kw_f->get_agent(), info);
                type_3_formulas[i].emplace_back(formulas_and_lists_grounder::build_formula(kw_f->get_formula(),
                                                                                           info));
            }
            return true;
        });

    formulas_and_lists_grounder::build_list<ast::finitary_S5_formula, bool>(
            init, ground_elem, info, info.context.types.get_type("entity"));

    return std::make_shared<del::finitary_s5_theory>(std::move(type_1_formulas), std::move(type_2_formulas),
                                                     std::move(type_3_formulas));
}

del::state_ptr
finitary_s5_theory_grounder::build_initial_state(const ast::finitary_S5_theory &init, grounder_info &info) {
    del::finitary_s5_theory_ptr theory = finitary_s5_theory_grounder::build_finitary_s5_theory(init, info);

    auto l_designated =
            finitary_s5_theory_grounder::compute_labels_and_designated(init, theory, info);

    const del::label_vector &l = l_designated.first;
    const del::world_bitset &designated = l_designated.second;
    del::world_id worlds_no = l.size();
    del::relations r = finitary_s5_theory_grounder::compute_relations(init, theory, l, info, worlds_no);

    name_vector worlds_names(worlds_no);

    for (del::world_id w = 0; w < worlds_no; ++w)
        worlds_names[w] = "w" + std::to_string(w);

    return std::make_shared<del::state>(info.language, worlds_no, std::move(r),
                                        std::move(l_designated.first), std::move(l_designated.second),
                                        std::move(worlds_names));
}

std::pair<del::label_vector, del::world_bitset>
finitary_s5_theory_grounder::compute_labels_and_designated(const ast::finitary_S5_theory &init,
                                                           const del::finitary_s5_theory_ptr &theory,
                                                           grounder_info &info) {
    del::formula_ptr f_designated = std::make_shared<del::and_formula>(theory->get_type_1_formulas());
    del::formula_ptr f_worlds = std::make_shared<del::and_formula>(theory->get_type_2_formulas());
    auto [bitset, fixed_bits] =
            finitary_s5_theory_grounder::compute_fixed_literal_set(theory->get_type_2_formulas(), info);

    del::label_vector l;
    bit_deque::index_set designated;
    bool stop = false;

    while (not stop) {
        del::label label{bitset};

        if (del::model_checker::satisfies_prop_formula(label, f_worlds)) {
            if (del::model_checker::satisfies_prop_formula(label, f_designated))
                designated.emplace(l.size());

            l.emplace_back(std::move(label));
        }

        if (stop = (bitset | fixed_bits).all(); not stop)
            bitset = finitary_s5_theory_grounder::next_bitset(bitset, fixed_bits);
    }

    finitary_s5_theory_grounder::check_worlds(info.err_managers.problem_err_manager, init,
                                              l.size(), designated.size());
    return {std::move(l), del::world_bitset{l.size(), designated}};
}

del::relations
finitary_s5_theory_grounder::compute_relations(const ast::finitary_S5_theory &init,
                                               const del::finitary_s5_theory_ptr &theory, const del::label_vector &l,
                                               grounder_info &info, del::world_id worlds_no) {
    del::relations r(info.language->get_agents_number());

    for (del::agent i = 0; i < info.language->get_agents_number(); ++i) {
        r[i] = del::agent_relation(worlds_no);

        for (del::world_id w = 0; w < worlds_no; ++w)
            r[i][w] = del::world_bitset(worlds_no);
    }

    for (del::world_id w = 0; w < worlds_no; ++w)
        for (del::world_id v = 0; v < worlds_no; ++v) {
            for (del::agent i = 0; i < info.language->get_agents_number(); ++i)
                if (w == v)
                    r[i][w].push_back(w);
                else {
                    bool good = std::all_of(theory->get_type_3_formulas(i).begin(),
                                            theory->get_type_3_formulas(i).end(),
                                            [&](const del::formula_ptr &f) {
                        return finitary_s5_theory_grounder::agree_on_formula(l[w], l[v], f);
                    });

                    if (good) {
                        r[i][w].push_back(v);
                        r[i][v].push_back(w);
                    }
                }
        }
    return r;
}


bool finitary_s5_theory_grounder::agree_on_formula(const del::label &l1, const del::label &l2,
                                                   const del::formula_ptr &f) {
    return del::model_checker::satisfies_prop_formula(l1, f) ==
           del::model_checker::satisfies_prop_formula(l2, f);
}

boost::dynamic_bitset<> finitary_s5_theory_grounder::next_bitset(const boost::dynamic_bitset<> &current) {
    boost::dynamic_bitset<> next = current;
    size_t index = next.size();

    while (index > 0 and next[--index])
        next[index] = false;

    next[index] = true;
    return next;
}

boost::dynamic_bitset<> finitary_s5_theory_grounder::next_bitset(const boost::dynamic_bitset<> &current,
                                                                 const boost::dynamic_bitset<> &fixed_bits) {
    boost::dynamic_bitset<> next = current;
    size_t index = next.size();

    while (index > 0 and (fixed_bits[--index] or next[index]))
        if (not fixed_bits[index])
            next[index] = false;

    next[index] = true;
    return next;
}

std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<>>
finitary_s5_theory_grounder::compute_fixed_literal_set(const del::formula_deque &fs, const grounder_info &info) {
    boost::dynamic_bitset<>
            atoms(info.language->get_atoms_number()),
            is_fixed(info.language->get_atoms_number());

    std::function<void(const del::formula_deque &)> compute_fixed_literal_set =
            [&](const del::formula_deque &fs_) {
        for (const del::formula_ptr &f : fs_) {
            if (auto l = finitary_s5_theory_grounder::is_literal(f); l.has_value()) {
                atoms[l->first] = l->second;
                is_fixed[l->first] = true;
            }

            if (std::holds_alternative<del::and_formula_ptr>(f))
                compute_fixed_literal_set(std::get<del::and_formula_ptr>(f)->get_formulas());
        }
    };

    for (const del::formula_ptr &f : fs)
        compute_fixed_literal_set(fs);

    // Facts atoms are fixed
    for (del::atom p = 0; p < info.language->get_atoms_number(); ++p)
        if (info.language->is_fact(p)) {
            atoms[p] = info.facts.get_bitset()[p];
            is_fixed[p] = true;
        }

    return {std::move(atoms), std::move(is_fixed)};
}

std::optional<std::pair<del::atom, bool>> finitary_s5_theory_grounder::is_literal(const del::formula_ptr &f) {
    std::optional<std::pair<del::atom, bool>> l = std::nullopt;

    if (std::holds_alternative<del::atom_formula_ptr>(f))
        l = {std::get<del::atom_formula_ptr>(f)->get_atom(), true};
    else if (std::holds_alternative<del::not_formula_ptr>(f)) {
        const auto &f_ = std::get<del::not_formula_ptr>(f);
        if (std::holds_alternative<del::atom_formula_ptr>(f_->get_formula()))
            l = {std::get<del::atom_formula_ptr>(f_->get_formula())->get_atom(), false};
    }

    return l;
}

void finitary_s5_theory_grounder::check_worlds(error_manager_ptr &err_manager, const ast::finitary_S5_theory &init,
                                               const del::world_id worlds_no, const del::world_id designated_no) {
    ast::info info = std::visit([&](auto &&arg) { return arg->get_info();}, init);

    if (worlds_no == 0)
        err_manager->throw_error(error_type::inconsistent_theory_worlds, info);

    if (designated_no == 0)
        err_manager->throw_error(error_type::inconsistent_theory_designated, info);
}