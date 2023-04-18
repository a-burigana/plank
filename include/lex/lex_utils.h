#ifndef EPDDL_LEX_UTILS_H
#define EPDDL_LEX_UTILS_H

#include <set>
#include <string_view>
#include <variant>

#include "token_types_generator.h"
#include "token_types_aliases_generator.h"
#include "../grammar/requirements.h"

namespace epddl {
    class dictionary {
    public:
        dictionary() :
#define epddl_token_type(token_type) token_type
#define epddl_tokens(_, tokens) tokens
#define tokens(tokens) tokens
#define epddl_token(token_type, scope, name, lexeme) lexeme,
                m_valid_keywords{ epddl_valid_keywords_def },
#undef epddl_token
#undef tokens
#undef epddl_tokens
#define epddl_req_keyword(req) req,
                m_valid_requirements{epddl_requirement_keywords },
                m_valid_val_requirements{epddl_val_requirement_keywords }
#undef epddl_req_keyword
#undef epddl_token_type
        {}

        dictionary(const dictionary&) = delete;
        dictionary& operator=(const dictionary&) = delete;

        dictionary(dictionary&&) = delete;
        dictionary& operator=(dictionary&&) = delete;

        [[nodiscard]] bool is_valid_keyword(const std::string& lexeme) const {
            return m_valid_keywords.find(lexeme) != m_valid_keywords.end();
        }

        [[nodiscard]] bool is_valid_requirement(const std::string& lexeme) const {
            return m_valid_requirements.find(lexeme) != m_valid_requirements.end();
        }

        [[nodiscard]] bool is_valid_val_requirement(const std::string& lexeme) const {
            return m_valid_val_requirements.find(lexeme) != m_valid_val_requirements.end();
        }

    private:
        const std::set<const std::string> m_valid_keywords, m_valid_requirements, m_valid_val_requirements;
    };
}

#endif //EPDDL_LEX_UTILS_H
