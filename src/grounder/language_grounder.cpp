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

#include "../../include/grounder/language_grounder.h"
#include "../../include/grounder/variables_assignment.h"
#include <memory>

using namespace epddl;
using namespace epddl::grounder;

del::language_ptr language_grounder::build_language(context &context) {
    auto [atom_names, is_static, is_public_static] = language_grounder::build_atoms(context);
    del::name_vector agent_names = language_grounder::build_agents(context);

    return std::make_shared<del::language>(std::move(atom_names), std::move(is_static),
                                           std::move(is_public_static), std::move(agent_names));
}

language_grounder::atoms_info language_grounder::build_atoms(context &context) {
    del::name_vector atom_names;
    boost::dynamic_bitset<> is_static, is_public_static;

    for (const auto &[p, param_types] : context.predicates.get_predicate_signatures()) {
        combinations_handler handler{param_types, context};
        bool is_static_p = context.predicates.is_static_predicate(p);
        bool is_public_static_p = context.predicates.is_public_static_predicate(p);

        if (handler.empty()) {
            atom_names.emplace_back(p);
            is_static.push_back(is_static_p);
            is_public_static.push_back(is_public_static_p);
        } else
            while (handler.has_next()) {
                std::string atom_name = p;

                for (unsigned long id: handler.next())
                    atom_name += "_" + context.entities.get_entity_name(id);

                atom_names.emplace_back(std::move(atom_name));
                is_static.push_back(is_static_p);
                is_public_static.push_back(is_public_static_p);
            }
    }
    return {std::move(atom_names), std::move(is_static), std::move(is_public_static)};
}

del::name_vector language_grounder::build_agents(context &context) {
    del::name_vector agent_names;
    const bit_deque &agents = context.entities.get_entities_with_type(context.types, context.types.get_type("agent"));

    for (del::agent ag : agents)
        agent_names.emplace_back(context.entities.get_entity_name(ag));

    return agent_names;
}

std::string language_grounder::get_predicate_name(const ast::predicate_ptr &pred, grounder_info &info) {
    std::string atom_name = pred->get_id()->get_token().get_lexeme();

    for (const ast::term &t : pred->get_terms())
        atom_name += "_" + language_grounder::get_term_name(t, info);

    return atom_name;
}

unsigned long language_grounder::get_predicate_id(const ast::predicate_ptr &pred, grounder_info &info) {
    return info.language->get_atom_id(language_grounder::get_predicate_name(pred, info));
}

std::string language_grounder::get_term_name(const ast::term &t, grounder_info &info, bool rename_variables) {
    if (std::holds_alternative<ast::identifier_ptr>(t))
        return std::get<ast::identifier_ptr>(t)->get_token().get_lexeme();
    else if (std::holds_alternative<ast::variable_ptr>(t))
        return info.assignment.get_assigned_entity_name(info.context.entities,
                std::get<ast::variable_ptr>(t)->get_token().get_lexeme(), rename_variables);

    return "";
}

unsigned long language_grounder::get_term_id(const ast::term &t, grounder_info &info, bool rename_variables) {
    const std::string &t_name = language_grounder::get_term_name(t, info, rename_variables);

    if (std::holds_alternative<ast::identifier_ptr>(t))
        return info.context.entities.get_entity_id(t_name);
    else if (std::holds_alternative<ast::variable_ptr>(t))
        return info.assignment.get_assigned_entity_id(info.context.entities, t_name);

    return 0;
}
