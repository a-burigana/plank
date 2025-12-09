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

#ifndef EPDDL_LEX_H_
#define EPDDL_LEX_H_

#include <cctype>
#include <fstream>
#include <optional>
#include <string>
#include <type_traits>
#include <variant>

#include "tokens/token_types.h"
#include "tokens/dictionary.h"
#include "tokens/token.h"

namespace epddl {
    class lexer {
    public:
        explicit lexer(const std::string &path);

        lexer(const lexer&) = delete;
        lexer& operator=(const lexer&) = delete;

        lexer(lexer&&) = default;
        lexer& operator=(lexer&&) = default;

        ~lexer() { m_stream.close(); }

        [[nodiscard]] bool good() const;
        [[nodiscard]] bool eof() const;

        token_ptr get_next_token();

//        [[nodiscard]] static unsigned long get_row   (const token_ptr& token);
//        [[nodiscard]] static unsigned long get_col   (const token_ptr& token);

    private:
        std::string m_path;
        char m_current_char;
        unsigned long m_input_row, m_input_col;
        bool m_good;
    
        std::ifstream m_stream;
        dictionary m_dictionary;

        static token_ptr make_token_ptr(token_type type, unsigned long row, unsigned long col,
                                        std::optional<std::string> lexeme = std::nullopt);

        token_ptr scan_keyword();
        token_ptr scan_variable();
        token_ptr scan_punctuation();
        token_ptr scan_identifier();
        token_ptr scan_integer();

        static token_ptr get_valid_keyword_token(const std::string &lexeme, unsigned long t_row, unsigned long t_col);
        static token_ptr get_valid_modality_token(const std::string &lexeme, unsigned long t_row, unsigned long t_col);
        static token_ptr get_valid_event_cond_token(const std::string &lexeme, unsigned long t_row, unsigned long t_col);

        bool ignore_spaces();
        bool ignore_comments();
    
        [[nodiscard]] char peek_next_char();
        char get_next_char();
    
        static bool is_ident_char(char c);
        static bool is_keyword_char(char c);
    };
}

#endif  // EPDDL_LEX_H_
