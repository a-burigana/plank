#include "../../../include/parser/problems/agent_groups_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::agent_groups_decl_ptr agent_groups_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::agent_groups>();
    auto agent_groups = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });

    return std::make_unique<ast::agent_groups_decl>(std::move(agent_groups));
}
