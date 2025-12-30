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

#ifndef EPDDL_ERROR_MANAGER_H
#define EPDDL_ERROR_MANAGER_H

#include <cstdint>
#include <memory>
#define INDENT ". . "

#include "epddl_exception.h"
#include "../lexer/tokens/token.h"
#include <_types/_uint8_t.h>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>

namespace epddl {
    class error_manager;
    using error_manager_ptr   = std::shared_ptr<error_manager>;
    using error_manager_map   = std::unordered_map<std::string, error_manager_ptr>;

    struct spec_error_managers {
        error_manager_ptr problem_err_manager;
        error_manager_ptr domain_err_manager;
        error_manager_map libraries_err_managers;
    };

    enum error_type : std::uint8_t {
        library_declaration,
        // Syntax errors
        invalid_token,
        token_mismatch,
        unexpected_token,
        missing_lpar,
        missing_rpar,
        empty_list,
        bad_obs_cond,
        out_of_range_int,
        expected_eof,
        unexpected_eof,
        // Type checking errors
        element_redeclaration,
        action_type_redeclaration,
        reserved_element_redeclaration,
        undeclared_element,
        bad_type_specialization,
        incompatible_types,
        incompatible_term_type,
        arguments_number_mismatch,
        predicate_is_not_fact,
        init_redeclaration,
        facts_init_redeclaration,
        missing_init,
        missing_goal,
        missing_obs_cond,
        default_obs_cond_redeclaration,
        missing_else_or_default_obs_cond,
        events_conditions_unsatisfied,
        empty_agent_set,
        inadmissible_formula_in_theory,
        // Grounding errors
        inconsistent_theory_worlds,
        inconsistent_theory_designated,
        agent_obs_cond_redeclaration,
        missing_agent_obs_cond,
        missing_agent_obs_cond_no_default
    };

    enum decl_type : std::uint8_t {
        // Main declarations
        domain,
        domain_decl,
        anon_domain_decl,
        problem_decl,
        anon_problem_decl,
        library,
        library_decl,
        anon_library_decl,
        // Common declarations
        requirements_decl,
        requirement,
        type_name,
        predicate_name,
        entity_name,
        object_name,
        agent_name,
        agent_list_decl,
        agent_group_name,
        modality_name,
        composite_type,
        variable,
        term,
        agent_term,
        agent_term_or_kw,
        modality_index_term,
        predicate,
        literal,
        literal_list,
        formula,
        quantified_params,
        modality_index,
        modality_group,
        relation,
        // Domain declarations
        domain_name,
        event_name,
        action_name,
        domain_name_decl,
        domain_item_decl,
        action_type_libraries_decl,
        types_decl,
        predicates_decl,
        predicate_decl,
        anon_predicate_decl,
        constants_decl,
        event,
        event_decl,
        event_params_decl,
        event_pre_decl,
        event_effects_decl,
        effects_decl,
        action,
        action_decl,
        action_params_decl,
        action_signature_decl,
        event_signature_decl,
        action_obs_cond_decl,
        obs_cond_decl,
        obs_condition,
        // Problem declarations
        problem_name,
        world_name,
        problem_name_decl,
        problem_item_decl,
        objects_decl,
        agents_decl,
        agent_group_decl,
        anon_agent_group_decl,
        facts_init,
        init_decl,
        explicit_init_worlds_decl,
        explicit_init_relations_decl,
        explicit_init_labels_decl,
        explicit_init_label_decl,
        explicit_init_designated_decl,
        finitary_S5_theory_decl,
        goal_decl,
        // Library declarations
        library_name,
        action_type_name,
        event_variable_decl,
        obs_type_name,
        library_name_decl,
        library_item_decl,
        action_type,
        action_type_decl,
        action_type_events_decl,
        action_type_obs_types_decl,
        action_type_relations_decl,
        action_type_designated_decl,
        action_type_event_conditions_decl,
        // Grounding
        ground_action
    };

