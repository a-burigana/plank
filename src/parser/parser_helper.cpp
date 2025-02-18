#include "../../include/parser/parser_helper.h"
#include "../../include/parser/main_decl_parser.h"
#include "../../include/error-manager/epddl_exception.h"
#include <iostream>

using namespace epddl;
using namespace epddl::parser;

parser_helper::parser_helper(const std::string &path) :
        m_lex{lexer{path}},
        m_current_token{std::nullopt},
        m_next_token{std::nullopt},
        m_is_choice_point{false},
        m_is_optional_node{false},
        m_choice_point_count{0},
        m_lpar_count{0} {}

ast::main_decl parser_helper::parse() {
    ast::main_decl decl;

    try {
        decl = main_decl_parser::parse(*this);
        std::cout << "Parsing successful!";
    } catch (EPDDLException &e) {
        std::cerr << e.what();
    }

    return decl;
}

const token_ptr &parser_helper::get_current_token() const {
    return *m_current_token;
}

//const token_ptr &helper::get_next_token() const {
//    return *m_next_token;
//}


unsigned long parser_helper::enter_choice_point() {
    m_is_choice_point = true;
    return ++m_choice_point_count;
}

unsigned long parser_helper::exit_choice_point() {
    m_is_choice_point = --m_choice_point_count != 0;
    return m_choice_point_count;
//    m_is_optional_node = false;     // We reset m_is_optional_node in the case we were parsing an optional variant node
//    m_next_tokens.clear();
//    m_cursor_token_index = 0;
}

bool parser_helper::is_inside_choice_point(unsigned long current_choice_point) const {
    return m_choice_point_count == current_choice_point;
}

//void helper::reset_choice_point() {
//    m_cursor_token_index = 0;
//}

void parser_helper::enter_optional_node() {
    m_is_optional_node = true;
}

void parser_helper::exit_optional_node() {
    m_is_optional_node = false;
}

void parser_helper::throw_error(const token_ptr& token, const std::string& file, const std::string& error) const {
    if (m_is_choice_point or m_is_optional_node)
        throw EPDDLBadChoicePointException{file, token->get_row(), token->get_col(), error};
    else
        throw EPDDLParserException{file, token->get_row(), token->get_col(), error};
}

//template<typename required_tok_type>
//void helper::throw_token_error(const token_ptr& token) {
//
//}

//bool helper::is_end_list() {
//    peek_next_token();
//
//    #define epddl_token_type(token_type) token_type
//    return (*m_next_token)->has_type<epddl_punctuation_token_type::rpar>()   or
//           (*m_next_token)->has_type<epddl_punctuation_token_type::rbrack>() or
//           (*m_next_token)->has_type<epddl_punctuation_token_type::rangle>();
//    #undef epddl_token_type
//}

void parser_helper::read_next_token() {
    if (m_next_token.has_value()) {     // If we already peeked a token, we read that
        m_current_token.emplace(std::move(*m_next_token));
        reset_next_token();
    }
//    if (not m_buffer.empty())       // If we have some tokens in the buffer, we read from there
//        read_from_buffer();
    else if (m_lex.good() and not m_lex.eof())      // Otherwise, we have the lexer read the next token from the input file
        m_current_token.emplace(std::move(m_lex.get_next_token()));
    else {
        // todo: throw some error here
    }
    update_scopes(*m_current_token);
}

/*void helper::peek_next_token() {
    if (m_is_optional_node and not m_is_choice_point)
        // If we are parsing an optional and *non-choice point* node, then we use the next token
        peek_next_token();
    else if (m_next_token.has_value())
        // If we previously used the next token to store a token (either because we checked for an end of list,
        // or because we were parsing an optional node) then 'm_next_token' contains a token. In this case,
        // we move this token to the end of the 'm_next_tokens' list and we reset 'm_next_token'.
        move_next_token();
    else if (m_lex.good() and not m_lex.eof())
        // Otherwise, we simply have the lexer retrieve the next token from the input file. Here we cover two cases:
        //  * We are parsing an optional and choice point node, or
        //  * We are parsing a non-optional choice point node.
        m_next_tokens.push_back(std::move(m_lex.get_next_token()));

    update_scopes(get_last_peeked_token(false));
}*/

