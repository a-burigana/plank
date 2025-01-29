#include "../../../../include/parser/libraries/act_types/act_type_effects_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/postconditions_parser.h"

using namespace epddl;

ast::event_postconditions_list act_type_effects_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::precondition>();
    return helper.parse_list<ast::event_postconditions>([&] () { return act_type_effects_parser::parse_event_postcondition(helper); }, true);
}

ast::event_postconditions act_type_effects_parser::parse_event_postcondition(epddl::parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    ast::identifier_ptr event = tokens_parser::parse_identifier(helper);
    ast::postconditions post = postconditions_parser::parse(helper);
    helper.check_next_token<punctuation_token::rpar>();

    return std::make_pair(std::move(event), std::move(post));
}
