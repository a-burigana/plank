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

#include "../../../include/lib/lexer/lexer.h"
#include <memory>
#include <stdexcept>

#define epddl_token_type(token_type) token_type

using namespace epddl;

lexer::lexer(const std::string &input, error_manager_ptr error_manager, bool from_file) :
        m_path{input},
        m_error_manager{std::move(error_manager)},
        m_current_char{'\0'},
        m_input_row{1},
        m_input_col{1},
        m_good{true},
        m_from_file{from_file} {
    m_dictionary = dictionary{};

    if (from_file) {
        m_file_stream = std::ifstream(input);

        if (m_file_stream.fail())
            throw std::runtime_error("File not found: " + input);

        if (not m_file_stream.is_open())
            m_good = false;
    } else {
        m_string_stream = std::istringstream{input};

        if (m_string_stream.fail())
            throw std::runtime_error("Bad input: " + input);

        if (not m_string_stream.good())
            m_good = false;
    }
}

bool lexer::good() const {
    return m_good;
}

bool lexer::eof() const {
    return m_current_char == std::ifstream::traits_type::eof();
}

token_ptr lexer::make_token_ptr(token_type type, unsigned long row, unsigned long col,
                                std::optional<std::string> lexeme) {
    return std::make_shared<token>(token{type, row, col, std::move(lexeme)});
}

token_ptr lexer::get_next_token() {
    return m_from_file
        ? get_next_token_helper<std::ifstream>(m_file_stream)
        : get_next_token_helper<std::istringstream>(m_string_stream);
}

token_ptr lexer::get_valid_keyword_token(const std::string &lexeme, const unsigned long t_row, const unsigned long t_col) {
    #define epddl_token(t_type, t_scope, t_name, t_lexeme)     \
    if (t_type::t_name::lexeme == lexeme) {                    \
        return make_token_ptr(t_type::t_name{}, t_row, t_col); \
    }
    #define tokens(tokens) tokens
    #define epddl_tokens(_, tokens) tokens
    epddl_valid_keywords_def
    #undef epddl_tokens
    #undef tokens
    #undef epddl_token

    return make_token_ptr(special_token::error{}, t_row, t_col, "Invalid keyword " + lexeme);
}

token_ptr lexer::get_valid_modality_token(const std::string &lexeme, unsigned long t_row, unsigned long t_col) {
    #define epddl_token(t_type, t_scope, t_name, t_lexeme)     \
    if (t_type::t_name::lexeme == lexeme) {                    \
        return make_token_ptr(t_type::t_name{}, t_row, t_col); \
    }
    #define tokens(tokens) tokens
    #define epddl_tokens(_, tokens) tokens
    epddl_modality_tokens_def
    #undef epddl_tokens
    #undef tokens
    #undef epddl_token
    #undef token_type

    return make_token_ptr(special_token::error{}, t_row, t_col, "Invalid modality " + lexeme);
}

token_ptr lexer::get_valid_event_cond_token(const std::string &lexeme, const unsigned long t_row, const unsigned long t_col) {
    #define epddl_token(t_type, t_scope, t_name, t_lexeme)     \
    if (t_type::t_name::lexeme == lexeme) {                    \
        return make_token_ptr(t_type::t_name{}, t_row, t_col); \
    }
    #define tokens(tokens) tokens
    #define epddl_tokens(_, tokens) tokens
    epddl_event_condition_tokens_def
    #undef epddl_tokens
    #undef tokens
    #undef epddl_token

    return make_token_ptr(special_token::error{}, t_row, t_col, "Invalid event condition: '" + lexeme + "'.");
}

bool lexer::is_ident_char(const char c) {
    return isalnum(c) or c == '_' or c == '-';
}

bool lexer::is_keyword_char(const char c) {
    return isalnum(c) or c == '-';
}

#undef epddl_token_type
