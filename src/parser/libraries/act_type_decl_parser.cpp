#include "../../../include/parser/libraries/act_type_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/relations_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::action_type_ptr act_type_decl_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::act_type>();
    ast::identifier_ptr action_type_name = tokens_parser::parse_identifier(helper);       // Eating action-type name (identifier)

    ast::identifier_list events_names = act_type_decl_parser::parse_events(helper);
    ast::relations relations = relations_parser::parse_model_relations(helper);
    ast::identifier_list designated_names = act_type_decl_parser::parse_designated(helper);

    return std::make_unique<ast::action_type>(std::move(action_type_name), std::move(events_names),
                                              std::move(relations), std::move(designated_names));
}

ast::identifier_list act_type_decl_parser::parse_events(parser_helper &helper) {
    helper.check_next_token<keyword_token::events>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}

ast::identifier_list act_type_decl_parser::parse_designated(parser_helper &helper) {
    helper.check_next_token<keyword_token::designated>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}
