#include "lex.h"

lexer::lexer(std::ifstream stream, error_handler error) :
        m_stream{std::move(stream)},
        m_error{std::move(error)},
        m_current_char{'\0'},
        m_input_row{1},
        m_input_col{1},
        m_good{true},
        m_valid_keywords{std::map<std::string, epddl_token::type>{
                {":action",                         epddl_token::scope::action},
                {":action-type",                    epddl_token::scope::act_type},
                {":action-type-libraries",          epddl_token::scope::act_type_lib},
                {":agents",                         epddl_token::scope::agents},
                {":agent-groups",                   epddl_token::scope::agent_groups},
                {":designated",                     epddl_token::scope::designated},
                {":domain",                         epddl_token::scope::prob_domain},
                {":event",                          epddl_token::scope::event},
                {":events",                         epddl_token::scope::events},
                {":goal",                           epddl_token::scope::goal},
                {":init",                           epddl_token::scope::init},
                {":objects",                        epddl_token::scope::objects},
                {":observability-conditions",       epddl_token::scope::obs_conditions},
                {":observability-groups",           epddl_token::scope::obs_groups},
                {":modalities",                     epddl_token::scope::modalities},
                {":parameters",                     epddl_token::scope::parameters},
                {":postconditions",                 epddl_token::scope::postconditions},
                {":precondition",                   epddl_token::scope::precondition},
                {":predicates",                     epddl_token::scope::predicates},
                {":relations",                      epddl_token::scope::relations},
                {":requirements",                   epddl_token::scope::requirements},
                {":state",                          epddl_token::scope::state},
                {":state-name",                     epddl_token::scope::state_name},
                {":static",                         epddl_token::scope::static_preds},
                {":types",                          epddl_token::scope::types},
                {":valuation",                      epddl_token::scope::valuation},
                {":where",                          epddl_token::scope::where},
                {":worlds",                         epddl_token::scope::worlds},
                {"define",                           epddl_token::scope::define},
                {"domain",                          epddl_token::scope::domain},
                {"library",                         epddl_token::scope::library},
                {"problem",                         epddl_token::scope::problem},
                {"not",                             epddl_token::connective::unary::negation},
                {"imply",                           epddl_token::connective::binary::implication},
                {"and",                             epddl_token::connective::n_ary::conjunction},
                {"or",                              epddl_token::connective::n_ary::disjunction},
                {"exists",                          epddl_token::quantifier::exists},
                {"forall",                          epddl_token::quantifier::forall},
                {"false",                           epddl_token::atomic_formula::bot},
                {"true",                            epddl_token::atomic_formula::top},
                {"iff",                             epddl_token::postcondition::iff},
                {"when",                            epddl_token::postcondition::when},
                {"if",                              epddl_token::observability::if_cond},
                {"otherwise",                       epddl_token::observability::otherwise},
                {"agent",                           epddl_token::reserved_type::agent},
                {"formula",                         epddl_token::reserved_type::formula},
                {"literal",                         epddl_token::reserved_type::literal},
                {"postcondition",                   epddl_token::reserved_type::postcondition},
                {"predicate",                       epddl_token::reserved_type::predicate},
                {"predicate-formula",               epddl_token::reserved_type::predicate_formula},
                {"All",                             epddl_token::agents::all},
                {":common-knowledge",               epddl_token::requirement::ck},
                {":del",                            epddl_token::requirement::del},
                {":dynamic-common-knowledge",       epddl_token::requirement::dyn_ck},
                {":equality",                       epddl_token::requirement::eq},
                {":existential-formulae",           epddl_token::requirement::exist_form},
                {":finitary-S5-theory",              epddl_token::requirement::fin_s5_th},
                {":maximum-modal-depth",            epddl_token::requirement::max_depth},
                {":maximum-postconditions-depth",   epddl_token::requirement::max_pre_depth},
                {":maximum-preconditions-depth",    epddl_token::requirement::max_post_depth},
                {":modal-postconditions",           epddl_token::requirement::mod_post},
                {":modal-preconditions",            epddl_token::requirement::mod_pre},
                {":ontic-change",                   epddl_token::requirement::ontic},
                {":typing",                         epddl_token::requirement::typing},
                {":universal-formulae",             epddl_token::requirement::univ_form},
                {":universal-postconditions",       epddl_token::requirement::univ_post}
        }} {}

