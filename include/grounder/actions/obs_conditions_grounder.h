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

#ifndef EPDDL_OBS_CONDITIONS_GROUNDER_H
#define EPDDL_OBS_CONDITIONS_GROUNDER_H

#include "../grounder_info.h"
#include "../../type-checker/context/context.h"
#include "../../del/semantics/actions/action.h"

using namespace epddl::type_checker;

namespace epddl::grounder {
    class obs_conditions_grounder {
    public:
        static del::obs_conditions
        build_obs_conditions(const ast::action_ptr &action, grounder_info &info);

    private:
        static void
        build_obs_condition(const ast::obs_cond &obs_cond, grounder_info &info,
                            del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                            const name_vector &obs_types_names, std::optional<del::obs_type> default_t);

        static void
        build_obs_condition(const ast::static_obs_cond_ptr &obs_cond, grounder_info &info,
                            del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                            const name_vector &obs_types_names, std::optional<del::obs_type> default_t);

        static void
        build_obs_condition(const ast::if_then_else_obs_cond_ptr &obs_cond, grounder_info &info,
                            del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                            const name_vector &obs_types_names, std::optional<del::obs_type> default_t);

        static void
        build_obs_condition(const ast::if_obs_cond_ptr &obs_cond, grounder_info &info,
                            del::obs_conditions &conditions, del::agent i, const name_id_map &obs_types_ids,
                            const name_vector &obs_types_names, std::optional<del::obs_type> default_t,
                            del::formula_deque &fs);
        static void
        build_obs_condition(const ast::else_if_obs_cond_ptr &obs_cond, grounder_info &info,
                            del::obs_conditions &conditions, del::agent i, const name_id_map &obs_types_ids,
                            const name_vector &obs_types_names, std::optional<del::obs_type> default_t,
                            del::formula_deque &fs);
        static void
        build_obs_condition(const std::optional<ast::else_obs_cond_ptr> &obs_cond, grounder_info &info,
                            del::obs_conditions &conditions, del::agent i, const name_id_map &obs_types_ids,
                            const name_vector &obs_types_names, std::optional<del::obs_type> default_t,
                            del::formula_deque &fs);

        static void
        build_obs_condition(const ast::default_obs_cond_ptr &obs_cond, grounder_info &info,
                            del::obs_conditions &conditions, const name_id_map &obs_types_ids,
                            const name_vector &obs_types_names, std::optional<del::obs_type> default_t);

        static void assign_obs_cond(grounder_info &info, const ast::info &token_info, del::obs_conditions &conditions,
                                    del::agent i, del::obs_type t, const del::formula_ptr &cond,
                                    const name_vector &obs_types_names);

        static void assign_default_obs_cond(grounder_info &info, const ast::info &token_info,
                                            del::obs_conditions &conditions, std::optional<del::obs_type> &default_t);
    };
}

#endif //EPDDL_OBS_CONDITIONS_GROUNDER_H
