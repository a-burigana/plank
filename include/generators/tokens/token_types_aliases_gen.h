#ifndef EPDDL_TOKEN_TYPES_ALIASES_GEN_H
#define EPDDL_TOKEN_TYPES_ALIASES_GEN_H

namespace epddl {
    template<typename token_type> class token;

/* * * * * * * * * * * * * * * * * *
 *      TOKEN_PTR ALIAS MACRO      *
 * * * * * * * * * * * * * * * * * */
#define token_alias0(t_type, t_name) t_type##_##t_name
#define token_alias(t_type, t_name) token_alias0(t_type, t_name)

#define token_ptr_alias0(t_type, t_name) t_type##_##t_name##_ptr
#define token_ptr_alias(t_type, t_name) token_ptr_alias0(t_type, t_name)

#define epddl_token_type(token_type) token_type
#define epddl_token(t_type, t_scope, t_name, t_lexeme) \
    using token_alias(t_type, t_name) = token<t_type::t_name>; \
    using token_ptr_alias(t_type, t_name) = std::unique_ptr<token_alias(t_type, t_name)>;
#define tokens(tokens) tokens
#define epddl_tokens(_, tokens) tokens
    epddl_all_token_types_def
#undef epddl_tokens
#undef tokens
#undef epddl_token
#undef epddl_token_type

// todo: change back to ptr of variant? in this way it would be consistent with grammar definitions
#define epddl_token_type(token_type) token_type
#define epddl_token(t_type, t_scope, t_name, t_lexeme) token_alias(t_type, t_name)
#define all_tokens(tokens...) \
    using token_variant = std::variant<tokens>; using token_ptr = std::unique_ptr<std::variant<tokens>>;
    epddl_all_tokens
#undef all_tokens
#undef epddl_token
#undef epddl_token_type
}

#endif //EPDDL_TOKEN_TYPES_ALIASES_GEN_H