    enum requirement_warning : std::uint8_t {
        equality,
        inequality,
        negative_formulas,
        disjunctive_formulas,
        implication_formulas,
        modal_formulas,
        universal_formulas,
        existential_formulas,
        lists,
        list_comprehensions,
        group_modalities,
        composite_types,
        obs_conditions,
        action_types_decl,
        action_types_incl,
        facts_decl,
        types_declaration,
        effects,
        conditional_effects_when,
        conditional_effects_iff,
        multiple_designated_worlds,
        multiple_designated_events,
        event_conditions,
        agent_groups,
        facts_initialization,
        finitary_S5_theory,
        knowing_whether,
        common_knowledge,
        static_common_knowledge
    };

    class error_manager {
    public:
        explicit error_manager(std::string path) :
                m_path{std::move(path)} {}

        static std::string get_error_info(const decl_type decl_type, const std::string &name = "") {
            switch (decl_type) {
                case domain:
                    return "domain";
                case domain_decl:
                    return "declaration of domain " + error_manager::quote(name);
                case anon_domain_decl:
                    return "domain declaration";
                case problem_decl:
                    return "declaration of problem " + error_manager::quote(name);
                case anon_problem_decl:
                    return "problem declaration";
                case library:
                    return "library";
                case library_decl:
                    return "declaration of action type library " + error_manager::quote(name);
                case anon_library_decl:
                    return "action type library declaration";
                case requirements_decl:
                    return "requirements declaration";
                case requirement:
                    return "requirement";
                case type_name:
                    return "type name";
                case predicate_name:
                    return "predicate name";
                case entity_name:
                    return "entity name";
                case object_name:
                    return "object name";
                case agent_name:
                    return "agent name";
                case agent_list_decl:
                    return "agent list";
                case agent_group_name:
                    return "agent group name";
                case modality_name:
                    return "modality name";
                case composite_type:
                    return "composite type";
                case variable:
                    return "variable";
                case term:
                    return "term";
                case agent_term:
                    return "agent term";
                case agent_term_or_kw:
                    return "agent term or " + error_manager::quote("Kw.");
                case modality_index_term:
                    return "modality index term";
                case predicate:
                    return "predicate";
                case literal:
                    return "literal";
                case literal_list:
                    return "literal list";
                case formula:
                    return "formula";
                case quantified_params:
                    return "quantified parameters";
                case modality_index:
                    return "modality index";
                case modality_group:
                    return "modality agent group";
                case relation:
                    return "relation";
                case domain_name:
                    return "domain name";
                case event_name:
                    return "event name";
                case action_name:
                    return "action name";
                case domain_name_decl:
                    return "domain name declaration";
                case domain_item_decl:
                    return "domain item declaration";
                case action_type_libraries_decl:
                    return "action type libraries declaration";
                case types_decl:
                    return "types declaration";
                case predicates_decl:
                    return "predicates declaration";
                case predicate_decl:
                    return "declaration of predicate " + error_manager::quote(name);
                case anon_predicate_decl:
                    return "predicate declaration";
                case constants_decl:
                    return "constants declaration";
                case event:
                    return "event";
                case event_decl:
                    return "declaration of event " + error_manager::quote(name);
                case event_params_decl:
                    return "parameters of event " + error_manager::quote(name);
                case event_pre_decl:
                    return "precondition of event " + error_manager::quote(name);
                case event_effects_decl:
                    return "effects of event " + error_manager::quote(name);
                case effects_decl:
                    return "effects declaration";
                case action:
                    return "action";
                case action_decl:
                    return "declaration of action " + error_manager::quote(name);
                case action_params_decl:
                    return "parameters of action " + error_manager::quote(name);
                case action_signature_decl:
                    return "signature of action " + error_manager::quote(name);
                case event_signature_decl:
                    return "event signature";
                case action_obs_cond_decl:
                    return "observability conditions of action " + error_manager::quote(name);
                case obs_cond_decl:
                    return "observability conditions declaration";
                case obs_condition:
                    return "observability condition";
                case problem_name:
                    return "problem name";
                case world_name:
                    return "world name";
                case problem_name_decl:
                    return "problem name declaration";
                case problem_item_decl:
                    return "problem item declaration";
                case objects_decl:
                    return "objects declaration";
                case agents_decl:
                    return "agents declaration";
                case agent_group_decl:
                    return "declaration of agent group " + error_manager::quote(name);
                case anon_agent_group_decl:
                    return "agent group declaration";
                case facts_init:
                    return "facts initialization";
                case init_decl:
                    return "declaration of initial state";
                case explicit_init_worlds_decl:
                    return "declaration of initial state worlds";
                case explicit_init_relations_decl:
                    return "declaration of initial state relations";
                case explicit_init_labels_decl:
                    return "declaration of initial state labels";
                case explicit_init_label_decl:
                    return "declaration of initial state label of world " + error_manager::quote(name);
                case explicit_init_designated_decl:
                    return "declaration of initial state designated worlds";
                case finitary_S5_theory_decl:
                    return "declaration of finitary-S5 theory";
                case goal_decl:
                    return "goal declaration";
                case library_name:
                    return "library name";
                case action_type:
                    return "action type";
                case action_type_name:
                    return "action type name";
                case library_name_decl:
                    return "action type library name declaration";
                case library_item_decl:
                    return "action type library item declaration";
                case event_variable_decl:
                    return "event_var able";
                case obs_type_name:
                    return "obs_type name";
                case action_type_decl:
                    return "declaration of action type " + error_manager::quote(name);
                case action_type_events_decl:
                    return "event variables of action type " + error_manager::quote(name);
                case action_type_obs_types_decl:
                    return "observability types of action type " + error_manager::quote(name);
                case action_type_relations_decl:
                    return "abstract relations of action type " + error_manager::quote(name);
                case action_type_designated_decl:
                    return "designated event variables of action type " + error_manager::quote(name);
                case action_type_event_conditions_decl:
                    return "event conditions of action type " + error_manager::quote(name);
                case ground_action:
                    return "generation of ground action " + error_manager::quote(name);
            }
        }

