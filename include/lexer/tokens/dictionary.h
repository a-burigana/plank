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
                m_valid_event_conditions{ epddl_event_condition_tokens_def },
#undef epddl_token
#undef tokens
#undef epddl_tokens

#define epddl_mod_keyword(mod) mod,
                m_valid_modalities{ epddl_modality_keywords },
#undef epddl_mod_keyword

#define epddl_req_keyword(req) req,
                m_valid_requirements{ epddl_requirement_keywords }
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

        [[nodiscard]] bool is_valid_event_condition(const std::string& lexeme) const {
            return m_valid_event_conditions.find(lexeme) != m_valid_event_conditions.end();
        }

    private:
        std::set<std::string> m_valid_keywords, m_valid_modalities, m_valid_requirements, m_valid_event_conditions;
    };
}

#endif //EPDDL_DICTIONARY_H
