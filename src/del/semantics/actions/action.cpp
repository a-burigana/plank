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

#include "../../../../include/del/semantics/actions/action.h"
#include "../../../../include/del/semantics/states/states_types.h"
#include "../../../../include/del/utils/printer/formula_printer.h"

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

const event_bitset &del::action::get_obs_type_possible_events(const del::obs_type t, const event_id e) const {
    return m_relations[t][e];
}

bool del::action::has_edge(const del::obs_type t, const event_id e, const event_id f) const {
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

std::ostream &del::operator<<(std::ostream &os, const action &act) {
    using edges_map = std::map<std::pair<event_id, event_id>, std::vector<del::obs_type>>;

    const std::string font = std::string{"\"Helvetica,Arial,sans-serif\""};

    os
            << "digraph {" << std::endl
            << "\tfontname=" << font << ";" << std::endl
            << "\tnode [fontname=" << font << "];" << std::endl
            << "\tedge [fontname=" << font << "];" << std::endl
            << "\tlabeljust=l;" << std::endl
            << "\trankdir=BT;" << std::endl
            << "\tranksep=0.5;" << std::endl
            << "\tnewrank=true;" << std::endl
            << "\tcompound=true;" << std::endl;

    os << std::endl << "\t{ node[shape=box] ";

    for (event_id e = 0; e < act.get_events_number(); ++e)
        if (not act.is_designated(e))
            os << "e" << e << "; ";

    os << "}" << std::endl;

    os << std::endl << "\t{ node[shape=box3d] ";

    for (const world_id ed : act.get_designated_events())
        os << "e" << ed << "; ";

    os << "}" << std::endl << std::endl;

    // Map: <accessible_worlds_hash> -> <list_of_worlds>
    try {
        std::map<unsigned long, std::deque<event_id>> ranks;

        for (world_id e = 0; e < act.get_events_number(); ++e) {
            boost::dynamic_bitset<> out(act.get_events_number());

            for (del::obs_type ag = 0; ag < act.get_obs_types_number(); ++ag)
                out |= *act.get_obs_type_possible_events(ag, e);

            ranks[out.to_ulong()].emplace_back(e);
        }

        for (const auto &[hash, es]: ranks) {
            os << "\t{ rank = same; ";

            for (const event_id e_id: es)
                os << "e" << e_id << "; ";

            os << "}" << std::endl;
        }

        os << std::endl;
    } catch (boost::wrapexcept<std::overflow_error> &e) {}

    edges_map edges;

    for (del::obs_type ag = 0; ag < act.get_obs_types_number(); ++ag)
        for (event_id e = 0; e < act.get_events_number(); ++e)
            for (const event_id f : act.get_obs_type_possible_events(ag, e))
                if (edges.find({e, f}) == edges.end())
                    edges[{e, f}] = {ag};
                else
                    edges[{e, f}].emplace_back(ag);

    auto print_ags = [&act](const std::vector<del::obs_type> &ags) {
        std::string ags_string;
        for (const del::obs_type &ag: ags)
            ags_string += std::string{act.get_obs_type_name(ag)} + ", ";
        return ags_string.substr(0, ags_string.size() - 2);
    };

    for (auto &[t, ags]: edges) {
        const world_id from = t.first, to = t.second;
        auto it = edges.find({to, from});
        if (it == edges.end())
            os << "\te" << from << " -> e" << to << " [label=\"" << print_ags(ags) << "\"];" << std::endl;
        else {
            std::vector<del::obs_type> ags2 = it->second;
            auto size = std::max(ags.size(), ags2.size());
            std::vector<del::obs_type> ags_intersection = std::vector<del::obs_type>(size), ags_difference = std::vector<del::obs_type>(size);

            std::sort(ags.begin(), ags.end());
            std::sort(ags2.begin(), ags2.end());

            auto it1 = std::set_intersection(ags.begin(), ags.end(), ags2.begin(), ags2.end(), ags_intersection.begin());
            auto it2 = std::set_difference(ags.begin(), ags.end(), ags2.begin(), ags2.end(), ags_difference.begin());

            ags_intersection.resize(it1 - ags_intersection.begin());
            ags_difference.resize(it2 - ags_difference.begin());

            if (not ags_intersection.empty()) {
                if (from < to)
                    os << "\te" << from << " -> e" << to << " [label=\"" << print_ags(ags_intersection) << "\" dir=both];" << std::endl;
                else if (from == to)
                    os << "\te" << from << " -> e" << to << " [label=\"" << print_ags(ags_intersection) << "\"];" << std::endl;
            }

            if (not ags_difference.empty())
                os << "\te" << from << " -> e" << to << " [label=\"" << print_ags(ags_difference) << "\"];" << std::endl;
        }
    }

    os
            << "\tnode [] val_table [shape=none label=<"                                       << std::endl
            << "\t\t<TABLE border=\"0\" cellspacing=\"0\" cellborder=\"1\" cellpadding=\"2\">" << std::endl;

    os
            << "\t\t\t<TR>"             << std::endl
            << "\t\t\t\t<TD>Event</TD>" << std::endl
            << "\t\t\t\t<TD>Pre</TD>"   << std::endl
            << "\t\t\t\t<TD>Post</TD>"  << std::endl
            << "\t\t\t</TR>"            << std::endl;

    for (world_id e = 0; e < act.get_events_number(); ++e) {
        os
                << "\t\t\t<TR>" << std::endl
                << "\t\t\t\t<TD>" << "e" << e << "</TD>" << std::endl;

        os
                << "\t\t\t\t<TD>" << printer::formula_printer::to_string(act.get_precondition(e), act.get_language(), true) << "</TD>" << std::endl;
//                << "\t\t\t\t<TD>" << act.get_precondition(e)->to_string(act.get_language(), true) << "</TD>" << std::endl;

        os << "\t\t\t\t<TD>" << std::endl;

        if (not act.is_ontic(e))
            os << "-";
        else
            for (const auto &[p, f_post] : act.get_postconditions(e))
                os
                    << "\t\t\t\t\t(<font color=\"blue\">" << act.get_language()->get_atom_name(p) << "</font>"
                    << " iff "
                    << printer::formula_printer::to_string(f_post, act.get_language(), true)
//                    << f_post->to_string(act.get_language(), true)
                    << ") " << std::endl;

        os
                << "\t\t\t\t</TD>" << std::endl
                << "\t\t\t</TR>"   << std::endl;
    }

    os
            << "\t\t</TABLE>" << std::endl
            << "\t>];"        << std::endl
            << "}";

    return os;
}