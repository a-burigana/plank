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

#ifndef EPDDL_VARIABLES_ASSIGNMENT_H
#define EPDDL_VARIABLES_ASSIGNMENT_H

#include "../type-checker/context/context.h"
#include "../del/language/language.h"
#include "combinations_handler.h"
#include <list>

using namespace epddl::type_checker;

namespace epddl::grounder {
    using assignment      = name_id_map;
    using assignment_list = std::list<assignment>;

    class variables_assignment {
    public:
        variables_assignment(const entities_context &entities_context) :
                m_entities_context{entities_context} {}

        explicit variables_assignment(const entities_context &entities_context, const typed_var_list &types,
                                      const combination &combination) :
                                      m_entities_context{entities_context} {
            push(types, combination);
        }

        [[nodiscard]] unsigned long get_assigned_entity_id(const std::string &var_name) const {
            for (const assignment &assignment : m_assignments)
                if (const auto &id = assignment.find(var_name); id != assignment.end())
                    return id->second;
            return 0;
        }

        [[nodiscard]] std::string get_assigned_entity_name(const std::string &var_name) const {
            unsigned long var_id = get_assigned_entity_id(var_name);
            return m_entities_context.get_entity_name(var_id);
        }

        void push(const typed_var_list &typed_vars, const combination &combination) {
            assignment assignment;

            for (auto [typer_var, id] = std::tuple{typed_vars.begin(), combination.begin()};
                 typer_var != typed_vars.end(); ++typer_var, ++id) {
                const auto &[var_name, _] = *typer_var;
                assignment[var_name] = *id;
            }
            m_assignments.emplace_back(std::move(assignment));
        }

        void pop() {
            m_assignments.pop_back();
        }

    private:
        assignment_list m_assignments;
        const entities_context &m_entities_context;
    };
}

#endif //EPDDL_VARIABLES_ASSIGNMENT_H