        static std::string get_requirement_warning(const requirement_warning req_warning,
                                                   const std::string &what = "") {
            switch (req_warning) {
                case equality:
                    return "Use of equality operator requires " +
                           error_manager::quote(":equality") + ".";
                case inequality:
                    return "Use of inequality operator requires " +
                           error_manager::quote(":equality") + ".";
                case negative_formulas:
                    return "Use of negation requires " +
                           error_manager::quote(":negative-" + what) + ".";
                case disjunctive_formulas:
                    return "Use of disjunction requires " +
                           error_manager::quote(":disjunctive-" + what) + ".";
                case implication_formulas:
                    return "Use of implication requires " +
                           error_manager::quote(":negative-" + what) + ".";
                case modal_formulas:
                    return "Use of modalities requires " +
                           error_manager::quote(":modal-" + what) + ".";
                case universal_formulas:
                    return "Use of universal quantification requires " +
                           error_manager::quote(":universal-" + what) + ".";
                case existential_formulas:
                    return "Use of existential quantification requires " +
                           error_manager::quote(":existential-" + what) + ".";
                case lists:
                    return "List declarations require " +
                           error_manager::quote(":lists") + ".";
                case list_comprehensions:
                    return "Use of list comprehensions require" +
                           error_manager::quote(":list-comprehensions") + ".";
                case group_modalities:
                    return "Use of group modalities requires " +
                           error_manager::quote(":group-modalities") + ".";
                case composite_types:
                    return "Use of composite types requires " +
                           error_manager::quote(":typing") + ".";
                case obs_conditions:
                    return "Observability conditions require " +
                           error_manager::quote(":partial-observability") + "";
                case action_types_decl:
                    return "Use of user-defined action types requires " +
                           error_manager::quote(":partial-observability") + ".";
                case action_types_incl:
                    return "Inclusion of action type libraries requires " +
                           error_manager::quote(":partial-observability") + ".";
                case facts_decl:
                    return "Fact declaration requires " +
                           error_manager::quote(":facts") + ".";
                case types_declaration:
                    return "Types declarations require " +
                           error_manager::quote(":typing") + ".";
                case effects:
                    return "Definition of effects requires " +
                           error_manager::quote(":ontic-actions") + ".";
                case conditional_effects_when:
                    return "Use of 'iff' in postconditions requires " +
                           error_manager::quote(":conditional-effects") + ".";
                case conditional_effects_iff:
                    return "Use of 'when' in postconditions requires " +
                           error_manager::quote(":conditional-effects") + ".";
                case multiple_designated_worlds:
                    return "Declaration of multiple designated worlds requires " +
                           error_manager::quote(":multi-pointed-models") + ".";
                case multiple_designated_events:
                    return "Declaration of multiple designated events requires " +
                           error_manager::quote(":multi-pointed-models") + ".";
                case event_conditions:
                    return "Declaration of events conditions requires " +
                           error_manager::quote(":events-conditions") + ".";
                case agent_groups:
                    return "Declaration of agent groups requires " +
                           error_manager::quote(":agent-groups") + ".";
                case facts_initialization:
                    return "Facts initialization requires " +
                           error_manager::quote(":facts") + ".";
                case finitary_S5_theory:
                    return "Declaration of finitary-S5 theory requires " +
                           error_manager::quote(":finitary-S5-theories") + ".";
                case knowing_whether:
                    return "Use of " + error_manager::quote("Kw.") + "modality requires " +
                           error_manager::quote(":knowing-whether") + ".";
                case common_knowledge:
                    return "Use of " + error_manager::quote("C.") + "modality in static formulas requires " +
                           error_manager::quote(":static-common-knowledge") + ".";
                case static_common_knowledge:
                    return "Use of " + error_manager::quote("C.") + "modality requires " +
                           error_manager::quote(":common-knowledge") + ".";
            }
        }

