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
#include "../../include/grounder/combinations_handler.h"
#include <memory>

using namespace epddl;
using namespace epddl::grounder;

del::language_ptr language_grounder::build_language(const context &context, const type_ptr &types_tree) {
    del::name_vector atom_names = language_grounder::build_atoms(context);
    del::name_vector agent_names = language_grounder::build_agents(context, types_tree);

    return std::make_shared<del::language>(std::move(atom_names), std::move(agent_names));
}

del::name_vector language_grounder::build_atoms(const context &context) {
    del::name_vector atom_names;

    for (const auto &[p, param_types] : context.get_predicate_signatures()) {
        combinations_handler handler{param_types, context};

        while (handler.has_next()) {
            std::string atom_name = p;

            for (unsigned long id : handler.next())
                atom_name += "_" + context.get_entity_name(id);

            atom_names.emplace_back(std::move(atom_name));
        }
    }
    return atom_names;
}

del::name_vector language_grounder::build_agents(const context &context, const type_ptr &types_tree) {
    del::name_vector agent_names;
    const bit_deque &agents = context.get_entities_with_type(type_utils::find(types_tree, "agent"));

    for (del::agent ag : agents)
        agent_names.emplace_back(context.get_entity_name(ag));

    return agent_names;
}
