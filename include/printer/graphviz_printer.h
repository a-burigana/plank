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

#ifndef PLANK_GRAPHVIZ_PRINTER_H
#define PLANK_GRAPHVIZ_PRINTER_H

#include "../del/semantics/states/state.h"
#include "../del/semantics/actions/action.h"
#include "formula_printer.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

namespace fs = std::filesystem;

namespace printer {
    class graphviz {
    public:
        static void print_state(const del::state_ptr &s, const fs::path &path, const std::string &name,
                const std::string &file_ext_flag) {
            graphviz::print_model_helper(s, path, name, file_ext_flag);
        }

        static void print_action(const del::action_ptr &a, const fs::path &path, const std::string &name,
                                 const std::string &file_ext_flag) {
            graphviz::print_model_helper(a, path, name, file_ext_flag);
        }

    private:
        template<class model_type>
        static void print_model_helper(const model_type &m, const fs::path &path, const std::string &name,
                                       const std::string &file_ext_flag) {
            static_assert(
                    std::is_same_v<model_type, del::state_ptr> or
                    std::is_same_v<model_type, del::action_ptr>);

            if (not fs::exists(path))
                fs::create_directories(path);

            const std::string img_ext = file_ext_flag.substr(2);

            fs::path dot_file_path = (path / std::string{"." + name + ".dot"}).lexically_normal();
            fs::path img_file_path = (path / std::string{name + "." + img_ext}).lexically_normal();
            std::ofstream dot_file = std::ofstream{dot_file_path};

            graphviz::print_dot(dot_file, m);
            dot_file.close();

            std::string command = "dot -T" + img_ext + " " + dot_file_path.string() + " > " + img_file_path.string();
            system(command.c_str());

            command = "rm " + dot_file_path.string();
            system(command.c_str());
        }

