#ifndef EPDDL_LEX_H_
#define EPDDL_LEX_H_

#include <cctype>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <variant>
#include "lex_utils.h"


namespace epddl {
    class Token {
    public:
        Token(unsigned long row, unsigned long col, token_type type, std::optional<std::string> lexeme = std::nullopt) :
            m_type{type},
            m_lexeme{std::move(lexeme)},
            m_row{row},
            m_col{col} {}

        Token(const Token&) = delete;
        Token(Token&&) noexcept = default;

        Token& operator=(const Token&) = delete;
        Token& operator=(Token&&) = delete;

        [[nodiscard]] std::string get_string()              const { return m_lexeme.has_value() ? m_lexeme.value() : ""; }
        [[nodiscard]] bool        has_type(token_type type) const { return m_type == type; }
        [[nodiscard]] token_type get_type()                const { return m_type; }

        [[nodiscard]] std::string to_string(const dictionary& dictionary) const;

        [[nodiscard]] unsigned long get_row() const { return m_row; }
        [[nodiscard]] unsigned long get_col() const { return m_col; }

    private:
        const token_type m_type;
        const std::optional<std::string> m_lexeme;
        const unsigned long m_row, m_col;
    };
    
    class lexer {
    public:
        explicit lexer(std::ifstream& stream, const dictionary& dictionary);

        lexer(const lexer&) = delete;
        lexer& operator=(const lexer&) = delete;

        lexer(lexer&&) = delete;
        lexer& operator=(lexer&&) = delete;

        [[nodiscard]] bool good() const;
        [[nodiscard]] bool eof() const;

        Token get_next_token();
        const dictionary & get_dictionary() const;

    private:
        char m_current_char;
        unsigned long m_input_row, m_input_col;
        bool m_good;
    
        std::ifstream& m_stream;
        const dictionary& m_dictionary;

        Token scan_keyword();
        Token scan_variable();
        Token scan_punctuation();
        Token scan_identifier();
        Token scan_integer();

        void ignore_spaces();
        void ignore_comments();
    
        [[nodiscard]] char peek_next_char();
        char get_next_char();
    
        static bool is_ident_char(char c);
        static bool is_keyword_char(char c);
    };
}

#endif  // EPDDL_LEX_H_
