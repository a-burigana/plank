#ifndef EPDDL_GENERATOR_MACROS_H
#define EPDDL_GENERATOR_MACROS_H


// todo: create x-marco representations of recursive functions and expand them to build recursive macros that use
//       NEXT as below (e.g., MAP_IF0/MAP_IF1, MAP_2ARY_IF_LIST0/MAP_2ARY_IF_LIST1, ...)


/*
 * IF: if condition is true (cond=1), argument 'then' is macro-expanded. Otherwise, nothing happens.
 * IF_LIST: same as IF, but it prepends a comma before the argument.
 * IFN: if condition is false (cond=0), argument 'then' is macro-expanded. Otherwise, nothing happens.
 */

// Credits: Travis Gockel
// https://stackoverflow.com/questions/46019370/conditional-definition-of-elements-in-an-x-macro

#define IF(cond, then) IF_IMPL(cond, then)
#define IF_IMPL(cond, then) IF_##cond(then)
#define IF_1(then) then
#define IF_0(then)

#define IF_LIST(cond, then) IF_IMPL_LIST(cond, then)
#define IF_IMPL_LIST(cond, then) IF_LIST_##cond(then)
#define IF_LIST_1(then) COMMA then
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

#define END(...)
#define OUT
#define COMMA ,

#define GET_END() 0, END
//#define GET_END1(...) GET_END2
//#define GET_END(...) GET_END1

#define NEXT0(test, next, ...) next OUT
#define NEXT1(test, next) NEXT0(test, next, 0)
#define NEXT(test, next)  NEXT1(GET_END test, next)

/*
 * MAP_IF
 */
#define MAP_IF0(f, cond, x, y, peek, ...) IF(cond, f(x, y)) NEXT(peek, MAP_IF1)(f, peek, __VA_ARGS__)
#define MAP_IF1(f, cond, x, y, peek, ...) IF(cond, f(x, y)) NEXT(peek, MAP_IF0)(f, peek, __VA_ARGS__)

#define CHECK_EMPTY_ARGS_MAP(f, cond, x, y, peek, ...) NEXT(cond, MAP_IF1)(f, cond, x, y, peek, __VA_ARGS__)

/**
 * Applies the binary function macro `f` to each of the remaining pairs if a condition is satisfied.
 */
//#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
#define MAP_IF(f, ...) EVAL(CHECK_EMPTY_ARGS_MAP(f, __VA_ARGS__, END_LIST))


/*
 * MAP_2ARY_IF_LIST
 */
#define MAP_2ARY_IF_LIST0(f, cond, x, y, peek, ...) IF_LIST(cond, f(x, y)) NEXT(peek, MAP_2ARY_IF_LIST1)(f, peek, __VA_ARGS__)
#define MAP_2ARY_IF_LIST1(f, cond, x, y, peek, ...) IF_LIST(cond, f(x, y)) NEXT(peek, MAP_2ARY_IF_LIST0)(f, peek, __VA_ARGS__)

#define MAP_2ARY_LIST_IF_PREFIX0(f, cond, x, y, peek, ...) IF(cond, f(x, y)) NEXT(peek, IF(cond, MAP_2ARY_IF_LIST1) IFN(cond, MAP_2ARY_LIST_IF_PREFIX1)) (f, peek, __VA_ARGS__)
#define MAP_2ARY_LIST_IF_PREFIX1(f, cond, x, y, peek, ...) IF(cond, f(x, y)) NEXT(peek, IF(cond, MAP_2ARY_IF_LIST1) IFN(cond, MAP_2ARY_LIST_IF_PREFIX0)) (f, peek, __VA_ARGS__)

#define CHECK_EMPTY_ARGS_MAP_2ARY_IF_LIST(f, cond, x, y, peek, ...) NEXT(cond, MAP_2ARY_LIST_IF_PREFIX1)(f, cond, x, y, peek, __VA_ARGS__)

/**
 * Applies the binary function macro `f` to each of the remaining pairs if a condition is satisfied and
 * inserts commas between the results.
 */
//#define MAP_LIST(f, ...) EVAL(MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
#define MAP_2ARY_IF_LIST(f, ...) EVAL(CHECK_EMPTY_ARGS_MAP_2ARY_IF_LIST(f, __VA_ARGS__, END_LIST))


/*
 * MAP_4ARY_IF_LIST
 */
#define MAP_4ARY_IF_LIST0(f, cond, w, x, y, z, peek, ...) IF_LIST(cond, f(w, x, y, z)) NEXT(peek, MAP_4ARY_IF_LIST1)(f, peek, __VA_ARGS__)
#define MAP_4ARY_IF_LIST1(f, cond, w, x, y, z, peek, ...) IF_LIST(cond, f(w, x, y, z)) NEXT(peek, MAP_4ARY_IF_LIST0)(f, peek, __VA_ARGS__)

#define MAP_4ARY_LIST_IF_PREFIX0(f, cond, w, x, y, z, peek, ...) IF(cond, f(w, x, y, z)) NEXT(peek, IF(cond, MAP_4ARY_IF_LIST1) IFN(cond, MAP_4ARY_LIST_IF_PREFIX1)) (f, peek, __VA_ARGS__)
#define MAP_4ARY_LIST_IF_PREFIX1(f, cond, w, x, y, z, peek, ...) IF(cond, f(w, x, y, z)) NEXT(peek, IF(cond, MAP_4ARY_IF_LIST1) IFN(cond, MAP_4ARY_LIST_IF_PREFIX0)) (f, peek, __VA_ARGS__)

