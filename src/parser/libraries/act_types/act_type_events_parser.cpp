#include "../../../../include/parser/libraries/act_types/act_type_events_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::ident_list act_type_events_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::events>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}
