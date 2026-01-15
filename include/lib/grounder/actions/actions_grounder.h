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

#ifndef PLANK_ACTIONS_GROUNDER_H
#define PLANK_ACTIONS_GROUNDER_H

#include "../grounder_info.h"
#include "../../type-checker/context/context.h"
#include "../../../lib/del/semantics/actions/action.h"
#include "../variables_assignment.h"

using namespace epddl::type_checker;

namespace epddl::grounder {
    class actions_grounder {
    public:
        static del::action_map build_actions(const planning_specification &spec, grounder_info &info);

    private:
        static del::action_ptr build_action(const ast::action_ptr &action, grounder_info &info);
        static del::action_ptr build_non_basic_action(const ast::action_ptr &action, grounder_info &info);
        static del::action_ptr build_basic_action(const ast::action_ptr &action, grounder_info &info);

        static del::action_relations
        build_action_relations(const ast::action_ptr &action, const ast::action_type_ptr &action_type,
                               grounder_info &info, const name_id_map &events_ids);

        static del::event_bitset
        build_designated_events(const ast::action_type_ptr &action_type, const name_id_map &events_ids,
                                const del::event_id events_no);

        static del::action_params
        build_action_params(const ast::action_ptr &action, grounder_info &info);

        static boost::dynamic_bitset<>
        build_is_ontic(grounder_info &info, const del::postconditions &post, del::event_id events_no);

        static std::string
        build_action_name(const ast::action_ptr &action, grounder_info &info);
    };
}

#endif //PLANK_ACTIONS_GROUNDER_H
