#ifndef EPDDL_LEX_UTILS_H
#define EPDDL_LEX_UTILS_H

#include <cstdint>
#include <variant>
#include <vector>
#include "token_types.h"

namespace epddl {
    class Token;
    using token = std::unique_ptr<Token>;
}

#define ENUM(token_type) token_type
#define VAL(_, scope, name, lexeme) name,
enum class SPECIAL_ENUM         : uint8_t { SPECIAL         };
enum class PUNCTUATION_ENUM     : uint8_t { PUNCTUATION     };
enum class BASIC_ENUM           : uint8_t { BASIC           };
enum class KEYWORD_ENUM         : uint8_t { KEYWORD         };
enum class CONNECTIVE_ENUM      : uint8_t { CONNECTIVE      };
enum class QUANTIFIER_ENUM      : uint8_t { QUANTIFIER      };
enum class ATOMIC_FORMULA_ENUM  : uint8_t { ATOMIC_FORMULA  };
enum class POSTCONDITION_ENUM   : uint8_t { POSTCONDITION   };
enum class OBSERVABILITY_ENUM   : uint8_t { OBSERVABILITY   };
enum class AGENT_GROUP_ENUM     : uint8_t { AGENT_GROUP     };
enum class RESERVED_TYPE_ENUM   : uint8_t { RESERVED_TYPE   };
enum class REQUIREMENT_ENUM     : uint8_t { REQUIREMENT     };
enum class VAL_REQUIREMENT_ENUM : uint8_t { VAL_REQUIREMENT };
#undef ENUM
#undef VAL

#define ENUM(token_type) token_type,
using token_type = std::variant<ALL_ENUMS std::monostate>;
#undef ENUM


class dictionary {
public:
    dictionary() :
            #define VAL(token_type, scope, name, lexeme) {token_type::name, lexeme},
            m_lexemes{ ALL_TOKENS },
            #undef VAL
            #define VAL(token_type, scope, name, lexeme) {token_type::name, #name},
            m_names{ ALL_TOKENS },
            #undef VAL
            #define VAL(token_type, scope, name, lexeme) {lexeme, token_type::name},
            m_valid_keywords{ VALID_KEYWORDS },
            #undef VAL
            #define VAL(token_type, scope, name, lexeme) {token_type::name, scope},
            m_is_scope{ ALL_TOKENS }
            #undef VAL
    {}

    dictionary(const dictionary&) = delete;
    dictionary& operator=(const dictionary&) = delete;

    dictionary(dictionary&&) = delete;
    dictionary& operator=(dictionary&&) = delete;

    [[nodiscard]] const std::string& to_string(const token_type type) const {
        auto lexeme_it = m_lexemes.find(type);
        return lexeme_it != m_lexemes.end() ? lexeme_it->second : m_lexemes.at(special_value::invalid);
    }

    [[nodiscard]] const std::string& get_name(const token_type type) const {
        auto lexeme_it = m_names.find(type);
        return lexeme_it != m_names.end() ? lexeme_it->second : m_lexemes.at(special_value::invalid);
    }

    [[nodiscard]] bool is_scope(const token_type type) const {
        auto scope_it = m_is_scope.find(type);
        return scope_it != m_is_scope.end() && scope_it->second;
    }

    [[nodiscard]] bool is_valid_keyword(const std::string& lexeme) const {
        return m_valid_keywords.find(lexeme) != m_valid_keywords.end();
    }

    [[nodiscard]] token_type get_valid_keyword_type(const std::string& lexeme) const {
        auto type_it = m_valid_keywords.find(lexeme);
        return type_it != m_valid_keywords.end() ? type_it->second : std::monostate();
    }

private:
    const std::map<const token_type, const std::string> m_lexemes, m_names;
    const std::map<const std::string, const token_type> m_valid_keywords;
    const std::map<const token_type, bool> m_is_scope;
};

#endif //EPDDL_LEX_UTILS_H
