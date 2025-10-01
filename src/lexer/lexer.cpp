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

#include "../../include/lexer/lexer.h"
#include "../../include/error-manager/epddl_exception.h"
#include <memory>

#define epddl_token_type(token_type) token_type

using namespace epddl;

lexer::lexer(const std::string &path) :
    m_current_char{'\0'},
    m_input_row{1},
    m_input_col{1},
    m_good{true} {
    m_dictionary = dictionary{};
    m_stream = std::ifstream(path);

    if (not m_stream.is_open())
        m_good = false;
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
    if (eof())
        return make_token_ptr(special_token::eof{}, m_input_row, m_input_col);

    bool has_ignored_spaces = false, has_ignored_comments = false;

    do {
        has_ignored_spaces = ignore_spaces();
        if (not m_stream.good())
            return make_token_ptr(special_token::eof{}, m_input_row, m_input_col);

        has_ignored_comments = ignore_comments();
        if (not m_stream.good())
            return make_token_ptr(special_token::eof{}, m_input_row, m_input_col);
    } while (has_ignored_spaces or has_ignored_comments);

    unsigned long t_row = m_input_row, t_col = m_input_col;
    char c = peek_next_char();

    if (c == ':')
        return scan_keyword();
    else if (c == '?')
        return scan_variable();
    else if (isalpha(c) or c == '_')
        return scan_identifier();
    else if (ispunct(c))
        return scan_punctuation();
    else if (isdigit(c))
        return scan_integer();
    else
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
}

token_ptr lexer::scan_keyword() {
    // Scanning regex :?[a-zA-Z-0-9\-]+
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    lexeme += get_next_char();       // Reading ':'

    while (m_stream.good() and is_keyword_char(peek_next_char()))
        lexeme += get_next_char();

    if (m_dictionary.is_valid_keyword(lexeme))
        return get_valid_keyword_token(lexeme, t_row, t_col);

    if (m_dictionary.is_valid_requirement(lexeme))
        return make_token_ptr(ast_token::requirement{}, t_row, t_col, std::move(lexeme));

    // A keyword identifier <K_ID> is invalid if one of these conditions hold:
    //  (1) <K_ID> is empty
    //  (2) <K_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)
    //  (3) <K_ID> is not a recognized EPDDL keyword

    bool empty_keyword_id = lexeme.length() == 1;   // empty_keyword == true iff lexeme == ":" iff lexeme.length() == 1

    if (empty_keyword_id)
        // CASE (1) If the keyword identifier is empty, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Expected keyword identifier."});

    // A keyword identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_keyword_id = isalpha(lexeme.at(1));

    if (not is_valid_keyword_id)
        // CASE (2) If the keyword identifier is not syntactically valid, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Invalid keyword identifier: "} + lexeme + std::string{"'."});
    else
        // CASE (3) If the keyword identifier is syntactically valid, but is not recognized, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Unknown keyword identifier: "} + lexeme + std::string{"'."});
}

token_ptr lexer::scan_variable() {
    // Scanning regex ?[_a-zA-Z][_'a-zA-Z0-9]*
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    lexeme += get_next_char();       // Reading '?'

    // We read the identifier
    while (m_stream.good() and is_ident_char(peek_next_char()))
        lexeme += get_next_char();

    // A variable identifier <V_ID> is invalid if one of these conditions hold:
    //  (1) <V_ID> is empty
    //  (2) <V_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)

    bool empty_variable_id = lexeme.length() == 1;  // empty_variable == true iff lexeme == "?" iff lexeme.length() == 1

    if (empty_variable_id)
        // CASE (1) If the variable identifier is empty, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Expected variable identifier."});

    // A variable identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_variable_id = isalpha(lexeme.at(1));

    if (not is_valid_variable_id)
        // CASE (2) If the variable identifier is not syntactically valid, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Invalid identifier: "} + lexeme + std::string{"'."});
    else
        return make_token_ptr(ast_token::variable{}, t_row, t_col, std::move(lexeme));
}

token_ptr lexer::scan_punctuation() {
    unsigned long t_row = m_input_row, t_col = m_input_col;

    switch (char c = peek_next_char(); c) {
        case '(':
            get_next_char();
            return make_token_ptr(punctuation_token::lpar{}, t_row, t_col);
        case ')':
            get_next_char();
            return make_token_ptr(punctuation_token::rpar{}, t_row, t_col);
        case '[':
            get_next_char();
            return make_token_ptr(punctuation_token::lbrack{}, t_row, t_col);
        case ']':
            get_next_char();
            return make_token_ptr(punctuation_token::rbrack{}, t_row, t_col);
        case '<':
            get_next_char();
            return make_token_ptr(punctuation_token::langle{}, t_row, t_col);
        case '>':
            get_next_char();
            return make_token_ptr(punctuation_token::rangle{}, t_row, t_col);
        case '-':
            get_next_char();
            return make_token_ptr(punctuation_token::dash{}, t_row, t_col);
        case '=':
            get_next_char();
            return make_token_ptr(punctuation_token::eq{}, t_row, t_col);
        case '/':
            get_next_char();
            if (char c2 = peek_next_char(); c2 != '=')
                throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Unexpected input symbols: '"} + c + c2 + std::string{"'."});

            get_next_char();
            return make_token_ptr(punctuation_token::neq{}, t_row, t_col);
        case '|':
            get_next_char();
            return make_token_ptr(punctuation_token::such_that{}, t_row, t_col);
        default:
            throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Unexpected input symbol: '"} + c + std::string{"'."});
    }
}

