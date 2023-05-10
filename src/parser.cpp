#include "../include/parser/parser.h"
#include "../include/epddl_exception.h"
#include <type_traits>

parser::parser(lexer& lex) :
        m_lex{lex},
        m_current_token{std::nullopt},
        m_next_tokens{},
        m_lpar_count{0} {}

template<typename token_type>
bool parser::has_type(const token_ptr &tok) const {
    return std::holds_alternative<token<token_type>>(tok);
}

void parser::get_next_token() {
    if (m_next_tokens.empty() and m_lex.good() and not m_lex.eof()) {
        m_current_token.emplace(std::move(m_lex.get_next_token()));
    } else {
        m_current_token.emplace(std::move(m_next_tokens.back()));
        m_next_tokens.clear();
    }

    std::visit([this](auto&& tok) {
        using token_type = get_argument_t<std::decay_t<decltype(tok)>>;

        if constexpr (std::is_same_v<token_type, punctuation_token::lpar>) {
            ++m_lpar_count;
        } else if constexpr (std::is_same_v<token_type, punctuation_token::rpar>) {
            if (m_lpar_count == m_scopes.top().first) {
                m_scopes.pop();
            }
            --m_lpar_count;
        } else {
            if (token_type::is_scope) {
                m_scopes.emplace(m_lpar_count, &*m_current_token);
            }
        }
    }, **m_current_token);
}

void parser::peek_next_token() {
    if (m_lex.good() and not m_lex.eof()) {
        m_next_tokens.push_back(std::move(m_lex.get_next_token()));
    }
}

const token_ptr& parser::get_last_peeked_token() {
    return m_next_tokens.back();
}

template<typename token_type>
bool parser::is_next_token_type() {
    peek_next_token();
    return has_type<token_type>(get_last_peeked_token());
}

template<typename token_type>
void parser::check_current_token() {
    if (not has_type<token_type>(**m_current_token)) {
        std::visit([this](auto&& tok) {
            std::string type;

            // We only check for basic values, punctuation or valid keywords
            // todo: check behaviour for all token types
            #define epddl_token_type(token_type) token_type
            if constexpr (std::is_same_v<epddl_pattern_token_type, get_super_t<token_type>>) {
                type = std::string{token_type::name};
            } else {
                type = std::string{"'"} + std::string{token_type::lexeme} + std::string{"'"};
            }
            #undef epddl_token_type
            // todo: create function 'throw_error' to print more detailed errors (using scope tokens)
            throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(), std::string{"Expected " + type + std::string{"."}}};
        }, **m_current_token);
    }
}

template<typename token_type>
void parser::check_next_token() {
    get_next_token();
    check_current_token<token_type>();
}

template<class node_type, typename token_type>
std::unique_ptr<node_type> parser::get_node_from_next_token() {
    check_next_token<token_type>();
    return std::make_unique<token_type>(std::move(*m_current_token));
}

template<class node_type>
std::list<node_type> parser::parse_list(std::function<node_type()> parse_elem, bool is_optional_list) {
    std::list<node_type> elems;
    bool end_list = false, is_empty_list = true;

    #define epddl_token_type(token_type) token_type
    do {
        peek_next_token();
        if (has_type<epddl_punctuation_token_type::rpar>(get_last_peeked_token())) {
            // If we peek ')'
            end_list = true;
        } else {
            // Otherwise we parse the element and, if we are successful, we add it to the list
            // We assume that parse_elem() takes care of errors concerning unexpected tokens
            elems.push_back(parse_elem());
            is_empty_list = false;
        }
    } while (not end_list);

    check_next_token<epddl_punctuation_token_type::rpar>();
    #undef epddl_token_type

    if (not is_optional_list and is_empty_list) {
        // todo: create better error description
        std::visit([this](auto&& tok) {
            throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(), std::string{"Empty list."}};
        }, **m_current_token);
    }
    return elems;
}
