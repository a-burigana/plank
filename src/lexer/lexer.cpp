#include "../../include/lexer/lexer.h"
#include "../../include/error-manager/epddl_exception.h"
#include "../../include/traits.h"
#include <memory>

#define epddl_token_type(token_type) token_type

using namespace epddl;

lexer::lexer(std::ifstream &stream, const dictionary &dictionary) :
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
    return std::make_unique<token_variant>(token<token_type>{row, col, std::move(lexeme)});
}

token_ptr lexer::get_next_token() {
    if (eof())
        return make_token_ptr<epddl_special_token_type::eof>(m_input_row, m_input_col);

    bool has_ignored_spaces = false, has_ignored_comments = false;

    do {
        has_ignored_spaces = ignore_spaces();
        if (not m_stream.good())
            return make_token_ptr<epddl_special_token_type::eof>(m_input_row, m_input_col);

        has_ignored_comments = ignore_comments();
        if (not m_stream.good())
            return make_token_ptr<epddl_special_token_type::eof>(m_input_row, m_input_col);
    } while (has_ignored_spaces or has_ignored_comments);

    unsigned long t_row = m_input_row, t_col = m_input_col;
    char c = peek_next_char();

    if (c == ':' or c == '~')
        return scan_keyword();
    else if (c == '?')
        return scan_variable();
    else if (ispunct(c))
        return scan_punctuation();
    else if (isalpha(c) or c == '_')
        return scan_identifier();
    else if (isdigit(c))
        return scan_integer();
    else
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
}

token_ptr lexer::scan_keyword() {
    // Scanning regex :?[a-zA-Z-0-9\-]+
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    lexeme += get_next_char();       // Reading ':' or '~'

    while (m_stream.good() and is_keyword_char(peek_next_char()))
        lexeme += get_next_char();

    if (m_dictionary.is_valid_keyword(lexeme))
        return get_valid_keyword_token(lexeme, t_row, t_col);

    if (m_dictionary.is_valid_requirement(lexeme) or m_dictionary.is_valid_val_requirement(lexeme))
        return make_token_ptr<epddl_pattern_token_type::requirement>(t_row, t_col, std::move(lexeme));

    // A keyword identifier <K_ID> is invalid if one of these conditions hold:
    //  (1) <K_ID> is empty
    //  (2) <K_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)
    //  (3) <K_ID> is not a recognized EPDDL keyword

    bool empty_keyword_id = lexeme.length() == 1;   // empty_keyword == true iff lexeme == ":" or "~" iff lexeme.length() == 1

    if (empty_keyword_id)
        // CASE (1) If the keyword identifier is empty, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Expected keyword identifier."});

    // A keyword identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_keyword_id = isalpha(lexeme.at(1));

    if (not is_valid_keyword_id)
        // CASE (2) If the keyword identifier is not syntactically valid, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Invalid keyword identifier: "} + lexeme);
    else
        // CASE (3) If the keyword identifier is syntactically valid, but is not recognized, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Unknown keyword identifier: "} + lexeme);
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
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Invalid identifier: "} + lexeme);
    else
        return make_token_ptr<epddl_pattern_token_type::variable>(t_row, t_col, std::move(lexeme));
}

token_ptr lexer::scan_punctuation() {
    unsigned long t_row = m_input_row, t_col = m_input_col;

    switch (char c = peek_next_char(); c) {
        case '(':
            get_next_char();
                return make_token_ptr<epddl_punctuation_token_type::lpar>(t_row, t_col);
        case ')':
            get_next_char();
            return make_token_ptr<epddl_punctuation_token_type::rpar>(t_row, t_col);
        case '[':
            get_next_char();
            return make_token_ptr<epddl_punctuation_token_type::lbrack>(t_row, t_col);
        case ']':
            get_next_char();
            return make_token_ptr<epddl_punctuation_token_type::rbrack>(t_row, t_col);
        case '<':
            get_next_char();
            if (peek_next_char() == '-') {
                get_next_char();
                return make_token_ptr<epddl_punctuation_token_type::gets>(t_row, t_col);
            }
            return make_token_ptr<epddl_punctuation_token_type::langle>(t_row, t_col);
        case '>':
            get_next_char();
            return make_token_ptr<epddl_punctuation_token_type::rangle>(t_row, t_col);
        case '-':
            get_next_char();
            return make_token_ptr<epddl_punctuation_token_type::dash>(t_row, t_col);
        case '=':
            get_next_char();
            return make_token_ptr<epddl_punctuation_token_type::eq>(t_row, t_col);
        default:
            throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + c + std::string{"'."});
    }
}