bool lexer::good() const {
    return m_good;
}

bool lexer::eof() const {
    return m_current_char == std::ifstream::traits_type::eof();
}

token lexer::get_next_token() {
    if (eof()) {
        return token{epddl_token::special::eof, m_input_row, m_input_col};
    }

    ignore_spaces();
    if (!m_stream.good()) {
        return token{epddl_token::special::eof, m_input_row, m_input_col};
    }

    ignore_comments();
    if (!m_stream.good()) {
        return token{epddl_token::special::eof, m_input_row, m_input_col};
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
        return token{epddl_token::special::invalid, t_row, t_col};
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
        return token{epddl_token::special::invalid, t_row, t_col};
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
    return token{epddl_token::special::invalid, t_row, t_col};
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
        return token{epddl_token::special::invalid, t_row, t_col};
    }

    // A variable identifier is syntactically valid iff it starts with an alphabetic char
    bool is_valid_variable_id = isalpha(lexeme.at(1));

    if (!is_valid_variable_id) {
        // CASE (2) If the variable identifier is not syntactically valid, we throw an error
        m_error(t_row, t_col, std::string{"Invalid identifier: "} + lexeme);
        m_good = false;
        return token{epddl_token::special::invalid, t_row, t_col};
    } else {
        return token{epddl_token::basic::variable, std::move(lexeme), t_row, t_col};
    }
}

token lexer::scan_punctuation() {
    long t_row = m_input_row, t_col = m_input_col;

    switch (char c = peek_next_char(); c) {
        case '(':
            get_next_char();
            return token{epddl_token::punctuation::lpar, t_row, t_col};
        case ')':
            get_next_char();
            return token{epddl_token::punctuation::rpar, t_row, t_col};
        case '[':
            get_next_char();
            return token{epddl_token::punctuation::lbrack, t_row, t_col};
        case ']':
            get_next_char();
            return token{epddl_token::punctuation::rbrack, t_row, t_col};
        case '<':
            get_next_char();
            if (peek_next_char() == '-') {
                get_next_char();
                return token{epddl_token::punctuation::gets, t_row, t_col};
            }
            return token{epddl_token::punctuation::lt, t_row, t_col};
        case '>':
            get_next_char();
            return token{epddl_token::punctuation::gt, t_row, t_col};
        case '-':
            get_next_char();
            return token{epddl_token::punctuation::dash, t_row, t_col};
        case '=':
            get_next_char();
            return token{epddl_token::punctuation::eq, t_row, t_col};
        default:
            m_error(t_row, t_col, std::string{"Unexpected input character: '"} + c + std::string{"'."});
            m_good = false;
            return token{epddl_token::special::invalid, t_row, t_col};
    }
}

