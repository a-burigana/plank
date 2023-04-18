#include "../include/lex/lex.h"
#include "../include/epddl_exception.h"
#include <iostream>
#include <string>

using namespace epddl;

int main() {
    std::string path = "../examples/test.epddl";
    std::ifstream stream(path);

    if (stream.is_open()) {
        dictionary dictionary;
        lexer lex{stream, dictionary};

        try {
            while (!lex.eof() && lex.good()) {
                token_ptr tok = lex.get_next_token();
                std::cout << epddl::lexer::to_string(tok) << std::endl;
            }
        } catch (EPDDLException &e) {
            std::cerr << e.what();
        }
    }

    stream.close();
    return 0;
}
