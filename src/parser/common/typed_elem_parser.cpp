#include "../../../include/parser/common/typed_elem_parser.h"
#include <memory>

using namespace epddl;

ast::typed_identifier_ptr typed_elem_parser::parse_typed_identifier(epddl::parser_helper &parser) {
    return typed_elem_parser::parse_typed_elem<ast::identifier>(parser);
//    ast::identifier_ptr id = tokens_parser::parse_identifier(parser);
//    std::optional<ast::identifier_ptr> type = std::nullopt;
//
//    const token_ptr &tok = parser.peek_next_token();          // Peeking either '-' or another identifier
//
//    if (tok->has_type<punctuation_token::dash>()) {
//        parser.read_next_token();       // Actually eating '-'
//        type = tokens_parser::parse_identifier(parser);
//    }
//    return std::make_unique<ast::typed_elem<ast::identifier>>(std::move(id), std::move(type));
}

ast::typed_variable_ptr typed_elem_parser::parse_typed_variable(parser_helper &parser) {
    return typed_elem_parser::parse_typed_elem<ast::variable>(parser);
//    ast::variable_ptr var = tokens_parser::parse_variable(parser);
//    std::optional<ast::identifier_ptr> type = std::nullopt;
//
//    const token_ptr &tok = parser.peek_next_token();          // Peeking either '-' or another variable
//
//    if (tok->has_type<punctuation_token::dash>()) {
//        parser.read_next_token();       // Actually eating '-'
//        type = tokens_parser::parse_identifier(parser);
//    }
//    return std::make_unique<ast::typed_elem<ast::variable>>(std::move(var), std::move(type));
}
