#include "../include/parser/parser_helper.h"

using namespace epddl;

int main(int argc, char *argv[]) {
    parser_helper helper{argv[1]};
    helper.parse();

    return 0;
}
