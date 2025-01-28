#include "../../../include/parser/tokens/tokens_parser.h"

#define epddl_token_type(token_type) token_type

using namespace epddl;

//template<typename ast_leaf_type>
//std::unique_ptr<ast_leaf_type> tokens_parser::parse_token(epddl::parser &parser) {
//    return std::make_unique<ast_leaf_type>(parser.get_leaf_from_next_token<ast_leaf_type::token_type>());
//}

ast::identifier_ptr tokens_parser::parse_identifier(epddl::parser_helper &parser) {
    return std::make_unique<ast::identifier>(parser.get_leaf_from_next_token<epddl_pattern_token_type::identifier>());
}

ast::variable_ptr tokens_parser::parse_variable(epddl::parser_helper &parser) {
    return std::make_unique<ast::variable>(parser.get_leaf_from_next_token<epddl_pattern_token_type::variable>());
}

ast::requirement_ptr tokens_parser::parse_requirement(epddl::parser_helper &parser) {
    return std::make_unique<ast::requirement>(parser.get_leaf_from_next_token<epddl_pattern_token_type::requirement>());
}

ast::integer_ptr tokens_parser::parse_integer(epddl::parser_helper &parser) {
    return std::make_unique<ast::integer>(parser.get_leaf_from_next_token<epddl_pattern_token_type::integer>());
}

#undef epddl_token_type
