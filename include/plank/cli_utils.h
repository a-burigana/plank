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

#ifndef PLANK_CLI_UTILS_H
#define PLANK_CLI_UTILS_H

#include "cli_types.h"
#include "cli_data/cli_data.h"
#include <_ctype.h>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace plank {
    constexpr size_t TERMINAL_WIDTH = 140;

    class cli_utils {
    public:
        static std::string quote(const std::string &str) {
            return "'" + str + "'";
        }

        static std::vector<std::string> split(const std::string &str) {
            std::vector<std::string> result;
            std::stringstream stream(str);
            std::string item;

            while (std::getline(stream, item, ' '))
                result.push_back(item);

            return result;
        }

        static inline std::string &ltrim(std::string &str) {
            str.erase(str.begin(), std::find_if(str.begin(), str.end(),
                                                [](int c) {
                                                    return not std::isspace(c);
                                                }));
            return str;
        }

        static fs::path get_absolute_path(const fs::path &cwd, const fs::path &path) {
            return path.is_absolute()
                   ? path
                   : (cwd / path).lexically_normal();
        }

        static bool check_directory_path(std::ostream &out, const fs::path &cwd, const std::string &dir_path,
                                         const std::string &cmd) {
            fs::path pdf_path = (cwd / dir_path).lexically_normal();
            bool result = true;

            if (not dir_path.empty()) {
                if (not fs::is_directory(pdf_path)) {
                    out << cmd << ": expected directory path." << std::endl;
                    result = false;
                } else if (not fs::exists(pdf_path))
                    fs::create_directories(pdf_path);
            }
            return result;
        }

        static bool check_name(std::ostream &out, const std::string &arg, const std::string &cmd,
                               bool quiet = false) {
            bool result = cli_utils::is_name_first_char(arg[0]);
            size_t c = 1;

            while (result and c < arg.size() and cli_utils::is_name_char(arg[c])) c++;

            if (result &= c == arg.size(); not result and not quiet)
                out << cmd << ": expected name, found " << cli_utils::quote(arg) << "." << std::endl;

            return result;
        }

        static void print_table(std::ostream &out, const string_vector &items) {
            if (items.empty())
                return;

            size_t column_width = 0;

            for (const std::string &item : items)
                if (cli_utils::get_column_width(item) > column_width)
                    column_width = cli_utils::get_column_width(item);

            const size_t
                columns = column_width > TERMINAL_WIDTH
                        ? 1
                        : TERMINAL_WIDTH / column_width;

            if (columns == 1)
                cli_utils::print_single_column(out, items);
            else
                cli_utils::print_multi_column(out, items, columns, column_width);
        }

        static size_t get_column_width(const std::string &item) {
            return item.size() + 4;         // We leave 4 whitespaces between columns
        }

        static bool is_name_first_char(const char c) {
            return isalpha(c) or c == '_';
        }

        static bool is_name_char(const char c) {
            return isalnum(c) or c == '_' or c == '-';
        }

    private:
        static void print_single_column(std::ostream &out, const string_vector &items) {
            for (const std::string &item : items)
                out << item << std::endl;
        }

        static void print_multi_column(std::ostream &out, const string_vector &items,
                                       const size_t columns, const size_t column_width) {
            size_t rows = (items.size() + columns - 1) / columns;

            for (size_t r = 0; r < rows; ++r) {
                size_t index = 0, printed = 0;

                for (const std::string &item : items) {
                    if (index % rows == r) {
                        if (printed == columns - 1)
                            out << item;
                        else
                            out << std::left
                                << std::setw(static_cast<int>(column_width))
                                << item;

                        if (++printed == columns)
                            break;
                    }
                    ++index;
                }
                out << std::endl;
            }
        }
    };
}

#endif //PLANK_CLI_UTILS_H
