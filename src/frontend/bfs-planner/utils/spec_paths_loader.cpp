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

#include "../../../../include/frontend/bfs-planner/utils/spec_paths_loader.h"
#include <fstream>
#include <iostream>

using namespace search;

bool spec_paths_loader::load_specification_paths(const fs::path &path,
                                                 epddl::parser::specification_paths &spec_paths) {
    std::ifstream f(path);
    json spec = json::parse(f);
    bool bad_json = not spec.is_object();

    json problem_json, domain_json, libraries_json;

    for (const auto &[key, value] : spec.items()) {
        if (key == "problem")
            problem_json = value;
        else if (key == "domain")
            domain_json = value;
        else if (key == "action-type-libraries")
            libraries_json = value;
        else
            bad_json = true;

        if (bad_json)
            std::cout << "bfs_planner: expected array of EPDDL components paths." << std::endl;
    }

    if (not spec_paths_loader::load_component("problem", problem_json, spec_paths))
        return false;

    if (not spec_paths_loader::load_component("domain", domain_json, spec_paths))
        return false;

    if (not spec_paths_loader::load_libraries(libraries_json, spec_paths))
        return false;

    return true;
}

bool spec_paths_loader::load_path(const std::string &component, const json &component_json,
                                  const std::function<void(const std::string &)> &load_f) {
    if (not component_json.is_string()) {
        std::cout << "bfs_planner: expected " << component << " path." << std::endl;
        return false;
    }

    fs::path component_path = component_json;

    if (not fs::is_regular_file(component_path)) {
        std::cout << "bfs_planner: no such file '"
                  << component_path.string() << "'." << std::endl;
        return false;
    }

    load_f(component_path.string());
    return true;
}

bool spec_paths_loader::load_component(const std::string &component, const json &component_json,
                                       epddl::parser::specification_paths &spec_paths) {
    if (component_json.empty()) {
        std::cout << "bfs_planner: missing " << component << " path." << std::endl;
        return false;
    }

    load_path(
        component, component_json,
        [&](const std::string &path) {
            if (component == "problem")
                spec_paths.problem_path = path;
            else
                spec_paths.domain_path = path;
        });

    return true;
}

bool spec_paths_loader::load_libraries(const json &libraries_json,
                                       epddl::parser::specification_paths &spec_paths) {
    if (libraries_json.empty()) {
        std::cout << "bfs_planner: missing action type libraries paths." << std::endl;
        return false;
    }

    if (not libraries_json.is_array()) {
        std::cout << "bfs_planner: expected array of action type libraries paths." << std::endl;
        return false;
    }

    for (const auto &library_json : libraries_json)
        load_path(
                "action type library", library_json,
                [&](const std::string &path) {
                    spec_paths.libraries_paths.emplace_back(path);
                });

    // Removing accidental duplicates from library paths
    spec_paths.libraries_paths.erase(
            std::unique(spec_paths.libraries_paths.begin(), spec_paths.libraries_paths.end()),
            spec_paths.libraries_paths.end());

    return true;
}
