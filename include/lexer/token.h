#ifndef EPDDL_TOKEN_H
#define EPDDL_TOKEN_H

#include <optional>
#include <string>
#include "../generators/tokens/token_types_gen.h"

#define epddl_token_type(token_type) token_type

namespace epddl {
    /*
     * The token class. Each token has its own type, which is given as a template
     * parameter. See directory grammar/tokens.
     */
    class token;
    using token_ptr = std::unique_ptr<token>;

    class token  {
    public:
//        token(token_type type, unsigned long row, unsigned long col, std::optional<std::string> lexeme = std::nullopt);
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

//        template<typename... other_token_types>
//        [[nodiscard]] bool has_either_type() const;

        template<typename other_token_type>
        [[nodiscard]] bool has_either_type() const {
            return has_type<other_token_type>();
        }

        template<typename first_token_type, typename second_token_type, typename... other_token_types>
        [[nodiscard]] bool has_either_type() const {
            return has_type<first_token_type>() or has_either_type<second_token_type, other_token_types...>();
        }

        [[nodiscard]] [[nodiscard]] token_type get_type() const {
            return m_type;
        }

        [[nodiscard]] [[nodiscard]] unsigned long get_row() const {
            return m_row;
        }

        [[nodiscard]] [[nodiscard]] unsigned long get_col() const {
            return m_col;
        }

        [[nodiscard]] [[nodiscard]] std::string get_lexeme() const {
            return std::visit([&](auto &&tok_var_type) {
                using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;

                if (std::is_same_v<typename tok_type::super_type, epddl_pattern_token_type> and m_lexeme.has_value())
                    return *m_lexeme;
                else
                    return std::string{tok_type::lexeme};
            }, m_type);
        }

        [[nodiscard]] [[nodiscard]] std::string get_name() const {
            return std::visit([](auto &&tok_var_type) {
                using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
                return std::string{tok_type::name};
            }, m_type);
        }

        [[nodiscard]] [[nodiscard]] bool is_scope() const {
            return std::visit([](auto &&tok_var_type) {
                using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
                return tok_type::is_scope;
            }, m_type);
        }

        [[nodiscard]] [[nodiscard]] std::string to_string() const {
            return std::visit([&](auto &&tok_var_type) {
                using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;

                if (std::is_same_v<typename tok_type::super_type, epddl_punctuation_token_type>) {
                    return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{tok_type::name} + std::string{"}"};
                } else if (std::is_same_v<typename tok_type::super_type, epddl_pattern_token_type> and m_lexeme.has_value()) {
                    return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{tok_type::name} + std::string{":\""} + *m_lexeme + std::string{"\"}"};
                } else {
                    return std::string{"{"} + std::to_string(m_row) + std::string{":"} + std::to_string(m_col) + std::string{", "} + std::string{tok_type::lexeme} + std::string{"}"};
                }
            }, m_type);
        }

//        [[nodiscard]] std::string get_string()              const { return m_lexeme.has_value() ? m_lexeme.value() : ""; }


//        [[nodiscard]] std::string to_string() const;

//        template<typename other_token_type>
//        [[nodiscard]] bool          has_type() const;
//        [[nodiscard]] token_type    get_type() const;
//        [[nodiscard]] unsigned long get_row()  const;
//        [[nodiscard]] unsigned long get_col()  const;
//
//        [[nodiscard]] std::string get_lexeme() const;
//        [[nodiscard]] std::string get_name  () const;
//        [[nodiscard]] std::string to_string () const;
//        [[nodiscard]] bool        is_scope  () const;

    private:
        token_type m_type;
        std::optional<std::string> m_lexeme;
        unsigned long m_row, m_col;
    };
}

#undef epddl_token_type

#endif //EPDDL_TOKEN_H
