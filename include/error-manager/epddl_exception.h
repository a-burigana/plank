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

#ifndef PLANK_PLANK_EXCEPTION_H
#define PLANK_PLANK_EXCEPTION_H

#include "../ast/ast_node.h"
#include "exit_code.h"
#include <exception>
#include <string>

namespace epddl {
    class EPDDLException : public std::exception {
    public:
        EPDDLException(const std::string &file, const unsigned long row, const unsigned long col,
                       const std::string &error, plank::exit_code exit_code) :
               m_row{row},
               m_col{col},
               m_message{"In file '" + file +
                         "' at (" + std::to_string(row) +
                         ":"  + std::to_string(col) + "):\n" +
                         error + "\n"},
               m_exit_code{exit_code} {}

        EPDDLException(const ast::info &info, const std::string &error, plank::exit_code exit_code) :
                EPDDLException(info.m_path, info.m_row, info.m_col, error, exit_code) {}

        EPDDLException(const std::string &file, const std::string &error, plank::exit_code exit_code) :
                m_row{0},
                m_col{0},
                m_message{"In file '" + file + "':\n" + error + "\n"},
                m_exit_code{exit_code} {}

        EPDDLException(const std::string &error, plank::exit_code exit_code) :
                m_row{0},
                m_col{0},
                m_message{error + "\n"},
                m_exit_code{exit_code} {}

        char *what() {
            return const_cast<char *>(m_message.data());
        }

        [[nodiscard]] unsigned long get_row() const { return m_row; }
        [[nodiscard]] unsigned long get_col() const { return m_col; }

        [[nodiscard]] plank::exit_code get_exit_code() const { return m_exit_code; }

    private:
        const unsigned long m_row, m_col;
        const std::string m_message;
        const plank::exit_code m_exit_code;
    };
}

#endif //PLANK_PLANK_EXCEPTION_H
