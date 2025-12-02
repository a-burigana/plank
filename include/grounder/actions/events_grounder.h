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

#ifndef EPDDL_EVENTS_GROUNDER_H
#define EPDDL_EVENTS_GROUNDER_H

#include "../../type-checker/context/context.h"
#include "../../del/semantics/actions/action.h"
#include "../variables_assignment.h"
#include <tuple>

using namespace epddl::type_checker;

namespace epddl::grounder {
    class events_grounder {
    public:
        static std::pair<del::formula_ptr, del::event_post>
        build_event(const ast::event_ptr &event, const ast::event_signature_ptr &sign,
                    const context &context, const type_ptr &types_tree, variables_assignment &assignment,
                    const del::atom_set &static_atoms, const del::language_ptr &language);

    private:
        using atom_conditions = std::vector<del::formula_deque>;
        using literal         = std::pair<bool, del::atom>;
        using literal_list    = std::list<literal>;

        static del::formula_ptr
        build_event_precondition(const ast::event_ptr &event, const context &context, const type_ptr &types_tree,
                                 variables_assignment &assignment, const del::atom_set &static_atoms,
                                 const del::language_ptr &language);

        static del::event_post
        build_event_postconditions(const ast::event_ptr &event, const context &context, const type_ptr &types_tree,
                                   variables_assignment &assignment, const del::atom_set &static_atoms,
                                   const del::language_ptr &language);

        static void
        build_postcondition(const ast::postcondition &post, const context &context, const type_ptr &types_tree,
                            variables_assignment &assignment, const del::atom_set &static_atoms,
                            const del::language_ptr &language, atom_conditions &conditions);

        static void
        build_postcondition(const ast::literal_postcondition_ptr &post, const context &context, const type_ptr &types_tree,
                            variables_assignment &assignment, const del::atom_set &static_atoms,
                            const del::language_ptr &language, atom_conditions &conditions);

        static void
        build_postcondition(const ast::when_postcondition_ptr &post, const context &context, const type_ptr &types_tree,
                            variables_assignment &assignment, const del::atom_set &static_atoms,
                            const del::language_ptr &language, atom_conditions &conditions);

        static void
        build_postcondition(const ast::iff_postcondition_ptr &post, const context &context, const type_ptr &types_tree,
                            variables_assignment &assignment, const del::atom_set &static_atoms,
                            const del::language_ptr &language, atom_conditions &conditions);

        static literal_list build_literals(const ast::list<ast::literal_ptr> &literals, const context &context,
                                           const type_ptr &types_tree, variables_assignment &assignment,
                                           const del::atom_set &static_atoms, const del::language_ptr &language);

        static typed_var_list build_reserved_params(const ast::event_ptr &event, const events_context &events);
        static std::string build_reserved_name(const std::string &name);
    };
}

#endif //EPDDL_EVENTS_GROUNDER_H
