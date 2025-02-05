#include "../../../include/parser/problems/initial_state_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/relations_parser.h"
#include "../../../include/parser/common/formulas_parser.h"

using namespace epddl;

ast::initial_state_ptr initial_state_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::init>();

    ast::identifier_list events_names = initial_state_parser::parse_worlds(helper);
    ast::relations relations = relations_parser::parse_model_relations(helper);
    ast::world_label_list labels = initial_state_parser::parse_labels(helper);
    ast::identifier_list designated_names = initial_state_parser::parse_designated(helper);

    return std::make_unique<ast::initial_state>(std::move(events_names), std::move(relations),
                                                std::move(labels), std::move(designated_names));
}

ast::identifier_list initial_state_parser::parse_worlds(parser_helper &helper) {
    helper.check_next_token<keyword_token::worlds>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}

ast::identifier_list initial_state_parser::parse_designated(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::designated>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}

ast::world_label_ptr initial_state_parser::parse_world_label(parser_helper &helper) {
    ast::identifier_ptr world_name = tokens_parser::parse_identifier(helper);
    auto predicates = helper.parse_list<ast::predicate_ptr>([&]() { return formulas_parser::parse_predicate(helper); });

    return std::make_unique<ast::world_label>(std::move(world_name), std::move(predicates));
}

ast::world_label_list initial_state_parser::parse_labels(epddl::parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();
    auto labels = helper.parse_list<ast::world_label_ptr>([&] () { return initial_state_parser::parse_world_label(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return labels;
}
