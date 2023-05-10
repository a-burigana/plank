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

//    using string_ptr = std::unique_ptr<std::string>;
//
//    std::string x = "test";
//    std::string x2 = "test2";
//    string_ptr x_ptr = std::make_unique<std::string>(x);
//    string_ptr x_ptr2 = std::make_unique<std::string>(x2);
//
//    std::list<string_ptr> ptrs;
//    ptrs.push_front(std::move(x_ptr2));
//    ptrs.push_front(std::move(x_ptr));
//
//    std::cout << *ptrs.front() << std::endl;
//
//    string_ptr y_ptr = std::move(ptrs.front());
//    std::cout << "size: " << ptrs.size() << std::endl;
//    std::cout << *ptrs.back() << std::endl;
//
//    ptrs.pop_front();
//    std::cout << "popping first element..." << std::endl;
//    std::cout << "is empty? " << ptrs.empty() << std::endl;
//    std::cout << *ptrs.front() << std::endl;

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
