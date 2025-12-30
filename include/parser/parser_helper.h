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

#ifndef PLANK_PARSER_HELPER_H
#define PLANK_PARSER_HELPER_H

#include "../../include/utils/traits.h"
#include "../lexer/lexer.h"
#include "../ast/ast_node.h"
#include "../error-manager/epddl_exception.h"
#include "../error-manager/error_manager.h"
#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <cassert>

namespace epddl::parser {
    class parser_helper {
    public:
        explicit parser_helper(const std::string &path, error_manager_ptr error_manager) :
                m_path{path},
                m_error_manager{std::move(error_manager)},
                m_lex{lexer{path, m_error_manager}},
                m_current_token{std::nullopt},
                m_next_token{std::nullopt} {}

        const token_ptr &get_last_token() const {
            if (m_next_token.has_value())
                return *m_next_token;
            if (m_current_token.has_value())
                return *m_current_token;

            assert(false);
            return *m_current_token;
        }

        void check_error_token(const token_ptr &tok) {
            if (tok->has_type<special_token::error>())
                m_error_manager->throw_error(error_type::invalid_token, tok, {tok->get_lexeme()});
        }

        void read_next_token() {
            if (m_next_token.has_value()) {     // If we already peeked a token, we read that
                m_current_token.emplace(std::move(*m_next_token));
                reset_token(m_next_token);
            } else if (m_lex.good() and not m_lex.eof()) {    // Otherwise, we have the lexer read the next token from the input file
                m_current_token.emplace(std::move(m_lex.get_next_token()));
                check_error_token(*m_current_token);
            } else {
                // todo: throw some error here
            }
        }

        const token_ptr &peek_next_token() {
            // The next token is used both for checking for end of lists and for reading optional nodes. If we already tried
            // (and failed) to read an optional node and we immediately next we check for an end of list, we check that we
            // did not already peek the next token to avoid losing the next token that we already peeked.
            if (not m_next_token.has_value() and m_lex.good() and not m_lex.eof()) {
                m_next_token = std::move(m_lex.get_next_token());
                check_error_token(*m_next_token);
            }
            return *m_next_token;
        }

        template<typename required_tok_type>
        void check_next_token(const std::string &msg = "", bool discard = true) {
            read_next_token();

            if constexpr (is_variant_member_v<required_tok_type, token_type>)
                check_token<required_tok_type>(
                        msg.empty() ? parser_helper::to_string<required_tok_type>() : msg,
                        error_type::token_mismatch);
            else if constexpr (is_variant_member_v<required_tok_type, super_token_type>)
                check_token_super_type<required_tok_type>(
                        msg.empty() ? parser_helper::to_string_token_super_type<required_tok_type>() : msg,
                        error_type::token_mismatch);
            else
                m_error_manager->throw_error(error_type::invalid_token, get_next_token(),
                                             {"Unexpected token type."});

            // After successfully verifying that the current token has the correct type, we can delete it
            if (discard) reset_token(m_current_token);
        }

        void check_left_par(const std::string &msg) {
            read_next_token();
            check_token<punctuation_token::lpar>(msg, error_type::missing_lpar);
        }

        void check_right_par(const std::string &msg) {
            read_next_token();
            check_token<punctuation_token::rpar>(msg, error_type::missing_rpar);
        }

        void check_eof(const std::string &msg) {
            read_next_token();
            check_token<special_token::eof>(msg, error_type::expected_eof);
        }

        ast::info get_info(const token_ptr &tok, const std::string &context = "", ast::node_requirement required_tokens = {}) {
            return ast::info{m_path, context, tok->get_row(), tok->get_col(), std::move(required_tokens)};
        }

        ast::info get_next_token_info(const std::string &context = "", ast::node_requirement required_tokens = {}) {
            if (not m_next_token.has_value())
                peek_next_token();

            return get_info(*m_next_token, context, std::move(required_tokens));
        }

        void push_error_info(const std::string &err_info) {
            m_error_manager->push_error_info(err_info);
        }

        void pop_error_info() {
            m_error_manager->pop_error_info();
        }

        template<typename required_tok_type>
        token_ptr get_ast_token(const std::string &msg = "") {
            check_next_token<required_tok_type>(msg, false);
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
                m_error_manager->throw_error(error_type::empty_list, get_next_token(), {"elements"});
            return elems;
        }

        template<class node_type, typename... first_tok_types>
        std::optional<node_type> parse_optional(const std::function<node_type()> &parse_elem) {
            const token_ptr &tok = peek_next_token();
            std::optional<node_type> elem = std::nullopt;

            if (tok->has_either_type<first_tok_types...>()) elem.emplace(parse_elem());
            return elem;
        }

        void throw_error(const error_type err_type, const token_ptr &token, const std::string &msg) {
            m_error_manager->throw_error(err_type, token, {msg});
        }

        void throw_error(const error_type err_type, const ast::info &info, const std::string &msg) {
            m_error_manager->throw_error(err_type, info, {msg});
        }

    private:
        std::string m_path;
        error_manager_ptr m_error_manager;
        lexer m_lex;
        std::optional<token_ptr> m_current_token, m_next_token;

        static void reset_token(std::optional<token_ptr> &tok) {
            tok->reset();
            tok = std::nullopt;
        }

        template<typename required_tok_type>
        void check_token(const std::string &msg, error_type err_type) {
            if (not (*m_current_token)->has_type<required_tok_type>())
                m_error_manager->throw_error(err_type, *m_current_token, {msg});
        }

        template<typename required_tok_super_type>
        void check_token_super_type(const std::string &msg, error_type err_type) {
            if (not (*m_current_token)->has_super_type<required_tok_super_type>())
                m_error_manager->throw_error(err_type, *m_current_token, {msg});
        }

        [[nodiscard]] static std::string to_string(const token_ptr &tok) {
            return std::visit([&](auto &&arg) {
                using arg_type = std::remove_reference_t<decltype(arg)>;
                return parser_helper::to_string<arg_type>();
            }, tok->get_type());
        }

        template<typename tok_type>
        [[nodiscard]] static std::string to_string() {
            return parser_helper::is_ast_token<tok_type>()
                   ? std::string{tok_type::name}
                   : "'" + std::string{tok_type::lexeme} + "'";
        }

        template<typename tok_super_type>
        [[nodiscard]] static std::string to_string_token_super_type() {
            return std::string{tok_super_type::name};
        }

        template<typename tok_type>
        [[nodiscard]] static bool is_ast_token() {
            #define epddl_token_type(token_type) token_type
            return std::is_same_v<get_super_t<tok_type>, epddl_ast_token_type>;
            #undef epddl_token_type
        }

        [[nodiscard]] const token_ptr& get_next_token() const {
            return *m_next_token;
        }
    };
}

#endif //PLANK_PARSER_HELPER_H
