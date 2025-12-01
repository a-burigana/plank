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

#include "../../../include/grounder/actions/actions_grounder.h"
#include "../../../include/grounder/actions/events_grounder.h"
#include "../../../include/grounder/actions/obs_conditions_grounder.h"
#include "../../../include/grounder/relations/relations_grounder.h"
#include <memory>

using namespace epddl;
using namespace epddl::grounder;

del::action_deque actions_grounder::build_actions(const planning_specification &spec, context &context,
                                                  const type_ptr &types_tree, const del::atom_set &static_atoms,
                                                  const del::language_ptr &language) {
    del::action_deque actions;

    for (const auto &[_, action] : context.actions.get_actions_map()) {
        typed_var_list typed_vars = context.actions.get_formal_param_types_action(action->get_name());
        combinations_handler handler{typed_vars, context};
        variables_assignment assignment{context.entities};

        while (handler.has_next()) {
            const combination &combination = handler.next();

            if (list_comprehensions_handler::holds_condition(
                    context.entities, assignment, action->get_params()->get_condition(), static_atoms, language)) {
                assignment.push(typed_vars, combination);
                actions.emplace_back(actions_grounder::build_action(action, context, types_tree, assignment,
                                                                    static_atoms, language));
                assignment.pop();
            }
        }
    }
    return actions;
}

del::action_ptr actions_grounder::build_action(const ast::action_ptr &action, context &context,
                                               const type_ptr &types_tree, variables_assignment &assignment,
                                               const del::atom_set &static_atoms, const del::language_ptr &language) {
    const ast::action_type_ptr &action_type =
            context.action_types.get_action_type_decl(action->get_signature()->get_name());
    unsigned long events_no = action_type->get_events().size();

    type_checker::name_id_map events_ids;
    del::event_id id = 0;

    for (const ast::variable_ptr &e: action_type->get_events())
        events_ids[e->get_token().get_lexeme()] = id++;

    del::action_relations q = relations_grounder::build_relations<ast::variable_ptr>(
            action_type->get_relations(), context, types_tree,
            static_atoms, language, events_ids, events_no);

    del::preconditions pre;
    del::postconditions post;

    for (const ast::event_signature_ptr &e : action->get_signature()->get_events()) {
        auto [e_pre, e_post] = events_grounder::build_event(
                context.events.get_event_decl(e->get_name()), e, context,
                types_tree, assignment, static_atoms, language);

        pre.emplace_back(std::move(e_pre));
        post.emplace_back(std::move(e_post));
    }

    del::obs_conditions obs;

    del::event_bitset designated{events_no};

    for (const ast::variable_ptr &e_d: action_type->get_designated())
        designated.push_back(events_ids.at(e_d->get_token().get_lexeme()));

    typed_var_list typed_vars = context.actions.get_formal_param_types_action(action->get_name());
    del::formula_ptr condition = formulas_and_lists_grounder::build_condition(
            action->get_params()->get_condition(), context,
            types_tree, assignment, static_atoms, language);

    del::action_params params{std::move(typed_vars), std::move(condition)};
    boost::dynamic_bitset<> is_ontic{events_no};

    for (const ast::event_signature_ptr &e: action->get_signature()->get_events())
        is_ontic[events_ids.at(e->get_name()->get_token().get_lexeme())] =
                context.events.is_ontic(e->get_name());

    return std::make_shared<del::action>(language, "", events_no, std::move(q), std::move(pre),
                                         std::move(post), std::move(obs), std::move(designated),
                                         std::move(params), std::move(is_ontic));
}