const token_ptr &parser_helper::peek_next_token() {
    // The next token is used both for checking for end of lists and for reading optional nodes. If we already tried
    // (and failed) to read an optional node and we immediately next we check for an end of list, we check that we
    // did not already peek the next token to avoid losing the next token that we already peeked.
    if (not m_next_token.has_value() and m_lex.good() and not m_lex.eof())
        m_next_token = std::move(m_lex.get_next_token());
//        m_buffer.push_back(std::move(m_lex.get_next_token()));

    return *m_next_token;
//    return m_buffer.back();
}

//void parser_helper::read_from_buffer() {
//    assert(not m_buffer.empty());
//    m_current_token.emplace(std::move(m_buffer.front()));
//    m_buffer.pop_front();
//}

void parser_helper::reset_next_token() {
    m_next_token->reset();
    m_next_token = std::nullopt;
}

//token_ptr& helper::get_last_peeked_token(bool move_next) {
//    if (move_next and m_next_token.has_value())
//        move_next_token();
//    return m_next_tokens.back();
//}

const token_ptr &parser_helper::get_last_peeked_token() const {
    return *m_next_token;
//    return m_buffer.back();
}

/* Assumptions:
 *  - Each production is unambiguously identifiable by a finite sequence of terminals
 *  - There are no nested choice points (i.e., variants of variants)
 *  - There exists a common prefix of terminals p = <t_1,  ..., t_k> such that for each
 *    node n in the choice point we have:
 *     + There exists a terminal t_n such that prefix(n) = p + t_n; and
 *     + For each node m != n, it holds that t_m != t_n.
 */
//template<typename required_tok_type>
//void helper::check_current_peeked_token() {
//    assert(m_next_token.has_value() or m_is_optional_node);
//
//    if (m_is_optional_node and not m_is_choice_point) {
//        // If we are parsing an optional and *non-choice point* node, then we use the next token
//        if ((*m_next_token)->has_type<required_tok_type>()) {
//            reset_next_token();             // If the next token has the correct type, we simply reset it
//            exit_optional_node();           // We can now safely conclude that the optional node exists
//        } else
//            throw_error(*m_next_token);
//    } else {
//        // Otherwise, we check that the cursor token has the correct type. Here we cover two cases:
//        //  * We are parsing an optional and choice point node, or
//        //  * We are parsing a non-optional choice point node.
//        if (get_cursor_token()->has_type<required_tok_type>())
//            ++m_cursor_token_index;
//        else
//            throw_token_error<required_tok_type>(get_cursor_token());
//    }
//}

//template<typename required_tok_type>
//void helper::check_current_token(bool discard) {
//
//}

//template<typename required_tok_type>
//void helper::check_next_token(bool discard) {
////    if (m_is_choice_point or m_is_optional_node) {
////        // The function 'check_next_token' may be called after a choice point has been reached, or not.
////        // In the first case, we peek the next token, and we check that it has the correct type.
////        if (m_cursor_token_index == m_next_tokens.size())   // We only peek a token we already checked the entire list
////            peek_next_token();
////        check_current_peeked_token<required_tok_type>();
////    } else {
//    // In the second case, we read the next token from the input file and we do the same check.
//
////    }
//}

void parser_helper::update_scopes(const token_ptr& token) {
//    std::visit([this](auto &&tok) {
//        using tok_type = get_argument_t<decltype(tok)>;
//
//        if constexpr (std::is_same_v<tok_type, punctuation_token::lpar>) {
//            ++m_lpar_count;
//        } else if constexpr (std::is_same_v<tok_type, punctuation_token::rpar>) {
//            if (m_lpar_count == m_scopes.top().first) {
//                m_scopes.pop();
//            }
//            --m_lpar_count;
//        } else {
//            if constexpr (tok_type::is_scope) {
//                m_scopes.emplace(m_lpar_count, &*m_current_token);
//            }
//        }
//    }, *token);
}

//template<typename required_tok_type>
//token_ptr helper::get_leaf_from_current_token() {
//
//}

