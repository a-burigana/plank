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
    template<typename token_type>
    class token_t  {
    public:
        token_t<token_type>(unsigned long row, unsigned long col, std::optional<std::string> lexeme = std::nullopt) :
            m_lexeme{std::move(lexeme)},
            m_row{row},
            m_col{col} {}

        token_t(const token_t<token_type>&) = delete;
        token_t(token_t<token_type>&&) noexcept = default;

        token_t& operator=(const token_t<token_type>&) = delete;
        token_t& operator=(token_t<token_type>&&) = delete;

        [[nodiscard]] std::string get_string()              const { return m_lexeme.has_value() ? m_lexeme.value() : ""; }

        template<typename other_token_type>
        [[nodiscard]] bool        has_type() const { return std::is_same<token_type, other_token_type>::value; }

        // todo: reimplement
//        [[nodiscard]] token_type  get_type()                const { return m_type; }

        [[nodiscard]] std::string to_string() const;

        [[nodiscard]] unsigned long get_row() const { return m_row; }
        [[nodiscard]] unsigned long get_col() const { return m_col; }

    private:
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

        token_ptr get_next_token();
        static std::string to_string(token_ptr &tok);

    private:
        char m_current_char;
        unsigned long m_input_row, m_input_col;
        bool m_good;
    
        std::ifstream& m_stream;
        const dictionary& m_dictionary;

        token_ptr scan_keyword();
        token_ptr scan_variable();
        token_ptr scan_punctuation();
        token_ptr scan_identifier();
        token_ptr scan_integer();

        static token_ptr get_valid_keyword_token(const std::string &lexeme, unsigned long t_row, unsigned long t_col);

        void ignore_spaces();
        void ignore_comments();
    
        [[nodiscard]] char peek_next_char();
        char get_next_char();
    
        static bool is_ident_char(char c);
        static bool is_keyword_char(char c);
    };
}

#endif  // EPDDL_LEX_H_
