// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano_
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

#ifndef EPDDL_ACTION_H
#define EPDDL_ACTION_H

#include <deque>
#include <set>
#include <map>
#include "actions_types.h"
#include "boost/dynamic_bitset.hpp"
#include "../../language/language.h"
#include "../../../type-checker/context/context_types.h"

namespace del {
    class action {
    public:
        action(del::language_ptr language, std::string name, std::string action_type_name, unsigned long events_number,
               action_relations relations, preconditions pre, postconditions post, obs_conditions obs,
               event_bitset designated_events, action_params params, name_vector events_names,
               name_vector event_variables_names, name_vector obs_types_names, boost::dynamic_bitset<> is_ontic);

        action(const action&) = delete;
        action& operator=(const action&) = delete;

        action(action&&) = default;
        action& operator=(action&&) = default;

        ~action() = default;

        [[nodiscard]] del::language_ptr get_language() const;
        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] std::string get_action_type_name() const;

        [[nodiscard]] unsigned long get_events_number() const;
        [[nodiscard]] unsigned long get_obs_types_number() const;

        [[nodiscard]] const event_bitset &get_obs_type_possible_events(del::agent ag, event_id e) const;
        [[nodiscard]] bool has_edge(del::agent ag, event_id e, event_id f) const;

        [[nodiscard]] del::formula_ptr get_precondition(event_id e) const;
        [[nodiscard]] const event_post &get_postconditions(event_id e) const;

        [[nodiscard]] const agent_obs_conditions &get_agent_obs_conditions(agent i) const;
        [[nodiscard]] const formula_ptr &get_obs_condition(obs_type t, agent i) const;

        [[nodiscard]] const event_bitset &get_designated_events() const;
        [[nodiscard]] bool is_designated(event_id e) const;

        [[nodiscard]] const std::string &get_event_name(unsigned long id) const;
        [[nodiscard]] const std::string &get_event_variable_name(unsigned long id) const;
        [[nodiscard]] const std::string &get_obs_type_name(unsigned long id) const;

        [[nodiscard]] const action_params &get_params() const;
        [[nodiscard]] bool is_ontic(event_id e) const;
        [[nodiscard]] bool is_purely_epistemic() const;

        friend std::ostream &operator<<(std::ostream &os, const action &act);

    private:
        del::language_ptr m_language;

        std::string m_name, m_action_type_name;
        unsigned long m_events_number, m_obs_types_number;
        action_relations m_relations;
        preconditions m_preconditions;
        postconditions m_postconditions;
        obs_conditions m_obs_conditions;
        event_bitset m_designated_events;

        action_params m_params;
        name_vector m_events_names, m_event_variables_names, m_obs_types_names;
        boost::dynamic_bitset<> m_is_ontic;
    };
}

#endif //EPDDL_ACTION_H
