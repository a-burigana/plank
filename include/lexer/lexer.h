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

#ifndef PLANK_LEX_H_
#define PLANK_LEX_H_

#include <cctype>
#include <fstream>
#include <sstream>
#include <optional>
#include <string>
#include <type_traits>
#include <variant>

#include "tokens/token_types.h"
#include "tokens/dictionary.h"
#include "tokens/token.h"
#include "../error-manager/error_manager.h"

namespace epddl {
    class lexer {
    public:
        lexer(const std::string &input, error_manager_ptr error_manager, bool from_file = true);

        lexer(const lexer&) = delete;
        lexer& operator=(const lexer&) = delete;

        lexer(lexer&&) = default;
        lexer& operator=(lexer&&) = default;

        ~lexer() {
            if (m_file_stream.is_open())
                m_file_stream.close();
        }

        [[nodiscard]] bool good() const;
        [[nodiscard]] bool eof() const;

        token_ptr get_next_token();

//        [[nodiscard]] static unsigned long get_row   (const token_ptr& token);
//        [[nodiscard]] static unsigned long get_col   (const token_ptr& token);

    private:
        std::string m_path;
        error_manager_ptr m_error_manager;
        char m_current_char;
        unsigned long m_input_row, m_input_col;
        bool m_good, m_from_file;

        std::ifstream m_file_stream;
        std::istringstream m_string_stream;
        dictionary m_dictionary;

        static token_ptr make_token_ptr(token_type type, unsigned long row, unsigned long col,
                                        std::optional<std::string> lexeme = std::nullopt);

        template<class stream_type>
        token_ptr get_next_token_helper(stream_type &stream) {
            if (eof())
                return make_token_ptr(special_token::eof{}, m_input_row, m_input_col);

            bool has_ignored_spaces = false, has_ignored_comments = false;

            do {
                has_ignored_spaces = ignore_spaces(stream);
                if (not stream.good())
                    return make_token_ptr(special_token::eof{}, m_input_row, m_input_col);

                has_ignored_comments = ignore_comments(stream);
                if (not stream.good())
                    return make_token_ptr(special_token::eof{}, m_input_row, m_input_col);
            } while (has_ignored_spaces or has_ignored_comments);

            unsigned long t_row = m_input_row, t_col = m_input_col;
            char c = peek_next_char(stream);

            if (c == ':')
                return scan_keyword(stream);
            else if (c == '?')
                return scan_variable(stream);
            else if (is_ident_char(c) and c != '-')
                return scan_identifier(stream);
            else if (ispunct(c))
                return scan_punctuation(stream);
//    else if (isdigit(c))
//        return scan_integer();
            else {
                token_ptr err = make_token_ptr(special_token::error{}, t_row, t_col, std::string{c});
                m_error_manager->throw_error(error_type::invalid_token, err, {"symbol"});
                return err;
            }
        }

        template<class stream_type>
        token_ptr scan_keyword(stream_type &stream) {
            // Scanning regex :?[a-zA-Z-0-9\-]+
            unsigned long t_row = m_input_row, t_col = m_input_col;
            std::string lexeme;

            lexeme += get_next_char(stream);       // Reading ':'

            while (stream.good() and is_keyword_char(peek_next_char(stream)))
                lexeme += get_next_char(stream);

            if (m_dictionary.is_valid_keyword(lexeme))
                return get_valid_keyword_token(lexeme, t_row, t_col);

            if (m_dictionary.is_valid_event_condition(lexeme))
                return get_valid_event_cond_token(lexeme, t_row, t_col);

            if (m_dictionary.is_valid_requirement(lexeme))
                return make_token_ptr(ast_token::requirement{}, t_row, t_col, std::move(lexeme));

            // A keyword identifier <K_ID> is invalid if one of these conditions hold:
            //  (1) <K_ID> is empty
            //  (2) <K_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)
            //  (3) <K_ID> is not a recognized EPDDL keyword

            bool empty_keyword_id =
                    lexeme.length() == 1;   // empty_keyword == true iff lexeme == ":" iff lexeme.length() == 1
            token_ptr err;

            if (empty_keyword_id) {
                // CASE (1) If the keyword identifier is empty, we throw an error
                err = make_token_ptr(special_token::error{}, t_row, t_col, std::string{get_next_char(stream)});
                m_error_manager->throw_error(error_type::invalid_token, err, {"keyword identifier"});
            } else {
                // CASE (2) If the keyword identifier is not syntactically valid, or is not recognized, we throw an error
                err = make_token_ptr(special_token::error{}, t_row, t_col, lexeme);
                m_error_manager->throw_error(error_type::invalid_token, err, {"keyword identifier"});
            }
            return err;
        }

