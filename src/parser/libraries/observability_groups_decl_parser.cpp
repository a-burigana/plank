#include "../../../include/parser/libraries/observability_groups_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::observability_groups_decl_ptr observability_groups_decl_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::obs_groups>();
    auto ids = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });

    return std::make_unique<ast::observability_groups_decl>(std::move(ids));
}
