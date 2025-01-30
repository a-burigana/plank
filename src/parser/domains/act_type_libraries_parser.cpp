#include "../../../include/parser/domains/act_type_libraries_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::domain_libraries_ptr act_type_libraries_parser::parse(parser_helper &parser) {
    parser.check_next_token<keyword_token::act_type_libs>();
    ast::ident_list ids = parser.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(parser); });

    return std::make_unique<ast::domain_libraries>(std::move(ids));
}