//template<typename required_tok_type>
//token_ptr helper::get_leaf_from_next_token(bool is_optional) {     // todo: do I need is_optional?
//
//}
//
//template<class node_type, typename delimiter_tok_type>
//std::list<node_type> helper::parse_list(const std::function<node_type()> &parse_elem, bool is_optional_list) {
//
//}

/*template<class variant_node_type, class node_type>
std::pair<bool, std::unique_ptr<variant_node_type>> helper::parse_variant_node(const std::function<std::unique_ptr<node_type>()>& parse_elem) {
    reset_choice_point();

    try {
        if (std::unique_ptr<node_type> element = std::move(parse_elem()))
            return {true, std::move(std::make_unique<variant_node_type>(std::move(element)))};
    } catch (EPDDLBadChoicePointException &e) {}
    return {false, std::unique_ptr<variant_node_type>{}};
}

template<class variant_leaf_type, typename required_tok_type>
std::pair<bool, std::unique_ptr<variant_leaf_type>> helper::parse_variant_leaf() {
    reset_choice_point();

    if (m_next_tokens.empty() and not m_next_token.has_value())
        peek_next_token();

    if (get_last_peeked_token()->has_type<required_tok_type>()) {
        std::unique_ptr<variant_leaf_type> result =
                std::move(parser_utils::convert_variant_type<token_variant, variant_leaf_type, token<token_type>>(*get_last_peeked_token()));

        exit_choice_point();
        return {true, std::move(result)};
    }
    return {false, std::unique_ptr<variant_leaf_type>{}};
}

template<class node_type>
std::pair<bool, std::unique_ptr<node_type>> helper::parse_optional_node(const std::function<std::unique_ptr<node_type>()>& parse_elem) {
    reset_choice_point();       // todo: do we really need this?

    try {
        m_is_optional_node = true;
        std::unique_ptr<node_type> element = std::move(parse_elem());
        return {true, std::move(element)};
    } catch (EPDDLBadChoicePointException &e) {
        m_is_optional_node = false;
        return {false, std::unique_ptr<node_type>{}};
    }
}

template<typename required_tok_type>
std::pair<bool, token_ptr> helper::parse_optional_leaf() {     // todo: can I use 'get_leaf_from_next_token' instead of this function?
    if (get_last_peeked_token()->has_type<required_tok_type>()) {
        token_ptr leaf = std::move(get_last_peeked_token());
//                std::move(parser_utils::unwrap_variant_type<token_variant, token<token_type>>(*get_last_peeked_token()));
        m_next_tokens.clear();
        return {true, std::move(leaf)};
    }
    return {false, nullptr};
}

ast::requirement_ptr helper::parse_requirement() {
#define epddl_token_type(token_type) token_type
    return std::make_unique<ast::requirement>(get_leaf_from_next_token<epddl_pattern_token_type::requirement>());
#undef epddl_token_type
//    peek_next_token();

//    if (std::holds_alternative<requirement_value>(m_next_tok->get_type())) {
//        get_next_token();       // Eating requirement
//        return std::make_unique<ast::Requirement>(std::move(*m_current_token));
//    } else if (std::get<punctuation_token>(m_next_tok->get_type()) == punctuation_token::lpar) {
//        get_next_token();       // Eating '('
//        get_next_token();       // Eating requirement
//
//        if (std::holds_alternative<requirement_value>(m_current_token->get_type())) {
//            Token req = std::move(*m_current_token);
//
//            if (std::holds_alternative<requirement_value>(m_current_token->get_type())) {
//                integer val = get_node_from_next_token<ast::Integer>(pattern_token::integer);
//                close_par();
//
//                return std::make_unique<ast::Requirement>(std::move(req), std::move(val));
//            }
//        }
//    }

    // todo: fix
//    if (std::get<punctuation_token>(m_next_token->get_type()) != punctuation_token::rpar) {
//        throw EPDDLException{std::string{""}, (*m_current_token)->get_row(), (*m_current_token)->get_col(), std::string{"Expected requirement."}};
//    }
    return {};
}*/

