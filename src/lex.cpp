#include "../include/lex/lex.h"
#include "../include/epddl_exception.h"

using namespace epddl;

lexer::lexer(std::ifstream& stream, const dictionary& dictionary) :
        m_stream{stream},
        m_dictionary{dictionary},
        m_current_char{'\0'},
        m_input_row{1},
        m_input_col{1},
        m_good{true} {}

bool lexer::good() const {
    return m_good;
}

bool lexer::eof() const {
    return m_current_char == std::ifstream::traits_type::eof();
}

template<typename token_type>
token_ptr lexer::make_token_ptr(unsigned long row, unsigned long col, std::optional<std::string> lexeme) {
    return std::make_unique<token<token_type>>(token<token_type>{row, col, std::move(lexeme)});
}

token_ptr lexer::get_next_token() {
    if (eof()) {
        return make_token_ptr<special_token::eof>(m_input_row, m_input_col);
    }

    ignore_spaces();
    if (not m_stream.good()) {
        return make_token_ptr<special_token::eof>(m_input_row, m_input_col);
    }

    ignore_comments();
    if (not m_stream.good()) {
        return make_token_ptr<special_token::eof>(m_input_row, m_input_col);
    }

    unsigned long t_row = m_input_row, t_col = m_input_col;
    char c = peek_next_char();

    if (c == ':') {
        return scan_keyword();
    } else if (c == '?') {
        return scan_variable();
    } else if (ispunct(c)) {
        return scan_punctuation();
    } else if (isalpha(c) or c == '_') {
        return scan_identifier();
    } else if (isdigit(c)) {
        return scan_integer();
    } else {
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
    }
}

