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

namespace del {
    class action {
    public:
        action(del::language_ptr language, std::string name, unsigned long long events_number, action_relations relations,
               preconditions pre, postconditions post, boost::dynamic_bitset<> is_ontic, event_set designated_events);

        action(const action&) = delete;
        action& operator=(const action&) = delete;

        action(action&&) = default;
        action& operator=(action&&) = default;

        ~action() = default;

        [[nodiscard]] del::language_ptr get_language() const;
        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] unsigned long long get_events_number() const;
        [[nodiscard]] const event_bitset &get_agent_possible_events(del::agent ag, event_id e) const;
        [[nodiscard]] bool has_edge(del::agent ag, event_id e, event_id f) const;
        [[nodiscard]] del::formula_ptr get_precondition(event_id e) const;
        [[nodiscard]] const event_post &get_postconditions(event_id e) const;
        [[nodiscard]] const event_set &get_designated_events() const;
        [[nodiscard]] bool is_designated(event_id e) const;

        [[nodiscard]] bool is_ontic(event_id e) const;
        [[nodiscard]] bool is_purely_epistemic() const;
        [[nodiscard]] unsigned long get_maximum_depth() const;

        friend std::ostream &operator<<(std::ostream &os, const action &act);

    private:
        del::language_ptr m_language;

        std::string m_name;
        unsigned long long m_events_number;
        action_relations m_relations;
        preconditions m_preconditions;
        postconditions m_postconditions;
        boost::dynamic_bitset<> m_is_ontic;
        event_set m_designated_events;
        unsigned long m_maximum_depth;

        void calculate_maximum_depth();
    };
}

#endif //EPDDL_ACTION_H
