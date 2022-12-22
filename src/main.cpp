#include "lex.hpp"

int main() {
    std::string path = "../examples/test.epddl";
    std::ifstream stream(path);
    std::function<void(long, long, const std::string&)> print_error =
            [&path](long row, long col, const std::string& err) {
        std::cerr << path << ":" << row << ":" << col << ": error: " << err << std::endl;
    };

    if (stream.is_open()) {
        lexer lex{stream, print_error};

        while (!lex.eof() && lex.good()) {
            std::optional<token> tok = lex.scan_next();
            std::cout << tok->to_string() << std::endl;
        }
    }

    stream.close();
    return 0;
}
