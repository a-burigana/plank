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

#include "../../../include/del/language/language.h"
#include <utility>
#include <string>

using namespace del;

language::language(name_vector &atoms_names, name_vector &agents_names) :
    m_atoms_names{std::move(atoms_names)},
    m_agents_names{std::move(agents_names)},
    m_atoms{m_atoms_names.size()},
    m_agents{m_agents_names.size()} {
    for (size_t i = 0; i < m_atoms_names.size(); ++i)
        m_atoms_map[m_atoms_names[i]] = i;
    for (size_t i = 0; i < m_agents_names.size(); ++i)
        m_agents_map[m_agents_names[i]] = i;
}

atom language::get_atoms_number() const {
    return m_atoms;
}

agent language::get_agents_number() const {
    return m_agents;
}

atom language::get_atom_id(const std::string &atom_name) const {
    return m_atoms_map.at(atom_name);
}

agent language::get_agent_id(const std::string &agent_name) const {
    return m_agents_map.at(agent_name);
}

const std::string &language::get_atom_name(const atom atom) const {
    return m_atoms_names[atom];
}

const std::string &language::get_agent_name(agent agent) const {
    return m_agents_names[agent];
}
