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

#ifndef PLANK_REQUIREMENTS_CONTEXT_H
#define PLANK_REQUIREMENTS_CONTEXT_H

#include "context_types.h"

namespace epddl::type_checker {
    class requirements_context {
    public:
        requirements_context() = default;

        [[nodiscard]] const string_set &get_requirements() const { return m_requirements; }
        [[nodiscard]] const std::set<std::string> &get_total_requirements() const { return m_total_requirements; }

        [[nodiscard]] bool is_declared_requirement(const std::string &req) const {
            return m_requirements.find(req) != m_requirements.end();
        }

        void add_requirement(const ast::requirement_ptr &req) {
            m_requirements.emplace(req->get_token()->get_lexeme());
            m_total_requirements.emplace(req->get_token()->get_lexeme());
        }

        void add_requirement(const std::string &req) {
            m_requirements.emplace(req);
            m_total_requirements.emplace(req);
        }

        void clear_requirements() {
            m_requirements.clear();
        }

        void expand_requirements() {
            expand_del();
            expand_formulas();
            expand_postconditions();

            expand_finitary_S5_theories();
            expand_common_knowledge();
            expand_groups();
        }

    private:
        string_set m_requirements;
        std::set<std::string> m_total_requirements;

        void expand_del() {
            if (m_requirements.find(":del") != m_requirements.end()) {
                add_requirement(":typing");
                add_requirement(":equality");
                add_requirement(":partial-observability");
                add_requirement(":ontic-actions");
                add_requirement(":multi-pointed-models");
                add_requirement(":general-formulas");
            }
        }

        void expand_formulas() {
            expand_general_formulas();
            expand_negative_formulas();
            expand_disjunctive_formulas();
            expand_quantified_formulas();
            expand_existential_formulas();
            expand_universal_formulas();
            expand_modal_formulas();
        }

        void expand_general_formulas() {
            if (m_requirements.find(":general-formulas") != m_requirements.end())
                for (const std::string &formula_type : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                    add_requirement(":general-" + formula_type);

            for (const std::string &formula_type : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                if (m_requirements.find(":general-" + formula_type) != m_requirements.end())
                    for (const std::string &str : {":negative-", ":disjunctive-", ":modal-", ":existential-", ":universal-", ":quantified-"})
                        if (formula_type != "list-formulas" or str != "modal")
                            add_requirement(str + formula_type);
        }

        void expand_negative_formulas() {
            if (m_requirements.find(":negative-formulas") != m_requirements.end())
                for (const std::string &str : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                    add_requirement(":negative-" + str);

            for (const std::string &str : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                if (m_requirements.find(":negative-" + str) != m_requirements.end())
                    add_requirement(":disjunctive-" + str);
        }

        void expand_disjunctive_formulas() {
            if (m_requirements.find(":disjunctive-formulas") != m_requirements.end())
                for (const std::string &str : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                    add_requirement(":disjunctive-" + str);
        }

        void expand_quantified_formulas() {
            if (m_requirements.find(":quantified-formulas") != m_requirements.end())
                for (const std::string &str : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                    add_requirement(":quantified-" + str);

            for (const std::string &str : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                if (m_requirements.find(":quantified-" + str) != m_requirements.end()) {
                    add_requirement(":universal-" + str);
                    add_requirement(":existential-" + str);
                }
        }

        void expand_existential_formulas() {
            if (m_requirements.find(":existential-formulas") != m_requirements.end())
                for (const std::string &str : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                    add_requirement(":existential-" + str);
        }

        void expand_universal_formulas() {
            if (m_requirements.find(":universal-formulas") != m_requirements.end())
                for (const std::string &str : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                    add_requirement(":universal-" + str);
        }

        void expand_modal_formulas() {
            if (m_requirements.find(":modal-formulas") != m_requirements.end())
                for (const std::string &str : {"preconditions", "postconditions", "obs-conditions", "goals", "list-formulas"})
                    add_requirement(":modal-" + str);
        }

        void expand_postconditions() {
            for (const std::string &str : {":negative", ":disjunctive", ":modal", ":existential", ":universal", ":quantified", ":general"})
                if (m_requirements.find(str + "-postconditions") != m_requirements.end())
                    add_requirement(":conditional-effects");
        }

        void expand_finitary_S5_theories() {
            if (m_requirements.find(":finitary-S5-theories") != m_requirements.end()) {
                add_requirement(":common-knowledge");
                add_requirement(":knowing-whether");
            }
        }

        void expand_common_knowledge() {
            // Requirement :facts is added only if :static-common-knowledge is explicitly declared,
            // and not if it is entailed by :common-knowledge
            if (m_requirements.find(":static-common-knowledge") != m_requirements.end()) {
                add_requirement(":group-modalities");
                add_requirement(":facts");
            }

            if (m_requirements.find(":common-knowledge") != m_requirements.end()) {
                add_requirement(":group-modalities");
                add_requirement(":static-common-knowledge");
            }
        }

        void expand_groups() {
            if (m_requirements.find(":agent-groups") != m_requirements.end() or
                m_requirements.find(":group-modalities") != m_requirements.end())
                add_requirement(":lists");
        }
    };
}

#endif //PLANK_REQUIREMENTS_CONTEXT_H
