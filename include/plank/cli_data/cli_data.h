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

#ifndef PLANK_CLI_DATA_H
#define PLANK_CLI_DATA_H

#include "cli_task_data.h"
#include "../cli_types.h"
#include <filesystem>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;

namespace plank {
    using task_data_map = std::unordered_map<std::string, cli_task_data>;

    class cli_data {
    public:
        cli_data() {
            m_cwd = fs::current_path();
        }

        [[nodiscard]] const fs::path &get_current_working_dir() const {
            return m_cwd;
        }

        [[nodiscard]] bool is_defined_task(const std::string &name) const {
            return m_tasks_data.find(name) != m_tasks_data.end();
        }

        [[nodiscard]] bool is_opened_task() const {
            return not m_current_task.empty();
        }

        [[nodiscard]] const std::string &get_current_task() const {
            return m_current_task;
        }

        [[nodiscard]] cli_task_data &get_task_data(const std::string &name) {
            return m_tasks_data.at(name);
        }

        [[nodiscard]] cli_task_data &get_current_task_data() {
            return m_tasks_data.at(m_current_task);
        }

        [[nodiscard]] const task_data_map &get_tasks_data() const {
            return m_tasks_data;
        }

        [[nodiscard]] const string_vector &get_tasks_names() const {
            return m_tasks_names;
        }

        void set_current_working_dir(const fs::path &cwd) {
            m_cwd = cwd;
        }

        void add_task_data(const std::string &name, cli_task_data data) {
            m_tasks_data.emplace(name, std::move(data));
            m_tasks_names.emplace_back(name);
        }

        void remove_task_data(const std::string &name) {
            m_tasks_data.erase(name);
            m_tasks_names.erase(std::find(m_tasks_names.begin(), m_tasks_names.end(), name));
        }

        void reset_tasks() {
            m_tasks_data.clear();
            m_tasks_names.clear();
            reset_current_task();
        }

        void set_current_task(const std::string &name) {
            m_current_task = name;
        }

        void reset_current_task() {
            m_current_task.clear();
        }

    private:
        fs::path m_cwd;
        std::string m_current_task;
        task_data_map m_tasks_data;
        string_vector m_tasks_names;
    };
}

#endif //PLANK_CLI_DATA_H
