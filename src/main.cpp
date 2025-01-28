#include "../include/lexer/lexer.h"
#include "../include/error-manager/epddl_exception.h"
#include "../include/generators/ast/ast_gen.h"
#include "../include/parser/parser_helper.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace epddl;

int main() {
    token_type type = punctuation_token::lpar{};
    assert(std::holds_alternative<punctuation_token::lpar>(type));

    std::string path = "../examples/domains/Coin-in-the-Box/cb.epddl";
//    std::string path = "../examples/domains/Collaboration-and-Communication/cc.epddl";
//    std::string path = "../examples/domains/Assemble/assemble.epddl";
    std::ifstream stream(path);

    ast::domain_ptr domain;

    if (stream.is_open()) {
        dictionary dictionary;
        lexer lex{std::move(stream), std::move(dictionary)};
        parser_helper parser{std::move(lex)};

        try {
            domain = std::move(parser.parse());
            std::cout << "Parsing successful.";
        } catch (EPDDLException &e) {
            std::cerr << e.what();
        }
    }

    stream.close();
    return 0;
}
