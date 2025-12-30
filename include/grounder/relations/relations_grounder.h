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

#ifndef PLANK_RELATIONS_GROUNDER_H
#define PLANK_RELATIONS_GROUNDER_H

#include "../grounder_info.h"
#include "../language_grounder.h"
#include "../formulas/formulas_and_lists_grounder.h"
#include "../../del/semantics/states/states_types.h"
#include "../../del/language/language.h"
#include <vector>

using namespace epddl::type_checker;

namespace epddl::grounder {
    class relations_grounder {
    public:
        template<typename node_type>
        static del::relations build_relations(const ast::agent_relation_list<node_type> &r, grounder_info &info,
                                              const name_id_map &nodes_ids, const name_id_map &edge_labels_ids,
                                              const unsigned long r_no, const unsigned long r_size) {
            del::relations r_ground(r_no);

            // Initializing empty relations: we need this step to cover the case where there are
            // undeclared relations for some agent/observability type
            for (unsigned long i = 0; i < r_no; ++i)
                r_ground[i] = del::agent_relation(r_size);

            for (const ast::agent_relation_ptr<node_type> &r_i : r) {
                auto i = edge_labels_ids.at(r_i->get_obs_type()->get_token().get_lexeme());
                r_ground[i] =
                        relations_grounder::build_agent_relation<node_type>(r_i, info, nodes_ids, r_no, r_size);
            }
            return r_ground;
        }

    private:
        template<typename node_type>
        static del::agent_relation build_agent_relation(const ast::agent_relation_ptr<node_type> &r_i,
                                                        grounder_info &info, const name_id_map &nodes_ids,
                                                        const unsigned long r_no, const unsigned long r_size) {
            static_assert(std::is_same_v<node_type, ast::term> or std::is_same_v<node_type, ast::variable_ptr>);

            using simple_ground_relation = std::pair<unsigned long, unsigned long>;
            del::agent_relation r_i_ground(r_size);

            for (unsigned long node = 0; node < r_size; ++node)
                r_i_ground[node] = bit_deque{r_size};

            auto ground_elem = formulas_and_lists_grounder::grounding_function_t<
                    ast::simple_relation_ptr<node_type>, simple_ground_relation>(
            [&](const ast::simple_relation_ptr<node_type> &r, grounder_info &info, const type_ptr &default_type) {
                return simple_ground_relation{
                    relations_grounder::get_node_id(r->get_first_node(), info, nodes_ids),
                    relations_grounder::get_node_id(r->get_second_node(), info, nodes_ids)};
            });

            const type_ptr &world_event = std::is_same_v<node_type, ast::term>
                    ? info.context.types.get_type("world")
                    : info.context.types.get_type("event");

            auto r_i_pairs = formulas_and_lists_grounder::build_list<
                    ast::simple_relation_ptr<node_type>, simple_ground_relation>(
                r_i->get_relation(), ground_elem, info, world_event);

            for (const auto &[x, y] : r_i_pairs)
                r_i_ground[x].push_back(y);

            return r_i_ground;
        }

        [[nodiscard]] static unsigned long get_node_id(const ast::term &t, grounder_info &info, const name_id_map &nodes_ids) {
            return std::visit([&](auto &&arg) -> unsigned long {
                unsigned long id = info.assignment.get_assigned_entity_id(info.context.entities,
                                                                          arg->get_token().get_lexeme());
                const std::string name = info.context.entities.get_entity_name(id);
                return nodes_ids.at(name);
            }, t);
        }
    };
}

#endif //PLANK_RELATIONS_GROUNDER_H
