#include "lex.h"

lexer::lexer(std::ifstream &stream, error_handler error) :
        m_stream(stream),
        m_error{std::move(error)},
        m_input_row(1),
        m_input_col(1),
        m_good(true),
        m_valid_keywords(std::map<std::string, token::type>{
                {":action",                         token::type::_BLOCK_ACT},
                {":action-type",                    token::type::_BLOCK_ACT_TYPE},
                {":action-type-libraries",          token::type::_BLOCK_ACT_TYPE_LIB},
                {":agents",                         token::type::_BLOCK_AGENTS},
                {":agent-groups",                   token::type::_BLOCK_AGENT_GROUPS},
                {":designated",                     token::type::_BLOCK_DESIGNATED},
                {":domain",                         token::type::_BLOCK_DOMAIN},
                {":event",                          token::type::_BLOCK_EVENT},
                {":events",                         token::type::_BLOCK_EVENTS},
                {":goal",                           token::type::_BLOCK_GOAL},
                {":init",                           token::type::_BLOCK_INIT},
                {":objects",                        token::type::_BLOCK_OBJECTS},
                {":observability-conditions",       token::type::_BLOCK_OBS_COND},
                {":observability-groups",           token::type::_BLOCK_OBS_GROUP},
                {":modalities",                     token::type::_BLOCK_MODALITIES},
                {":parameters",                     token::type::_BLOCK_PARAM},
                {":postconditions",                 token::type::_BLOCK_POSTCOND},
                {":precondition",                   token::type::_BLOCK_PRECOND},
                {":predicates",                     token::type::_BLOCK_PREDICATES},
                {":relations",                      token::type::_BLOCK_REL},
                {":requirements",                   token::type::_BLOCK_REQ},
                {":state",                          token::type::_BLOCK_STATE},
                {":state-name",                     token::type::_BLOCK_STATE_NAME},
                {":static",                         token::type::_BLOCK_STATIC},
                {":types",                          token::type::_BLOCK_TYPES},
                {":valuation",                      token::type::_BLOCK_VAL},
                {":where",                          token::type::_BLOCK_WHERE},
                {":worlds",                         token::type::_BLOCK_WORLDS},
                {"define",                           token::type::_EPDDL_DEF},
                {"domain",                          token::type::_EPDDL_DOM},
                {"library",                         token::type::_EPDDL_LIB},
                {"problem",                         token::type::_EPDDL_PROB},
                {"true",                            token::type::_FORM_TRUE},
                {"false",                           token::type::_FORM_FALSE},
                {"not",                             token::type::_FORM_NOT},
                {"and",                             token::type::_FORM_AND},
                {"or",                              token::type::_FORM_OR},
                {"imply",                           token::type::_FORM_IMPLY},
                {"exists",                          token::type::_FORM_EXISTS},
                {"forall",                          token::type::_FORM_FORALL},
                {"iff",                             token::type::_POST_IFF},
                {"when",                            token::type::_POST_WHEN},
                {"if",                              token::type::_OBS_IF},
                {"otherwise",                       token::type::_OBS_OTHERWISE},
                {"All",                             token::type::_AG_GROUP_ALL},
//                {"as",                              token::type::_AG_GROUP_AS},
                {"agent",                           token::type::_TYPE_AG},
                {"predicate",                       token::type::_TYPE_PRED},
                {"literal",                         token::type::_TYPE_LIT},
                {"predicate-formula",               token::type::_TYPE_PRED_FORM},
                {"formula",                         token::type::_TYPE_FORM},
                {"postcondition",                   token::type::_TYPE_POSTCOND},
                {":common-knowledge",               token::type::_REQ_CK},
                {":del",                            token::type::_REQ_DEL},
                {":dynamic-common-knowledge",       token::type::_REQ_DYN_CK},
                {":equality",                       token::type::_REQ_EQ},
                {":existential-formulae",           token::type::_REQ_EXIST_FORM},
                {":finitary-S5-theory",              token::type::_REQ_FIN_S5_TH},
                {":maximum-modal-depth",            token::type::_REQ_MAX_DEPTH},
                {":maximum-postconditions-depth",   token::type::_REQ_MAX_PRE_DEPTH},
                {":maximum-preconditions-depth",    token::type::_REQ_MAX_POST_DEPTH},
                {":modal-postconditions",           token::type::_REQ_MOD_POST},
                {":modal-preconditions",            token::type::_REQ_MOD_PRE},
                {":ontic-change",                   token::type::_REQ_ONTIC},
                {":typing",                         token::type::_REQ_TYPING},
                {":universal-formulae",             token::type::_REQ_UNIV_FORM},
                {":universal-postconditions",       token::type::_REQ_UNIV_POST}
        }) {}

