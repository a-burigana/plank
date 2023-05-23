#ifndef EPDDL_AST_VARIANT_ELEMENTS_GEN_H
#define EPDDL_AST_VARIANT_ELEMENTS_GEN_H

#include "../../grammar/grammar.h"
#include "ast_forward_decl_gen.h"
//#include "ast_classes_gen.h"

namespace epddl::ast {
    // Type trait for recursively flattening variants of variants
    template <typename T0, typename...>
    struct flatten_variant_helper {
        using type = T0;
    };

    template <typename... Ts1, typename T0, typename... Ts2>
    struct flatten_variant_helper<std::variant<Ts1...>, T0, Ts2...>
        : flatten_variant_helper<std::variant<Ts1..., T0>, Ts2...> {};

    template <typename... Ts1, typename... Ts2, typename... Ts3>
    struct flatten_variant_helper<std::variant<Ts1...>, std::variant<Ts2...>, Ts3...>
        : flatten_variant_helper<std::variant<Ts1...>, Ts2..., Ts3...> {};

    template <typename T>
    using flatten_variant_t = typename flatten_variant_helper<std::variant<>, T>::type;


    template<typename... Ts>
    struct type_list{};

//    template<typename Head, typename Tail>
//    struct _type_list{};
//
//    struct nil{};
//
//    template<typename... Ts>
//    struct build_type_list {};
//
//    template<typename Head, typename... Tail>
//    struct build_type_list<Head, Tail...> {
//        using list = typename _type_list<Head, build_type_list<Tail...>>::list;
//    };
//
//    template<>
//    struct build_type_list<> {
//        using list = nil;
//    };
//
//    template<typename... Ts>
//    using type_list = typename build_type_list<Ts...>::list;


#define epddl_token_type(token_type) token_type
#define type_name(name) name
#define epddl_token(t_type, t_scope, t_name, t_lexeme) token_alias(t_type, t_name)
#define element_name(name) name
#define node(n) unique_ptr(n)
#define leaf(l) unique_ptr(l)
#define element_bnf(nodes...) nodes
#define epddl_variant_element(name, nodes) \
    using name = std::variant<nodes>; \
    using unique_ptr(name) = std::unique_ptr<name>;
    // Declaration of auxiliary types and auxiliary unique pointer types
    epddl_all_variant_element_defs
#undef epddl_variant_element

// todo: use flatten_variant_t?

#undef epddl_token

//#define epddl_token(t_type, t_scope, t_name, t_lexeme) t_type::t_name
//
//#define epddl_variant_element(name, nodes)    \
//    struct name {                             \
//        using syntax_list = type_list<nodes>; \
//    };
//
//    struct choice_point {
//        // Defining syntax lists of BNF choice points
//        epddl_all_variant_element_defs
//    };
//
//#undef epddl_variant_element
#undef element_bnf
#undef leaf
#undef node
#undef element_name
#undef epddl_token
#undef type_name
#undef epddl_token_type

//#define epddl_token_type(token_type) token_type
//#define epddl_token(t_type, t_scope, t_name, t_lexeme) t_type::t_name
//
//#define element_name(name) name
//
//#define terminal(t)               t
//
//#define node(type, name)          type
//#define list_node(type, name)     type
//#define opt_node(type, name)      type
//#define opt_list_node(type, name) type
//
//#define leaf(type, name)          type
//#define list_leaf(type, name)     type
//#define opt_leaf(type, name)      type
//#define opt_list_leaf(type, name) type
//
//#define element_bnf(params...) params
//
//#define epddl_element(name, _, nodes)    \
//    struct name {                             \
//        using syntax_list = type_list<nodes>; \
//    };
//
//    struct bnf_rule {
//        // Defining syntax lists of BNF choice points
//        epddl_all_element_defs
//    };
}

#endif //EPDDL_AST_VARIANT_ELEMENTS_GEN_H
