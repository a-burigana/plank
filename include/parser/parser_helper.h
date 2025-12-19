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
        explicit parser_helper(const std::string &path) :
                m_path{path},
                m_lex{lexer{path}},
                m_current_token{std::nullopt},
                m_next_token{std::nullopt},
                m_lpar_count{0} {}

        const token_ptr &get_last_token() const {
            if (m_next_token.has_value())
                return *m_next_token;
            if (m_current_token.has_value())
                return *m_current_token;

            assert(false);
            return *m_current_token;
        }

        void read_next_token() {
            if (m_next_token.has_value()) {     // If we already peeked a token, we read that
                m_current_token.emplace(std::move(*m_next_token));
                reset_token(m_next_token);
            } else if (m_lex.good() and not m_lex.eof())      // Otherwise, we have the lexer read the next token from the input file
                m_current_token.emplace(std::move(m_lex.get_next_token()));
            else {
                // todo: throw some error here
            }
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
                throw_error(get_next_token(), std::string{"Unexpected token type."});

            if (discard) reset_token(m_current_token);      // After successfully verifying that the current token has the correct type, we can delete it
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

        void push_info(ast::info info, const std::string &context) {
            info.set_context("In " + context + ":");
            m_infos.emplace_back(info);
        }

        void pop_info() {
            m_infos.pop_back();
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

        void throw_error(const token_ptr& token, const std::string& error = "") {
            auto context = build_error_context();
            throw EPDDLParserException{m_path, token->get_row(), token->get_col(), context + error};
        }

        void throw_error(const token_ptr& token, const std::string& msg, const error_type err_type) {
            auto context = build_error_context();
            throw EPDDLParserException{m_path, token->get_row(), token->get_col(),
                                       context + get_error_message(msg, err_type)};
        }

    private:
        std::string m_path;
        lexer m_lex;
        std::optional<token_ptr> m_current_token, m_next_token;

        std::list<ast::info> m_infos;
        unsigned long m_lpar_count;

        std::string build_error_context() {
            std::string context;
            unsigned long indent = 1;

            for (const ast::info &info : m_infos) {
                for (unsigned long i = 0; i < indent; ++i)
                    context += INDENT;

                context += info.m_context + "\n";
                ++indent;
            }

            /*for (const auto &[lpar_count, tok] : m_scopes) {
                for (unsigned long i = 0; i < indent; ++i)
                    context += INDENT;

                context += "In ... declaration " + parser_helper::to_string(tok) + "\n";
                ++indent;
            }*/

            for (unsigned long i = 0; i < indent; ++i)
                context += INDENT;

            return std::move(context);
        }

        static void reset_token(std::optional<token_ptr> &tok) {
            tok->reset();
            tok = std::nullopt;
        }

        std::string get_error_message(const std::string &msg, const error_type err_type) const {
            switch (err_type) {
                case token_mismatch:
                    return error_manager::get_token_mismatch_error(msg, get_last_token());
                case unexpected_token:
                    return error_manager::get_unexpected_token_error(msg);
                case missing_lpar:
                    return error_manager::get_missing_lpar_error(msg);
                case missing_rpar:
                    return error_manager::get_missing_rpar_error(msg);
                case bad_obs_cond:
                    return error_manager::get_bad_obs_condition_error(msg);
                case expected_eof:
                    return error_manager::get_expected_eof_error(msg);
                case unexpected_eof:
                    return error_manager::get_unexpected_eof_error(msg);
            }
        }

        template<typename required_tok_type>
        void check_token(const std::string &msg, error_type err_type) {
            if (not (*m_current_token)->has_type<required_tok_type>())
                throw_error(*m_current_token, get_error_message(msg, err_type));
        }

        template<typename required_tok_super_type>
        void check_token_super_type(const std::string &msg, error_type err_type) {
            if (not (*m_current_token)->has_super_type<required_tok_super_type>())
                throw_error(*m_current_token, get_error_message(msg, err_type));
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

#endif //EPDDL_PARSER_HELPER_H
