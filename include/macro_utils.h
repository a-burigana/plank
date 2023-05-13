#ifndef EPDDL_MACRO_UTILS_H
#define EPDDL_MACRO_UTILS_H

/*
 * IF: if condition is true (cond=1), argument 'then' is macro-expanded. Otherwise, nothing happens.
 * IF_LIST: same as IF, but it prepends a comma before the argument.
 * IFN: if condition is false (cond=0), argument 'then' is macro-expanded. Otherwise, nothing happens.
 */

#define IF(cond, then) IF_IMPL(cond, then)
#define IF_IMPL(cond, then) IF_##cond(then)
#define IF_1(then) then
#define IF_0(then)

#define IF_LIST(cond, then) IF_IMPL_LIST(cond, then)
#define IF_IMPL_LIST(cond, then) IF_LIST_##cond(then)
#define IF_LIST_1(then) MAP_COMMA then
#define IF_LIST_0(then)

#define IFN(cond, then) IFN_IMPL(cond, then)
#define IFN_IMPL(cond, then) IFN_##cond(then)
#define IFN_1(then)
#define IFN_0(then) then


// Credits: William Swanson and René Kijewski
// https://github.com/swansontec/map-macro

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL(...)  EVAL4(EVAL4(EVAL4(__VA_ARGS__)))

#define END_LIST (), 0

#define MAP_END(...)
#define MAP_OUT
#define MAP_COMMA ,

#define MAP_GET_END() 0, MAP_END
//#define MAP_GET_END1(...) MAP_GET_END2
//#define MAP_GET_END(...) MAP_GET_END1

#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) MAP_NEXT0(test, next, 0)
#define MAP_NEXT(test, next)  MAP_NEXT1(MAP_GET_END test, next)

#define MAP_IF0(f, cond, x, y, peek, ...) IF(cond, f(x, y)) MAP_NEXT(peek, MAP_IF1)(f, peek, __VA_ARGS__)
#define MAP_IF1(f, cond, x, y, peek, ...) IF(cond, f(x, y)) MAP_NEXT(peek, MAP_IF0)(f, peek, __VA_ARGS__)

#define CHECK_EMPTY_ARGS(f, cond, x, y, peek, ...) MAP_NEXT(cond, MAP_IF1)(f, cond, x, y, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters.
 */
//#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
#define MAP_IF(f, ...) EVAL(CHECK_EMPTY_ARGS(f, __VA_ARGS__, END_LIST))

#define MAP_LIST0(f, cond, x, y, peek, ...) IF_LIST(cond, f(x, y)) MAP_NEXT(peek, MAP_LIST1)(f, peek, __VA_ARGS__)
#define MAP_LIST1(f, cond, x, y, peek, ...) IF_LIST(cond, f(x, y)) MAP_NEXT(peek, MAP_LIST0)(f, peek, __VA_ARGS__)

#define MAP_LIST_PREFIX0(f, cond, x, y, peek, ...) IF(cond, f(x, y)) MAP_NEXT(peek, IF(cond, MAP_LIST1) IFN(cond, MAP_LIST_PREFIX1)) (f, peek, __VA_ARGS__)
#define MAP_LIST_PREFIX1(f, cond, x, y, peek, ...) IF(cond, f(x, y)) MAP_NEXT(peek, IF(cond, MAP_LIST1) IFN(cond, MAP_LIST_PREFIX0)) (f, peek, __VA_ARGS__)

#define CHECK_EMPTY_ARGS_LIST(f, cond, x, y, peek, ...) MAP_NEXT(cond, MAP_LIST_PREFIX1)(f, cond, x, y, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters and
 * inserts commas between the results.
 */
//#define MAP_LIST(f, ...) EVAL(MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
#define MAP_IF_LIST(f, ...) EVAL(CHECK_EMPTY_ARGS_LIST(f, __VA_ARGS__, END_LIST))

#endif //EPDDL_MACRO_UTILS_H
