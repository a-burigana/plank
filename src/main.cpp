#include "../include/lexer/lexer.h"
#include "../include/error-manager/epddl_exception.h"
#include "../include/generators/ast/ast_gen.h"
#include "../include/parser/parser.h"
#include <iostream>
#include <string>

using namespace epddl;

int main() {
    std::string path = "../examples/domains/Coin-in-the-Box/cb.epddl";
//    std::string path = "../examples/domains/Collaboration-and-Communication/cc.epddl";
//    std::string path = "../examples/domains/Assemble/assemble.epddl";
    std::ifstream stream(path);

    ast::domain_ptr domain;

    if (stream.is_open()) {
        dictionary dictionary;
        lexer lex{stream, dictionary};
        parser parser{lex};

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
