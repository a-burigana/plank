#include "lex.h"

lexer::lexer(std::ifstream stream, error_handler error) :
        m_stream{std::move(stream)},
        m_error{std::move(error)},
        m_current_char{'\0'},
        m_input_row{1},
        m_input_col{1},
        m_good{true},
        m_valid_keywords{std::map<std::string, token::type>{
                {":action",                         token::scope::action},
                {":action-type",                    token::scope::act_type},
                {":action-type-libraries",          token::scope::act_type_lib},
                {":agents",                         token::scope::agents},
                {":agent-groups",                   token::scope::agent_groups},
                {":designated",                     token::scope::designated},
                {":domain",                         token::scope::prob_domain},
                {":event",                          token::scope::event},
                {":events",                         token::scope::events},
                {":goal",                           token::scope::goal},
                {":init",                           token::scope::init},
                {":objects",                        token::scope::objects},
                {":observability-conditions",       token::scope::obs_conditions},
                {":observability-groups",           token::scope::obs_groups},
                {":modalities",                     token::scope::modalities},
                {":parameters",                     token::scope::parameters},
                {":postconditions",                 token::scope::postconditions},
                {":precondition",                   token::scope::precondition},
                {":predicates",                     token::scope::predicates},
                {":relations",                      token::scope::relations},
                {":requirements",                   token::scope::requirements},
                {":state",                          token::scope::state},
                {":state-name",                     token::scope::state_name},
                {":static",                         token::scope::static_preds},
                {":types",                          token::scope::types},
                {":valuation",                      token::scope::valuation},
                {":where",                          token::scope::where},
                {":worlds",                         token::scope::worlds},
                {"define",                           token::scope::define},
                {"domain",                          token::scope::domain},
                {"library",                         token::scope::library},
                {"problem",                         token::scope::problem},
                {"not",                             token::connective::unary::negation},
                {"imply",                           token::connective::binary::implication},
                {"and",                             token::connective::n_ary::conjunction},
                {"or",                              token::connective::n_ary::disjunction},
                {"exists",                          token::quantifier::exists},
                {"forall",                          token::quantifier::forall},
                {"false",                           token::atomic_formula::bot},
                {"true",                            token::atomic_formula::top},
                {"iff",                             token::postcondition::iff},
                {"when",                            token::postcondition::when},
                {"if",                              token::observability::if_cond},
                {"otherwise",                       token::observability::otherwise},
                {"agent",                           token::reserved_type::agent},
                {"formula",                         token::reserved_type::formula},
                {"literal",                         token::reserved_type::literal},
                {"postcondition",                   token::reserved_type::postcondition},
                {"predicate",                       token::reserved_type::predicate},
                {"predicate-formula",               token::reserved_type::predicate_formula},
                {"All",                             token::agents::all},
                {":common-knowledge",               token::requirement::ck},
                {":del",                            token::requirement::del},
                {":dynamic-common-knowledge",       token::requirement::dyn_ck},
                {":equality",                       token::requirement::eq},
                {":existential-formulae",           token::requirement::exist_form},
                {":finitary-S5-theory",              token::requirement::fin_s5_th},
                {":maximum-modal-depth",            token::requirement::max_depth},
                {":maximum-postconditions-depth",   token::requirement::max_pre_depth},
                {":maximum-preconditions-depth",    token::requirement::max_post_depth},
                {":modal-postconditions",           token::requirement::mod_post},
                {":modal-preconditions",            token::requirement::mod_pre},
                {":ontic-change",                   token::requirement::ontic},
                {":typing",                         token::requirement::typing},
                {":universal-formulae",             token::requirement::univ_form},
                {":universal-postconditions",       token::requirement::univ_post}
        }} {}

bool lexer::good() const {
    return m_good;
}

bool lexer::eof() const {
    return m_current_char == std::ifstream::traits_type::eof();
}

token lexer::get_next_token() {
    if (eof()) {
        return token{token::special::eof, m_input_row, m_input_col};
    }

    ignore_spaces();
    if (!m_stream.good()) {
        return token{token::special::eof, m_input_row, m_input_col};
    }

    ignore_comments();
    if (!m_stream.good()) {
        return token{token::special::eof, m_input_row, m_input_col};
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
        return token{token::special::invalid, t_row, t_col};
    }
}

token lexer::scan_keyword() {
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
        return token{token::special::invalid, t_row, t_col};
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
    return token{token::special::invalid, t_row, t_col};
}

