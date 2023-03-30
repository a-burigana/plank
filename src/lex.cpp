#include "../include/lex.h"

#include <utility>
#include "../include/epddl_exception.h"

using namespace epddl;

lexer::lexer(std::ifstream& stream, const dictionary& dictionary) :
        m_stream{stream},
        m_dictionary{dictionary},
        m_current_char{'\0'},
        m_input_row{1},
        m_input_col{1},
        m_good{true} {}

const dictionary& lexer::get_dictionary() const {
    return m_dictionary;
}

bool lexer::good() const {
    return m_good;
}

bool lexer::eof() const {
    return m_current_char == std::ifstream::traits_type::eof();
}

Token lexer::get_next_token() {
    if (eof()) {
        return Token{m_input_row, m_input_col, special_value::eof};
    }

    ignore_spaces();
    if (!m_stream.good()) {
        return Token{m_input_row, m_input_col, special_value::eof};
    }

    ignore_comments();
    if (!m_stream.good()) {
        return Token{m_input_row, m_input_col, special_value::eof};
    }

    unsigned long t_row = m_input_row, t_col = m_input_col;
    char c = peek_next_char();

    if (c == ':') {
        return scan_keyword();
    } else if (c == '?') {
        return scan_variable();
    } else if (ispunct(c)) {
        return scan_punctuation();
    } else if (isalpha(c) || c == '_') {
        return scan_identifier();
    } else if (isdigit(c)) {
        return scan_integer();
    } else {
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
    }
}

