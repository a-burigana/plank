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

#ifndef PLANK_LOAD_H
#define PLANK_LOAD_H

#include "../../../external/interactive-cli/cli.h"
#include "../../../external/clipp.h"
#include "../cli_types.h"
#include "../cli_data/cli_data.h"
#include "../../parser/file_parser.h"
#include "../../../external/json.hpp"

using namespace nlohmann;

namespace plank::commands {
    class load {
    public:
        static void add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code);

        static std::string get_name();
        static std::string get_help();
        static std::string get_cmd_syntax();

        static clipp::group get_cli(std::string &file_type, std::string &path);
        static cmd_function<string_vector> run_cmd(cli_data &data, plank::exit_code &exit_code);

        static plank::exit_code load_specification(std::ostream &out, cli_data &data, const fs::path &path);

    private:
        static plank::exit_code load_path(std::ostream &out, const std::string &component, const json &component_json,
                                          const std::function<void(const std::string &)> &load_f);

        static plank::exit_code load_component(std::ostream &out, const std::string &component,
                                               const json &component_json,
                                               epddl::parser::specification_paths &spec_paths);

        static plank::exit_code load_libraries(std::ostream &out, const json &libraries_json,
                                               epddl::parser::specification_paths &spec_paths);
    };
}

#endif //PLANK_LOAD_H
