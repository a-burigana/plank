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

#ifndef PLANK_CLI_TASK_DATA_H
#define PLANK_CLI_TASK_DATA_H

#include "../cli_utils.h"
#include "../../../../lib/epddl/error-manager/error_manager.h"
#include "../../../../lib/epddl/ast/planning_specification.h"
#include "../../../../lib/epddl/parser/file_parser.h"
#include "../../../../lib/epddl/type-checker/type_checker.h"
#include "../../../../lib/epddl/grounder/grounder_helper.h"
#include "../../../../lib/del/semantics/planning_task.h"
#include "../../../../lib/del/semantics/states/state.h"
#include "../../../../lib/del/language/formulas.h"
#include "../cli_types.h"
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace plank {
    using state_map     = std::unordered_map<std::string, std::pair<del::state_ptr, std::string>>;
    using formula_map   = std::unordered_map<std::string, del::formula_ptr>;

    class cli_task_data {
    public:
        cli_task_data() = default;

        explicit cli_task_data(epddl::parser::specification_paths spec_paths) :
                m_spec_paths{std::move(spec_paths)} {}

        [[nodiscard]] bool is_loaded_problem() const {
            return not m_spec_paths.problem_path.empty();
        }

        [[nodiscard]] bool is_loaded_domain() const {
            return not m_spec_paths.domain_path.empty();
        }

        [[nodiscard]] bool is_set_specification() const {
            return m_spec.has_value();
        }

        [[nodiscard]] bool is_set_error_managers() const {
            return m_err_managers.has_value();
        }

        [[nodiscard]] bool is_set_context() const {
            return m_context.has_value();
        }

        [[nodiscard]] bool is_set_info() const {
            return m_info.has_value();
        }

        [[nodiscard]] bool is_set_task() const {
            return m_task.has_value();
        }

        [[nodiscard]] bool is_defined_state(const std::string &name) const {
            return m_states.find(name) != m_states.end();
        }

        [[nodiscard]] bool is_defined_formula(const std::string &name) const {
            return m_formulas.find(name) != m_formulas.end();
        }

        [[nodiscard]] const std::string &get_problem_path() const {
            return m_spec_paths.problem_path;
        }

        [[nodiscard]] const std::string &get_domain_path() const {
            return m_spec_paths.domain_path;
        }

        [[nodiscard]] auto get_libraries_paths() const {
            return m_spec_paths.libraries_paths;
        }

        [[nodiscard]] auto get_spec_paths() const {
            return m_spec_paths;
        }

        [[nodiscard]] auto get_absolute_spec_paths(const fs::path &cwd) const {
            auto absolute_spec_paths = m_spec_paths;

            absolute_spec_paths.problem_path =
                    cli_utils::get_absolute_path(cwd, absolute_spec_paths.problem_path).string();

            absolute_spec_paths.domain_path =
                    cli_utils::get_absolute_path(cwd, absolute_spec_paths.domain_path).string();

            for (std::string &library_path : absolute_spec_paths.libraries_paths)
                library_path =
                        cli_utils::get_absolute_path(cwd, library_path).string();
            return m_spec_paths;
        }

        [[nodiscard]] const epddl::ast::planning_specification &get_specification() const {
            return *m_spec;
        }

        [[nodiscard]] const epddl::spec_error_managers &get_error_managers() const {
            return *m_err_managers;
        }

        [[nodiscard]] epddl::type_checker::context &get_context() {
            return *m_context;
        }

        [[nodiscard]] epddl::grounder::grounder_info &get_info() {
            return *m_info;
        }

        [[nodiscard]] del::planning_task &get_task() {
            return *m_task;
        }

        [[nodiscard]] const state_map &get_states() const {
            return m_states;
        }

        [[nodiscard]] const del::state_ptr &get_state(const std::string &name) const {
            return m_states.at(name).first;
        }

        [[nodiscard]] const std::string &get_state_description(const std::string &name) const {
            return m_states.at(name).second;
        }

        [[nodiscard]] const del::formula_ptr &get_formula(const std::string &name) const {
            return m_formulas.at(name);
        }

        [[nodiscard]] const string_vector &get_states_names() const {
            return m_states_names;
        }

        [[nodiscard]] const string_vector &get_formulas_names() const {
            return m_formulas_names;
        }

        void set_problem_path(const std::string &problem_path) {
            m_spec_paths.problem_path = problem_path;
        }

        void set_domain_path(const std::string &domain_path) {
            m_spec_paths.domain_path = domain_path;
        }

        void add_library_path(const std::string &library_path) {
            m_spec_paths.libraries_paths.emplace_back(library_path);
        }

        void set_spec_paths(epddl::parser::specification_paths spec_paths) {
            m_spec_paths = std::move(spec_paths);
        }

        void reset_problem_path() {
            m_spec_paths.problem_path.clear();
        }

        void reset_domain_path() {
            m_spec_paths.domain_path.clear();
        }

        void reset_libraries_paths() {
            m_spec_paths.libraries_paths.clear();
        }

        void reset_spec_paths() {
            reset_problem_path();
            reset_domain_path();
            reset_libraries_paths();
        }

        void set_specification(epddl::ast::planning_specification spec) {
            m_spec.emplace(std::move(spec));
        }

        void set_error_managers(epddl::spec_error_managers err_managers) {
            m_err_managers.emplace(std::move(err_managers));
        }

        void set_context(epddl::type_checker::context context) {
            m_context.emplace(std::move(context));
        }

        void set_info(epddl::grounder::grounder_info info) {
            m_info.emplace(std::move(info));
        }

        void set_task(del::planning_task task) {
            m_task.emplace(std::move(task));
        }

        void add_state(const std::string &name, const del::state_ptr &state, const std::string &desc) {
            m_states[name] = {state, desc};
            m_states_names.emplace_back(name);
        }

        void add_formula(const std::string &name, const del::formula_ptr &f) {
            m_formulas[name] = f;
            m_formulas_names.emplace_back(name);
        }

        void remove_state(const std::string &name) {
            m_states.erase(name);
            m_states_names.erase(std::find(m_states_names.begin(), m_states_names.end(), name));
        }

        void remove_formula(const std::string &name) {
            m_formulas.erase(name);
            m_formulas_names.erase(std::find(m_formulas_names.begin(), m_formulas_names.end(), name));
        }

        void reset_states() {
            m_states.clear();
            m_states_names.clear();
        }

        void reset_formulas() {
            m_formulas.clear();
            m_formulas_names.clear();
        }

        plank::exit_code check_spec_paths(std::ostream &out, const std::string &cmd) {
            if (not fs::exists(m_spec_paths.problem_path)) {
                out << cmd << ": no such file "
                    << cli_utils::quote(m_spec_paths.problem_path) << "." << std::endl;
                return plank::exit_code::file_not_found_error;
            } else if (not fs::exists(m_spec_paths.domain_path)) {
                out << cmd << ": no such file "
                    << cli_utils::quote(m_spec_paths.domain_path) << "." << std::endl;
                return plank::exit_code::file_not_found_error;
            } else
                for (const std::string &library_path : m_spec_paths.libraries_paths)
                    if (not fs::exists(library_path)) {
                        out << cmd << ": no such file "
                            << cli_utils::quote(library_path) << "." << std::endl;
                        return plank::exit_code::file_not_found_error;
                    }

            return plank::exit_code::all_good;
        }

        plank::exit_code parse(std::ostream &out, const std::string &cmd,
                               bool quiet = false, bool silence_warnings = false) {
            if (not quiet) out << "Parsing..." << std::flush;

            if (auto exit_code = check_spec_paths(out, cmd); exit_code != plank::exit_code::all_good)
                return exit_code;

            try {
                auto [spec, err_managers] =
                        epddl::parser::file_parser::parse_planning_specification(get_spec_paths(), silence_warnings);

                epddl::type_checker::context context =
                        epddl::type_checker::do_semantic_check(spec, err_managers);

                set_specification(std::move(spec));
                set_error_managers(std::move(err_managers));
                set_context(std::move(context));
            } catch (epddl::EPDDLException &e) {
                out << std::endl << e.what();
                return plank::exit_code::parser_error;
            }

            if (not quiet) out << "done." << std::endl;

            return plank::exit_code::all_good;
        }

        plank::exit_code build_info(std::ostream &out, const std::string &cmd,
                                    bool quiet = false, bool silence_warnings = false) {
            if (auto exit_code = parse(out, cmd, quiet, silence_warnings); exit_code != plank::exit_code::all_good)
                return exit_code;

            out << "Grounding task language..." << std::flush;

            epddl::grounder::grounder_info info = epddl::grounder::grounder_helper::build_info(
                    get_specification(),
                    get_context(),
                    get_error_managers());

            if (update_grounding_output(out, std::move(info)))
                out << "done." << std::endl;
            else
                out << "canceled by user." << std::endl;

            return plank::exit_code::all_good;
        }

        /*plank::exit_code ground_actions(std::ostream &out, const std::string &cmd, bool silence_warnings = false) {
            if (auto exit_code = parse(out, cmd, false, silence_warnings); exit_code != plank::exit_code::all_good)
                return exit_code;

            if (is_set_specification() and is_set_error_managers() and is_set_context()) {
                out << "Grounding task language..." << std::flush;

                epddl::grounder::grounder_info info = epddl::grounder::grounder_helper::build_info(
                        get_specification(),
                        get_context(),
                        get_error_managers());

                if (update_grounding_output(out, std::move(info))) {
                    out << "done." << std::endl;
                    out << "Grounding actions..." << std::flush;

                    try {
                        auto ground_actions = epddl::grounder::actions_grounder::build_actions(*m_spec, info);


                    } catch (epddl::EPDDLException &e) {
                        out << std::endl << e.what();
                        return plank::exit_code::grounding_error;
                    }

                } else
                    out << "canceled by user." << std::endl;
            }

            return plank::exit_code::all_good;
        }*/

        plank::exit_code ground(std::ostream &out, const std::string &cmd, bool silence_warnings = false) {
            if (auto exit_code = parse(out, cmd, false, silence_warnings); exit_code != plank::exit_code::all_good)
                return exit_code;

            if (is_set_specification() and is_set_error_managers() and is_set_context()) {
                out << "Grounding..." << std::flush;
                bool has_updated;

                try {
                    auto [task, info] = epddl::grounder::grounder_helper::ground(
                            get_specification(),
                            get_context(),
                            get_error_managers());

                    has_updated = update_grounding_output(out, std::move(info), std::move(task));
                } catch (epddl::EPDDLException &e) {
                    out << std::endl << e.what();
                    return plank::exit_code::grounding_error;
                }

                if (has_updated)
                    out << "done." << std::endl;
                else
                    out << "canceled by user." << std::endl;
            }

            return plank::exit_code::all_good;
        }

    private:
        epddl::parser::specification_paths m_spec_paths;
        std::optional<epddl::ast::planning_specification> m_spec;

        std::optional<epddl::spec_error_managers> m_err_managers;

        std::optional<epddl::type_checker::context> m_context;
        std::optional<epddl::grounder::grounder_info> m_info;

        std::optional<del::planning_task> m_task;

        state_map m_states;
        formula_map m_formulas;

        string_vector m_states_names, m_formulas_names;

        bool update_grounding_output(std::ostream &out, epddl::grounder::grounder_info info,
                                     std::optional<del::planning_task> task = std::nullopt) {
            // If m_info is std::nullopt, then I can safely set my infos, otherwise I check
            // whether the languages of the old and new infos are equal. If they are, then
            // I'm safe, otherwise I need to check whether I stored some states or formulas
            // of the old language. If there aren't any, then I'm safe again. Otherwise, we
            // ask whether the user wants to clear the current states and formulas, or cancel
            // the operation and leave the current info and task as they are.
            if (not is_set_info() or *m_info->language == *info.language or
                (m_states.empty() and m_formulas.empty())) {
                set_info(std::move(info));

                if (task.has_value())
                    set_task(std::move(*task));

                return true;
            } else {
                out << std::endl
                    << "The language of the grounded task changed. "
                    << "Currently stored states and/or formulas will be deleted." << std::endl;

                bool good_answer = false;
                std::string answer;

                do {
                    out << "Continue? [y/n]" << std::endl;
                    std::getline(std::cin, answer);

                    if (answer == "y" or answer == "Y" or
                        answer == "n" or answer == "N")
                        break;
                } while (not std::cin.fail());

                // If the user answers yes, we reset states and formulas and update info and task,
                // otherwise we do nothing.
                if (answer == "y" or answer == "Y") {
                    reset_states();
                    reset_formulas();

                    set_info(std::move(info));

                    if (task.has_value())
                        set_task(std::move(*task));

                    return true;
                }

                return false;
            }
        }
    };
}

#endif //PLANK_CLI_TASK_DATA_H