Token lexer::scan_keyword() {
    // Scanning regex :?[a-zA-Z-0-9\-]+
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    lexeme += get_next_char();       // Reading ':'

    while (m_stream.good() && is_keyword_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    if (m_dictionary.is_valid_keyword(lexeme)) {
        return Token{t_row, t_col, m_dictionary.get_valid_keyword_type(lexeme)};
    }

    // A keyword identifier <K_ID> is invalid if one of these conditions hold:
    //  (1) <K_ID> is empty
    //  (2) <K_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)
    //  (3) <K_ID> is not a recognized EPDDL keyword

    bool empty_keyword_id = lexeme.length() == 1;   // empty_keyword == true iff lexeme == ":" iff lexeme.length() == 1

    if (empty_keyword_id) {
        // CASE (1) If the keyword identifier is empty, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Expected keyword identifier."});
    }

    // A keyword identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_keyword_id = isalpha(lexeme.at(1));

    if (!is_valid_keyword_id) {
        // CASE (2) If the keyword identifier is not syntactically valid, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Invalid keyword identifier: "} + lexeme);
    } else {
        // CASE (3) If the keyword identifier is syntactically valid, but is not recognized, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unknown keyword identifier: "} + lexeme);
    }
}

Token lexer::scan_variable() {
    // Scanning regex ?[_a-zA-Z][_'a-zA-Z0-9]*
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    lexeme += get_next_char();       // Reading '?'

    // We read the identifier
    while (m_stream.good() && is_ident_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    // A variable identifier <V_ID> is invalid if one of these conditions hold:
    //  (1) <V_ID> is empty
    //  (2) <V_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)

    bool empty_variable_id = lexeme.length() == 1;  // empty_variable == true iff lexeme == "?" iff lexeme.length() == 1

    if (empty_variable_id) {
        // CASE (1) If the variable identifier is empty, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Expected variable identifier."});
    }

    // A variable identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_variable_id = isalpha(lexeme.at(1));

    if (!is_valid_variable_id) {
        // CASE (2) If the variable identifier is not syntactically valid, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Invalid identifier: "} + lexeme);
    } else {
        return Token{t_row, t_col, basic_value::variable, std::move(lexeme)};
    }
}

Token lexer::scan_punctuation() {
    unsigned long t_row = m_input_row, t_col = m_input_col;

    switch (char c = peek_next_char(); c) {
        case '(':
            get_next_char();
            return Token{t_row, t_col, punctuation_value::lpar};
        case ')':
            get_next_char();
            return Token{t_row, t_col, punctuation_value::rpar};
        case '[':
            get_next_char();
            return Token{t_row, t_col, punctuation_value::lbrack};
        case ']':
            get_next_char();
            return Token{t_row, t_col, punctuation_value::rbrack};
        case '<':
            get_next_char();
            if (peek_next_char() == '-') {
                get_next_char();
                return Token{t_row, t_col, punctuation_value::gets};
            }
            return Token{t_row, t_col, punctuation_value::lt};
        case '>':
            get_next_char();
            return Token{t_row, t_col, punctuation_value::gt};
        case '-':
            get_next_char();
            return Token{t_row, t_col, punctuation_value::dash};
        case '=':
            get_next_char();
            return Token{t_row, t_col, punctuation_value::eq};
        default:
            throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + c + std::string{"'."});
    }
}

Token lexer::scan_identifier() {
    // Scanning regex [_a-zA-Z][_'a-zA-Z0-9]*
    unsigned long t_row = m_input_row, t_col = m_input_col;
    basic_value token_value = basic_value::identifier;
    std::string lexeme;

    // We read the identifier
    while (m_stream.good() && is_ident_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    if (peek_next_char() == '.') {
        token_value = basic_value::modality;
        lexeme += get_next_char();       // Reading '.'
    }

    if (token_value == basic_value::identifier && m_dictionary.is_valid_keyword(lexeme)) {
        return Token{t_row, t_col, m_dictionary.get_valid_keyword_type(lexeme)};
    } else {
        return Token{t_row, t_col, token_value, std::move(lexeme)};
    }
}

Token lexer::scan_integer() {
    // Scanning regex [0-9]|[1-9][0-9]+
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    while (m_stream.good() && isdigit(peek_next_char())) {
        lexeme += get_next_char();
    }

    // An integer <N> is invalid if one of these conditions hold:
    //  (1) <N> is immediately followed by an identifier character
    //  (2) <N> is out of range (max value is std::numeric_limits<unsigned long>::max();)
    //  (3) <N> starts with '0' and it is immediately followed by other digits (i.e., it is syntactically invalid)

    // CASE (1)
    if (m_stream.good() && is_ident_char(peek_next_char())) {
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
    }

    try {
        std::stoul(lexeme);
    } catch (const std::out_of_range& oor) {
        // CASE (2)
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Integer out fo range: "} + lexeme);
    }

    // An integer is syntactically valid iff it is not the case that it starts with '0' and its length is > 1
    bool is_valid_integer = !(lexeme.at(0) == '0' && lexeme.length() > 1);

    // A non-zero integer can not start with 0
    if (is_valid_integer) {
        return Token{t_row, t_col, basic_value::integer, std::move(lexeme)};
    } else {
        // CASE (3) If the integer is not syntactically valid, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Invalid integer: "} + lexeme);
    }
}

void lexer::ignore_spaces() {
    char c = peek_next_char();

    while (m_stream.good() && isspace(c)) {
        get_next_char();
        c = peek_next_char();
    }

    if (c == std::ifstream::traits_type::eof()) {
        get_next_char();
    }
}

void lexer::ignore_comments() {
    char c = peek_next_char();

    if (c == ';') {
        while (m_stream.good() && c != '\n') {
            get_next_char();
            c = peek_next_char();
        }
        get_next_char();    // Reading '\n'
    }
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
    return isalnum(c) || c == '_' || c == '\'';
}

bool lexer::is_keyword_char(const char c) {
    return isalnum(c) || c == '-';
}

std::string Token::to_string(const dictionary& dictionary) const {
    if (std::holds_alternative<punctuation_value>(m_type)) {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + dictionary.get_name(m_type) + std::string{"}"};
    } else if (std::holds_alternative<basic_value>(m_type) && m_lexeme != std::nullopt) {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + dictionary.get_name(m_type) + std::string{":\""} + *m_lexeme + std::string{"\"}"};
    } else {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + dictionary.to_string(m_type) + std::string{"}"};
    }
}
