#include "../../../../include/parser/domains/actions/action_postconditions_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/postconditions_parser.h"

using namespace epddl;

ast::event_postconditions_list action_postconditions_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::effects>();
    helper.check_next_token<punctuation_token::lpar>();
    auto post = helper.parse_list<ast::event_postconditions>([&] () { return action_postconditions_parser::parse_event_postcondition(helper); }, true);
    helper.check_next_token<punctuation_token::rpar>();

    return post;
}

ast::event_postconditions action_postconditions_parser::parse_event_postcondition(epddl::parser_helper &helper) {
    ast::identifier_ptr event = tokens_parser::parse_identifier(helper);
    ast::postconditions post = postconditions_parser::parse(helper);

    return std::make_pair(std::move(event), std::move(post));
}
