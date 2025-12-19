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

#ifndef EPDDL_ERROR_MANAGER_H
#define EPDDL_ERROR_MANAGER_H

#include "epddl_exception.h"
#include "../lexer/tokens/token.h"
#include <_types/_uint8_t.h>
#include <string>

namespace epddl {
    enum error_type : std::uint8_t {
        token_mismatch,
        unexpected_token,
        missing_lpar,
        missing_rpar,
        bad_obs_cond,
        expected_eof,
        unexpected_eof
    };
    class error_manager {
    public:
        static std::string get_token_mismatch_error(const std::string &expected, const token_ptr &found) {
            return "Expected " + expected + " (found " + found->to_string() + ").";
        }

        static std::string get_unexpected_token_error(const std::string &unexpected) {
            return "Unexpected " + unexpected + ".";
        }

        static std::string get_missing_lpar_error(const std::string &where) {
            return "Expected '(' at beginning of " + where + ".";
        }

        static std::string get_missing_rpar_error(const std::string &where) {
            return "Expected ')' at end of " + where + ".";
        }

        static std::string get_expected_eof_error(const std::string &where) {
            return "Expected end of file after " + where + ".";
        }

        static std::string get_unexpected_eof_error(const std::string &where) {
            return "Unexpected end of file in " + where + ".";
        }

        static std::string get_bad_obs_condition_error(const std::string &msg) {
            return "Ill formed observability condition: " + msg + ".";
        }
    };
}

#endif //EPDDL_ERROR_MANAGER_H
