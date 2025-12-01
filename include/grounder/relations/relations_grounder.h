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

#ifndef EPDDL_RELATIONS_GROUNDER_H
#define EPDDL_RELATIONS_GROUNDER_H

#include "../../type-checker/context/context.h"
#include "../language_grounder.h"
#include "../formulas/formulas_and_lists_grounder.h"
#include "../../del/semantics/states/states_types.h"
#include "../../del/language/language.h"

using namespace epddl::type_checker;

namespace epddl::grounder {
    class relations_grounder {
    public:
        template<typename node_type>
        static del::relations build_relations(const ast::agent_relation_list<node_type> &r, context &context,
                                              const type_ptr &types_tree, const del::atom_set &static_atoms,
                                              const del::language_ptr &language,
                                              const name_id_map &nodes_ids, const unsigned long r_size) {
            del::relations r_ground;

            for (const ast::agent_relation_ptr<node_type> &r_i : r)
                r_ground.emplace_back(
                        relations_grounder::build_agent_relation<node_type>(r_i, context, types_tree, static_atoms,
                                                                            language, nodes_ids, r_size));
            return r_ground;
        }

    private:
        template<typename node_type>
        static del::agent_relation build_agent_relation(const ast::agent_relation_ptr<node_type> &r_i, context &context,
                                                        const type_ptr &types_tree, const del::atom_set &static_atoms,
                                                        const del::language_ptr &language,
                                                        const name_id_map &nodes_ids, const unsigned long r_size) {
            static_assert(std::is_same_v<node_type, ast::term> or std::is_same_v<node_type, ast::variable_ptr>);

            using simple_ground_relation = std::pair<unsigned long, unsigned long>;
            del::agent_relation r_i_ground(r_size);

            for (unsigned long x = 0; x < r_size; ++x)
                r_i_ground[x] = bit_deque{r_size};

            auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
                    ast::simple_relation_ptr<node_type>, simple_ground_relation>(
            [&](const ast::simple_relation_ptr<node_type> &r, const class context &context, const type_ptr &types_tree,
                const type_ptr &default_type, variables_assignment &assignment,
                const del::atom_set &static_atoms, const del::language_ptr &language) {
                return simple_ground_relation{
                    relations_grounder::get_node_id(r->get_first_node(), nodes_ids),
                    relations_grounder::get_node_id(r->get_second_node(), nodes_ids)};
            });

            variables_assignment assignment{context.entities};
            const type_ptr &world_event = std::is_same_v<node_type, ast::term>
                    ? type_utils::find(types_tree, "world")
                    : type_utils::find(types_tree, "event");

            auto r_i_pairs = formulas_and_lists_grounder::build_list<
                    ast::simple_relation_ptr<node_type>, simple_ground_relation>(
                r_i->get_relation(), ground_elem, context, types_tree,
                world_event, assignment, static_atoms, language);

            for (const auto &[x, y] : r_i_pairs)
                r_i_ground[x].push_back(y);

            return r_i_ground;
        }

        [[nodiscard]] static unsigned long get_node_id(const ast::term &t, const name_id_map &nodes_ids) {
            return std::visit([&](auto &&arg) -> unsigned long {
                return nodes_ids.at(arg->get_token().get_lexeme());
            }, t);
        }
    };
}

#endif //EPDDL_RELATIONS_GROUNDER_H