#define CHECK_EMPTY_ARGS_MAP_4ARY_IF_LIST(f, cond, w, x, y, z, peek, ...) NEXT(cond, MAP_4ARY_LIST_IF_PREFIX1)(f, cond, w, x, y, z, peek, __VA_ARGS__)

/**
 * Applies the quaternary function macro `f` to each of the remaining 4-tuples if a condition is satisfied and
 * inserts commas between the results.
 */
//#define MAP_LIST(f, ...) EVAL(MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
#define MAP_4ARY_IF_LIST(f, ...) EVAL(CHECK_EMPTY_ARGS_MAP_4ARY_IF_LIST(f, __VA_ARGS__, END_LIST))


/*
 * PARSE
 */
#define PARSE_ELEMS0(_, f, x, y, z, peek, ...) f(x, y, z) NEXT(peek, PARSE_ELEMS1)(peek, __VA_ARGS__)
#define PARSE_ELEMS1(_, f, x, y, z, peek, ...) f(x, y, z) NEXT(peek, PARSE_ELEMS0)(peek, __VA_ARGS__)

/**
 * Input: list of 5-tuples <cond, parse_function, type, tok_type, name>, where:
 *  - cond: the value is ignored here
 *  - parse_function: the function-like macro to be invoked on the remaining arguments
 *  - type: type-category of the token (if we are parsing a leaf or a terminal) or type of the node (otherwise)
 *  - tok_type: type of the token (if we are parsing a leaf or a terminal) or null (otherwise)
 *  - name: name of the ast element (if we are parsing a leaf or a node) or null (otherwise)
 *
 *  Output: expands the function-like macro parse_function(type, tok_type, name) for each 5-tuple in the input list
 */
#define PARSE_ELEMS(...) EVAL(PARSE_ELEMS1(__VA_ARGS__, END_LIST))

/*
 * PARSE_VARIANT
 */
#define PARSE_VARIANT_ELEMS0(var_type, _, f, x, y, peek, ...) f(var_type, x, y) NEXT(peek, PARSE_VARIANT_ELEMS1)(var_type, peek, __VA_ARGS__)
#define PARSE_VARIANT_ELEMS1(var_type, _, f, x, y, peek, ...) f(var_type, x, y) NEXT(peek, PARSE_VARIANT_ELEMS0)(var_type, peek, __VA_ARGS__)

/**
 * Input: list of 4-tuples <cond, parse_function, type, tok_type>, where:
 *  - cond: the value is ignored here
 *  - parse_function: the function-like macro to be invoked on the remaining arguments
 *  - type: type-category of the token (if we are parsing a leaf or a terminal) or type of the node (otherwise)
 *  - tok_type: type of the token (if we are parsing a leaf or a terminal) or null (otherwise)
 *
 *  Output: expands the function-like macro parse_function(type, tok_type) for each 4-tuple in the input list
 */
#define PARSE_VARIANT_ELEMS(var_type, ...) EVAL(PARSE_VARIANT_ELEMS1(var_type, __VA_ARGS__, END_LIST))

#endif //EPDDL_GENERATOR_MACROS_H








//#define FILTER_LIST0(cond, x, y, peek, ...) IF_LIST(cond, x) IF(cond, y) NEXT(peek, FILTER_LIST1)(peek, __VA_ARGS__)
//#define FILTER_LIST1(cond, x, y, peek, ...) IF_LIST(cond, x) IF(cond, y) NEXT(peek, FILTER_LIST0)(peek, __VA_ARGS__)
//
//#define FILTER_LIST_PREFIX0(cond, x, y, peek, ...) IF(cond, x) IF(cond, y) NEXT(peek, IF(cond, FILTER_LIST1) IFN(cond, FILTER_LIST_PREFIX1)) (peek, __VA_ARGS__)
//#define FILTER_LIST_PREFIX1(cond, x, y, peek, ...) IF(cond, x) IF(cond, y) NEXT(peek, IF(cond, FILTER_LIST1) IFN(cond, FILTER_LIST_PREFIX0)) (peek, __VA_ARGS__)
//
//#define FILTER_CHECK_EMPTY_ARGS(cond, x, y, peek, ...) NEXT(cond, FILTER_LIST_PREFIX1)(cond, x, y, peek, __VA_ARGS__)
//
///**
// * Applies the function macro `f` to each of the remaining parameters and
// * inserts commas between the results.
// */
////#define MAP_LIST(f, ...) EVAL(MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
//#define FILTER_LIST(...) EVAL(FILTER_CHECK_EMPTY_ARGS(__VA_ARGS__, END_LIST))
//
//#define CHECK_FILTERED_LIST(m, cond, x, y, peek, ...) NEXT(cond, m)(m, cond, x, y, peek, __VA_ARGS__)
//
////#define IFN_EMPTY(m, cond, x, y, peek, ...) NEXT(cond, m)(m, cond, x, y, peek, __VA_ARGS__)
//#define IFN_EMPTY(m, ...) CHECK_FILTERED_LIST(m, __VA_ARGS__, END_LIST)
