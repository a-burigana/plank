#ifndef EPDDL_LEX_H_
#define EPDDL_LEX_H_

#include <cctype>
#include <fstream>
#include <optional>
#include <string>
#include <type_traits>
#include <variant>

#include "../generators/tokens/token_types_gen.h"
#include "dictionary.h"
#include "token.h"

namespace epddl {
    class lexer {
    public:
        explicit lexer(std::ifstream stream, dictionary dictionary);

        lexer(const lexer&) = delete;
        lexer& operator=(const lexer&) = delete;

        lexer(lexer&&) = default;
        lexer& operator=(lexer&&) = default;

        [[nodiscard]] bool good() const;
        [[nodiscard]] bool eof() const;

        token_ptr get_next_token();

//        [[nodiscard]] static unsigned long get_row   (const token_ptr& token);
//        [[nodiscard]] static unsigned long get_col   (const token_ptr& token);

    private:
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

        bool ignore_spaces();
        bool ignore_comments();
    
        [[nodiscard]] char peek_next_char();
        char get_next_char();
    
        static bool is_ident_char(char c);
        static bool is_keyword_char(char c);
    };
}

#endif  // EPDDL_LEX_H_
