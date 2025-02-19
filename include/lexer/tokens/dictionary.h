#ifndef EPDDL_DICTIONARY_H
#define EPDDL_DICTIONARY_H

#include <set>
#include <string_view>
#include <variant>

#include "definitions/tokens_def.h"
#include "definitions/token_types_def.h"
#include "definitions/modalities_def.h"
#include "definitions/requirements_def.h"

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

#define epddl_mod_keyword(mod) mod,
                m_valid_modalities{ epddl_modality_keywords },
#undef epddl_mod_keyword

#define epddl_req_keyword(req) req,
                m_valid_requirements{ epddl_requirement_keywords },
                m_valid_val_requirements{ epddl_val_requirement_keywords }
#undef epddl_req_keyword
#undef epddl_token_type
        {}

        dictionary(const dictionary&) = delete;
        dictionary& operator=(const dictionary&) = delete;

        dictionary(dictionary&&) = default;
        dictionary& operator=(dictionary&&) = default;

        [[nodiscard]] bool is_valid_keyword(const std::string& lexeme) const {
            return m_valid_keywords.find(lexeme) != m_valid_keywords.end();
        }

        [[nodiscard]] bool is_valid_modality(const std::string& lexeme) const {
            return m_valid_modalities.find(lexeme) != m_valid_modalities.end();
        }

        [[nodiscard]] bool is_valid_requirement(const std::string& lexeme) const {
            return m_valid_requirements.find(lexeme) != m_valid_requirements.end();
        }

        [[nodiscard]] bool is_valid_val_requirement(const std::string& lexeme) const {
            return m_valid_val_requirements.find(lexeme) != m_valid_val_requirements.end();
        }

    private:
        std::set<std::string> m_valid_keywords, m_valid_modalities, m_valid_requirements, m_valid_val_requirements;
    };
}

#endif //EPDDL_DICTIONARY_H
