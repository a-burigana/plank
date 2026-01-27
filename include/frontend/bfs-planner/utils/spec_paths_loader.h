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

#ifndef PLANK_SPEC_PATHS_LOADER_H
#define PLANK_SPEC_PATHS_LOADER_H

#include "../../../lib/epddl/parser/file_parser.h"
#include "../../../../external/json.hpp"

#include <filesystem>

using namespace nlohmann;

namespace fs = std::filesystem;

namespace search {
    class spec_paths_loader {
    public:
        static bool load_specification_paths(const fs::path &path,
                                             epddl::parser::specification_paths &spec_paths);

    private:
        static bool load_path(const std::string &component, const json &component_json,
                              const std::function<void(const std::string &)> &load_f);
        static bool load_component(const std::string &component, const json &component_json,
                                   epddl::parser::specification_paths &spec_paths);
        static bool load_libraries(const json &libraries_json,
                                   epddl::parser::specification_paths &spec_paths);
    };
}

#endif //PLANK_SPEC_PATHS_LOADER_H
