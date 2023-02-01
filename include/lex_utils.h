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
    dictionary& operator=(dictionary&&) = delete;   // todo: check delete

    [[nodiscard]] const std::string& to_string(const token_type type) const {
        auto lexeme_it = m_lexemes.find(type);
        return lexeme_it != m_lexemes.end() ? lexeme_it->second : m_lexemes.at(special_value::invalid);
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
    const std::map<const token_type, const std::string> m_lexemes;
    const std::map<const std::string, const token_type> m_valid_keywords;
    const std::map<const token_type, bool> m_is_scope;
};


/*class Special : public Type<special_value> {
public:
    explicit Special(special_value val) :
            Type{val} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { SPECIAL };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { SPECIAL };
        #undef VAL
    }
};

class Punctuation : public Type<punctuation_value> {
public:
    explicit Punctuation(punctuation_value val) :
            Type{val} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { PUNCTUATION };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { PUNCTUATION };
        #undef VAL
    }
};

class Basic : public Type<basic_value> {
public:
    explicit Basic(basic_value val) :
            Type{val} {
        m_lexemes = {};

        #define VAL(name, lexeme) #name,
        m_names = { BASIC };
        #undef VAL
    }
};

class Keyword : public Type<keyword_value> {
public:
    explicit Keyword(keyword_value val) :
            Type{val, true} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { KEYWORD };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { KEYWORD };
        #undef VAL
    }
};

class Connective : public Type<connective_value> {
public:
    explicit Connective(connective_value val) :
            Type{val} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { CONNECTIVE };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { CONNECTIVE };
        #undef VAL
    }
};

class Quantifier : public Type<quantifier_value> {
public:
    explicit Quantifier(quantifier_value val) :
            Type{val, true} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { QUANTIFIER };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { QUANTIFIER };
        #undef VAL
    }
};

class AtomicFormula : public Type<atomic_formula_value> {
public:
    explicit AtomicFormula(atomic_formula_value val) :
            Type{val} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { ATOMIC_FORMULA };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { ATOMIC_FORMULA };
        #undef VAL
    }
};

class Postcondition : public Type<postcondition_value> {
public:
    explicit Postcondition(postcondition_value val) :
            Type{val, true} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { POSTCONDITION };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { POSTCONDITION };
        #undef VAL
    }
};

class Observability : public Type<observability_value> {
public:
    explicit Observability(observability_value val) :
            Type{val, true} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { OBSERVABILITY };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { OBSERVABILITY };
        #undef VAL
    }
};

class AgentGroup : public Type<agent_group_value> {
public:
    explicit AgentGroup(agent_group_value val) :
            Type{val} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { AGENT_GROUP };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { AGENT_GROUP };
        #undef VAL
    }
};

class ReservedType : public Type<reserved_type_value> {
public:
    explicit ReservedType(reserved_type_value val) :
            Type{val} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { RESERVED_TYPE };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { RESERVED_TYPE };
        #undef VAL
    }
};

class Requirement : public Type<requirement_value> {
public:
    explicit Requirement(requirement_value val) :
            Type{val} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { REQUIREMENT };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { REQUIREMENT };
        #undef VAL
    }
};

class ValuedRequirement : public Type<val_requirement_value> {
public:
    explicit ValuedRequirement(val_requirement_value val) :
            Type{val, true} {
        #define VAL(name, lexeme) lexeme,
        m_lexemes = { VAL_REQUIREMENT };
        #undef VAL

        #define VAL(name, lexeme) #name,
        m_names = { VAL_REQUIREMENT };
        #undef VAL
    }
};*/

#endif //EPDDL_LEX_UTILS_H
