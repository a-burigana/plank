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

#ifndef PLANK_CLI_DATA_PRINTER_H
#define PLANK_CLI_DATA_PRINTER_H

#include "../../../external/json.hpp"
#include "../plank/cli_data/cli_data.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

using namespace nlohmann;

namespace fs = std::filesystem;

namespace printer {
    class cli_data {
    public:
        static void save_data(const fs::path &path, plank::cli_data &data);

    private:
        static json build_json(plank::cli_data &data);
        static json build_task_json(plank::cli_task_data &task_data, const std::string &name);
        static json build_states_json(plank::cli_task_data &task_data);
        static json build_formulas_json(plank::cli_task_data &task_data);
    };
}

#endif //PLANK_CLI_DATA_PRINTER_H
