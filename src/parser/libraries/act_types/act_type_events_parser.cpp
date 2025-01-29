#include "../../../../include/parser/libraries/act_types/act_type_events_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::ident_list act_type_events_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::events>();
    return helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
}
