#include "../../../../include/parser/problems/initial_states/explicit_initial_state_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include "../../../../include/parser/common/relations_parser.h"
#include "../../../../include/error-manager/epddl_exception.h"

using namespace epddl;
using namespace epddl::parser;

ast::explicit_initial_state_ptr explicit_initial_state_parser::parse(parser_helper &helper) {
    ast::identifier_list events_names = explicit_initial_state_parser::parse_worlds(helper);
    ast::relations relations = relations_parser::parse_model_relations(helper);
    ast::world_label_list labels = explicit_initial_state_parser::parse_labels(helper);
    ast::identifier_list designated_names = explicit_initial_state_parser::parse_designated(helper);

    return std::make_unique<ast::explicit_initial_state>(std::move(events_names), std::move(relations),
                                                         std::move(labels), std::move(designated_names));
}

ast::identifier_list explicit_initial_state_parser::parse_worlds(parser_helper &helper) {
    helper.check_next_token<keyword_token::worlds>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}

ast::world_label_ptr explicit_initial_state_parser::parse_world_label(parser_helper &helper) {
    ast::identifier_ptr world_name = tokens_parser::parse_identifier(helper);
    auto literals = helper.parse_list<ast::literal_ptr, ast_token::identifier>([&]() { return formulas_parser::parse_literal(helper); });

    return std::make_unique<ast::world_label>(std::move(world_name), std::move(literals));
}

ast::world_label_list explicit_initial_state_parser::parse_labels(parser_helper &helper) {
    helper.check_next_token<keyword_token::labels>();
    helper.check_next_token<punctuation_token::lpar>();
    auto labels = helper.parse_list<ast::world_label_ptr>([&] () { return explicit_initial_state_parser::parse_world_label(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return labels;
}

ast::identifier_list explicit_initial_state_parser::parse_designated(parser_helper &helper) {
    helper.check_next_token<keyword_token::designated>();
    helper.check_next_token<punctuation_token::lpar>();
    auto event_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return event_names;
}
