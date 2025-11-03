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

#ifndef EPDDL_LANGUAGE_H
#define EPDDL_LANGUAGE_H

#include "language_types.h"
#include <memory>

namespace del {
    class language;
    using language_ptr = std::shared_ptr<language>;

    class language {
    public:
        language(name_vector atoms_names, name_vector agents_names);

        language(const language&) = delete;
        language& operator=(const language&) = delete;

        language(language&&) = default;
        language& operator=(language&&) = default;

        ~language() = default;

        [[nodiscard]] atom  get_atoms_number()  const;
        [[nodiscard]] agent get_agents_number() const;

        [[nodiscard]] atom  get_atom_id(const std::string& atom_name)   const;
        [[nodiscard]] agent get_agent_id(const std::string &agent_name) const;

        [[nodiscard]] const std::string &get_atom_name(atom atom)    const;
        [[nodiscard]] const std::string &get_agent_name(agent agent) const;

    private:
        name_vector m_atoms_names, m_agents_names;
        atom_id_map m_atoms_map;
        agent_id_map m_agents_map;
        unsigned long long m_atoms, m_agents;
    };
}

#endif //EPDDL_LANGUAGE_H
