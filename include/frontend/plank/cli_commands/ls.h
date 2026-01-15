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

#ifndef PLANK_LS_H
#define PLANK_LS_H

#include "../../../../external/interactive-cli/cli.h"
#include "../../../../external/clipp.h"
#include "../cli_types.h"
#include "../cli_data/cli_data.h"

namespace plank::commands {
    class ls {
    public:
        static void add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code);

        static std::string get_name();
        static std::string get_help();
        static std::string get_cmd_syntax();

        static clipp::group get_cli(std::string &path);
        static cmd_function<string_vector> run_cmd(cli_data &data, plank::exit_code &exit_code);

    private:
        static std::string format_entry(const fs::directory_entry &entry);

        static string_vector get_directory_entries(const fs::path &path, bool show_hidden);
    };
}

#endif //PLANK_LS_H
