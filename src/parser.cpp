#include "parser.h"

#include <utility>

parser::parser(lexer lex, error_handler error) :
    m_lex(std::move(lex)),
    m_error(std::move(error)),
    m_tok(std::nullopt) {}

parser::~parser() = default;

void parser::get_next_token() {
    m_tok = m_lex.scan_next();
}
