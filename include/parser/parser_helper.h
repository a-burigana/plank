// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef EPDDL_PARSER_HELPER_H
#define EPDDL_PARSER_HELPER_H

#include "../../include/utils/traits.h"
#include "../lexer/lexer.h"
#include "../ast/ast_node.h"
#include "../error-manager/epddl_exception.h"
#include <deque>
#include <list>
#include <memory>
#include <optional>
#include <stack>

namespace epddl::parser {
    class parser_helper {
    public:
        explicit parser_helper(const std::string &path) :
                m_path{path},
                m_lex{lexer{path}},
                m_current_token{std::nullopt},
                m_next_token{std::nullopt},
                m_lpar_count{0} {}

        void read_next_token() {
            if (m_next_token.has_value()) {     // If we already peeked a token, we read that
                m_current_token.emplace(std::move(*m_next_token));
                reset_token(m_next_token);
            } else if (m_lex.good() and not m_lex.eof())      // Otherwise, we have the lexer read the next token from the input file
                m_current_token.emplace(std::move(m_lex.get_next_token()));
            else {
                // todo: throw some error here
            }
            update_scopes(*m_current_token);
        }

        const token_ptr &peek_next_token() {
            // The next token is used both for checking for end of lists and for reading optional nodes. If we already tried
            // (and failed) to read an optional node and we immediately next we check for an end of list, we check that we
            // did not already peek the next token to avoid losing the next token that we already peeked.
            if (not m_next_token.has_value() and m_lex.good() and not m_lex.eof())
                m_next_token = std::move(m_lex.get_next_token());

            return *m_next_token;
        }

        template<typename required_tok_type>
        void check_next_token(bool discard = true, const std::string &error = "") {
            read_next_token();
            check_token<required_tok_type>(*m_current_token, error);
            if (discard) reset_token(m_current_token);      // After successfully verifying that the current token has the correct type, we can delete it
        }

        ast::info get_info(const token_ptr &tok, ast::string_pair_set required_tokens = {}) {
            return ast::info{m_path, tok->get_row(), tok->get_col(), std::move(required_tokens)};
        }

        ast::info get_next_token_info(ast::string_pair_set required_tokens = {}) {
            if (not m_next_token.has_value())
                peek_next_token();

            return get_info(*m_next_token, std::move(required_tokens));
        }

        template<typename required_tok_type>
        token_ptr get_ast_token() {
            check_next_token<required_tok_type>(false);
            token_ptr leaf = std::move(*m_current_token);
            reset_token(m_current_token);

            return leaf;
        }

        template<class node_type, typename... delimiter_tok_types>
        std::list<node_type> parse_list(const std::function<node_type()> &parse_elem, bool is_optional_list = false) {
            std::list<node_type> elems;
            bool is_empty_list = true;
            peek_next_token();

            while (not get_next_token()->has_either_type<punctuation_token::rpar, delimiter_tok_types...>()) {
                // If we do not peek the list delimiter, we parse the element and, if we are successful, we add it to the list.
                // We assume that parse_elem() takes care of its relative syntax errors.
                elems.push_back(std::move(parse_elem()));
                is_empty_list = false;
                peek_next_token();
            }

            if (not is_optional_list and is_empty_list)
                throw_error(get_next_token(), std::string{"Empty list."});
            // todo: create better error description
            return elems;
        }

        template<class node_type, typename... first_tok_types>
        std::optional<node_type> parse_optional(const std::function<node_type()> &parse_elem) {
            const token_ptr &tok = peek_next_token();
            std::optional<node_type> elem = std::nullopt;

            if (tok->has_either_type<first_tok_types...>()) elem.emplace(parse_elem());
            return elem;
        }

    private:
        std::string m_path;
        lexer m_lex;
        std::optional<token_ptr> m_current_token, m_next_token;

        std::stack<std::pair<unsigned long, const token_ptr*>> m_scopes;
        unsigned long m_lpar_count;

        void throw_error(const token_ptr& token, const std::string& error = "") {
            throw EPDDLParserException{m_path, token->get_row(), token->get_col(), error};
        }

        template<typename required_tok_type>
        void throw_token_error(const token_ptr& token) {
            if (not token->has_type<required_tok_type>()) {
                // We only check for identifiers, punctuation and valid keywords
                // todo: check behaviour for all token types
                #define epddl_token_type(token_type) token_type
                std::string required_tok_type_str = std::is_same_v<get_super_t<required_tok_type>, epddl_ast_token_type>
                        ? std::string{required_tok_type::name}
                        : std::string{required_tok_type::lexeme};
//                = std::visit([](auto &&tok_var_type) {
//                    using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
//                    return std::is_same_v<epddl_ast_token_type, get_super_t<tok_type>>
//                    ? std::string{tok_type::name}
//                    : std::string{tok_type::lexeme};
//                }, token->get_type());
                #undef epddl_token_type

                throw_error(token,
                            std::string{"Expected '"} + required_tok_type_str +
                            std::string{"'. Found '"} + token->get_lexeme() + std::string{"'."});
            }
        }

        static void reset_token(std::optional<token_ptr> &tok) {
            tok->reset();
            tok = std::nullopt;
        }

        template<typename required_tok_type>
        void check_token(const token_ptr &tok, const std::string &error) {
            if (not tok->has_type<required_tok_type>())
                throw_error(*m_current_token, error);
        }

        [[nodiscard]] const token_ptr& get_next_token() const {
            return *m_next_token;
        }

        void update_scopes(const token_ptr& token) {
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
    };
}

#endif //EPDDL_PARSER_HELPER_H
