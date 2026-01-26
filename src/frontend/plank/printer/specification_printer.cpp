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

#include "../../../../include/frontend/plank/printer/specification_printer.h"

using namespace printer;

void specification_printer::print_specification_json(const epddl::parser::specification_paths &paths,
                                                     const fs::path &output_path) {
    ordered_json task_json = specification_printer::build_specification_json(paths);

    auto path = fs::path(output_path);
    auto json_path = path.parent_path() / (path.stem().string() + ".json");

    std::ofstream json_of;
    json_of.open(json_path);

    if (json_of.is_open())
        json_of << task_json.dump(4) << std::endl;
    else
        std::cerr << "Unable to write to file '" << json_path << "'." << std::endl;

    json_of.close();
}

ordered_json specification_printer::build_specification_json(const epddl::parser::specification_paths &paths) {
    json libraries = json::array();

    for (const std::string &lib_path : paths.libraries_paths)
        libraries.emplace_back(lib_path);

    ordered_json spec;

    spec["domain"] = paths.domain_path;
    spec["problem"] = paths.problem_path;
    spec["action-type-libraries"] = std::move(libraries);

    return spec;
}
