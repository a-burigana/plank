#include "../../../include/parser/domains/requirements_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::requirements_decl_ptr requirements_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::requirements>();
    ast::requirement_list reqs = helper.parse_list<ast::requirement_ptr >([&] () { return tokens_parser::parse_requirement(helper); });

    return std::make_unique<ast::requirements_decl>(std::move(reqs));
}
