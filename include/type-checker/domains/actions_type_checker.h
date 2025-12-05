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

#ifndef EPDDL_ACTIONS_TYPE_CHECKER_H
#define EPDDL_ACTIONS_TYPE_CHECKER_H

#include "../context/context.h"
#include "../../ast/domains/actions/action_decl_ast.h"

namespace epddl::type_checker {
    class actions_type_checker {
    public:
        static void check(const ast::action_ptr &action, context &context);

    private:
        static void check_action_signature(const ast::action_signature_ptr &signature, context &context);

        static void check_events_conditions(const ast::action_signature_ptr &signature, context &context);
        static void check_event_condition(const ast::event_ptr &e, const ast::event_condition_ptr &cond, const std::string &e_var_name, const std::string &act_type_name, context &context);

        static void check_prop_precondition(const ast::event_ptr &e, const std::string &e_var_name, const std::string &act_type_name, context &context);
        static void check_prop_postconditions(const ast::event_ptr &e, const std::string &e_var_name, const std::string &act_type_name, context &context);
        static void check_prop_event(const ast::event_ptr &e, const std::string &e_var_name, const std::string &act_type_name, context &context);

        [[nodiscard]] static bool has_prop_postconditions(const ast::event_ptr &e, context &context);

        static void check_trivial_precondition(const ast::event_ptr &e, const std::string &e_var_name, const std::string &act_type_name, context &context, bool check_positive);
        static void check_trivial_postconditions(const ast::event_ptr &e, const std::string &e_var_name, const std::string &act_type_name, context &context, bool check_positive);
        static void check_trivial_event(const ast::event_ptr &e, const std::string &e_var_name, const std::string &act_type_name, context &context, bool check_positive);

        static void check_obs_conditions(const ast::obs_cond &obs_cond, context &context);

        static void check_obs_conditions(const ast::static_obs_cond_ptr &obs_cond, context &context);
        static void check_obs_conditions(const ast::if_then_else_obs_cond_ptr &obs_cond, context &context);
        static void check_obs_conditions(const ast::if_obs_cond_ptr &obs_cond, context &context);
        static void check_obs_conditions(const ast::else_if_obs_cond_ptr &obs_cond, context &context);
        static void check_obs_conditions(const ast::else_obs_cond_ptr &obs_cond, context &context);
        static void check_obs_conditions(const ast::default_obs_cond_ptr &obs_cond, context &context);
    };
}

#endif //EPDDL_ACTIONS_TYPE_CHECKER_H