        void push_error_info(const std::string &err_info) {
            m_infos.emplace_back("In " + err_info + ":");
        }

        void pop_error_info() {
            m_infos.pop_back();
        }

        void throw_error(const error_type err_type, const token_ptr &token,
                         const std::vector<std::string> &msg = {}) const {
            auto context = build_error_context();
            throw EPDDLException{m_path, token->get_row(), token->get_col(),
                                 context + error_manager::get_error_message(err_type, token, msg)};
        }

        void throw_error(const error_type err_type, const ast::info &info,
                         const std::vector<std::string> &msg = {}) const {
            auto context = build_error_context();
            throw EPDDLException{m_path, info.m_row, info.m_col,
                                 context + error_manager::get_error_message(err_type, nullptr, msg)};
        }

        void throw_error(const error_type err_type, const std::vector<std::string> &msg = {}) const {
            auto context = build_error_context();
            throw EPDDLException{m_path,
                                 context + error_manager::get_error_message(err_type, nullptr, msg)};
        }

        static void throw_error(const std::string &path, const error_type err_type,
                                const std::vector<std::string> &msg = {}) {
            throw EPDDLException{path,
                                 INDENT + error_manager::get_error_message(err_type, nullptr, msg)};
        }

    private:
        const std::string m_path;

        std::list<std::string> m_infos;

        [[nodiscard]] std::string build_error_context() const {
            std::string context;
            unsigned long indent = 1;

            for (const std::string &info : m_infos) {
                for (unsigned long i = 0; i < indent; ++i)
                    context += INDENT;

                context += info + "\n";
                ++indent;
            }

            for (unsigned long i = 0; i < indent; ++i)
                context += INDENT;

            return context;
        }

