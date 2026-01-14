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
    enum error_type : std::uint8_t {
        // Lexing errors
        invalid_token,
        out_of_range_int,
        // Parsing errors
        token_mismatch,
        unexpected_token,
        missing_lpar,
        missing_rpar,
        empty_list,
        bad_obs_cond,
        expected_eof,
        unexpected_eof,
        // Type checking errors
        library_declaration,
        element_redeclaration,
        action_type_redeclaration,
        reserved_element_redeclaration,
        undeclared_element,
        bad_type_specialization,
        incompatible_types,
        incompatible_term_type,
        arguments_number_mismatch,
        predicate_is_not_fact,
        init_redeclaration,
        facts_init_redeclaration,
        missing_init,
        missing_goal,
        missing_obs_cond,
        default_obs_cond_redeclaration,
        missing_else_or_default_obs_cond,
        events_conditions_unsatisfied,
        empty_agent_set,
        inadmissible_formula_in_theory,
        missing_requirement,
        // Grounding errors
        inconsistent_theory_worlds,
        inconsistent_theory_designated,
        agent_obs_cond_redeclaration,
        missing_agent_obs_cond,
        missing_agent_obs_cond_no_default
    };

    class EPDDLException : public std::exception {
    public:
        EPDDLException(const std::string &file, const unsigned long row, const unsigned long col,
                       const std::string &error, error_type err_type) :
               m_row{row},
               m_col{col},
               m_message{"In file '" + file +
                         "' at (" + std::to_string(row) +
                         ":"  + std::to_string(col) + "):\n" +
                         error + "\n"},
               m_err_type{err_type},
               m_exit_code{EPDDLException::get_exit_code(err_type)} {}

        EPDDLException(const ast::info &info, const std::string &error, error_type err_type) :
                EPDDLException(info.m_path, info.m_row, info.m_col, error, err_type) {}

        EPDDLException(const std::string &file, const std::string &error, error_type err_type) :
                m_row{0},
                m_col{0},
                m_message{"In file '" + file + "':\n" + error + "\n"},
                m_err_type{err_type},
                m_exit_code{EPDDLException::get_exit_code(err_type)} {}

        EPDDLException(const std::string &error, error_type err_type) :
                m_row{0},
                m_col{0},
                m_message{error + "\n"},
                m_err_type{err_type},
                m_exit_code{EPDDLException::get_exit_code(err_type)} {}

        char *what() {
            return const_cast<char *>(m_message.data());
        }

        [[nodiscard]] unsigned long get_row() const { return m_row; }
        [[nodiscard]] unsigned long get_col() const { return m_col; }

        [[nodiscard]] error_type get_error_type() const { return m_err_type; }
        [[nodiscard]] plank::exit_code get_exit_code() const { return m_exit_code; }

    private:
        const unsigned long m_row, m_col;
        const std::string m_message;
        const plank::exit_code m_exit_code;
        const error_type m_err_type;

        static plank::exit_code get_exit_code(const error_type err_type) {
            switch (err_type) {
                case invalid_token:
                case out_of_range_int:
                    return plank::exit_code::lexer_error;
                case token_mismatch:
                case unexpected_token:
                case missing_lpar:
                case missing_rpar:
                case empty_list:
                case bad_obs_cond:
                case expected_eof:
                case unexpected_eof:
                    return plank::exit_code::parser_error;
                case library_declaration:
                case element_redeclaration:
                case action_type_redeclaration:
                case reserved_element_redeclaration:
                case undeclared_element:
                case bad_type_specialization:
                case incompatible_types:
                case incompatible_term_type:
                case arguments_number_mismatch:
                case predicate_is_not_fact:
                case init_redeclaration:
                case facts_init_redeclaration:
                case missing_init:
                case missing_goal:
                case missing_obs_cond:
                case default_obs_cond_redeclaration:
                case missing_else_or_default_obs_cond:
                case events_conditions_unsatisfied:
                case empty_agent_set:
                case inadmissible_formula_in_theory:
                    return plank::exit_code::type_checker_error;
                case inconsistent_theory_worlds:
                case inconsistent_theory_designated:
                case agent_obs_cond_redeclaration:
                case missing_agent_obs_cond:
                case missing_agent_obs_cond_no_default:
                    return plank::exit_code::grounding_error;
                case missing_requirement:
                    return plank::exit_code::all_good;
            }
        }
    };
}

#endif //PLANK_PLANK_EXCEPTION_H
