#include "../include/lex/lex.h"
#include "../include/epddl_exception.h"
#include "../include/generators/ast/ast_gen.h"
#include <iostream>
//#include <memory>
//#include <ostream>
#include <string>

using namespace epddl;

int main() {
    std::string path = "../examples/test.epddl";
    std::ifstream stream(path);

    using T0 = std::variant<int, std::string, double, std::pair<bool, bool>>;
    using T1 = std::variant<std::variant<int, std::string>, std::variant<double, std::pair<bool, bool>>>;
    using T2 = ast::flatten_variant_t<T1>;
    using T3 = std::variant<int, std::variant<std::string, double>, std::pair<bool, bool>>;
    using T4 = ast::flatten_variant_t<T3>;
    using T5 = std::variant<std::variant<int, std::variant<std::string, double>, std::pair<bool, bool>>>;
    using T6 = ast::flatten_variant_t<T5>;

    static_assert(std::is_same_v<T0, T2>, "!");
    static_assert(std::is_same_v<T0, T4>, "!");
    static_assert(std::is_same_v<T2, T4>, "!");
    static_assert(std::is_same_v<T0, T6>, "!");

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