        static std::string get_error_message(const error_type err_type, const token_ptr &token,
                                             const std::vector<std::string> &msg) {
            switch (err_type) {
                case library_declaration:
                    return "Redeclaration of action type library " + error_manager::quote(msg[0]) + ".";
                case invalid_token:
                    return error_manager::get_invalid_token_error(msg[0], token->get_lexeme());
                case token_mismatch:
                    return error_manager::get_token_mismatch_error(msg[0], token->get_lexeme());
                case unexpected_token:
                    return error_manager::get_unexpected_token_error(msg[0]);
                case missing_lpar:
                    return error_manager::get_missing_lpar_error(msg[0]);
                case missing_rpar:
                    return error_manager::get_missing_rpar_error(msg[0]);
                case empty_list:
                    return error_manager::get_empty_list_error(msg[0], token->get_lexeme());
                case bad_obs_cond:
                    return error_manager::get_bad_obs_condition_error(msg[0]);
                case out_of_range_int:
                    return error_manager::get_out_of_range_int_error(token->get_lexeme());
                case expected_eof:
                    return error_manager::get_expected_eof_error(msg[0]);
                case unexpected_eof:
                    return error_manager::get_unexpected_eof_error(msg[0]);
                case element_redeclaration:
                    return error_manager::get_redeclaration_error(msg[0], token->get_lexeme(),
                                                                  msg[1], msg[2]);
                case action_type_redeclaration:
                    return error_manager::get_action_type_redeclaration_error(token->get_lexeme(),
                                                                              msg[0], msg[1], msg[2]);
                case reserved_element_redeclaration:
                    return error_manager::get_redeclaration_reserved_error(msg[0], token->get_lexeme());
                case undeclared_element:
                    return error_manager::get_undeclared_element_error(msg[0], token->get_lexeme());
                case bad_type_specialization:
                    return error_manager::get_bad_type_specialization_error(token->get_lexeme());
                case incompatible_types:
                    return error_manager::get_incompatible_types_error(msg[0], msg[1]);
                case incompatible_term_type:
                    return error_manager::get_incompatible_term_type_error(msg[0], token->get_lexeme(),
                                                                           msg[1]);
                case arguments_number_mismatch:
                    return error_manager::get_arguments_number_mismatch_error(msg[0], msg[1],
                                                                              token->get_lexeme(),
                                                                              msg[2], msg[3]);
                case predicate_is_not_fact:
                    return error_manager::get_predicate_is_not_fact_error(token->get_lexeme());
                case init_redeclaration:
                    return "Redeclaration of initial state.";
                case facts_init_redeclaration:
                    return "Redeclaration of facts initialization.";
                case missing_init:
                    return "Missing initial state declaration.";
                case missing_goal:
                    return "Missing goal declaration.";
                case missing_obs_cond:
                    return "Missing observability conditions for action " +
                           error_manager::quote(token->get_lexeme()) + ".";
                case default_obs_cond_redeclaration:
                    return "Redeclaration of default observability condition.";
                case missing_else_or_default_obs_cond:
                    return "Ill-formed if-then-else observability condition: missing else statement or default condition.";
                case events_conditions_unsatisfied:
                    return "Could not bind event " + error_manager::quote(token->get_lexeme()) +
                           " to event variable " + error_manager::quote(msg[0]) +
                           " (action type " + error_manager::quote(msg[1]) + "): " + msg[2];
                case empty_agent_set:
                    return "Specification must declare at least one agent.";
                case inadmissible_formula_in_theory:
                    return msg[0] + " cannot be used in finitary-S5 formulas.";
                case inconsistent_theory_worlds:
                    return "Grounding error: inconsistent finitary-S5 theory: induced epistemic state contains no possible worlds.";
                case inconsistent_theory_designated:
                    return "Grounding error: inconsistent finitary-S5 theory: induced epistemic state contains no designated worlds.";
                case agent_obs_cond_redeclaration:
                    return "Grounding error: redeclaration of observability condition for agent " +
                           error_manager::quote(msg[0]) + " and observability type " +
                           error_manager::quote(msg[1]) + ".";
                case missing_agent_obs_cond:
                    return "Grounding error: missing observability conditions for agent " +
                           error_manager::quote(msg[0]) + ".";
                case missing_agent_obs_cond_no_default:
                    return "Grounding error: missing observability conditions for agent " +
                           error_manager::quote(msg[0]) + ", maybe you forgot the default condition?";
            }
        }

