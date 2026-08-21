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

#include "epddl/grounder/grounder_helper.h"
#include "epddl/grounder/grounder_info.h"
#include "epddl/grounder/language_grounder.h"
#include "epddl/grounder/actions/actions_grounder.h"
#include "epddl/grounder/formulas/formulas_and_lists_grounder.h"
#include "epddl/grounder/initial_state/facts_init_grounder.h"
#include "epddl/grounder/initial_state/initial_state_grounder.h"
#include "epddl/type-checker/type_checker.h"
#include "epddl/utils/spec_paths_loader.h"

using namespace plank;
using namespace plank::epddl;
using namespace plank::epddl::grounder;

del::planning_task
grounder_helper::build_ground_task(const parser::specification_paths &spec_paths, bool silent) {
    return grounder_helper::ground(spec_paths, silent).first;
}

std::pair<del::planning_task, grounder_info>
grounder_helper::ground(const parser::specification_paths &spec_paths, const bool silent) {
    // Parsing...
    if (not silent) std::cout << "Parsing..." << std::flush;

    auto [spec, err_managers] =
            parser::file_parser::parse_planning_specification(spec_paths);

    if (not silent) std::cout << "done." << std::endl;

    // Type-checking...
    if (not silent) std::cout << "Type-checking..." << std::flush;

    type_checker::context context =
            type_checker::do_semantic_check(spec, err_managers);

    if (not silent) std::cout << "done." << std::endl;

    // Grounding...
    if (not silent) std::cout << "Grounding..." << std::flush;

    auto [task, info] = epddl::grounder::grounder_helper::ground(
            spec, context, err_managers);

    if (not silent) std::cout << "done." << std::endl;

    return {std::move(task), std::move(info)};
}

std::pair<del::planning_task, grounder_info>
grounder_helper::ground(const planning_specification &spec, context &context, spec_error_managers err_managers) {
    grounder_info info = grounder_helper::build_info(spec, context, std::move(err_managers));

    auto initial_state = initial_state_grounder::build_initial_state(spec, info);
    auto [actions_names, actions_map, actions] = actions_grounder::build_actions(spec, info);
    auto goal = formulas_and_lists_grounder::build_goal(spec, info);
    auto task = del::planning_task{std::move(initial_state), std::move(actions_names),
        std::move(actions_map), std::move(actions), std::move(goal)};

    return {std::move(task), std::move(info)};
}

grounder_info grounder_helper::build_info(const planning_specification &spec, context &context,
                                          spec_error_managers err_managers) {
    del::language_ptr language = language_grounder::build_language(context);
    variables_assignment assignment;
    const del::atom_set empty{language->get_atoms_number()};

    grounder_info info{std::move(context), std::move(assignment),
                       empty, std::move(language), std::move(err_managers)};

    info.facts = facts_init_grounder::build_facts(spec, info);
    info.label_storage = std::make_shared<utils::label_storage>();

    return info;
}

std::pair<parser::specification_paths, bool>
grounder_helper::get_specification_paths(const std::string &domain_path, const std::string &problem_path,
    std::vector<std::string> &libraries_paths, const std::string &spec_paths_json_file) {
    parser::specification_paths spec_paths;
    bool failed = false;

    // Loading from user files
    if (spec_paths_json_file.empty()) {
        // Removing accidental duplicates from library paths
        libraries_paths.erase(
                std::unique(libraries_paths.begin(), libraries_paths.end()),
                libraries_paths.end());

        spec_paths = parser::specification_paths{problem_path, domain_path, libraries_paths};
    } else {
        // Loading from JSON file
        if (not spec_paths_loader::load_specification_paths(spec_paths_json_file, spec_paths))
            failed = true;
    }

    return {std::move(spec_paths), failed};
}