#include "../include/parser/parser_helper.h"
#include "../include/ast/main_decl_ast.h"
#include "../include/parser/main_decl_parser.h"
#include "../include/error-manager/epddl_exception.h"
#include <iostream>

using namespace epddl;
using namespace epddl::parser;

int main(int argc, char *argv[]) {
    parser_helper helper{argv[1]};
    ast::main_decl decl;

    try {
        decl = main_decl_parser::parse(helper);
        std::cout << "Parsing successful!";
    } catch (EPDDLException &e) {
        std::cerr << e.what();
    }

    return 0;
}