        static std::string get_invalid_token_error(const std::string &expected, const std::string &what) {
            return "Syntax error: invalid " + expected + " " + error_manager::quote(what) + ".";
        }

        static std::string get_token_mismatch_error(const std::string &expected, const std::string &found) {
            return "Syntax error: expected " + expected + " (found " + error_manager::quote(found) + ").";
        }

        static std::string get_unexpected_token_error(const std::string &unexpected) {
            return "Syntax error: unexpected " + unexpected + ".";
        }

        static std::string get_missing_lpar_error(const std::string &where) {
            return "Syntax error: expected '(' at beginning of " + where + ".";
        }

        static std::string get_missing_rpar_error(const std::string &where) {
            return "Syntax error: expected ')' at end of " + where + ".";
        }

        static std::string get_empty_list_error(const std::string &what, const std::string &found) {
            return "Syntax error: expected non-empty list of " + what + " (found " + error_manager::quote(found) + ").";
        }

        static std::string get_bad_obs_condition_error(const std::string &msg) {
            return "Syntax error: ill formed observability condition: " + msg + ".";
        }

        static std::string get_out_of_range_int_error(const std::string &msg) {
            return "Syntax error: integer " + error_manager::quote(msg) + " is out of range.";
        }

        static std::string get_expected_eof_error(const std::string &where) {
            return "Syntax error: expected end of file after " + where + ".";
        }

        static std::string get_unexpected_eof_error(const std::string &where) {
            return "Syntax error: unexpected end of file in " + where + ".";
        }

        static std::string get_redeclaration_error(const std::string &what, const std::string &name,
                                                   const std::string &row, const std::string &col) {
            return "Redeclaration of " + what + " " + error_manager::quote(name) +
                   ". Previous declaration at (" + row + ":" + col + ").";
        }

        static std::string get_action_type_redeclaration_error(const std::string &name, const std::string &lib_name,
                                                               const std::string &row, const std::string &col) {
            return "Redeclaration of action type " + error_manager::quote(name) +
                   ". Previous declaration in action type library " +
                   error_manager::quote(lib_name) + " at (" + row + ":" + col + ").";
        }

        static std::string get_redeclaration_reserved_error(const std::string &what, const std::string &name) {
            return "Redeclaration of " + what + " " + error_manager::quote(name) + ".";
        }

        static std::string get_undeclared_element_error(const std::string &what, const std::string &name) {
            return "Use of undeclared " + what + " " + error_manager::quote(name) + ".";
        }

        static std::string get_bad_type_specialization_error(const std::string &name) {
            return "Specialization of non-specializable type " + error_manager::quote(name) + ".";
        }

        static std::string get_incompatible_types_error(const std::string &given_type, const std::string &decl_type) {
            return "Type error: given type " + error_manager::quote(given_type) +
                   " is not compatible with required type " + error_manager::quote(decl_type) + ".";
        }

        static std::string get_incompatible_term_type_error(const std::string &term_type, const std::string &term_name,
                                                            const std::string &decl_type) {
            return "Type error: type " + error_manager::quote(term_type) +
                   " of term " + error_manager::quote(term_name) +
                   " is not compatible with required type " + error_manager::quote(decl_type) + ".";
        }

        static std::string get_arguments_number_mismatch_error(const std::string &many_few, const std::string &what,
                                                               const std::string &name, const std::string &expected,
                                                               const std::string &found) {
            return "Type error: too " + many_few + " arguments for " + what + " " + error_manager::quote(name) +
                   " (expected " + expected + ", found " + found + ").";
        }

        static std::string get_predicate_is_not_fact_error(const std::string &name) {
            return "Predicate " + error_manager::quote(name) + " is not a fact.";
        }


        static std::string quote(const std::string &str) {
            return "'" + str + "'";
        }
    };
}

#endif //EPDDL_ERROR_MANAGER_H
