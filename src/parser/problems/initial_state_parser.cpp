#include "../../../include/parser/problems/initial_state_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/relations_parser.h"

using namespace epddl;

ast::initial_state_ptr initial_state_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::init>();

    ast::ident_list events_names = initial_state_parser::parse_worlds(helper);
    ast::agent_relation_list relations = relations_parser::parse_agent_relation_list(helper);
    ast::ident_list designated_names = initial_state_parser::parse_designated(helper);

    return std::make_unique<ast::initial_state>(std::move(events_names),
                                                std::move(relations), std::move(designated_names));
}

ast::ident_list initial_state_parser::parse_worlds(parser_helper &helper) {
    helper.check_next_token<keyword_token::worlds>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}

ast::ident_list initial_state_parser::parse_designated(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::designated>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}
