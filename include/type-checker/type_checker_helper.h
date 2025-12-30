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

#ifndef PLANK_TYPE_CHECKER_HELPER_H
#define PLANK_TYPE_CHECKER_HELPER_H

#include <deque>
#include <tuple>
#include "context/action_types_context.h"
#include "context/actions_context.h"
#include "context/context.h"
#include "context/entities_context.h"
#include "context/events_context.h"
#include "context/predicates_context.h"
#include "context/types_context.h"
#include "domains/actions_type_checker.h"
#include "type.h"
#include "../error-manager/error_manager.h"

namespace epddl::type_checker {
    class type_checker_helper {
    public:
        static context do_semantic_check(const planning_specification &spec, spec_error_managers &err_managers);

    private:
        static context build_context(const planning_specification &spec, spec_error_managers &spec_err_managers);

        static types_context build_types_context(const domain_ptr &domain, error_manager_ptr &domain_err_manager);

        static entities_context build_entities(const planning_specification &spec, types_context &types_context,
                                               error_manager_ptr &domain_err_manager,
                                               error_manager_ptr &problem_err_manager);

        static predicates_context build_predicate_signatures(const planning_specification &spec,
                                                             types_context &types_context,
                                                             entities_context &entities_context,
                                                             error_manager_ptr &domain_err_manager);

        static events_context build_event_signatures(const planning_specification &spec,
                                                     types_context &types_context,
                                                     entities_context &entities_context,
                                                     error_manager_ptr &domain_err_manager);

        static action_types_context build_action_type_signatures(const planning_specification &spec,
                                                                 types_context &types_context,
                                                                 entities_context &entities_context,
                                                                 error_manager_map &library_err_managers);

        static actions_context build_action_signatures(const planning_specification &spec,
                                                       types_context &types_context,
                                                       entities_context &entities_context,
                                                       error_manager_ptr &domain_err_manager);
    };
}

#endif //PLANK_TYPE_CHECKER_HELPER_H
