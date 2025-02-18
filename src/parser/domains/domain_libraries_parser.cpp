#include "../../../include/parser/domains/domain_libraries_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::domain_libraries_ptr act_type_libraries_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::domain_libs>();
    ast::identifier_list ids = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });

    return std::make_unique<ast::domain_libraries>(std::move(ids));
}