        static void print_dot(std::ofstream &os, const del::state_ptr &s) {
            using edges_map = std::map<std::pair<del::world_id, del::world_id>, std::vector<del::agent>>;
            const std::string font = std::string{"\"Helvetica,Arial,sans-serif\""};

            os << "digraph {" << std::endl
               << "\tfontname=" << font << ";" << std::endl
               << "\tnode [fontname=" << font << "];" << std::endl
               << "\tedge [fontname=" << font << "];" << std::endl
               << "\tlabeljust=l;" << std::endl
               << "\trankdir=BT;" << std::endl
               << "\tranksep=0.5;" << std::endl
               << "\tnewrank=true;" << std::endl
               << "\tcompound=true;" << std::endl;

            os << std::endl << "\t{ node[shape=doublecircle] ";

            for (const del::world_id wd: s->get_designated_worlds())
                os << "w" << wd << "; ";

            os << "}" << std::endl << std::endl;

            // Map: <accessible_worlds_hash> -> <list_of_worlds>
            try {
                std::map<unsigned long, std::deque<del::world_id>> ranks;

                for (del::world_id w = 0; w < s->get_worlds_number(); ++w) {
                    boost::dynamic_bitset<> out(s->get_worlds_number());

                    for (del::agent ag = 0; ag < s->get_language()->get_agents_number(); ++ag)
                        out |= *s->get_agent_possible_worlds(ag, w);

                    ranks[out.to_ulong()].emplace_back(w);
                }

                for (const auto &[hash, ws]: ranks) {
                    os << "\t{ rank = same; ";

                    for (const del::world_id w_id: ws)
                        os << "w" << w_id << "; ";

                    os << "}" << std::endl;
                }

                os << std::endl;
            } catch (boost::wrapexcept<std::overflow_error> &e) {}

            edges_map edges;

            for (del::agent ag = 0; ag < s->get_language()->get_agents_number(); ++ag)
                for (del::world_id w = 0; w < s->get_worlds_number(); ++w)
                    for (const del::world_id v: s->get_agent_possible_worlds(ag, w))
//            for (del::world_id v = 0; v < state.get_worlds_number(); ++v)
                        if (edges.find({w, v}) == edges.end())      // state.has_edge(ag, w, v) and
                            edges[{w, v}] = {ag};
                        else
                            edges[{w, v}].emplace_back(ag);

            auto print_ags = [&s](const std::vector<del::agent> &ags) {
                std::string ags_string;
                for (const del::agent &ag: ags)
                    ags_string += std::string{s->get_language()->get_agent_name(ag)} + ", ";
                return ags_string.substr(0, ags_string.size() - 2);
            };

            for (auto &[t, ags]: edges) {
                const del::world_id from = t.first, to = t.second;
                auto it = edges.find({to, from});
                if (it == edges.end())
                    os << "\tw" << from << " -> w" << to << " [label=\"" << print_ags(ags) << "\"];" << std::endl;
                else {
                    std::vector<del::agent> ags2 = it->second;
                    auto size = std::max(ags.size(), ags2.size());
                    std::vector<del::agent> ags_intersection = std::vector<del::agent>(
                            size), ags_difference = std::vector<del::agent>(size);

                    std::sort(ags.begin(), ags.end());
                    std::sort(ags2.begin(), ags2.end());

                    auto it1 = std::set_intersection(ags.begin(), ags.end(), ags2.begin(), ags2.end(),
                                                     ags_intersection.begin());
                    auto it2 = std::set_difference(ags.begin(), ags.end(), ags2.begin(), ags2.end(),
                                                   ags_difference.begin());

                    ags_intersection.resize(it1 - ags_intersection.begin());
                    ags_difference.resize(it2 - ags_difference.begin());

                    if (not ags_intersection.empty()) {
                        if (from < to)
                            os << "\tw" << from << " -> w" << to << " [label=\"" << print_ags(ags_intersection)
                               << "\" dir=both];" << std::endl;
                        else if (from == to)
                            os << "\tw" << from << " -> w" << to << " [label=\"" << print_ags(ags_intersection)
                               << "\"];"
                               << std::endl;
                    }

                    if (not ags_difference.empty())
                        os << "\tw" << from << " -> w" << to << " [label=\"" << print_ags(ags_difference) << "\"];"
                           << std::endl;
                }
            }

            os << "\tnode [] val_table [shape=none label=<" << std::endl
               << "\t\t<TABLE border=\"0\" cellspacing=\"0\" cellborder=\"1\" cellpadding=\"2\">" << std::endl;

            os << "\t\t\t<TR>" << std::endl
               << "\t\t\t\t<TD>World</TD>" << std::endl
               << "\t\t\t\t<TD>Label</TD>" << std::endl
               << "\t\t\t</TR>" << std::endl;

            for (del::world_id w = 0; w < s->get_worlds_number(); ++w) {
                os << "\t\t\t<TR>" << std::endl
                   << "\t\t\t\t<TD>" << "w" << w << "</TD>" << std::endl;

                os << "\t\t\t\t<TD>" << std::endl;

                for (del::atom p = 0; p < s->get_language()->get_atoms_number(); ++p) {
                    if (s->get_label(w)[p]) {
                        std::string_view color = "blue";        // s->get_label(w)[p] ? "blue" : "red";
                        std::string_view sep = " ";           // p < s->get_language()->get_atoms_number() - 1 ? ", " : "";

                        os << "\t\t\t\t\t<font color=\"" << color << "\">" << s->get_language()->get_atom_name(p)
                           << "</font>"
                           << sep << std::endl;
                    }
                }

                os << "\t\t\t\t</TD>" << std::endl
                   << "\t\t\t</TR>" << std::endl;
            }

            os << "\t\t</TABLE>" << std::endl
               << "\t>];" << std::endl
               << "}";
        }