token_ptr lexer::scan_keyword() {
    // Scanning regex :?[a-zA-Z-0-9\-]+
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    lexeme += get_next_char();       // Reading ':'

    while (m_stream.good() and is_keyword_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    if (m_dictionary.is_valid_keyword(lexeme)) {
        return get_valid_keyword_token(lexeme, t_row, t_col);
    }

    if (m_dictionary.is_valid_requirement(lexeme) or m_dictionary.is_valid_val_requirement(lexeme)) {
        return make_token_ptr<basic_token::requirement>(t_row, t_col, std::move(lexeme));
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

    if (not is_valid_keyword_id) {
        // CASE (2) If the keyword identifier is not syntactically valid, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Invalid keyword identifier: "} + lexeme);
    } else {
        // CASE (3) If the keyword identifier is syntactically valid, but is not recognized, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unknown keyword identifier: "} + lexeme);
    }
}

token_ptr lexer::scan_variable() {
    // Scanning regex ?[_a-zA-Z][_'a-zA-Z0-9]*
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    lexeme += get_next_char();       // Reading '?'

    // We read the identifier
    while (m_stream.good() and is_ident_char(peek_next_char())) {
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

    if (not is_valid_variable_id) {
        // CASE (2) If the variable identifier is not syntactically valid, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Invalid identifier: "} + lexeme);
    } else {
        return make_token_ptr<basic_token::variable>(t_row, t_col, std::move(lexeme));
    }
}

token_ptr lexer::scan_punctuation() {
    unsigned long t_row = m_input_row, t_col = m_input_col;

    switch (char c = peek_next_char(); c) {
        case '(':
            get_next_char();
                return make_token_ptr<punctuation_token::lpar>(t_row, t_col);
        case ')':
            get_next_char();
            return make_token_ptr<punctuation_token::rpar>(t_row, t_col);
        case '[':
            get_next_char();
            return make_token_ptr<punctuation_token::lbrack>(t_row, t_col);
        case ']':
            get_next_char();
            return make_token_ptr<punctuation_token::rbrack>(t_row, t_col);
        case '<':
            get_next_char();
            if (peek_next_char() == '-') {
                get_next_char();
                return make_token_ptr<punctuation_token::gets>(t_row, t_col);
            }
            return make_token_ptr<punctuation_token::lt>(t_row, t_col);
        case '>':
            get_next_char();
            return make_token_ptr<punctuation_token::gt>(t_row, t_col);
        case '-':
            get_next_char();
            return make_token_ptr<punctuation_token::dash>(t_row, t_col);
        case '=':
            get_next_char();
            return make_token_ptr<punctuation_token::eq>(t_row, t_col);
        default:
            throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + c + std::string{"'."});
    }
}

token_ptr lexer::scan_identifier() {
    // Scanning regex [_a-zA-Z][_'a-zA-Z0-9]*
    unsigned long t_row = m_input_row, t_col = m_input_col;
    bool is_identifier = true;
    std::string lexeme;

    // We read the identifier
    while (m_stream.good() and is_ident_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    if (peek_next_char() == '.') {
        is_identifier = false;
        lexeme += get_next_char();       // Reading '.'
    }

    if (is_identifier) {
        if (m_dictionary.is_valid_keyword(lexeme)) {
            return get_valid_keyword_token(lexeme, t_row, t_col);
        } else {
            return make_token_ptr<basic_token::identifier>(t_row, t_col, std::move(lexeme));
        }
    } else {
        return make_token_ptr<basic_token::modality>(t_row, t_col, std::move(lexeme));
    }
}

token_ptr lexer::scan_integer() {
    // Scanning regex [0-9]|[1-9][0-9]+
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    while (m_stream.good() and isdigit(peek_next_char())) {
        lexeme += get_next_char();
    }

    // An integer <N> is invalid if one of these conditions hold:
    //  (1) <N> is immediately followed by an identifier character
    //  (2) <N> is out of range (max value is std::numeric_limits<unsigned long>::max();)
    //  (3) <N> starts with '0' and it is immediately followed by other digits (i.e., it is syntactically invalid)

    // CASE (1)
    if (m_stream.good() and is_ident_char(peek_next_char())) {
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
    }

    try {
        std::stoul(lexeme);
    } catch (const std::out_of_range& oor) {
        // CASE (2)
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Integer out fo range: "} + lexeme);
    }

    // An integer is syntactically valid iff it is not the case that it starts with '0' and its length is > 1
    bool is_valid_integer = not (lexeme.at(0) == '0' and lexeme.length() > 1);

    // A non-zero integer can not start with 0
    if (is_valid_integer) {
        return make_token_ptr<basic_token::integer>(t_row, t_col, std::move(lexeme));
    } else {
        // CASE (3) If the integer is not syntactically valid, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Invalid integer: "} + lexeme);
    }
}

token_ptr lexer::get_valid_keyword_token(const std::string &lexeme, const unsigned long t_row, const unsigned long t_col) {
#define epddl_token_type(token_type) token_type
#define epddl_token(t_type, t_scope, t_name, t_lexeme) \
    if (t_type::t_name::lexeme == lexeme) {                  \
        return make_token_ptr<t_type::t_name>(t_row, t_col); \
    }
#define tokens(tokens) tokens
#define epddl_tokens(_, tokens) tokens
    epddl_keyword_tokens_def
#undef epddl_tokens
#undef tokens
#undef epddl_token
#undef token_type

    return make_token_ptr<special_token::invalid>(t_row, t_col);
}

void lexer::ignore_spaces() {
    char c = peek_next_char();

    while (m_stream.good() and isspace(c)) {
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
        while (m_stream.good() and c != '\n') {
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
    return isalnum(c) or c == '_' or c == '\'';
}

bool lexer::is_keyword_char(const char c) {
    return isalnum(c) or c == '-';
}

template<typename token_type>
std::string token<token_type>::to_string() const {
#define epddl_token_type(token_type) token_type
    if (std::is_same_v<typename token_type::super_type, epddl_punctuation_token_type>) {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{token_type::name} + std::string{"}"};
    } else if (std::is_same_v<typename token_type::super_type, epddl_basic_token_type> and m_lexeme != std::nullopt) {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{token_type::name} + std::string{":\""} + *m_lexeme + std::string{"\"}"};
    } else {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{token_type::lexeme} + std::string{"}"};
    }
#undef epddl_token_type
}

std::string lexer::to_string(token_ptr &tok) {
#define epddl_token_type(token_type) token_type
#define epddl_token(t_type, t_scope, t_name, t_lexeme) \
    if (const token_ptr_alias(t_type, t_name) *t =            \
        std::get_if<token_ptr_alias(t_type, t_name)>(&tok)) { \
        return (*t)->to_string();                             \
    }
#define tokens(tokens) tokens
#define epddl_tokens(_, tokens) tokens
    epddl_all_token_types_def
#undef epddl_tokens
#undef tokens
#undef epddl_token

    if (const special_token_eof_ptr *t = std::get_if<special_token_eof_ptr>(&tok)) { return (*t)->to_string(); }

#define epddl_token(t_type, t_scope, t_name, t_lexeme) t_type::t_name::name
    return std::string{epddl_tok_invalid};
#undef epddl_token
#undef epddl_token_type
}