token_ptr lexer::scan_identifier() {
    // Scanning regex [_a-zA-Z][_'a-zA-Z0-9]*
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    // We read the identifier
    while (m_stream.good() and is_ident_char(peek_next_char()))
        lexeme += get_next_char();

    if (char c = peek_next_char(); c == '.') {
        lexeme += get_next_char();

        if (m_dictionary.is_valid_modality(lexeme))
            return get_valid_modality_token(lexeme, t_row, t_col);
        else
            throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Unknown modality name: '"} + lexeme + std::string{".'."});
    } else {
        if (m_dictionary.is_valid_keyword(lexeme))
            return get_valid_keyword_token(lexeme, t_row, t_col);
        else
            return make_token_ptr(ast_token::identifier{}, t_row, t_col, std::move(lexeme));
    }
}

token_ptr lexer::scan_integer() {
    // Scanning regex [0-9]|[1-9][0-9]+
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    while (m_stream.good() and isdigit(peek_next_char()))
        lexeme += get_next_char();

    // An integer <N> is invalid if one of these conditions hold:
    //  (1) <N> is immediately followed by an identifier character
    //  (2) <N> is out of range (max value is std::numeric_limits<unsigned long>::max();)
    //  (3) <N> starts with '0' and it is immediately followed by other digits (i.e., it is syntactically invalid)

    // CASE (1)
    if (m_stream.good() and is_ident_char(peek_next_char()))
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});

    try {
        std::stoul(lexeme);
    } catch (const std::out_of_range& oor) {
        // CASE (2)
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Integer out fo range: "} + lexeme + std::string{"'."});
    }

    // An integer is syntactically valid iff it is not the case that it starts with '0' and its length is > 1
    bool is_valid_integer = not (lexeme.at(0) == '0' and lexeme.length() > 1);

    // A non-zero integer can not start with 0
    if (is_valid_integer)
        return make_token_ptr(ast_token::integer{}, t_row, t_col, std::move(lexeme));
    else
        // CASE (3) If the integer is not syntactically valid, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Invalid integer_ptr: "} + lexeme + std::string{"'."});
}

token_ptr lexer::get_valid_keyword_token(const std::string &lexeme, const unsigned long t_row, const unsigned long t_col) {
    #define epddl_token(t_type, t_scope, t_name, t_lexeme) \
    if (t_type::t_name::lexeme == lexeme) {                  \
        return make_token_ptr(t_type::t_name{}, t_row, t_col); \
    }
    #define tokens(tokens) tokens
    #define epddl_tokens(_, tokens) tokens
    epddl_valid_keywords_def
    #undef epddl_tokens
    #undef tokens
    #undef epddl_token

    return make_token_ptr(special_token::invalid{}, t_row, t_col);
}

token_ptr lexer::get_valid_modality_token(const std::string &lexeme, unsigned long t_row, unsigned long t_col) {
    #define epddl_token(t_type, t_scope, t_name, t_lexeme) \
    if (t_type::t_name::lexeme == lexeme) {                  \
        return make_token_ptr(t_type::t_name{}, t_row, t_col); \
    }
    #define tokens(tokens) tokens
    #define epddl_tokens(_, tokens) tokens
    epddl_modality_tokens_def
    #undef epddl_tokens
    #undef tokens
    #undef epddl_token
    #undef token_type

    return make_token_ptr(special_token::invalid{}, t_row, t_col);
}

bool lexer::ignore_spaces() {
    char c = peek_next_char();
    bool has_ignored = false;

    while (m_stream.good() and isspace(c)) {
        get_next_char();
        c = peek_next_char();
        has_ignored = true;
    }

    if (c == std::ifstream::traits_type::eof()) {
        get_next_char();
    }
    return has_ignored;
}

bool lexer::ignore_comments() {
    char c = peek_next_char();
    bool has_ignored = false;

    if (c == ';') {
        while (m_stream.good() and c != '\n') {
            get_next_char();
            c = peek_next_char();
        }
        get_next_char();    // Reading '\n'
        has_ignored = true;
    }
    return has_ignored;
}

char lexer::peek_next_char() {
    return (char)m_stream.peek();
}

char lexer::get_next_char() {
    m_current_char = (char)m_stream.get();

    if (m_current_char == '\n') {
        ++m_input_row;
        m_input_col = 1;
    } else {
        ++m_input_col;
    }

    return m_current_char;
}

bool lexer::is_ident_char(const char c) {
    return isalnum(c) or c == '_' or c == '-';
}

bool lexer::is_keyword_char(const char c) {
    return isalnum(c) or c == '-';
}

#undef epddl_token_type
