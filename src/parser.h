#ifndef EPDDL_PARSER_H
#define EPDDL_PARSER_H

#include "ast.h"
#include "lex.h"

class parser {
public:
    using error_handler = std::function<void(long, long, std::string)>;

    explicit parser(lexer lex, error_handler error);
    ~parser();

    void get_next_token();

private:
    lexer m_lex;
    error_handler m_error;
    std::optional<token> m_tok;
};


#endif //EPDDL_PARSER_H
