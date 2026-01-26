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

#ifndef PLANK_CLI_MANAGER_H
#define PLANK_CLI_MANAGER_H

#include "../../../../external/clipp.h"
#include "../../../../external/interactive-cli/filehistorystorage.h"
#include "cli_types.h"
#include "data/cli_data.h"
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

namespace plank {
    class cli_manager {
    public:
        static int start(int argc, char *argv[]);

    private:
        static int start_interactive_cli();

        static std::unique_ptr<cli::FileHistoryStorage> get_history();
        static std::string get_plank_description();

        static clipp::group get_plank_cli(std::string &operation, std::string &problem_path, std::string &domain_path,
                                          std::string &spec_path, std::string &json_path,
                                          string_vector &libraries_paths, string_vector &action_names);


        static void run_wrong_command_handler(std::ostream &out, const std::string &cmd);
    };
}

#endif //PLANK_CLI_MANAGER_H
