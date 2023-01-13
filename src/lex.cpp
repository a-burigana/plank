#include "../include/lex.h"
#include "../include/epddl_exception.h"

using namespace epddl;

lexer::lexer(std::ifstream stream) :
        m_stream{std::move(stream)},
        m_current_char{'\0'},
        m_input_row{1},
        m_input_col{1},
        m_good{true},
        m_valid_keywords{std::map<std::string, utils::token::type>{
                {":action",                         utils::token::keyword::action},
                {":action-type",                    utils::token::keyword::act_type},
                {":action-type-libraries",          utils::token::keyword::act_type_lib},
                {":agents",                         utils::token::keyword::agents},
                {":agent-groups",                   utils::token::keyword::agent_groups},
                {":designated",                     utils::token::keyword::designated},
                {":domain",                         utils::token::keyword::prob_domain},
                {":event",                          utils::token::keyword::event},
                {":events",                         utils::token::keyword::events},
                {":goal",                           utils::token::keyword::goal},
                {":init",                           utils::token::keyword::init},
                {":objects",                        utils::token::keyword::objects},
                {":observability-conditions",       utils::token::keyword::obs_conditions},
                {":observability-groups",           utils::token::keyword::obs_groups},
                {":modalities",                     utils::token::keyword::modalities},
                {":parameters",                     utils::token::keyword::parameters},
                {":postconditions",                 utils::token::keyword::postconditions},
                {":precondition",                   utils::token::keyword::precondition},
                {":predicates",                     utils::token::keyword::predicates},
                {":relations",                      utils::token::keyword::relations},
                {":requirements",                   utils::token::keyword::requirements},
                {":state",                          utils::token::keyword::state},
                {":state-name",                     utils::token::keyword::state_name},
                {":static",                         utils::token::keyword::static_preds},
                {":types",                          utils::token::keyword::types},
                {":valuation",                      utils::token::keyword::valuation},
                {":where",                          utils::token::keyword::where},
                {":worlds",                         utils::token::keyword::worlds},
                {"define",                           utils::token::keyword::define},
                {"domain",                          utils::token::keyword::domain},
                {"library",                         utils::token::keyword::library},
                {"problem",                         utils::token::keyword::problem},
                {"not",                             utils::token::connective::unary::negation},
                {"imply",                           utils::token::connective::binary::implication},
                {"and",                             utils::token::connective::n_ary::conjunction},
                {"or",                              utils::token::connective::n_ary::disjunction},
                {"exists",                          utils::token::quantifier::exists},
                {"forall",                          utils::token::quantifier::forall},
                {"false",                           utils::token::atomic_formula::bot},
                {"true",                            utils::token::atomic_formula::top},
                {"iff",                             utils::token::postcondition::iff},
                {"when",                            utils::token::postcondition::when},
                {"if",                              utils::token::observability::if_cond},
                {"otherwise",                       utils::token::observability::otherwise},
                {"agent",                           utils::token::reserved_type::agent},
                {"formula",                         utils::token::reserved_type::formula},
                {"literal",                         utils::token::reserved_type::literal},
                {"postcondition",                   utils::token::reserved_type::postcondition},
                {"predicate",                       utils::token::reserved_type::predicate},
                {"predicate-formula",               utils::token::reserved_type::predicate_formula},
                {"All",                             utils::token::agents::all},
                {":common-knowledge",               utils::token::requirement::ck},
                {":del",                            utils::token::requirement::del},
                {":dynamic-common-knowledge",       utils::token::requirement::dyn_ck},
                {":equality",                       utils::token::requirement::eq},
                {":existential-formulae",           utils::token::requirement::exist_form},
                {":finitary-S5-theory",              utils::token::requirement::fin_s5_th},
                {":maximum-modal-depth",            utils::token::requirement::max_depth},
                {":maximum-postconditions-depth",   utils::token::requirement::max_pre_depth},
                {":maximum-preconditions-depth",    utils::token::requirement::max_post_depth},
                {":modal-postconditions",           utils::token::requirement::mod_post},
                {":modal-preconditions",            utils::token::requirement::mod_pre},
                {":ontic-change",                   utils::token::requirement::ontic},
                {":typing",                         utils::token::requirement::typing},
                {":universal-formulae",             utils::token::requirement::univ_form},
                {":universal-postconditions",       utils::token::requirement::univ_post}
        }} {}

bool lexer::good() const {
    return m_good;
}

bool lexer::eof() const {
    return m_current_char == std::ifstream::traits_type::eof();
}