token_ptr lexer::scan_identifier() {
    // Scanning regex [_a-zA-Z][_'a-zA-Z0-9]*
    unsigned long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    // We read the identifier
    while (m_stream.good() and is_ident_char(peek_next_char()))
        lexeme += get_next_char();

    if (m_dictionary.is_valid_keyword(lexeme))
        return get_valid_keyword_token(lexeme, t_row, t_col);
    else
        return make_token_ptr<epddl_pattern_token_type::identifier>(t_row, t_col, std::move(lexeme));
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
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Integer out fo range: "} + lexeme);
    }

    // An integer is syntactically valid iff it is not the case that it starts with '0' and its length is > 1
    bool is_valid_integer = not (lexeme.at(0) == '0' and lexeme.length() > 1);

    // A non-zero integer can not start with 0
    if (is_valid_integer)
        return make_token_ptr<epddl_pattern_token_type::integer>(t_row, t_col, std::move(lexeme));
    else
        // CASE (3) If the integer is not syntactically valid, we throw an error
        throw EPDDLLexerException(std::string{""}, t_row, t_col, std::string{"Invalid integer: "} + lexeme);
}

token_ptr lexer::get_valid_keyword_token(const std::string &lexeme, const unsigned long t_row, const unsigned long t_col) {
    #define epddl_token(t_type, t_scope, t_name, t_lexeme) \
    if (t_type::t_name::lexeme == lexeme) {                  \
        return make_token_ptr<t_type::t_name>(t_row, t_col); \
    }
    #define tokens(tokens) tokens
    #define epddl_tokens(_, tokens) tokens
    epddl_valid_keywords_def
    #undef epddl_tokens
    #undef tokens
    #undef epddl_token
    #undef token_type

    return make_token_ptr<epddl_special_token_type::invalid>(t_row, t_col);
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
    return isalnum(c) or c == '_' or c == '-' or c == '\'';
}

bool lexer::is_keyword_char(const char c) {
    return isalnum(c) or c == '-';
}

unsigned long lexer::get_row(const token_ptr &token) {
    return std::visit([](auto &&tok) { return tok.get_row(); }, *token);
}

unsigned long lexer::get_col(const token_ptr &token) {
    return std::visit([](auto &&tok) { return tok.get_col(); }, *token);
}

std::string lexer::get_lexeme(const token_ptr &token) {
    return std::visit([](auto &&tok) {
        using tok_type = get_argument_t<decltype(tok)>;

        if (std::is_same_v<typename tok_type::super_type, epddl_pattern_token_type> and tok.get_lexeme().has_value())
            return *tok.get_lexeme();
        else
            return std::string{get_argument_t<decltype(tok)>::lexeme};
    }, *token);
}

std::string lexer::get_name(const token_ptr &token) {
    return std::visit([](auto &&tok) { return std::string{get_argument_t<decltype(tok)>::name}; }, *token);
}

bool lexer::is_scope(const token_ptr& token) {
    return std::visit([](auto &&tok) { return get_argument_t<decltype(tok)>::is_scope; }, *token);
}

std::string lexer::to_string(const token_ptr &token) {
    return std::visit([&](auto &&tok) {
        using tok_type = get_argument_t<decltype(tok)>;
        const unsigned long row = lexer::get_row(token), col = lexer::get_col(token);

        if (std::is_same_v<get_super_t<tok_type>, epddl_punctuation_token_type>) {
            return std::string{"{"} + std::to_string(row) + std::string{":"} + std::to_string(col) + std::string{", "} + std::string{tok_type::name} + std::string{"}"};
        } else if (std::is_same_v<typename tok_type::super_type, epddl_pattern_token_type> and tok.get_lexeme().has_value()) {
            return std::string{"{"} + std::to_string(row) + std::string{":"} + std::to_string(col) + std::string{", "} + std::string{tok_type::name} + std::string{":\""} + *tok.get_lexeme() + std::string{"\"}"};
        } else {
            return std::string{"{"} + std::to_string(row) + std::string{":"} + std::to_string(col) + std::string{", "} + std::string{tok_type::lexeme} + std::string{"}"};
        }
    }, *token);
}

#undef epddl_token_type