bool lexer::good() const {
    return m_good;
}

bool lexer::eof() const {
    return peek_next_char() == std::ifstream::traits_type::eof();
}

std::optional<token> lexer::scan_next() {
    if (eof()) {
        return token{token::type::_EOF, m_input_row, m_input_col};
    }

    ignore_spaces();
    if (!m_stream.good()) {
        return token{token::type::_EOF, m_input_row, m_input_col};
    }

    ignore_comments();
    if (!m_stream.good()) {
        return token{token::type::_EOF, m_input_row, m_input_col};
    }

    long t_row = m_input_row, t_col = m_input_col;
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
        m_error(t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
        m_good = false;
        return token{token::type::_INVALID, t_row, t_col};
    }
}

std::optional<token> lexer::scan_keyword() {
    // Scanning regex :?[a-zA-Z-0-9\-]+
    long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    lexeme += get_next_char();       // Reading ':'

    while (m_stream.good() && is_keyword_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    if (is_valid_keyword(lexeme)) {
        return token{m_valid_keywords.find(lexeme)->second, t_row, t_col};
    }

    // A keyword identifier <K_ID> is invalid if one of these conditions hold:
    //  (1) <K_ID> is empty
    //  (2) <K_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)
    //  (3) <K_ID> is not a recognized EPDDL keyword

    // empty_keyword == true iff lexeme == ":" iff lexeme.length() == 1
    bool empty_keyword_id = lexeme.length() == 1;

    if (empty_keyword_id) {
        // CASE (1) If the keyword identifier is empty, we throw an error
        m_error(t_row, t_col, std::string{"Expected keyword identifier."});
        m_good = false;
        return token{token::type::_INVALID, t_row, t_col};
    }

    // A keyword identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_keyword_id = isalpha(lexeme.at(1));

    if (!is_valid_keyword_id) {
        // CASE (2) If the keyword identifier is not syntactically valid, we throw an error
        m_error(t_row, t_col, std::string{"Invalid keyword identifier: "} + lexeme);
    } else {
        // CASE (3) If the keyword identifier is syntactically valid, but is not recognized, we throw an error
        m_error(t_row, t_col, std::string{"Unknown keyword identifier: "} + lexeme);
    }
    m_good = false;
    return token{token::type::_INVALID, t_row, t_col};
}

std::optional<token> lexer::scan_variable() {
    // Scanning regex ?[_a-zA-Z][_'a-zA-Z0-9]*
    long t_row = m_input_row, t_col = m_input_col;
    std::string lexeme;

    lexeme += get_next_char();       // Reading '?'

    // We read the identifier
    while (m_stream.good() && is_ident_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    // A variable identifier <V_ID> is invalid if one of these conditions hold:
    //  (1) <V_ID> is empty
    //  (2) <V_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)

    // empty_variable == true iff lexeme == "?" iff lexeme.length() == 1
    bool empty_variable_id = lexeme.length() == 1;

    if (empty_variable_id) {
        // CASE (1) If the variable identifier is empty, we throw an error
        m_error(t_row, t_col, std::string{"Expected identifier."});
        m_good = false;
        return token{token::type::_INVALID, t_row, t_col};
    }

    // A variable identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_variable_id = isalpha(lexeme.at(1));

    if (!is_valid_variable_id) {
        // CASE (2) If the variable identifier is not syntactically valid, we throw an error
        m_error(t_row, t_col, std::string{"Invalid identifier: "} + lexeme);
        m_good = false;
        return token{token::type::_INVALID, t_row, t_col};
    } else {
        return token{token::type::_VAR, std::move(lexeme), t_row, t_col};
    }
}

std::optional<token> lexer::scan_punctuation() {
    long t_row = m_input_row, t_col = m_input_col;

    switch (char c = peek_next_char(); c) {
        case '(':
            get_next_char();
            return token{token::type::_LPAR, t_row, t_col};
        case ')':
            get_next_char();
            return token{token::type::_RPAR, t_row, t_col};
        case '[':
            get_next_char();
            return token{token::type::_LBRACK, t_row, t_col};
        case ']':
            get_next_char();
            return token{token::type::_RBRACK, t_row, t_col};
        case '{':
            get_next_char();
            return token{token::type::_LBRACE, t_row, t_col};
        case '}':
            get_next_char();
            return token{token::type::_RBRACE, t_row, t_col};
        case '<':
            get_next_char();

            if (peek_next_char() == '-') {
                get_next_char();
                return token{token::type::_GETS, t_row, t_col};
            }
            return token{token::type::_LT, t_row, t_col};
        case '>':
            get_next_char();
            return token{token::type::_GT, t_row, t_col};
        case '-':
            get_next_char();
            return token{token::type::_DASH, t_row, t_col};
        case '=':
            get_next_char();
            return token{token::type::_EQ, t_row, t_col};
        default:
            m_error(t_row, t_col, std::string{"Unexpected input character: '"} + c + std::string{"'."});
            m_good = false;
            return token{token::type::_INVALID, t_row, t_col};
    }
}

std::optional<token> lexer::scan_identifier() {
    // Scanning regex [_a-zA-Z][_'a-zA-Z0-9]*
    long t_row = m_input_row, t_col = m_input_col;
    token::type type = token::type::_IDENT;
    std::string lexeme;

    // We read the identifier
    while (m_stream.good() && is_ident_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    if (peek_next_char() == '.') {
        type = token::type::_FORM_MODALITY;
        lexeme += get_next_char();       // Reading '.'
    }

    if (type == token::type::_IDENT && is_valid_keyword(lexeme)) {
        return token{m_valid_keywords.find(lexeme)->second, t_row, t_col};
    } else {
        return token{type, std::move(lexeme), t_row, t_col};
    }
}

std::optional<token> lexer::scan_integer() {
    // Scanning regex [0-9]|[1-9][0-9]+
    long t_row = m_input_row, t_col = m_input_col;
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
        m_error(t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
        m_good = false;
        return token{token::type::_INVALID, t_row, t_col};
    }

    try {
        std::stoul(lexeme);
    } catch (const std::out_of_range& oor) {
        // CASE (2)
        m_error(t_row, t_col, std::string{"Integer out fo range: "} + lexeme);
        m_good = false;
        return token{token::type::_INVALID, t_row, t_col};
    }

    // An integer is syntactically valid iff it is not the case that it starts with '0' and its length is > 1
    bool is_valid_integer = !(lexeme.at(0) == '0' && lexeme.length() > 1);

    // A non-zero integer can not start with 0
    if (is_valid_integer) {
        return token{token::type::_INT, std::move(lexeme), t_row, t_col};
    } else {
        // CASE (3) If the integer is not syntactically valid, we throw an error
        m_error(t_row, t_col, std::string{"Invalid integer: "} + lexeme);
        m_good = false;
        return token{token::type::_INVALID, t_row, t_col};
    }
}

bool lexer::is_valid_keyword(const std::string& s) const {
    return m_valid_keywords.find(s) != m_valid_keywords.end();
}

void lexer::ignore_spaces() {
    char c = peek_next_char();

    while (m_stream.good() && isspace(c)) {
        get_next_char();
        c = peek_next_char();
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

char lexer::peek_next_char() const {
    return (char)m_stream.peek();
}

char lexer::get_next_char() {
    char c = (char)m_stream.get();

    if (c == '\n') {
        ++m_input_row;
        m_input_col = 1;
    } else {
        ++m_input_col;
    }

    return c;
}

bool lexer::is_ident_char(const char c) {
    return isalnum(c) || c == '_' || c == '\'';
}

bool lexer::is_keyword_char(const char c) {
    return isalnum(c) || c == '-';
}

std::string token::to_string() {
    if (m_lexeme != std::nullopt) {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{","} + to_string(m_type) + std::string{","} + *m_lexeme + std::string{"}"};
    } else {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{","} + to_string(m_type) + std::string{"}"};
    }
}

std::string token::to_string(type t) {
    switch (t) {
        case type::_EOF:
            return "_EOF";
        case type::_INVALID:
            return "_INVALID";
        case type::_LPAR:
            return "_LPAR";
        case type::_RPAR:
            return "_RPAR";
        case type::_LBRACK:
            return "_LBRACK";
        case type::_RBRACK:
            return "_RBRACK";
        case type::_LBRACE:
            return "_LBRACE";
        case type::_RBRACE:
            return "_RBRACE";
        case type::_LT:
            return "_LT";
        case type::_GT:
            return "_GT";
        case type::_DASH:
            return "_DASH";
        case type::_EQ:
            return "_EQ";
//        case type::_COLON:
//            return "_COLON";
        case type::_GETS:
            return "_GETS";
        case type::_IDENT:
            return "_IDENT";
        case type::_VAR:
            return "_VAR";
        case type::_INT:
            return "_INT";
        case type::_FORM_MODALITY:
            return "_FORM_MODALITY";
        case type::_BLOCK_ACT:
            return "_BLOCK_ACT";
        case type::_BLOCK_ACT_TYPE:
            return "_BLOCK_ACT_TYPE";
        case type::_BLOCK_ACT_TYPE_LIB:
            return "_BLOCK_ACT_TYPE_LIB";
        case type::_BLOCK_AGENTS:
            return "_BLOCK_AGENTS";
        case type::_BLOCK_AGENT_GROUPS:
            return "_BLOCK_AGENT_GROUPS";
        case type::_BLOCK_DESIGNATED:
            return "_BLOCK_DESIGNATED";
        case type::_BLOCK_DOMAIN:
            return "_BLOCK_DOMAIN";
        case type::_BLOCK_EVENT:
            return "_BLOCK_EVENT";
        case type::_BLOCK_EVENTS:
            return "_BLOCK_EVENTS";
        case type::_BLOCK_GOAL:
            return "_BLOCK_GOAL";
        case type::_BLOCK_INIT:
            return "_BLOCK_INIT";
        case type::_BLOCK_OBJECTS:
            return "_BLOCK_OBJECTS";
        case type::_BLOCK_OBS_COND:
            return "_BLOCK_OBS_COND";
        case type::_BLOCK_OBS_GROUP:
            return "_BLOCK_OBS_GROUP";
        case type::_BLOCK_MODALITIES:
            return "_BLOCK_MODALITIES";
        case type::_BLOCK_PARAM:
            return "_BLOCK_PARAM";
        case type::_BLOCK_POSTCOND:
            return "_BLOCK_POSTCOND";
        case type::_BLOCK_PRECOND:
            return "_BLOCK_PRECOND";
        case type::_BLOCK_PREDICATES:
            return "_BLOCK_PREDICATES";
        case type::_BLOCK_REL:
            return "_BLOCK_REL";
        case type::_BLOCK_REQ:
            return "_BLOCK_REQ";
        case type::_BLOCK_STATE:
            return "_BLOCK_STATE";
        case type::_BLOCK_STATE_NAME:
            return "_BLOCK_STATE_NAME";
        case type::_BLOCK_STATIC:
            return "_BLOCK_STATIC";
        case type::_BLOCK_TYPES:
            return "_BLOCK_TYPES";
        case type::_BLOCK_VAL:
            return "_BLOCK_VAL";
        case type::_BLOCK_WHERE:
            return "_BLOCK_WHERE";
        case type::_BLOCK_WORLDS:
            return "_BLOCK_WORLDS";
        case type::_EPDDL_DEF:
            return "_EPDDL_DEF";
        case type::_EPDDL_DOM:
            return "_EPDDL_DOM";
        case type::_EPDDL_LIB:
            return "_EPDDL_LIB";
        case type::_EPDDL_PROB:
            return "_EPDDL_PROB";
        case type::_FORM_TRUE:
            return "_FORM_TRUE";
        case type::_FORM_FALSE:
            return "_FORM_FALSE";
        case type::_FORM_NOT:
            return "_FORM_NOT";
        case type::_FORM_AND:
            return "_FORM_AND";
        case type::_FORM_OR:
            return "_FORM_OR";
        case type::_FORM_IMPLY:
            return "_FORM_IMPLY";
        case type::_FORM_EXISTS:
            return "_FORM_EXISTS";
        case type::_FORM_FORALL:
            return "_FORM_FORALL";
        case type::_POST_IFF:
            return "_POST_IFF";
        case type::_POST_WHEN:
            return "_POST_WHEN";
        case type::_OBS_IF:
            return "_OBS_IF";
        case type::_OBS_OTHERWISE:
            return "_OBS_OTHERWISE";
        case type::_AG_GROUP_ALL:
            return "_AG_GROUP_ALL";
//        case type::_AG_GROUP_AS:
//            return "_AG_GROUP_AS";
        case type::_TYPE_AG:
            return "_TYPE_AG";
        case type::_TYPE_PRED:
            return "_TYPE_PRED";
        case type::_TYPE_LIT:
            return "_TYPE_LIT";
        case type::_TYPE_PRED_FORM:
            return "_TYPE_PRED_FORM";
        case type::_TYPE_FORM:
            return "_TYPE_FORM";
        case type::_TYPE_POSTCOND:
            return "_TYPE_POSTCOND";
        case type::_REQ_CK:
            return "_REQ_CK";
        case type::_REQ_DEL:
            return "_REQ_DEL";
        case type::_REQ_DYN_CK:
            return "_REQ_DYN_CK";
        case type::_REQ_EQ:
            return "_REQ_EQ";
        case type::_REQ_EXIST_FORM:
            return "_REQ_EXIST_FORM";
        case type::_REQ_FIN_S5_TH:
            return "_REQ_FIN_S5_TH";
        case type::_REQ_MAX_DEPTH:
            return "_REQ_MAX_DEPTH";
        case type::_REQ_MAX_PRE_DEPTH:
            return "_REQ_MAX_PRE_DEPTH";
        case type::_REQ_MAX_POST_DEPTH:
            return "_REQ_MAX_POST_DEPTH";
        case type::_REQ_MOD_POST:
            return "_REQ_MOD_POST";
        case type::_REQ_MOD_PRE:
            return "_REQ_MOD_PRE";
        case type::_REQ_ONTIC:
            return "_REQ_ONTIC";
        case type::_REQ_TYPING:
            return "_REQ_TYPING";
        case type::_REQ_UNIV_FORM:
            return "_REQ_UNIV_FORM";
        case type::_REQ_UNIV_POST:
            return "_REQ_UNIV_POST";
        default:
            return "";
    }
}
