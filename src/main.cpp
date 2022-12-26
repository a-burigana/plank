#include "lex.h"

int main() {
    std::string path = "../examples/test.epddl";
    std::ifstream stream(path);
    std::function<void(long, long, const std::string&)> print_error =
            [&path](long row, long col, const std::string& err) {
        std::cerr << path << ":" << row << ":" << col << ": error: " << err << std::endl;
    };

    if (stream.is_open()) {
        lexer lex{std::move(stream), print_error};

        while (!lex.eof() && lex.good()) {
            token tok = lex.get_next_token();
            std::cout << tok.to_string() << std::endl;
        }
    }

    stream.close();
    return 0;
}