token lexer::scan_variable() {
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
        return token{token::special::invalid, t_row, t_col};
    }

    // A variable identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_variable_id = isalpha(lexeme.at(1));

    if (!is_valid_variable_id) {
        // CASE (2) If the variable identifier is not syntactically valid, we throw an error
        m_error(t_row, t_col, std::string{"Invalid identifier: "} + lexeme);
        m_good = false;
        return token{token::special::invalid, t_row, t_col};
    } else {
        return token{token::basic::variable, std::move(lexeme), t_row, t_col};
    }
}

token lexer::scan_punctuation() {
    long t_row = m_input_row, t_col = m_input_col;

    switch (char c = peek_next_char(); c) {
        case '(':
            get_next_char();
            return token{token::punctuation::lpar, t_row, t_col};
        case ')':
            get_next_char();
            return token{token::punctuation::rpar, t_row, t_col};
        case '[':
            get_next_char();
            return token{token::punctuation::lbrack, t_row, t_col};
        case ']':
            get_next_char();
            return token{token::punctuation::rbrack, t_row, t_col};
        case '<':
            get_next_char();
            if (peek_next_char() == '-') {
                get_next_char();
                return token{token::punctuation::gets, t_row, t_col};
            }
            return token{token::punctuation::lt, t_row, t_col};
        case '>':
            get_next_char();
            return token{token::punctuation::gt, t_row, t_col};
        case '-':
            get_next_char();
            return token{token::punctuation::dash, t_row, t_col};
        case '=':
            get_next_char();
            return token{token::punctuation::eq, t_row, t_col};
        default:
            m_error(t_row, t_col, std::string{"Unexpected input character: '"} + c + std::string{"'."});
            m_good = false;
            return token{token::special::invalid, t_row, t_col};
    }
}

