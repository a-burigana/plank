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

#include <memory>
#define INDENT "    "

#include "epddl_exception.h"
#include "../lexer/tokens/token.h"
#include <_types/_uint8_t.h>
#include <list>
#include <string>
#include <utility>

namespace epddl {
    class error_manager;
    using error_manager_ptr = std::shared_ptr<error_manager>;

    enum error_type : std::uint8_t {
        invalid_token,
        token_mismatch,
        unexpected_token,
        missing_lpar,
        missing_rpar,
        empty_list,
        bad_obs_cond,
        out_of_range_int,
        expected_eof,
        unexpected_eof
    };

    class error_manager {
    public:
        error_manager(std::string path) :
                m_path{std::move(path)} {}

        void push_error_info(const std::string &context) {
            m_infos.emplace_back("In " + context + ":");
        }

        void pop_error_info() {
            m_infos.pop_back();
        }

//        void throw_error(const error_type err_type, const token_ptr &token, const std::string &msg,
//                         const std::string &found) {
//            auto context = build_error_context();
//            throw EPDDLParserException{m_path, token->get_row(), token->get_col(),
//                                       context + error_manager::get_error_message(err_type, msg, found)};
//        }

        void throw_error(const error_type err_type, const token_ptr &token, const std::string &msg = "") {
            auto context = build_error_context();
            throw EPDDLParserException{m_path, token->get_row(), token->get_col(),
                                       context + error_manager::get_error_message(err_type, token, msg)};
//            throw_error(err_type, token, msg, token->to_string());
        }

    private:
        const std::string m_path;
        std::list<std::string> m_infos;

        std::string build_error_context() {
            std::string context;
            unsigned long indent = 1;

            for (const std::string &info : m_infos) {
                for (unsigned long i = 0; i < indent; ++i)
                    context += INDENT;

                context += info + "\n";
                ++indent;
            }

            for (unsigned long i = 0; i < indent; ++i)
                context += INDENT;

            return context;
        }

        template<typename... Args>
        static std::string get_error_message(const error_type err_type, const token_ptr &token, const std::string &msg) {
            switch (err_type) {
                case invalid_token:
                    return error_manager::get_invalid_token_error(msg, token->get_lexeme());
                case token_mismatch:
                    return error_manager::get_token_mismatch_error(msg, token->get_lexeme());
                case unexpected_token:
                    return error_manager::get_unexpected_token_error(msg);
                case missing_lpar:
                    return error_manager::get_missing_lpar_error(msg);
                case missing_rpar:
                    return error_manager::get_missing_rpar_error(msg);
                case empty_list:
                    return error_manager::get_empty_list_error(msg, token->get_lexeme());
                case bad_obs_cond:
                    return error_manager::get_bad_obs_condition_error(msg);
                case out_of_range_int:
                    return error_manager::get_out_of_range_int_error(token->get_lexeme());
                case expected_eof:
                    return error_manager::get_expected_eof_error(msg);
                case unexpected_eof:
                    return error_manager::get_unexpected_eof_error(msg);
            }
        }

        static std::string get_invalid_token_error(const std::string &expected, const std::string &what) {
            return "Invalid " + expected + " " + error_manager::quote(what) + ".";
        }

        static std::string get_token_mismatch_error(const std::string &expected, const std::string &found) {
            return "Expected " + expected + " (found " + error_manager::quote(found) + ").";
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

        static std::string get_empty_list_error(const std::string &what, const std::string &found) {
            return "Expected non-empty list of " + what + " (found " + error_manager::quote(found) + ").";
        }

        static std::string get_bad_obs_condition_error(const std::string &msg) {
            return "Ill formed observability condition: " + msg + ".";
        }

        static std::string get_out_of_range_int_error(const std::string &msg) {
            return "Integer " + error_manager::quote(msg) + " is out of range.";
        }

        static std::string get_expected_eof_error(const std::string &where) {
            return "Expected end of file after " + where + ".";
        }

        static std::string get_unexpected_eof_error(const std::string &where) {
            return "Unexpected end of file in " + where + ".";
        }

        [[nodiscard]] static std::string quote(const std::string str) {
            return "'" + str + "'";
        }
    };
}

#endif //EPDDL_ERROR_MANAGER_H
