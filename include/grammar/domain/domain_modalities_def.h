#ifndef EPDDL_DOMAIN_MODALITIES_DEF_H
#define EPDDL_DOMAIN_MODALITIES_DEF_H

#include "../../tokens/tokens.h"

#define epddl_domain_modalities domain_modalities

#define epddl_all_domain_modalities_element_defs \
    epddl_domain_modalities_def

#define epddl_all_domain_modalities_auxiliary_type_defs

#define epddl_domain_modalities_def \
    epddl_element(                                             \
        ast_class(                                             \
            class_name(epddl_domain_modalities),               \
            class_params(                                      \
                list_param(epddl_tok_modality, modalities)     \
            )                                                  \
        ),                                                     \
        parse_element(                                         \
            terminal(epddl_tok_lpar)                           \
            terminal(epddl_tok_modalities)                     \
            list_terminal(epddl_tok_modality)                  \
            terminal(epddl_tok_rpar)                           \
        )                                                      \
    )


//#define EVAL0(...) __VA_ARGS__
//#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
//#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
//#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
//#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
//#define EVAL(...)  EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
//
//#define MAP_END(...)
//#define MAP_OUT
//#define MAP_COMMA ,
//
//#define MAP_GET_END2() 0, MAP_END
//#define MAP_GET_END1(...) MAP_GET_END2
//#define MAP_GET_END(...) MAP_GET_END1
//#define MAP_NEXT0(test, next, ...) next MAP_OUT
//#define MAP_NEXT1(test, next) MAP_NEXT0(test, next, 0)
//#define MAP_NEXT(test, next)  MAP_NEXT1(MAP_GET_END test, next)
//
//#define MAP0(f, x, y, peek, ...) f(x, y) MAP_NEXT(peek, MAP1)(f, peek, __VA_ARGS__)
//#define MAP1(f, x, y, peek, ...) f(x, y) MAP_NEXT(peek, MAP0)(f, peek, __VA_ARGS__)
//
//#define MAP_LIST_NEXT1(test, next) MAP_NEXT0(test, MAP_COMMA next, 0)
//#define MAP_LIST_NEXT(test, next)  MAP_LIST_NEXT1(MAP_GET_END test, next)
//
//#define MAP_LIST0(f, x, y, peek, ...) f(x, y) MAP_LIST_NEXT(peek, MAP_LIST1)(f, peek, __VA_ARGS__)
//#define MAP_LIST1(f, x, y, peek, ...) f(x, y) MAP_LIST_NEXT(peek, MAP_LIST0)(f, peek, __VA_ARGS__)
//
///**
// * Applies the function macro `f` to each of the remaining parameters.
// */
//#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
//
///**
// * Applies the function macro `f` to each of the remaining parameters and
// * inserts commas between the results.
// */
//#define MAP_LIST(f, ...) EVAL(MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
//
//
//
//#define dummy \
//    class_def(         \
//        param(int, x), \
//        param(char, c), \
//        list_param(double, d) \
//    )
//
//#define comma ,
//
//#define expand(x) x
//#define param(type, name) type, name
//#define list_param(type, name) std::list<type>, name
//#define constructor_params_(type, name) type p_##name
//#define constructor_init_(type, name) m_##name{std::move(p_##name)}
//#define class_attributes_(type, name) const type m_##name;
//
//
//#define class_def(params...) \
//    class cl {                \
//    public:                   \
//        explicit cl(MAP_LIST(constructor_params_, params)) : MAP_LIST(constructor_init_, params) {} \
//                             \
//    private:                 \
//        MAP(class_attributes_, params)                                              \
//    };
//
//dummy

#endif //EPDDL_DOMAIN_MODALITIES_DEF_H
