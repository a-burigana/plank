#ifndef EPDDL_TOKEN_TYPES_H
#define EPDDL_TOKEN_TYPES_H

#include <cstdint>
#include <memory>
#include "../grammar/tokens/tokens_def.h"

namespace epddl {
    // Macro expansion of all token types
//    enum class token_type : uint8_t {
//        #define token_alias0(t_type, t_name) t_type##_##t_name
//        #define token_alias(t_type, t_name) token_alias0(t_type, t_name)
//
//        #define epddl_token_type(token_type) token_type
//        #define epddl_token(t_type, t_scope, t_name, t_lexeme) token_alias(t_type, t_name)
//        #define all_tokens(tokens...) tokens
//                epddl_all_tokens
//        #undef all_tokens
//        #undef epddl_token
//        #undef epddl_token_type
//        #undef token_alias
//        #undef token_alias0
//    };


}

#endif //EPDDL_TOKEN_TYPES_H
