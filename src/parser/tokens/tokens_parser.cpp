#include "../../../include/parser/tokens/tokens_parser.h"
#include <type_traits>

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

ast::modality_name_ptr tokens_parser::parse_modality_name(epddl::parser_helper &parser) {
    const token_ptr &tok = parser.peek_next_token();
    return std::visit([&](auto &&arg) {
        using tok_type = std::remove_reference_t<decltype(arg)>;
        return std::make_unique<ast::modality_name>(parser.get_leaf_from_next_token<tok_type>());
    }, tok->get_type());

//    if (tok->has_type<modality_token::ck>())
//        return std::make_unique<ast::modality_name>(parser.get_leaf_from_next_token<epddl_modality_token_type::ck>());
//    else if (tok->has_type<modality_token::kw>())
//        return std::make_unique<ast::modality_name>(parser.get_leaf_from_next_token<epddl_modality_token_type::kw>());
//    else if (tok->has_type<modality_token::modality>())
//        return std::make_unique<ast::modality_name>(parser.get_leaf_from_next_token<epddl_modality_token_type::modality>());
}

ast::requirement_ptr tokens_parser::parse_requirement(epddl::parser_helper &parser) {
    return std::make_unique<ast::requirement>(parser.get_leaf_from_next_token<epddl_pattern_token_type::requirement>());
}

ast::integer_ptr tokens_parser::parse_integer(epddl::parser_helper &parser) {
    return std::make_unique<ast::integer>(parser.get_leaf_from_next_token<epddl_pattern_token_type::integer>());
}

#undef epddl_token_type
