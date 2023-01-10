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
#include "../include/lex_utils.h"


namespace epddl {
    class Token {
    public:
        Token(utils::token::type type, std::string lexeme, long row, long col) : m_type{type}, m_lexeme{std::move(lexeme)}, m_row{row}, m_col{col} {}
        Token(utils::token::type type, long row, long col) : m_type{type}, m_lexeme{std::nullopt}, m_row{row}, m_col{col} {}

        Token(const Token&) = delete;
        Token(Token&&) = default;

        Token& operator=(const Token&) = delete;
        Token& operator=(Token&&) = delete;

        [[nodiscard]]       std::string         get_string()                      const { return m_lexeme.has_value() ? m_lexeme.value() : ""; }
        [[nodiscard]]       bool                has_type(utils::token::type type) const { return m_type == type; }
        [[nodiscard]] const utils::token::type& get_type()                        const { return m_type; }

        [[nodiscard]] std::string to_string() const;
    
    private:
        const utils::token::type m_type;
        const std::optional<std::string> m_lexeme;
        const long m_row, m_col;
    
        template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
        template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
    
        static std::string to_string(utils::token::type t);
    
        static std::string to_string(utils::token::special t_) ;
        static std::string to_string(utils::token::punctuation t_);
        static std::string to_string(utils::token::basic t_);
        static std::string to_string(utils::token::keyword t_);
        static std::string to_string(utils::token::connective::unary t_);
        static std::string to_string(utils::token::connective::binary t_);
        static std::string to_string(utils::token::connective::n_ary t_);
        static std::string to_string(utils::token::quantifier t_);
        static std::string to_string(utils::token::atomic_formula t_);
        static std::string to_string(utils::token::postcondition t_);
        static std::string to_string(utils::token::observability t_);
        static std::string to_string(utils::token::reserved_type t_);
        static std::string to_string(utils::token::agents t_);
        static std::string to_string(utils::token::requirement t_);
    };
    
    class lexer {
    public:
        using error_handler = std::function<void(long, long, std::string)>;
    
        explicit lexer(std::ifstream stream, error_handler error);
    
        [[nodiscard]] bool good() const;
        [[nodiscard]] bool eof() const;

        Token get_next_token();

//        const Token get() {
////            m_tok(std::move(get_next_token()));
//
//            return std::move(m_tok);
//        }      // todo: is this good practice
//        const Token& peek() { return m_tok; }

    private:
//        Token m_tok;
        char m_current_char;
        long m_input_row, m_input_col;
        bool m_good;
    
        std::ifstream m_stream;
        error_handler m_error;
    
        std::map<std::string, utils::token::type> m_valid_keywords;

        Token scan_keyword();
        Token scan_variable();
        Token scan_punctuation();
        Token scan_identifier();
        Token scan_integer();
    
        [[nodiscard]] bool is_valid_keyword(const std::string& s) const;
    
        void ignore_spaces();
        void ignore_comments();
    
        [[nodiscard]] char peek_next_char();
        char get_next_char();
    
        static bool is_ident_char(char c);
        static bool is_keyword_char(char c);
    };
}

#endif  // EPDDL_LEX_H_
