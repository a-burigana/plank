#include "../../../include/parser/problems/agents_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::agents_decl_ptr agents_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::agents>();
    auto agents = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });

    return std::make_unique<ast::agents_decl>(std::move(agents));
}