        template<class stream_type>
        token_ptr scan_variable(stream_type &stream) {
            // Scanning regex ?[_a-zA-Z][_'a-zA-Z0-9]*
            unsigned long t_row = m_input_row, t_col = m_input_col;
            std::string lexeme;

            lexeme += get_next_char(stream);       // Reading '?'

            // We read the identifier
            while (stream.good() and is_ident_char(peek_next_char(stream)))
                lexeme += get_next_char(stream);

            // A variable identifier <V_ID> is invalid if one of these conditions hold:
            //  (1) <V_ID> is empty
            //  (2) <V_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)

            bool empty_variable_id =
                    lexeme.length() == 1;  // empty_variable == true iff lexeme == "?" iff lexeme.length() == 1
            token_ptr err;

            if (empty_variable_id) {
                // CASE (1) If the variable identifier is empty, we throw an error
                err = make_token_ptr(special_token::error{}, t_row, t_col, std::string{get_next_char(stream)});
                m_error_manager->throw_error(error_type::invalid_token, err, {"variable identifier"});
            }

            // A variable identifier is syntactically valid iff it starts with an alphabetic char
            bool is_valid_variable_id = isalpha(lexeme.at(1));

            if (not is_valid_variable_id) {
                // CASE (2) If the variable identifier is not syntactically valid, we throw an error
                err = make_token_ptr(special_token::error{}, t_row, t_col, lexeme);
                m_error_manager->throw_error(error_type::invalid_token, err, {"variable identifier"});
            } else
                return make_token_ptr(ast_token::variable{}, t_row, t_col, std::move(lexeme));

            return err;
        }