token lexer::scan_identifier() {
    // Scanning regex [_a-zA-Z][_'a-zA-Z0-9]*
    long t_row = m_input_row, t_col = m_input_col;
    token::basic type = token::basic::ident;
    std::string lexeme;

    // We read the identifier
    while (m_stream.good() && is_ident_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    if (peek_next_char() == '.') {
        type = token::basic::modality;
        lexeme += get_next_char();       // Reading '.'
    }

    if (type == token::basic::ident && is_valid_keyword(lexeme)) {
        return token{m_valid_keywords.find(lexeme)->second, t_row, t_col};
    } else {
        return token{type, std::move(lexeme), t_row, t_col};
    }
}

token lexer::scan_integer() {
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
        return token{token::special::invalid, t_row, t_col};
    }

    try {
        std::stoul(lexeme);
    } catch (const std::out_of_range& oor) {
        // CASE (2)
        m_error(t_row, t_col, std::string{"Integer out fo range: "} + lexeme);
        m_good = false;
        return token{token::special::invalid, t_row, t_col};
    }

    // An integer is syntactically valid iff it is not the case that it starts with '0' and its length is > 1
    bool is_valid_integer = !(lexeme.at(0) == '0' && lexeme.length() > 1);

    // A non-zero integer can not start with 0
    if (is_valid_integer) {
        return token{token::basic::integer, std::move(lexeme), t_row, t_col};
    } else {
        // CASE (3) If the integer is not syntactically valid, we throw an error
        m_error(t_row, t_col, std::string{"Invalid integer: "} + lexeme);
        m_good = false;
        return token{token::special::invalid, t_row, t_col};
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

std::string token::to_string() const {
    if (m_lexeme != std::nullopt) {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{","} + to_string(m_type) + std::string{","} + *m_lexeme + std::string{"}"};
    } else {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{","} + to_string(m_type) + std::string{"}"};
    }
}

std::string token::to_string(type t) {
    std::visit(overloaded {
        [](token::special            t_) { return token::to_string(t_); },
        [](token::punctuation        t_) { return token::to_string(t_); },
        [](token::basic              t_) { return token::to_string(t_);},
        [](token::reserved_type      t_) { return token::to_string(t_); },
        [](token::scope              t_) { return token::to_string(t_); },
        [](token::requirement        t_) { return token::to_string(t_); },
        [](token::connective::unary  t_) { return token::to_string(t_); },
        [](token::connective::binary t_) { return token::to_string(t_); },
        [](token::connective::n_ary  t_) { return token::to_string(t_); },
        [](token::quantifier          t_) { return token::to_string(t_); },
        [](token::atomic_formula     t_) { return token::to_string(t_); },
        [](token::postcondition      t_) { return token::to_string(t_); },
        [](token::observability      t_) { return token::to_string(t_); },
        [](token::agents             t_) { return token::to_string(t_); }
    }, t);
    return {};
}

std::string token::to_string(token::special t_) {
    switch (t_) {
        case token::special::eof:
            return "eof";
        case token::special::invalid:
            return "invalid";
    }
}

std::string token::to_string(token::punctuation t_) {
    switch (t_) {
        case punctuation::lpar:
            return "lpar";
        case punctuation::rpar:
            return "rpar";
        case punctuation::lbrack:
            return "lbrack";
        case punctuation::rbrack:
            return "rbrack";
        case punctuation::lt:
            return "lt";
        case punctuation::gt:
            return "gt";
        case punctuation::dash:
            return "dash";
        case punctuation::eq:
            return "eq";
        case punctuation::gets:
            return "gets";
    }
}

std::string token::to_string(token::basic t_) {
    switch (t_) {
        case basic::ident:
            return "ident";
        case basic::variable:
            return "variable";
        case basic::modality:
            return "modality";
        case basic::integer:
            return "integer";
    }
}

std::string token::to_string(token::scope t_) {
    switch (t_) {
        case scope::define:
            return "define";
        case scope::domain:
            return "domain";
        case scope::library:
            return "library";
        case scope::problem:
            return "problem";
        case scope::action:
            return "action";
        case scope::act_type:
            return "act_type";
        case scope::act_type_lib:
            return "act_type_lib";
        case scope::agents:
            return "agents";
        case scope::agent_groups:
            return "agent_groups";
        case scope::designated:
            return "designated";
        case scope::prob_domain:
            return "domain";
        case scope::event:
            return "event";
        case scope::events:
            return "events";
        case scope::goal:
            return "goal";
        case scope::init:
            return "init";
        case scope::objects:
            return "objects";
        case scope::obs_conditions:
            return "obs_conditions";
        case scope::obs_groups:
            return "obs_groups";
        case scope::modalities:
            return "modalities";
        case scope::parameters:
            return "parameters";
        case scope::postconditions:
            return "postconditions";
        case scope::precondition:
            return "precondition";
        case scope::predicates:
            return "predicates";
        case scope::relations:
            return "relations";
        case scope::requirements:
            return "requirements";
        case scope::state:
            return "state";
        case scope::state_name:
            return "state_name";
        case scope::static_preds:
            return "static";
        case scope::types:
            return "types";
        case scope::valuation:
            return "valuation";
        case scope::where:
            return "where";
        case scope::worlds:
            return "worlds";
    }
}

std::string token::to_string(token::connective::unary t_) {
    switch (t_) {
        case connective::unary::negation:
            return "negation";
    }
}

std::string token::to_string(token::connective::binary t_) {
    switch (t_) {
        case connective::binary::implication:
            return "implication";
    }
}

std::string token::to_string(token::connective::n_ary t_) {
    switch (t_) {
        case connective::n_ary::conjunction:
            return "conjunction";
        case connective::n_ary::disjunction:
            return "disjunction";
    }
}

std::string token::to_string(token::quantifier t_) {
    switch (t_) {
        case quantifier::exists:
            return "exists";
        case quantifier::forall:
            return "forall";
    }
}

std::string token::to_string(token::atomic_formula t_) {
    switch (t_) {
        case atomic_formula::bot:
            return "bot";
        case atomic_formula::top:
            return "top";
    }
}

std::string token::to_string(token::postcondition t_) {
    switch (t_) {
        case postcondition::iff:
            return "iff";
        case postcondition::when:
            return "when";
    }
}

std::string token::to_string(token::observability t_) {
    switch (t_) {
        case observability::if_cond:
            return "if_cond";
        case observability::otherwise:
            return "otherwise";
    }
}

std::string token::to_string(token::reserved_type t_) {
    switch (t_) {
        case reserved_type::agent:
            return "agent";
        case reserved_type::formula:
            return "formula";
        case reserved_type::literal:
            return "literal";
        case reserved_type::postcondition:
            return "postcondition";
        case reserved_type::predicate:
            return "predicate";
        case reserved_type::predicate_formula:
            return "predicate_formula";
    }
}

std::string token::to_string(token::agents t_) {
    switch (t_) {
        case agents::all:
            return "all";
    }
}

std::string token::to_string(token::requirement t_) {
    switch (t_) {
        case requirement::ck:
            return "ck";
        case requirement::del:
            return "del";
        case requirement::dyn_ck:
            return "dyn_ck";
        case requirement::eq:
            return "eq";
        case requirement::exist_form:
            return "exist_form";
        case requirement::fin_s5_th:
            return "fin_s5_th";
        case requirement::max_depth:
            return "max_depth";
        case requirement::max_pre_depth:
            return "max_pre_depth";
        case requirement::max_post_depth:
            return "max_post_depth";
        case requirement::mod_post:
            return "mod_post";
        case requirement::mod_pre:
            return "mod_pre";
        case requirement::ontic:
            return "ontic";
        case requirement::typing:
            return "typing";
        case requirement::univ_form:
            return "univ_form";
        case requirement::univ_post:
            return "univ_post";
    }
}
