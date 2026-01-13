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

#ifndef PLANK_SHOW_H
#define PLANK_SHOW_H

#include "../../../ext/interactive-cli/cli.h"
#include "../../../ext/clipp.h"
#include "../cli_types.h"

namespace plank::commands {
    class show {
    public:
        static void add_to_menu(std::unique_ptr<cli::Menu> &menu, cli_data &data, plank::exit_code &exit_code);

        static std::string get_name();
        static std::string get_help();
        static std::string get_cmd_syntax();

        static clipp::group get_cli(std::string &operation, bool &ground, bool &show_types);
        static cmd_function<string_vector> run_cmd(cli_data &data, plank::exit_code &exit_code);

    private:
        static plank::exit_code show_tasks(std::ostream &out, cli_data &data);
        static plank::exit_code show_states(std::ostream &out, cli_data &data);
        static plank::exit_code show_actions(std::ostream &out, cli_data &data, bool ground);
        static plank::exit_code show_formulas(std::ostream &out, cli_data &data, bool ground);
        static plank::exit_code show_types(std::ostream &out, cli_data &data, bool ground, bool show_types);
        static plank::exit_code show_predicates(std::ostream &out, cli_data &data, bool ground);
        static plank::exit_code show_entities(std::ostream &out, cli_data &data, bool ground, bool show_types);
        static plank::exit_code show_objects(std::ostream &out, cli_data &data, bool ground, bool show_types);
        static plank::exit_code show_agents(std::ostream &out, cli_data &data, bool ground, bool show_types);
        static plank::exit_code show_agent_groups(std::ostream &out, cli_data &data, bool ground, bool show_types);

        static plank::exit_code show_entities_with_type(std::ostream &out, cli_data &data, const std::string &type,
                                                        bool ground, bool show_types);
    };
}

#endif //PLANK_SHOW_H
