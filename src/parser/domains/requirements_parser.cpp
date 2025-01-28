#include "../../../include/parser/domains/requirements_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::domain_requirements_ptr requirements_parser::parse(epddl::parser_helper &parser) {
    parser.check_next_token<keyword_token::requirements>();
    ast::requirement_list reqs = parser.parse_list<ast::requirement_ptr >([&] () { return tokens_parser::parse_requirement(parser); });

    return std::make_unique<ast::domain_requirements>(std::move(reqs));
}
