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

#ifndef EPDDL_EPDDL_EXCEPTION_H
#define EPDDL_EPDDL_EXCEPTION_H

#include <exception>
#include <string>
#include "../ast/ast_node.h"

namespace epddl {
    class EPDDLException : public std::exception {
    public:
        EPDDLException(const std::string &file, const unsigned long row, const unsigned long col,
                       const std::string &error) :
                m_message{std::string{"In file: "} + file + "\n    " + std::to_string(row) + ":" + std::to_string(col) + ": " + error + "\n\n"} {}

        EPDDLException(const ast::info &info, const std::string &error) :
                EPDDLException(info.m_path, info.m_row, info.m_row, error) {}

        char *what() {
            return const_cast<char *>(m_message.data());
        }

    private:
        const std::string m_message;
    };

    class EPDDLLexerException : public EPDDLException {
    public:
        EPDDLLexerException(const std::string &file, const unsigned long row, const unsigned long col,
                            const std::string &error) :
                EPDDLException(file, row, col, error) {}
    };

    class EPDDLParserException : public EPDDLException {
    public:
        EPDDLParserException(const std::string &file, const unsigned long row, const unsigned long col,
                             const std::string &error) :
                EPDDLException(file, row, col, error) {}
    };

    class EPDDLBadChoicePointException : public EPDDLParserException {
    public:
        EPDDLBadChoicePointException(const std::string &file, const unsigned long row, const unsigned long col,
                                     const std::string &error) :
                EPDDLParserException(file, row, col, error) {}
    };
}

#endif //EPDDL_EPDDL_EXCEPTION_H
