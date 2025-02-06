#include "../include/parser/parser_helper.h"
#include <string>

using namespace epddl;

int main() {
//    std::string path = "../examples/libraries/ma_star.epddl";
//    std::string path = "../examples/domains/Coin-in-the-Box/cb.epddl";
//    std::string path = "../examples/domains/Collaboration-and-Communication/cc.epddl";
//    std::string path = "../examples/domains/Assemble/assemble.epddl";
    std::string path = "../examples/domains/Coin-in-the-Box/instances/cb2.epddl";

    parser_helper helper{path};
    helper.parse();

    return 0;
}
