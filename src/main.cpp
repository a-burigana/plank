#include "../include/lex.h"
#include "../include/epddl_exception.h"

using namespace epddl;

int main() {
    std::string path = "../examples/test.epddl";
    std::ifstream stream(path);

    if (stream.is_open()) {
        dictionary dictionary;
        lexer lex{stream, dictionary};

        try {
            while (!lex.eof() && lex.good()) {
                Token tok = lex.get_next_token();
                std::cout << tok.to_string(lex.get_dictionary()) << std::endl;
            }
        } catch (EPDDLException &e) {
            std::cerr << e.what();
        }
    }

    stream.close();
    return 0;
}