        template<class stream_type>
        token_ptr scan_punctuation(stream_type &stream) {
            unsigned long t_row = m_input_row, t_col = m_input_col;
            token_ptr err;

            switch (char c = peek_next_char(stream); c) {
                case '(':
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::lpar{}, t_row, t_col);
                case ')':
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::rpar{}, t_row, t_col);
                case '[':
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::lbrack{}, t_row, t_col);
                case ']':
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::rbrack{}, t_row, t_col);
                case '<':
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::langle{}, t_row, t_col);
                case '>':
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::rangle{}, t_row, t_col);
                case '-':
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::dash{}, t_row, t_col);
                case '=':
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::eq{}, t_row, t_col);
                case '/':
                    get_next_char(stream);
                    if (char c2 = peek_next_char(stream); c2 != '=') {
                        err = make_token_ptr(special_token::error{}, t_row, t_col, std::string{c} + std::string{c2});
                        m_error_manager->throw_error(error_type::invalid_token, err, {"symbol"});
                    }
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::neq{}, t_row, t_col);
                case '|':
                    get_next_char(stream);
                    return make_token_ptr(punctuation_token::such_that{}, t_row, t_col);
                default: {
                    err = make_token_ptr(special_token::error{}, t_row, t_col, std::string{c});
                    m_error_manager->throw_error(error_type::invalid_token, err, {"symbol"});
                }
            }
            return err;
        }

        template<class stream_type>
        token_ptr scan_identifier(stream_type &stream) {
            // Scanning regex [_a-zA-Z][_'a-zA-Z0-9]*
            unsigned long t_row = m_input_row, t_col = m_input_col;
            std::string lexeme;

            // We read the identifier
            while (stream.good() and is_ident_char(peek_next_char(stream)))
                lexeme += get_next_char(stream);

            token_ptr err;

            if (char c = peek_next_char(stream); c == '.') {
                lexeme += get_next_char(stream);

                if (m_dictionary.is_valid_modality(lexeme))
                    return get_valid_modality_token(lexeme, t_row, t_col);
                else {
                    err = make_token_ptr(special_token::error{}, t_row, t_col, lexeme);
                    m_error_manager->throw_error(error_type::invalid_token, err, {"modality name"});
                }
            } else {
                if (m_dictionary.is_valid_keyword(lexeme))
                    return get_valid_keyword_token(lexeme, t_row, t_col);
                else {
                    if (isalpha(lexeme.at(0)) or lexeme.at(0) == '_')
                        return make_token_ptr(ast_token::identifier{}, t_row, t_col, std::move(lexeme));
                    else {
                        err = make_token_ptr(special_token::error{}, t_row, t_col, lexeme);
                        m_error_manager->throw_error(error_type::invalid_token, err, {"identifier"});
                    }
                }
            }
            return err;
        }

        template<class stream_type>
        token_ptr scan_integer(stream_type &stream) {
            // Scanning regex [0-9]|[1-9][0-9]+
            unsigned long t_row = m_input_row, t_col = m_input_col;
            std::string lexeme;

            while (stream.good() and isdigit(peek_next_char(stream)))
                lexeme += get_next_char(stream);

            // An integer <N> is invalid if one of these conditions hold:
            //  (1) <N> is immediately followed by an identifier character
            //  (2) <N> is out of range (max value is std::numeric_limits<unsigned long>::max();)
            //  (3) <N> starts with '0' and it is immediately followed by other digits (i.e., it is syntactically invalid)

            token_ptr err;

            // CASE (1)
            if (stream.good() and is_ident_char(peek_next_char(stream))) {
                err = make_token_ptr(special_token::error{}, t_row, t_col, std::string{peek_next_char(stream)});
                m_error_manager->throw_error(error_type::invalid_token, err, {"digit"});
            }

            try {
                std::stoul(lexeme);
            } catch (const std::out_of_range &oor) {
                // CASE (2)
                err = make_token_ptr(special_token::error{}, t_row, t_col, lexeme);
                m_error_manager->throw_error(error_type::out_of_range_int, err);
            }

            // An integer is syntactically valid iff it is not the case that it starts with '0' and its length is > 1
            bool is_valid_integer = not(lexeme.at(0) == '0' and lexeme.length() > 1);

            // A non-zero integer can not start with 0
            if (is_valid_integer)
                return make_token_ptr(ast_token::integer{}, t_row, t_col, std::move(lexeme));
            else {
                // CASE (3) If the integer is not syntactically valid, we throw an error
                err = make_token_ptr(special_token::error{}, t_row, t_col, lexeme);
                m_error_manager->throw_error(error_type::invalid_token, err, {"integer"});
            }

            return err;
        }

        template<class stream_type>
        bool ignore_spaces(stream_type &stream) {
            char c = peek_next_char(stream);
            bool has_ignored = false;

            while (stream.good() and isspace(c)) {
                get_next_char(stream);
                c = peek_next_char(stream);
                has_ignored = true;
            }

            if (c == std::ifstream::traits_type::eof())
                get_next_char(stream);

            return has_ignored;
        }

        template<class stream_type>
        bool ignore_comments(stream_type &stream) {
            char c = peek_next_char(stream);
            bool has_ignored = false;

            if (c == ';') {
                while (stream.good() and c != '\n') {
                    get_next_char(stream);
                    c = peek_next_char(stream);
                }
                get_next_char(stream);    // Reading '\n'
                has_ignored = true;
            }
            return has_ignored;
        }

        template<class stream_type>
        [[nodiscard]] char peek_next_char(stream_type &stream) {
            return (char)stream.peek();
        }

        template<class stream_type>
        char get_next_char(stream_type &stream) {
            m_current_char = (char)stream.get();

            if (m_current_char == '\n') {
                ++m_input_row;
                m_input_col = 1;
            } else {
                ++m_input_col;
            }

            return m_current_char;
        }

        static token_ptr get_valid_keyword_token(const std::string &lexeme, unsigned long t_row, unsigned long t_col);
        static token_ptr get_valid_modality_token(const std::string &lexeme, unsigned long t_row, unsigned long t_col);
        static token_ptr get_valid_event_cond_token(const std::string &lexeme, unsigned long t_row, unsigned long t_col);

        static bool is_ident_char(char c);
        static bool is_keyword_char(char c);
    };
}

#endif  // PLANK_LEX_H_
