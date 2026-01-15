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

#include "../../../../../include/lib/del/semantics/actions/action.h"
#include "../../../../../include/lib/del/semantics/states/states_types.h"

using namespace del;

del::action::action(del::language_ptr language, std::string name, std::string action_type_name, unsigned long events_number,
                    action_relations relations, preconditions pre, postconditions post, obs_conditions obs,
                    event_bitset designated_events, action_params params, name_vector events_names,
                    name_vector event_variables_names, name_vector obs_types_names, boost::dynamic_bitset<> is_ontic) :
       m_language{std::move(language)},
       m_name{std::move(name)},
       m_action_type_name{std::move(action_type_name)},
       m_events_number{events_number},
       m_relations{std::move(relations)},
       m_preconditions{std::move(pre)},
       m_postconditions{std::move(post)},
       m_obs_conditions{std::move(obs)},
       m_designated_events{std::move(designated_events)},
       m_params{std::move(params)},
       m_events_names{std::move(events_names)},
       m_event_variables_names{std::move(event_variables_names)},
       m_obs_types_names{std::move(obs_types_names)},
       m_is_ontic{std::move(is_ontic)} {
    m_obs_types_number = m_relations.size();
}

language_ptr del::action::get_language() const {
    return m_language;
}

std::string del::action::get_name() const {
    return m_name;
}

std::string del::action::get_action_type_name() const {
    return m_action_type_name;
}

unsigned long del::action::get_events_number() const {
    return m_events_number;
}

unsigned long del::action::get_obs_types_number() const {
    return m_obs_types_number;
}

const event_bitset &del::action::get_obs_type_possible_events(const obs_type t, const event_id e) const {
    return m_relations[t][e];
}

bool del::action::has_edge(const obs_type t, const event_id e, const event_id f) const {
    return std::find(m_relations[t].at(e).begin(), m_relations[t].at(e).end(), f) != m_relations[t].at(e).end();
}

del::formula_ptr del::action::get_precondition(const event_id e) const {
    return m_preconditions[e];
}

const event_post &del::action::get_postconditions(const event_id e) const {
    return m_postconditions[e];
}

const event_bitset &del::action::get_designated_events() const {
    return m_designated_events;
}

const agent_obs_conditions &del::action::get_agent_obs_conditions(agent i) const {
    return m_obs_conditions[i];
}

const del::formula_ptr &del::action::get_obs_condition(agent i, obs_type t) const {
    return m_obs_conditions[i].at(t);
}

bool del::action::is_designated(const event_id e) const {
    return std::find(m_designated_events.begin(), m_designated_events.end(), e) != m_designated_events.end();
}

const std::string &del::action::get_event_name(unsigned long id) const {
    return m_events_names[id];
}

const std::string &del::action::get_event_variable_name(unsigned long id) const {
    return m_event_variables_names[id];
}

const std::string &del::action::get_obs_type_name(unsigned long id) const {
    return m_obs_types_names[id];
}

const action_params &del::action::get_params() const {
    return m_params;
}

bool del::action::is_ontic(const event_id e) const {
    return m_is_ontic[e];
}

bool del::action::is_purely_epistemic() const {
    return m_is_ontic.none();
}