        static void print_dot(std::ostream &os, const del::action_ptr &a) {
            using edges_map = std::map<std::pair<del::event_id, del::event_id>, std::vector<del::obs_type>>;

            const std::string font = std::string{"\"Helvetica,Arial,sans-serif\""};

            os  << "digraph {" << std::endl
                << "\tfontname=" << font << ";" << std::endl
                << "\tnode [fontname=" << font << "];" << std::endl
                << "\tedge [fontname=" << font << "];" << std::endl
                << "\tlabeljust=l;" << std::endl
                << "\trankdir=BT;" << std::endl
                << "\tranksep=0.5;" << std::endl
                << "\tnewrank=true;" << std::endl
                << "\tcompound=true;" << std::endl;

            os << std::endl << "\t{ node[shape=box] ";

            for (del::event_id e = 0; e < a->get_events_number(); ++e)
                if (not a->is_designated(e))
                    os << "e" << e << "; ";

            os << "}" << std::endl;

            os << std::endl << "\t{ node[shape=box3d] ";

            for (const del::world_id ed: a->get_designated_events())
                os << "e" << ed << "; ";

            os << "}" << std::endl << std::endl;

            // Map: <accessible_worlds_hash> -> <list_of_worlds>
            try {
                std::map<unsigned long, std::deque<del::event_id>> ranks;

                for (del::event_id e = 0; e < a->get_events_number(); ++e) {
                    boost::dynamic_bitset<> out(a->get_events_number());

                    for (del::obs_type ag = 0; ag < a->get_obs_types_number(); ++ag)
                        out |= *a->get_obs_type_possible_events(ag, e);

                    ranks[out.to_ulong()].emplace_back(e);
                }

                for (const auto &[hash, es]: ranks) {
                    os << "\t{ rank = same; ";

                    for (const del::event_id e_id: es)
                        os << "e" << e_id << "; ";

                    os << "}" << std::endl;
                }

                os << std::endl;
            } catch (boost::wrapexcept<std::overflow_error> &e) {}

            edges_map edges;

            for (del::obs_type ag = 0; ag < a->get_obs_types_number(); ++ag)
                for (del::event_id e = 0; e < a->get_events_number(); ++e)
                    for (const del::event_id f: a->get_obs_type_possible_events(ag, e))
                        if (edges.find({e, f}) == edges.end())
                            edges[{e, f}] = {ag};
                        else
                            edges[{e, f}].emplace_back(ag);

            auto print_ags = [&](const std::vector<del::obs_type> &ags) {
                std::string ags_string;
                for (const del::obs_type &ag: ags)
                    ags_string += std::string{a->get_obs_type_name(ag)} + ", ";
                return ags_string.substr(0, ags_string.size() - 2);
            };

            for (auto &[t, ags]: edges) {
                const del::event_id from = t.first, to = t.second;
                auto it = edges.find({to, from});
                if (it == edges.end())
                    os << "\te" << from << " -> e" << to << " [label=\"" << print_ags(ags) << "\"];" << std::endl;
                else {
                    std::vector<del::obs_type> ags2 = it->second;
                    auto size = std::max(ags.size(), ags2.size());
                    std::vector<del::obs_type> ags_intersection = std::vector<del::obs_type>(
                            size), ags_difference = std::vector<del::obs_type>(size);

                    std::sort(ags.begin(), ags.end());
                    std::sort(ags2.begin(), ags2.end());

                    auto it1 = std::set_intersection(ags.begin(), ags.end(), ags2.begin(), ags2.end(),
                                                     ags_intersection.begin());
                    auto it2 = std::set_difference(ags.begin(), ags.end(), ags2.begin(), ags2.end(),
                                                   ags_difference.begin());

                    ags_intersection.resize(it1 - ags_intersection.begin());
                    ags_difference.resize(it2 - ags_difference.begin());

                    if (not ags_intersection.empty()) {
                        if (from < to)
                            os << "\te" << from << " -> e" << to << " [label=\"" << print_ags(ags_intersection)
                               << "\" dir=both];" << std::endl;
                        else if (from == to)
                            os << "\te" << from << " -> e" << to << " [label=\"" << print_ags(ags_intersection)
                               << "\"];" << std::endl;
                    }

                    if (not ags_difference.empty())
                        os << "\te" << from << " -> e" << to << " [label=\"" << print_ags(ags_difference) << "\"];"
                           << std::endl;
                }
            }

            os  << "\tnode [] val_table [shape=none label=<" << std::endl
                << "\t\t<TABLE border=\"0\" cellspacing=\"0\" cellborder=\"1\" cellpadding=\"2\">" << std::endl;

            os  << "\t\t\t<TR>" << std::endl
                << "\t\t\t\t<TD>Event</TD>" << std::endl
                << "\t\t\t\t<TD>Pre</TD>" << std::endl
                << "\t\t\t\t<TD>Post</TD>" << std::endl
                << "\t\t\t</TR>" << std::endl;

            for (del::event_id e = 0; e < a->get_events_number(); ++e) {
                os  << "\t\t\t<TR>" << std::endl
                    << "\t\t\t\t<TD>" << "e" << e << "</TD>" << std::endl;

                os  << "\t\t\t\t<TD>"
                    << printer::formula_printer::to_string(a->get_precondition(e), a->get_language(), true)
                    << "</TD>" << std::endl;
//                << "\t\t\t\t<TD>" << a->get_precondition(e)->to_string(a->get_language(), true) << "</TD>" << std::endl;

                os << "\t\t\t\t<TD>" << std::endl;

                if (not a->is_ontic(e))
                    os << "-";
                else
                    for (const auto &[p, f_post]: a->get_postconditions(e))
                        os  << "\t\t\t\t\t(<font color=\"blue\">" << a->get_language()->get_atom_name(p)
                            << "</font>"
                            << " iff "
                            << printer::formula_printer::to_string(f_post, a->get_language(), true)
                            //                    << f_post->to_string(a->get_language(), true)
                            << ") " << std::endl;

                os  << "\t\t\t\t</TD>" << std::endl
                    << "\t\t\t</TR>" << std::endl;
            }

            os  << "\t\t</TABLE>" << std::endl
                << "\t>];" << std::endl
                << "}";
        }
    };
}

#endif //PLANK_GRAPHVIZ_PRINTER_H
