#include "../../include/lexer/token.h"

#define epddl_token_type(token_type) token_type
using namespace epddl;

//token::token(token_type type, unsigned long row, unsigned long col, std::optional<std::string> lexeme) :
//        m_type{type},
//        m_lexeme{std::move(lexeme)},
//        m_row{row},
//        m_col{col} {}
//
//template<typename other_token_type>
//bool token::has_type() const {
//    return std::visit([](auto &&tok_var_type) {
//        using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
//        return std::is_same_v<tok_type, other_token_type>;
//    }, m_type);
//}
//
//token_type token::get_type() const {
//    return m_type;
//}
//
//unsigned long token::get_row() const {
//    return m_row;
//}
//
//unsigned long token::get_col() const {
//    return m_col;
//}
//
//std::string token::get_lexeme() const {
//    return std::visit([&](auto &&tok_var_type) {
//        using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
//
//        if (std::is_same_v<typename tok_type::super_type, epddl_pattern_token_type> and m_lexeme.has_value())
//            return *m_lexeme;
//        else
//            return std::string{tok_type::lexeme};
//    }, m_type);
//}
//
//std::string token::get_name() const {
//    return std::visit([](auto &&tok_var_type) {
//        using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
//        return std::string{tok_type::name};
//    }, m_type);
//}
//
//bool token::is_scope() const {
//    return std::visit([](auto &&tok_var_type) {
//        using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
//        return tok_type::is_scope;
//    }, m_type);
//}
//
//std::string token::to_string() const {
//    return std::visit([&](auto &&tok_var_type) {
//        using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
//
//        if (std::is_same_v<typename tok_type::super_type, epddl_punctuation_token_type>) {
//            return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{tok_type::name} + std::string{"}"};
//        } else if (std::is_same_v<typename tok_type::super_type, epddl_pattern_token_type> and m_lexeme.has_value()) {
//            return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{tok_type::name} + std::string{":\""} + *m_lexeme + std::string{"\"}"};
//        } else {
//            return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{tok_type::lexeme} + std::string{"}"};
//        }
//    }, m_type);
//}

#undef epddl_token_type
