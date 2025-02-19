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

#ifndef EPDDL_TOKEN_TYPES_H
#define EPDDL_TOKEN_TYPES_H

#include <string_view>
#include "definitions/tokens_def.h"
#include "definitions/token_types_def.h"

namespace epddl {
    /* * * * * * * * * * * * * * * * * *
     *     TOKEN STRUCTS DEFINITION    *
     * * * * * * * * * * * * * * * * * */
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
    #undef epddl_token_type

    /* * * * * * * * * * * * * * * * * *
     *      TOKEN TYPE DEFINITION      *
     * * * * * * * * * * * * * * * * * */

    #define epddl_token_type(token_type) token_type
    #define epddl_token(t_type, t_scope, t_name, t_lexeme) t_type::t_name
    #define all_tokens(tokens...) using token_type = std::variant<tokens>;
        epddl_all_tokens
    #undef all_tokens
    #undef epddl_token
    #undef epddl_token_type
}

#endif //EPDDL_TOKEN_TYPES_H
