#include "../include/parser/parser_helper.h"
#include "../include/parser/main_decl_parser.h"
#include "../include/error-manager/epddl_exception.h"
#include <iostream>
#include <string>

using namespace epddl;

int main() {
//    std::string path = "../examples/libraries/ma_star.epddl";
//    std::string path = "../examples/domains/Coin-in-the-Box/cb.epddl";
//    std::string path = "../examples/domains/Collaboration-and-Communication/cc.epddl";
//    std::string path = "../examples/domains/Assemble/assemble.epddl";
    std::string path = "../examples/domains/Coin-in-the-Box/instances/cb5.epddl";

    parser_helper helper{path};

    try {
        ast::main_decl decl = main_decl_parser::parse(helper);
        std::cout << "Parsing successful!";
    } catch (EPDDLException &e) {
        std::cerr << e.what();
    }

    return 0;
}