token lexer::scan_identifier() {
    // Scanning regex [_a-zA-Z][_'a-zA-Z0-9]*
    long t_row = m_input_row, t_col = m_input_col;
    epddl_token::basic type = epddl_token::basic::ident;
    std::string lexeme;

    // We read the identifier
    while (m_stream.good() && is_ident_char(peek_next_char())) {
        lexeme += get_next_char();
    }

    if (peek_next_char() == '.') {
        type = epddl_token::basic::modality;
        lexeme += get_next_char();       // Reading '.'
    }

    if (type == epddl_token::basic::ident && is_valid_keyword(lexeme)) {
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
        return token{epddl_token::special::invalid, t_row, t_col};
    }

    try {
        std::stoul(lexeme);
    } catch (const std::out_of_range& oor) {
        // CASE (2)
        m_error(t_row, t_col, std::string{"Integer out fo range: "} + lexeme);
        m_good = false;
        return token{epddl_token::special::invalid, t_row, t_col};
    }

    // An integer is syntactically valid iff it is not the case that it starts with '0' and its length is > 1
    bool is_valid_integer = !(lexeme.at(0) == '0' && lexeme.length() > 1);

    // A non-zero integer can not start with 0
    if (is_valid_integer) {
        return token{epddl_token::basic::integer, std::move(lexeme), t_row, t_col};
    } else {
        // CASE (3) If the integer is not syntactically valid, we throw an error
        m_error(t_row, t_col, std::string{"Invalid integer: "} + lexeme);
        m_good = false;
        return token{epddl_token::special::invalid, t_row, t_col};
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

std::string token::to_string(epddl_token::type t) {
    std::visit(overloaded {
        [](epddl_token::special            t_) { return to_string(t_); },
        [](epddl_token::punctuation        t_) { return to_string(t_); },
        [](epddl_token::basic              t_) { return to_string(t_);},
        [](epddl_token::reserved_type      t_) { return to_string(t_); },
        [](epddl_token::scope              t_) { return to_string(t_); },
        [](epddl_token::requirement        t_) { return to_string(t_); },
        [](epddl_token::connective::unary  t_) { return to_string(t_); },
        [](epddl_token::connective::binary t_) { return to_string(t_); },
        [](epddl_token::connective::n_ary  t_) { return to_string(t_); },
        [](epddl_token::quantifier          t_) { return to_string(t_); },
        [](epddl_token::atomic_formula     t_) { return to_string(t_); },
        [](epddl_token::postcondition      t_) { return to_string(t_); },
        [](epddl_token::observability      t_) { return to_string(t_); },
        [](epddl_token::agents             t_) { return to_string(t_); }
    }, t);
    return {};
}

std::string token::to_string(epddl_token::special t_) {
    switch (t_) {
        case epddl_token::special::eof:
            return "eof";
        case epddl_token::special::invalid:
            return "invalid";
    }
}

std::string token::to_string(epddl_token::punctuation t_) {
    switch (t_) {
        case epddl_token::punctuation::lpar:
            return "lpar";
        case epddl_token::punctuation::rpar:
            return "rpar";
        case epddl_token::punctuation::lbrack:
            return "lbrack";
        case epddl_token::punctuation::rbrack:
            return "rbrack";
        case epddl_token::punctuation::lt:
            return "lt";
        case epddl_token::punctuation::gt:
            return "gt";
        case epddl_token::punctuation::dash:
            return "dash";
        case epddl_token::punctuation::eq:
            return "eq";
        case epddl_token::punctuation::gets:
            return "gets";
    }
}

std::string token::to_string(epddl_token::basic t_) {
    switch (t_) {
        case epddl_token::basic::ident:
            return "ident";
        case epddl_token::basic::variable:
            return "variable";
        case epddl_token::basic::modality:
            return "modality";
        case epddl_token::basic::integer:
            return "integer";
    }
}

std::string token::to_string(epddl_token::scope t_) {
    switch (t_) {
        case epddl_token::scope::define:
            return "define";
        case epddl_token::scope::domain:
            return "domain";
        case epddl_token::scope::library:
            return "library";
        case epddl_token::scope::problem:
            return "problem";
        case epddl_token::scope::action:
            return "action";
        case epddl_token::scope::act_type:
            return "act_type";
        case epddl_token::scope::act_type_lib:
            return "act_type_lib";
        case epddl_token::scope::agents:
            return "agents";
        case epddl_token::scope::agent_groups:
            return "agent_groups";
        case epddl_token::scope::designated:
            return "designated";
        case epddl_token::scope::prob_domain:
            return "domain";
        case epddl_token::scope::event:
            return "event";
        case epddl_token::scope::events:
            return "events";
        case epddl_token::scope::goal:
            return "goal";
        case epddl_token::scope::init:
            return "init";
        case epddl_token::scope::objects:
            return "objects";
        case epddl_token::scope::obs_conditions:
            return "obs_conditions";
        case epddl_token::scope::obs_groups:
            return "obs_groups";
        case epddl_token::scope::modalities:
            return "modalities";
        case epddl_token::scope::parameters:
            return "parameters";
        case epddl_token::scope::postconditions:
            return "postconditions";
        case epddl_token::scope::precondition:
            return "precondition";
        case epddl_token::scope::predicates:
            return "predicates";
        case epddl_token::scope::relations:
            return "relations";
        case epddl_token::scope::requirements:
            return "requirements";
        case epddl_token::scope::state:
            return "state";
        case epddl_token::scope::state_name:
            return "state_name";
        case epddl_token::scope::static_preds:
            return "static";
        case epddl_token::scope::types:
            return "types";
        case epddl_token::scope::valuation:
            return "valuation";
        case epddl_token::scope::where:
            return "where";
        case epddl_token::scope::worlds:
            return "worlds";
    }
}

std::string token::to_string(epddl_token::connective::unary t_) {
    switch (t_) {
        case epddl_token::connective::unary::negation:
            return "negation";
    }
}

std::string token::to_string(epddl_token::connective::binary t_) {
    switch (t_) {
        case epddl_token::connective::binary::implication:
            return "implication";
    }
}

std::string token::to_string(epddl_token::connective::n_ary t_) {
    switch (t_) {
        case epddl_token::connective::n_ary::conjunction:
            return "conjunction";
        case epddl_token::connective::n_ary::disjunction:
            return "disjunction";
    }
}

std::string token::to_string(epddl_token::quantifier t_) {
    switch (t_) {
        case epddl_token::quantifier::exists:
            return "exists";
        case epddl_token::quantifier::forall:
            return "forall";
    }
}

std::string token::to_string(epddl_token::atomic_formula t_) {
    switch (t_) {
        case epddl_token::atomic_formula::bot:
            return "bot";
        case epddl_token::atomic_formula::top:
            return "top";
    }
}

std::string token::to_string(epddl_token::postcondition t_) {
    switch (t_) {
        case epddl_token::postcondition::iff:
            return "iff";
        case epddl_token::postcondition::when:
            return "when";
    }
}

std::string token::to_string(epddl_token::observability t_) {
    switch (t_) {
        case epddl_token::observability::if_cond:
            return "if_cond";
        case epddl_token::observability::otherwise:
            return "otherwise";
    }
}

std::string token::to_string(epddl_token::reserved_type t_) {
    switch (t_) {
        case epddl_token::reserved_type::agent:
            return "agent";
        case epddl_token::reserved_type::formula:
            return "formula";
        case epddl_token::reserved_type::literal:
            return "literal";
        case epddl_token::reserved_type::postcondition:
            return "postcondition";
        case epddl_token::reserved_type::predicate:
            return "predicate";
        case epddl_token::reserved_type::predicate_formula:
            return "predicate_formula";
    }
}

std::string token::to_string(epddl_token::agents t_) {
    switch (t_) {
        case epddl_token::agents::all:
            return "all";
    }
}

std::string token::to_string(epddl_token::requirement t_) {
    switch (t_) {
        case epddl_token::requirement::ck:
            return "ck";
        case epddl_token::requirement::del:
            return "del";
        case epddl_token::requirement::dyn_ck:
            return "dyn_ck";
        case epddl_token::requirement::eq:
            return "eq";
        case epddl_token::requirement::exist_form:
            return "exist_form";
        case epddl_token::requirement::fin_s5_th:
            return "fin_s5_th";
        case epddl_token::requirement::max_depth:
            return "max_depth";
        case epddl_token::requirement::max_pre_depth:
            return "max_pre_depth";
        case epddl_token::requirement::max_post_depth:
            return "max_post_depth";
        case epddl_token::requirement::mod_post:
            return "mod_post";
        case epddl_token::requirement::mod_pre:
            return "mod_pre";
        case epddl_token::requirement::ontic:
            return "ontic";
        case epddl_token::requirement::typing:
            return "typing";
        case epddl_token::requirement::univ_form:
            return "univ_form";
        case epddl_token::requirement::univ_post:
            return "univ_post";
    }
}
