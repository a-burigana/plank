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

#ifndef PLANK_CLI_STATE_H
#define PLANK_CLI_STATE_H

#include "../../../ext/interactive-cli/cli.h"
#include "../../../ext/clipp.h"
#include "../cli_types.h"
#include "../cli_data/cli_data.h"

namespace plank::commands {
    class state {
    public:
        static void add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data);

        static std::string get_name();
        static std::string get_help();
        static std::string get_cmd_syntax();

        static clipp::group get_cli(std::string &operation, std::string &state_name, std::string &dir_path,
                                    std::string &new_state_name, std::string &formula, std::string &export_file_ext,
                                    string_vector &actions_names, bool &contract, bool &ground, bool &export_all);

        static cmd_function<string_vector> run_cmd(cli_data &data);

    private:
        static void add(std::ostream &out, cli_data &data, const std::string &state_name);
        static void remove(std::ostream &out, cli_data &data, const std::string &state_name);
        static void rename(std::ostream &out, cli_data &data, const std::string &state_name,
                           const std::string &new_state_name);
        static void copy(std::ostream &out, cli_data &data, const std::string &state_name,
                         const std::string &new_state_name);
        static void check(std::ostream &out, cli_data &data, const std::string &state_name,
                          const std::string &formula);
        static void applicable(std::ostream &out, cli_data &data, const std::string &state_name,
                               const string_vector &actions_names, bool ground);
        static void update(std::ostream &out, cli_data &data, const std::string &state_name,
                           const string_vector &actions_names, const std::string &new_state_name,
                           bool contract, bool ground, bool export_all, const std::string &dir_path,
                           const std::string &export_file_ext);
        static void contract(std::ostream &out, cli_data &data, const std::string &state_name,
                             const std::string &new_state_name, const std::string &dir_path,
                             const std::string &export_file_ext);

//        static void to_pdf(std::ostream &out, cli_data &data, const std::string &state_name,
//                           const std::string &dir_path);

        static del::action_deque check_state_actions(std::ostream &out, cli_data &data, const std::string &state_name,
                                                     const string_vector &actions_names);

        static std::string to_string_product(const std::string &state_name, const string_vector &actions_names,
                                             bool contract = false);
    };
}

#endif //PLANK_CLI_STATE_H
