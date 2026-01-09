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

#ifndef PLANK_TASK_H
#define PLANK_TASK_H

#include "../../../ext/interactive-cli/cli.h"
#include "../../../ext/clipp.h"
#include "../cli_types.h"
#include "../cli_data/cli_data.h"

namespace plank::commands {
    class task {
    public:
        static void add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data);

        static std::string get_name();
        static std::string get_help();
        static std::string get_cmd_syntax();

        static clipp::group get_cli(std::string &operation, std::string &task_name, std::string &path,
                                    std::string &new_task_name);
        static cmd_function<string_vector> run_cmd(std::unique_ptr<cli::Menu> &menu, cli_data &data);

    private:
        static void add(std::ostream &out, cli_data &data, const std::string &task_name, cli_task_data from = {});
        static void remove(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data, const std::string &task_name);
        static void rename(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data, const std::string &task_name, const std::string &new_task_name);
        static void copy(std::ostream &out, cli_data &data, const std::string &task_name, const std::string &new_task_name);
        static void open(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data, const std::string &task_name);
        static void close(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data);
        static void save(std::ostream &out, cli_data &data, const std::string &path);
        static void switch_(std::ostream &out, std::unique_ptr<cli::Menu> &menu, cli_data &data, const std::string &task_name);
    };
}

#endif //PLANK_TASK_H