Token lexer::get_next_token() {
    if (eof()) {
        return Token{m_input_row, m_input_col, utils::token::special::eof};
    }

    ignore_spaces();
    if (!m_stream.good()) {
        return Token{m_input_row, m_input_col, utils::token::special::eof};
    }

    ignore_comments();
    if (!m_stream.good()) {
        return Token{m_input_row, m_input_col, utils::token::special::eof};
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
//        m_error(t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
//        m_good = false;
//        return Token{t_row, t_col, utils::token::special::invalid};
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

    if (is_valid_keyword(lexeme)) {
        return Token{t_row, t_col, m_valid_keywords.find(lexeme)->second};
    }

    // A keyword identifier <K_ID> is invalid if one of these conditions hold:
    //  (1) <K_ID> is empty
    //  (2) <K_ID> does not start with an alphabetic char (i.e., it is syntactically invalid)
    //  (3) <K_ID> is not a recognized EPDDL keyword

    // empty_keyword == true iff lexeme == ":" iff lexeme.length() == 1
    bool empty_keyword_id = lexeme.length() == 1;

    if (empty_keyword_id) {
        // CASE (1) If the keyword identifier is empty, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Expected keyword identifier."});
//        m_error(t_row, t_col, std::string{"Expected keyword identifier."});
//        m_good = false;
//        return Token{t_row, t_col, utils::token::special::invalid};
    }

    // A keyword identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_keyword_id = isalpha(lexeme.at(1));

    if (!is_valid_keyword_id) {
        // CASE (2) If the keyword identifier is not syntactically valid, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Invalid keyword identifier: "} + lexeme);
//        m_error(t_row, t_col, std::string{"Invalid keyword identifier: "} + lexeme);
    } else {
        // CASE (3) If the keyword identifier is syntactically valid, but is not recognized, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unknown keyword identifier: "} + lexeme);
//        m_error(t_row, t_col, std::string{"Unknown keyword identifier: "} + lexeme);
    }
//    m_good = false;
//    return Token{t_row, t_col, utils::token::special::invalid};
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

    // empty_variable == true iff lexeme == "?" iff lexeme.length() == 1
    bool empty_variable_id = lexeme.length() == 1;

    if (empty_variable_id) {
        // CASE (1) If the variable identifier is empty, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Expected variable identifier."});
//        m_error(t_row, t_col, std::string{"Expected variable identifier."});
//        m_good = false;
//        return Token{t_row, t_col, utils::token::special::invalid};
    }

    // A variable identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_variable_id = isalpha(lexeme.at(1));

    if (!is_valid_variable_id) {
        // CASE (2) If the variable identifier is not syntactically valid, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Invalid identifier: "} + lexeme);
//        m_error(t_row, t_col, std::string{"Invalid identifier: "} + lexeme);
//        m_good = false;
//        return Token{t_row, t_col, utils::token::special::invalid};
    } else {
        return Token{t_row, t_col, utils::token::basic::variable, std::move(lexeme)};
    }
}

Token lexer::scan_punctuation() {
    unsigned long t_row = m_input_row, t_col = m_input_col;

    switch (char c = peek_next_char(); c) {
        case '(':
            get_next_char();
            return Token{t_row, t_col, utils::token::punctuation::lpar};
        case ')':
            get_next_char();
            return Token{t_row, t_col, utils::token::punctuation::rpar};
        case '[':
            get_next_char();
            return Token{t_row, t_col, utils::token::punctuation::lbrack};
        case ']':
            get_next_char();
            return Token{t_row, t_col, utils::token::punctuation::rbrack};
        case '<':
            get_next_char();
            if (peek_next_char() == '-') {
                get_next_char();
                return Token{t_row, t_col, utils::token::punctuation::gets};
            }
            return Token{t_row, t_col, utils::token::punctuation::lt};
        case '>':
            get_next_char();
            return Token{t_row, t_col, utils::token::punctuation::gt};
        case '-':
            get_next_char();
            return Token{t_row, t_col, utils::token::punctuation::dash};
        case '=':
            get_next_char();
            return Token{t_row, t_col, utils::token::punctuation::eq};
        default:
            throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Unexpected input character: '"} + c + std::string{"'."});
//            m_error(t_row, t_col, std::string{"Unexpected input character: '"} + c + std::string{"'."});
//            m_good = false;
//            return Token{t_row, t_col, utils::token::special::invalid};
    }
}

Token lexer::scan_identifier() {
    // Scanning regex [_a-zA-Z][_'a-zA-Z0-9]*
    unsigned long t_row = m_input_row, t_col = m_input_col;
    utils::token::basic type = utils::token::basic::ident;
    std::string lexeme;

    // We read the identifier
    while (m_stream.good() && is_ident_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    if (peek_next_char() == '.') {
        type = utils::token::basic::modality;
        lexeme += get_next_char();       // Reading '.'
    }

    if (type == utils::token::basic::ident && is_valid_keyword(lexeme)) {
        return Token{t_row, t_col, m_valid_keywords.find(lexeme)->second};
    } else {
        return Token{t_row, t_col, type, std::move(lexeme)};
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
//        m_error(t_row, t_col, std::string{"Unexpected input character: '"} + peek_next_char() + std::string{"'."});
//        m_good = false;
//        return Token{t_row, t_col, utils::token::special::invalid};
    }

    try {
        std::stoul(lexeme);
    } catch (const std::out_of_range& oor) {
        // CASE (2)
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Integer out fo range: "} + lexeme);
//        m_error(t_row, t_col, std::string{"Integer out fo range: "} + lexeme);
//        m_good = false;
//        return Token{t_row, t_col, utils::token::special::invalid};
    }

    // An integer is syntactically valid iff it is not the case that it starts with '0' and its length is > 1
    bool is_valid_integer = !(lexeme.at(0) == '0' && lexeme.length() > 1);

    // A non-zero integer can not start with 0
    if (is_valid_integer) {
        return Token{t_row, t_col, utils::token::basic::integer, std::move(lexeme)};
    } else {
        // CASE (3) If the integer is not syntactically valid, we throw an error
        throw EPDDLException(std::string{""}, t_row, t_col, std::string{"Invalid integer: "} + lexeme);
//        m_error(t_row, t_col, std::string{"Invalid integer: "} + lexeme);
//        m_good = false;
//        return Token{t_row, t_col, utils::token::special::invalid};
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

std::string Token::to_string() const {
    if (m_lexeme != std::nullopt) {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{","} + to_string(m_type) + std::string{","} + *m_lexeme + std::string{"}"};
    } else {
        return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{","} + to_string(m_type) + std::string{"}"};
    }
}

std::string Token::to_string(utils::token::type t) {
    std::visit(overloaded {
        [](utils::token::special            t_) { return to_string(t_); },
        [](utils::token::punctuation        t_) { return to_string(t_); },
        [](utils::token::basic              t_) { return to_string(t_);},
        [](utils::token::reserved_type      t_) { return to_string(t_); },
        [](utils::token::keyword            t_) { return to_string(t_); },
        [](utils::token::requirement        t_) { return to_string(t_); },
        [](utils::token::connective::unary  t_) { return to_string(t_); },
        [](utils::token::connective::binary t_) { return to_string(t_); },
        [](utils::token::connective::n_ary  t_) { return to_string(t_); },
        [](utils::token::quantifier          t_) { return to_string(t_); },
        [](utils::token::atomic_formula     t_) { return to_string(t_); },
        [](utils::token::postcondition      t_) { return to_string(t_); },
        [](utils::token::observability      t_) { return to_string(t_); },
        [](utils::token::agents             t_) { return to_string(t_); }
    }, t);
    return {};
}

std::string Token::to_string(utils::token::special t_) {
    switch (t_) {
        case utils::token::special::eof:
            return "eof";
        case utils::token::special::invalid:
            return "invalid";
    }
}

std::string Token::to_string(utils::token::punctuation t_) {
    switch (t_) {
        case utils::token::punctuation::lpar:
            return "lpar";
        case utils::token::punctuation::rpar:
            return "rpar";
        case utils::token::punctuation::lbrack:
            return "lbrack";
        case utils::token::punctuation::rbrack:
            return "rbrack";
        case utils::token::punctuation::lt:
            return "lt";
        case utils::token::punctuation::gt:
            return "gt";
        case utils::token::punctuation::dash:
            return "dash";
        case utils::token::punctuation::eq:
            return "eq";
        case utils::token::punctuation::gets:
            return "gets";
    }
}

std::string Token::to_string(utils::token::basic t_) {
    switch (t_) {
        case utils::token::basic::ident:
            return "ident";
        case utils::token::basic::variable:
            return "variable";
        case utils::token::basic::modality:
            return "modality";
        case utils::token::basic::integer:
            return "integer";
    }
}

std::string Token::to_string(utils::token::keyword t_) {
    switch (t_) {
        case utils::token::keyword::define:
            return "define";
        case utils::token::keyword::domain:
            return "domain";
        case utils::token::keyword::library:
            return "library";
        case utils::token::keyword::problem:
            return "problem";
        case utils::token::keyword::action:
            return "action";
        case utils::token::keyword::act_type:
            return "act_type";
        case utils::token::keyword::act_type_lib:
            return "act_type_lib";
        case utils::token::keyword::agents:
            return "agents";
        case utils::token::keyword::agent_groups:
            return "agent_groups";
        case utils::token::keyword::designated:
            return "designated";
        case utils::token::keyword::prob_domain:
            return "domain";
        case utils::token::keyword::event:
            return "event";
        case utils::token::keyword::events:
            return "events";
        case utils::token::keyword::goal:
            return "goal";
        case utils::token::keyword::init:
            return "init";
        case utils::token::keyword::objects:
            return "objects";
        case utils::token::keyword::obs_conditions:
            return "obs_conditions";
        case utils::token::keyword::obs_groups:
            return "obs_groups";
        case utils::token::keyword::modalities:
            return "modalities";
        case utils::token::keyword::parameters:
            return "parameters";
        case utils::token::keyword::postconditions:
            return "postconditions";
        case utils::token::keyword::precondition:
            return "precondition";
        case utils::token::keyword::predicates:
            return "predicates";
        case utils::token::keyword::relations:
            return "relations";
        case utils::token::keyword::requirements:
            return "requirements";
        case utils::token::keyword::state:
            return "state";
        case utils::token::keyword::state_name:
            return "state_name";
        case utils::token::keyword::static_preds:
            return "static";
        case utils::token::keyword::types:
            return "types";
        case utils::token::keyword::valuation:
            return "valuation";
        case utils::token::keyword::where:
            return "where";
        case utils::token::keyword::worlds:
            return "worlds";
    }
}

std::string Token::to_string(utils::token::connective::unary t_) {
    switch (t_) {
        case utils::token::connective::unary::negation:
            return "negation";
    }
}

std::string Token::to_string(utils::token::connective::binary t_) {
    switch (t_) {
        case utils::token::connective::binary::implication:
            return "implication";
    }
}

std::string Token::to_string(utils::token::connective::n_ary t_) {
    switch (t_) {
        case utils::token::connective::n_ary::conjunction:
            return "conjunction";
        case utils::token::connective::n_ary::disjunction:
            return "disjunction";
    }
}

std::string Token::to_string(utils::token::quantifier t_) {
    switch (t_) {
        case utils::token::quantifier::exists:
            return "exists";
        case utils::token::quantifier::forall:
            return "forall";
    }
}

std::string Token::to_string(utils::token::atomic_formula t_) {
    switch (t_) {
        case utils::token::atomic_formula::bot:
            return "bot";
        case utils::token::atomic_formula::top:
            return "top";
    }
}

std::string Token::to_string(utils::token::postcondition t_) {
    switch (t_) {
        case utils::token::postcondition::iff:
            return "iff";
        case utils::token::postcondition::when:
            return "when";
    }
}

std::string Token::to_string(utils::token::observability t_) {
    switch (t_) {
        case utils::token::observability::if_cond:
            return "if_cond";
        case utils::token::observability::otherwise:
            return "otherwise";
    }
}

std::string Token::to_string(utils::token::reserved_type t_) {
    switch (t_) {
        case utils::token::reserved_type::agent:
            return "agent";
        case utils::token::reserved_type::formula:
            return "formula";
        case utils::token::reserved_type::literal:
            return "literal";
        case utils::token::reserved_type::object:
            return "object";
        case utils::token::reserved_type::postcondition:
            return "postcondition";
        case utils::token::reserved_type::predicate:
            return "predicate";
        case utils::token::reserved_type::predicate_formula:
            return "predicate_formula";
    }
}

std::string Token::to_string(utils::token::agents t_) {
    switch (t_) {
        case utils::token::agents::all:
            return "All";
    }
}

std::string Token::to_string(utils::token::requirement t_) {
    switch (t_) {
        case utils::token::requirement::ck:
            return "ck";
        case utils::token::requirement::del:
            return "del";
        case utils::token::requirement::dyn_ck:
            return "dyn_ck";
        case utils::token::requirement::eq:
            return "eq";
        case utils::token::requirement::exist_form:
            return "exist_form";
        case utils::token::requirement::fin_s5_th:
            return "fin_s5_th";
        case utils::token::requirement::max_depth:
            return "max_depth";
        case utils::token::requirement::max_pre_depth:
            return "max_pre_depth";
        case utils::token::requirement::max_post_depth:
            return "max_post_depth";
        case utils::token::requirement::mod_post:
            return "mod_post";
        case utils::token::requirement::mod_pre:
            return "mod_pre";
        case utils::token::requirement::ontic:
            return "ontic";
        case utils::token::requirement::typing:
            return "typing";
        case utils::token::requirement::univ_form:
            return "univ_form";
        case utils::token::requirement::univ_post:
            return "univ_post";
    }
}
