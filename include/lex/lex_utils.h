#ifndef EPDDL_LEX_UTILS_H
#define EPDDL_LEX_UTILS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <string_view>
#include <variant>
#include <vector>
#include "../tokens/token_types.h"
#include "../grammar/requirements.h"

namespace epddl {
    template<typename token_type>
    class token;

#define epddl_token_type(token_type) token_type

#define epddl_token(t_type, t_scope, t_name, t_lexeme) \
    struct t_name {                                         \
        using super_type = t_type;                          \
        static constexpr std::string_view lexeme{t_lexeme}; \
        static constexpr std::string_view name{#t_name};    \
        static constexpr bool is_scope = t_scope;           \
    };

#define tokens(tokens) tokens
#define epddl_tokens(token_type, tokens) struct token_type { tokens };
    epddl_all_token_types_def
#undef epddl_tokens
#undef tokens
#undef epddl_token

/* * * * * * * * * * * * * * * * * *
 *      TOKEN_PTR ALIAS MACRO      *
 * * * * * * * * * * * * * * * * * */
#define token_ptr_alias(t_type, t_name) t_type##_##t_name##_ptr

#define epddl_token(t_type, t_scope, t_name, t_lexeme) using token_ptr_alias(t_type, t_name) = std::unique_ptr<token<t_type::t_name>>;
#define tokens(tokens) tokens
#define epddl_tokens(_, tokens) tokens
    epddl_all_token_types_def
#undef epddl_tokens
#undef tokens
#undef epddl_token

//#define epddl_token(t_type, t_scope, t_name, t_lexeme) token_t<t_type::t_name>
//#define all_tokens(tokens...) using token = std::variant<tokens>;
//    epddl_all_tokens
//#undef all_tokens
//#undef epddl_token
#define epddl_token(t_type, t_scope, t_name, t_lexeme) token_ptr_alias(t_type, t_name)
#define all_tokens(tokens...) using token_ptr = std::variant<tokens>;
    epddl_all_tokens
#undef all_tokens
#undef epddl_token

//    using token_ptr = std::unique_ptr<token>;


class dictionary {
public:
    dictionary() :
            #define epddl_tokens(_, tokens) tokens
            #define tokens(tokens) tokens
            #define epddl_token(token_type, scope, name, lexeme) lexeme,
            m_valid_keywords{ epddl_valid_keywords_def },
            #undef epddl_token
            #undef tokens
            #undef epddl_tokens
            #define epddl_req(req) req,
            m_valid_requirements{ epddl_requirements },
            m_valid_val_requirements{ epddl_val_requirements }
            #undef epddl_req
    {}

    dictionary(const dictionary&) = delete;
    dictionary& operator=(const dictionary&) = delete;

    dictionary(dictionary&&) = delete;
    dictionary& operator=(dictionary&&) = delete;

    [[nodiscard]] bool is_valid_keyword(const std::string& lexeme) const {
        return m_valid_keywords.find(lexeme) != m_valid_keywords.end();
    }

    [[nodiscard]] bool is_valid_requirement(const std::string& lexeme) const {
        return (m_valid_requirements.find(lexeme) != m_valid_requirements.end()) ||
               (m_valid_val_requirements.find(lexeme) != m_valid_val_requirements.end());
    }

    [[nodiscard]] bool is_valid_val_requirement(const std::string& lexeme) const {
        return m_valid_val_requirements.find(lexeme) != m_valid_val_requirements.end();
    }

private:
    const std::set<const std::string> m_valid_keywords, m_valid_requirements, m_valid_val_requirements;
};

#undef epddl_token_type
}

#endif //EPDDL_LEX_UTILS_H
