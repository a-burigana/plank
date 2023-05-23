#include "../include/lex/lex.h"
#include "../include/epddl_exception.h"
#include "../include/generators/ast/ast_gen.h"
#include "../include/parser/parser.h"
#include <iostream>
//#include <memory>
//#include <ostream>
#include <string>

using namespace epddl;

int main() {
    std::string path = "../examples/test.epddl";
    std::ifstream stream(path);

    if (stream.is_open()) {
        dictionary dictionary;
        lexer lex{stream, dictionary};
        parser parser{lex};

        try {
            ast::domain_ptr domain = std::move(parser.parse());
            int x = 0;
//            while (!lex.eof() && lex.good()) {
//                token_ptr tok = lex.get_next_token();
//                std::cout << epddl::lexer::to_string(tok) << std::endl;
//            }
        } catch (EPDDLException &e) {
            std::cerr << e.what();
        }
    }

    stream.close();
    return 0;
}
