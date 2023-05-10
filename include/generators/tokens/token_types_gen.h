#ifndef EPDDL_TOKEN_TYPES_GEN_H
#define EPDDL_TOKEN_TYPES_GEN_H

#include "../../grammar/tokens/tokens_def.h"
#include "../../grammar/tokens/token_types_def.h"

namespace epddl {
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
#undef epddl_token
#undef epddl_token_type

template<typename TokenType>
using get_super_t = typename TokenType::super_type;

}

#endif //EPDDL_TOKEN_TYPES_GEN_H
