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

#ifndef EPDDL_TOKEN_H
#define EPDDL_TOKEN_H

#include <optional>
#include <string>
#include <memory>
#include "token_types.h"

#define epddl_token_type(token_type) token_type

namespace epddl {
    class token;
    using token_ptr = std::shared_ptr<token>;

    class token  {
    public:
        token(token_type type, unsigned long row, unsigned long col, std::optional<std::string> lexeme) :
                m_type{type},
                m_lexeme{std::move(lexeme)},
                m_row{row},
                m_col{col} {}

        token(const token&) = delete;
        token(token&&) noexcept = default;

        token& operator=(const token&) = delete;
        token& operator=(token&&) = default;

        template<typename other_token_type>
        [[nodiscard]] bool has_type() const {
            return std::holds_alternative<other_token_type>(m_type);
        }

        template<typename other_token_type>
        [[nodiscard]] bool has_either_type() const {
            return has_type<other_token_type>();
        }

        template<typename first_token_type, typename second_token_type, typename... other_token_types>
        [[nodiscard]] bool has_either_type() const {
            return has_type<first_token_type>() or has_either_type<second_token_type, other_token_types...>();
        }

        [[nodiscard]] token_type get_type() const {
            return m_type;
        }

        [[nodiscard]] unsigned long get_row() const {
            return m_row;
        }

        [[nodiscard]] unsigned long get_col() const {
            return m_col;
        }

        [[nodiscard]] std::string get_lexeme() const {
            return std::visit([&](auto &&tok_var_type) {
                using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;

                if (std::is_same_v<typename tok_type::super_type, epddl_ast_token_type> and m_lexeme.has_value())
                    return *m_lexeme;
                else
                    return std::string{tok_type::lexeme};
            }, m_type);
        }

        [[nodiscard]] std::string get_name() const {
            return std::visit([](auto &&tok_var_type) {
                using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
                return std::string{tok_type::name};
            }, m_type);
        }

        [[nodiscard]] bool is_scope() const {
            return std::visit([](auto &&tok_var_type) {
                using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
                return tok_type::is_scope;
            }, m_type);
        }

        [[nodiscard]] std::string to_string() const {
            return std::visit([&](auto &&tok_var_type) {
                using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;

                if (std::is_same_v<typename tok_type::super_type, epddl_punctuation_token_type>) {
                    return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{tok_type::name} + std::string{"}"};
                } else if (std::is_same_v<typename tok_type::super_type, epddl_ast_token_type> and m_lexeme.has_value()) {
                    return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{tok_type::name} + std::string{":\""} + *m_lexeme + std::string{"\"}"};
                } else {
                    return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{tok_type::lexeme} + std::string{"}"};
                }
            }, m_type);
        }

    private:
        token_type m_type;
        std::optional<std::string> m_lexeme;
        unsigned long m_row, m_col;
    };
}

#undef epddl_token_type

#endif //EPDDL_TOKEN_H
