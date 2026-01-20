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

        plank::exit_code parse(std::ostream &out, bool quiet = false, bool silence_warnings = false) {
            if (not quiet) out << "Parsing..." << std::flush;

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

        plank::exit_code build_info(std::ostream &out, bool ground, bool quiet = false, bool silence_warnings = false) {
            if (auto exit_code = parse(out, quiet, silence_warnings); exit_code != plank::exit_code::all_good)
                return exit_code;

            if (ground or not is_set_info()) {
                out << "Grounding task language..." << std::flush;

                epddl::grounder::grounder_info info = epddl::grounder::grounder_helper::build_info(
                        get_specification(),
                        get_context(),
                        get_error_managers());

                out << "done." << std::endl;
                set_info(std::move(info));
            }

            return plank::exit_code::all_good;
        }

        plank::exit_code ground(std::ostream &out, bool silence_warnings = false) {
            if (auto exit_code = parse(out, false, silence_warnings); exit_code != plank::exit_code::all_good)
                return exit_code;

            if (is_set_specification() and is_set_error_managers() and is_set_context()) {
                out << "Grounding..." << std::flush;

                try {
                    auto [task, info] = epddl::grounder::grounder_helper::ground(
                            get_specification(),
                            get_context(),
                            get_error_managers());

                    set_info(std::move(info));
                    set_task(std::move(task));
                } catch (epddl::EPDDLException &e) {
                    out << std::endl << e.what();
                    return plank::exit_code::grounding_error;
                }

                out << "done." << std::endl;
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
    };
}

#endif //PLANK_CLI_TASK_DATA_H
