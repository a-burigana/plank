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

#ifndef PLANK_PLANNING_TASK_PRINTER_H
#define PLANK_PLANNING_TASK_PRINTER_H

#include "../../../../external/json.hpp"
#include "../../del/semantics/planning_task.h"
#include "../grounder/grounder_info.h"
#include <filesystem>
#include <fstream>

using namespace nlohmann;
namespace fs = std::filesystem;

namespace printer {
    class planning_task_printer {
    public:
        static void print_planning_task_json(const del::planning_task &task, const epddl::grounder::grounder_info &info,
                                             const fs::path &output_path);

        static json build_planning_task_json(const del::planning_task &task, const epddl::grounder::grounder_info &info);

    private:
        static json build_planning_task_info_json(const del::planning_task &task, const epddl::grounder::grounder_info &info);
    };
}

#endif //PLANK_PLANNING_TASK_PRINTER_H
