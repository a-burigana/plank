#include "../include/lex.h"

using namespace epddl;

int main() {
    std::string path = "../examples/test.epddl";
    std::ifstream stream(path);

    if (stream.is_open()) {
        dictionary dictionary;
        lexer lex{stream, dictionary};

        while (!lex.eof() && lex.good()) {
            Token tok = lex.get_next_token();
            std::cout << tok.to_string(lex.get_dictionary()) << std::endl;
        }
    }

    stream.close();
    return 0;
}
