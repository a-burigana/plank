#include <memory>
#include <optional>
#include <type_traits>
#include "../include/parser/parser.h"
#include "../include/traits.h"
#include "../include/epddl_exception.h"

using namespace epddl;

parser::parser(lexer &lex) :
    m_lex{lex},
    m_current_token{std::nullopt},
    m_extra_token{std::nullopt},
    m_next_tokens{},
    m_cursor_token_index{0},
    m_is_choice_point{false},
    m_was_choice_point{false},
    m_is_optional_node{false},
    m_lpar_count{0} {}

ast::domain_ptr parser::parse() {
    return std::move(parse_domain());
}

void parser::enter_choice_point() {
    m_is_choice_point  = true;
    m_was_choice_point = true;
}

void parser::exit_choice_point() {
    m_is_choice_point  = false;
    m_was_choice_point = false;
    m_next_tokens.clear();
    m_cursor_token_index = 0;
}

void parser::reset_choice_point() {
    m_cursor_token_index = 0;
}

void parser::throw_error(const token_ptr& token, const std::string& file, const std::string& error) const {
    if (m_is_choice_point or m_is_optional_node)
        throw EPDDLBadChoicePointException{file, lexer::get_row(token), lexer::get_col(token), error};
    else if (not m_was_choice_point)
        throw EPDDLParserException{file, lexer::get_row(token), lexer::get_col(token), error};
}

template<typename token_type>
bool parser::has_type(const token_ptr &tok) const {
    return std::holds_alternative<token<token_type>>(*tok);
}

void parser::peek_next_token() {
    if (m_is_optional_node)
        peek_extra_token();
    else if (m_extra_token.has_value())
        // If we previously used the extra token to store a token (either because we checked for an end of list,
        // or because we were parsing an optional node) then 'm_extra_token' contains a token. In this case,
        // we move this token to the end of the 'm_next_tokens' list and we reset 'm_extra_token'.
        move_extra_token();
    else if (m_lex.good() and not m_lex.eof())
        // Otherwise, we simply have the lexer retrieve the next token from the input file.
        m_next_tokens.push_back(std::move(m_lex.get_next_token()));

    update_scopes(get_last_peeked_token(false));
}

void parser::peek_extra_token() {
    // The extra token is used both for checking for end of lists and for reading optional nodes. If we already tried
    // (and failed) to read an optional node and we immediately next we check for an end of list, we check that we
    // did not already peek an extra token to avoid losing the extra token that we already peeked.
    if (not m_extra_token.has_value() and m_lex.good() and not m_lex.eof())
        m_extra_token.emplace(std::move(m_lex.get_next_token()));
}

void parser::reset_extra_token() {
    m_extra_token->reset();
    m_extra_token = std::nullopt;
}

void parser::move_extra_token() {
    m_next_tokens.push_back(std::move(*m_extra_token));
    reset_extra_token();
}

token_ptr& parser::get_last_peeked_token(bool move_extra) {
    if (move_extra and m_extra_token.has_value())
        move_extra_token();
    return m_next_tokens.back();
}

token_ptr& parser::get_cursor_token() {
    return m_next_tokens[m_cursor_token_index];
}

template<typename token_type>
void parser::throw_token_error(const token_ptr& token) {
    if (not has_type<token_type>(token)) {
        // We only check for identifiers, punctuation and valid keywords
        // todo: check behaviour for all token types
        #define epddl_token_type(token_type) token_type
        std::string type = (std::is_same_v<epddl_pattern_token_type, get_super_t<token_type>>)
                           ? std::string{token_type::name}
                           : std::string{token_type::lexeme};
        #undef epddl_token_type

        throw_error(token, std::string{""}, std::string{"Expected '"} + type +
                                            std::string{"'. Found '"} + lexer::get_lexeme(token) + std::string{"'."});
    }
}

/* Assumptions:
 *  - Each production is unambiguously identifiable by a finite sequence of terminals
 *  - There are no nested choice points (i.e., variants of variants)
 *  - There exists a common prefix of terminals p = <t_1,  ..., t_k> such that for each
 *    node n in the choice point we have:
 *     + There exists a terminal t_n such that prefix(n) = p + t_n; and
 *     + For each node m != n, it holds that t_m != t_n.
 */
template<typename token_type>
void parser::check_next_peeked_token() {
    assert(not m_next_tokens.empty() or m_is_optional_node);

    if (m_is_optional_node) {
        if (has_type<token_type>(*m_extra_token)) {
            reset_extra_token();            // If the extra token has the correct type, we simply reset it
            m_is_optional_node = false;     // We can now safely conclude that the optional node exists
        } else
            throw_error(*m_extra_token);
    } else {
        if (has_type<token_type>(get_cursor_token()))
            ++m_cursor_token_index;
        else
            throw_token_error<token_type>(get_cursor_token());
    }
}

void parser::get_next_token() {
//    assert(not m_choice_point and not m_optional_node);

    if (m_next_tokens.empty() and not m_extra_token.has_value() and m_lex.good() and not m_lex.eof()) {
        // If neither we previously peeked any token, nor we peeked an extra token,
        // then we simply have the lexer retrieve the next token from the input file.
        m_current_token.emplace(std::move(m_lex.get_next_token()));
    } else {
        // Otherwise, we first look wheter we checked for and end of list. If we did, then we
        // move this token to the end of the 'm_next_tokens' list and we reset 'm_extra_token'.
        if (m_extra_token.has_value())
            move_extra_token();
        // Then, we simply move the last peeked token into 'm_current_token' and we clear the 'm_next_tokens' list.
        m_current_token.emplace(std::move(get_last_peeked_token()));
        m_next_tokens.clear();
    }
    update_scopes(*m_current_token);
}

void parser::update_scopes(const token_ptr& token) {
//    std::visit([this](auto &&tok) {
//        using tok_type = get_argument_t<decltype(tok)>;
//
//        if constexpr (std::is_same_v<tok_type, punctuation_token::lpar>) {
//            ++m_lpar_count;
//        } else if constexpr (std::is_same_v<tok_type, punctuation_token::rpar>) {
//            if (m_lpar_count == m_scopes.top().first) {
//                m_scopes.pop();
//            }
//            --m_lpar_count;
//        } else {
//            if constexpr (tok_type::is_scope) {
//                m_scopes.emplace(m_lpar_count, &*m_current_token);
//            }
//        }
//    }, *token);
}

template<typename token_type>
void parser::check_current_token(bool discard) {
    if (not has_type<token_type>(*m_current_token))
        throw_token_error<token_type>(*m_current_token);
//    if (not has_type<token_type>(*m_current_token)) {
//        // We only check for identifiers, punctuation and valid keywords
//        // todo: check behaviour for all token types
//        #define epddl_token_type(token_type) token_type
//        std::string type = (std::is_same_v<epddl_pattern_token_type, get_super_t<token_type>>)
//                ? std::string{token_type::name}
//                : std::string{"'"} + std::string{token_type::lexeme} + std::string{"'"};
//        #undef epddl_token_type
//
//        throw_error(*m_current_token, std::string{""}, std::string{"Expected "} + type + std::string{". Found "} + lexer::get_lexeme(*m_current_token));
//    }

    // After successfully verifying that the current token has the correct type, we can delete it
    if (discard) {
        m_current_token->reset();
        m_current_token = std::nullopt;
    }
}

template<typename token_type>
void parser::check_next_token(bool discard) {
    if (m_is_choice_point or m_is_optional_node) {
        // The function 'check_next_token' may be called after a choice point has been reached, or not.
        // In the first case, we peek the next token and we check that it has the correct type.
        if (m_cursor_token_index == m_next_tokens.size())   // We only peek a token we already checked the entire list
            peek_next_token();
        check_next_peeked_token<token_type>();
    } else {
        // In the second case, we read the next token from the input file and we do the same check.
        get_next_token();
        check_current_token<token_type>(discard);
    }
}

template<class variant_type, class element_type>
std::unique_ptr<element_type> parser::unwrap_variant_type(variant_type& elem) {
    std::unique_ptr<element_type> unwrapped_elem;       // Here we store the value of 'elem' after we unwrap it from its variant type

    std::visit([&unwrapped_elem](auto &&e) {
        using e_type = std::decay_t<decltype(e)>;

        if constexpr (std::is_same_v<element_type, e_type>) {
            unwrapped_elem = std::move(std::make_unique<e_type>(std::forward<e_type>(e)));      // Unwrapping variant
        }
    }, elem);
    return unwrapped_elem;
}

template<class variant_from, class variant_to, class element_type>
std::unique_ptr<variant_to> parser::convert_variant_type(variant_from& elem) {
    std::unique_ptr<element_type> unwrapped_elem = unwrap_variant_type<variant_from, element_type>(elem);
    return std::make_unique<variant_to>(std::move(unwrapped_elem));     // Wrapping back with 'variant_to' variant type
}

template<typename token_type>
std::unique_ptr<token<token_type>> parser::get_leaf_from_current_token() {
    std::unique_ptr<token<token_type>> leaf = std::move(unwrap_variant_type<token_variant, token<token_type>>(**m_current_token));

    m_current_token->reset();
    m_current_token = std::nullopt;

    return leaf;
}

template<typename token_type>
std::unique_ptr<token<token_type>> parser::get_leaf_from_next_token(bool is_optional) {     // todo: do I need is_optional?
    std::unique_ptr<token<token_type>> leaf;
    bool consume_token = true;

    if (m_is_choice_point or is_optional) {
        if (m_cursor_token_index >= m_next_tokens.size())
            peek_next_token();

        // todo: after 'get_next_token()' should we reset the 'm_next_tokens' list?
        if (has_type<token_type>(get_last_peeked_token()))  // If the last token we scanned has the correct type,
            get_next_token();                               // then we move it to the current token
        else
            consume_token = false;
    } else {
        check_next_token<token_type>(false);
    }

    if (consume_token)
        return get_leaf_from_current_token<token_type>();

    throw_error(get_last_peeked_token());
    return {};
}

bool parser::is_end_list() {
    peek_extra_token();

    #define epddl_token_type(token_type) token_type
    return has_type<epddl_punctuation_token_type::rpar>(*m_extra_token)   or
           has_type<epddl_punctuation_token_type::rbrack>(*m_extra_token) or
           has_type<epddl_punctuation_token_type::rangle>(*m_extra_token);
    #undef epddl_token_type
}

template<class node_type>
std::list<node_type> parser::parse_list(std::function<node_type()> parse_elem, bool is_optional_list) {
    std::list<node_type> elems;
    bool is_empty_list = true;

    while (not is_end_list()) {
        // If we do not peek ')', we parse the element and, if we are successful, we add it to the list.
        // We assume that parse_elem() takes care of its relative syntax errors.
        elems.push_back(std::move(parse_elem()));
        is_empty_list = false;
    }

    if (not is_optional_list and is_empty_list)
        throw_error(get_last_peeked_token(), std::string{""}, std::string{"Empty list."});
        // todo: create better error description
    return elems;
}

template<class node_type>
std::pair<bool, std::unique_ptr<node_type>> parser::parse_optional_node(std::function<std::unique_ptr<node_type>()> parse_elem) {
    m_cursor_token_index = 0;       // todo: do we really need this?

    try {
        m_is_optional_node = true;
        std::unique_ptr<node_type> element = std::move(parse_elem());
//        m_optional_node = false;      // todo: check if we can remove this. It should be taken care of by check_next_peeked_token
        return {true, std::move(element)};
    } catch (EPDDLBadChoicePointException &e) {
        m_is_optional_node = false;
        return {false, std::unique_ptr<node_type>{}};
    }
}

template<typename token_type>
std::pair<bool, std::unique_ptr<token<token_type>>> parser::parse_optional_leaf() {     // todo: can I use 'get_leaf_from_next_token' instead of this function?
    if (has_type<token_type>(get_last_peeked_token())) {
        std::unique_ptr<token<token_type>> leaf =
                std::move(unwrap_variant_type<token_variant, token<token_type>>(*get_last_peeked_token()));

        m_next_tokens.clear();
        return {true, std::move(leaf)};
    }
    return {false, std::unique_ptr<token<token_type>>{}};
}

template<class variant_node_type, class node_type>        // todo: why 'parse_elem' is not const ref?
std::pair<bool, std::unique_ptr<variant_node_type>> parser::parse_variant_node(std::function<std::unique_ptr<node_type>()> parse_elem) {
    reset_choice_point();

    try {
        if (std::unique_ptr<node_type> element = std::move(parse_elem()))
            return {true, std::move(std::make_unique<variant_node_type>(std::move(element)))};
    } catch (EPDDLBadChoicePointException &e) {}
    return {false, std::unique_ptr<variant_node_type>{}};
}

template<class variant_leaf_type, typename token_type>
std::pair<bool, std::unique_ptr<variant_leaf_type>> parser::parse_variant_leaf() {
    reset_choice_point();

    if (m_next_tokens.empty() and not m_extra_token.has_value())
        peek_next_token();

    if (has_type<token_type>(get_last_peeked_token())) {
        std::unique_ptr<variant_leaf_type> result =
                std::move(convert_variant_type<token_variant, variant_leaf_type, token<token_type>>(*get_last_peeked_token()));

        exit_choice_point();
        return {true, std::move(result)};
    }
    return {false, std::unique_ptr<variant_leaf_type>{}};
}


#define epddl_token_type(token_type) token_type
#define epddl_token(t_type, t_scope, t_name, t_lexeme) t_type, t_name

#define element_name(name) name

#define get_token_type(t_type, t_name) t_type::t_name

#define parse_leaf_function(t_type, t_name, is_optional) \
    std::move(get_leaf_from_next_token<get_token_type(t_type, t_name)>(is_optional))


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                       EPDDL ELEMENT PARSING FUNCTIONS                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



// Macro argument 'tok' comes from X-macro 'epddl_token' that is expanded as a pair 't_type, t_name'
#define terminal(tok)             0, parse_terminal,      tok,        null

#define node(type, name)          1, parse_node_simple,   type, null, name
#define list_node(type, name)     1, parse_node_list,     type, null, name
#define opt_node(type, name)      1, parse_node_opt,      type, null, name
#define opt_list_node(type, name) 1, parse_node_opt_list, type, null, name

// Macro argument 'type' comes from X-macro 'epddl_token' that is expanded as a pair 't_type, t_name'
#define leaf(type, name)          1, parse_leaf_simple,   type,       name
#define list_leaf(type, name)     1, parse_leaf_list,     type,       name
#define opt_leaf(type, name)      1, parse_leaf_opt,      type,       name
#define opt_list_leaf(type, name) 1, parse_leaf_opt_list, type,       name

#define end_rule                  0, parse_end,           null, null, null

/* Parsing terminals: we call the function check_next_token<token_type>, where token_type is the
 *                    type of the expected token as specified by the BNF
 */
#define parse_terminal(     type, tok_type, _   ) \
    check_next_token<get_token_type(type, tok_type)>();

/* Parsing nodes: we call the correct parse function (i.e., for an element of type 'x', we call 'parse_x')
 *                and we store its value in a corresponding variable
 */
#define parse_node_simple(  type,   _,      name) \
    exit_choice_point();                          \
    ast::unique_ptr(type) name = call_parse_node_function(type);

/* Parsing lists of nodes: we pass the correct parse function to the function parse_list (with parameter 'is_optional'
 *                         set to false) and we store its value in a corresponding variable
 */
#define parse_node_list(    type,   _,      name) \
    exit_choice_point();                                                     \
    std::function<ast::unique_ptr(type)()>                                   \
        parse_##name = [this] () { return call_parse_node_function(type); }; \
    list_(ast::unique_ptr(type)) name = parse_list(parse_##name, false);

/* Parsing optional nodes: we call the correct parse function and we store its value in a corresponding variable.
 *                         If nothing is returned, we assign std::nullopt to the variable
 */
#define parse_node_opt(     type,   _,      name) \
    std::function<ast::unique_ptr(type)()>                                                                       \
        parse_##name = [this] () { return call_parse_node_function(type); };                                     \
    std::pair<bool, optional_(ast::unique_ptr(type))> opt_##name = parse_optional_node<ast::type>(parse_##name); \
    optional_(ast::unique_ptr(type)) name = opt_##name.first ? std::move(opt_##name.second) : std::nullopt;

// todo: this was before std::pair<bool, ...
//       exit_choice_point();                                                                                      \

/* Parsing optional lists of nodes: we pass the correct parse function to the function parse_list (with parameter
 *                                  'is_optional' set to true) and we store its value in a corresponding variable
 */
#define parse_node_opt_list(type,   _,      name) \
    exit_choice_point();                                                     \
    std::function<ast::unique_ptr(type)()>                                   \
        parse_##name = [this] () { return call_parse_node_function(type); }; \
    list_(ast::unique_ptr(type)) name = parse_list(parse_##name, true);


/* Parsing leafs: we call the correct parse function (i.e., for a leaf_token of type 'x', we call 'get_leaf_from_next_token<x>'
 *                with parameter 'is_optional' set to false) and we store its value in a corresponding variable
 */
#define parse_leaf_simple(  type, tok_type, name) \
    token_ptr_alias(type, tok_type) name = parse_leaf_function(type, tok_type, false); \
    exit_choice_point();                                                               \

/* Parsing lists of leafs: we pass the correct parse function to the function parse_list (with parameter 'is_optional'
 *                         set to false) and we store its value in a corresponding variable
 */
#define parse_leaf_list(    type, tok_type, name) \
    exit_choice_point();                                                                 \
    std::function<token_ptr_alias(type, tok_type)()>                                     \
        parse_##name = [this] () { return parse_leaf_function(type, tok_type, false); }; \
    list_(token_ptr_alias(type, tok_type)) name = parse_list(parse_##name, false);

/* Parsing optional leafs: we call the correct parse function (i.e., for a leaf_token of type 'x', we call 'get_leaf_from_next_token<x>'
 *                         with parameter 'is_optional' set to true) and we store its value in a corresponding variable
 */
#define parse_leaf_opt(     type, tok_type, name) \
    optional_(token_ptr_alias(type, tok_type)) name = parse_leaf_function(type, tok_type, true);

// todo: fix optional leafs
//exit_choice_point();                                                              \

//result = parse_variant_leaf<ast::var_type, type::tok_type>(); \
//    if (result.first) return std::move(result.second);

/* Parsing lists of leafs: we pass the correct parse function to the function parse_list (with parameter 'is_optional'
 *                         set to true) and we store its value in a corresponding variable
 */
#define parse_leaf_opt_list(type, tok_type, name) \
    exit_choice_point();                                                                 \
    std::function<token_ptr_alias(type, tok_type)()>                                     \
        parse_##name = [this] () { return parse_leaf_function(type, tok_type, false); }; \
    list_(token_ptr_alias(type, tok_type)) name = parse_list(parse_##name, true);

#define parse_end(_, __, ___)

#define move_node(_, __, ___, name) std::move(name)

#define element_bnf(nodes...) nodes, end_rule

#define epddl_element(name, _, nodes) \
    ast::unique_ptr(name) parser::decl_parse_node_function(name) {              \
        PARSE_ELEMS(nodes)                                                      \
        return std::make_unique<ast::name>(MAP_4ARY_IF_LIST(move_node, nodes)); \
    }

    // Parsing functions
    epddl_all_element_defs

#undef epddl_element
#undef element_bnf
#undef move_node
#undef parse_end
#undef parse_leaf_opt_list
#undef parse_leaf_opt
#undef parse_leaf_list
#undef parse_leaf_simple
#undef parse_node_opt_list
#undef parse_node_opt
#undef parse_node_list
#undef parse_node_simple
#undef parse_terminal
#undef end_rule
#undef opt_list_leaf
#undef opt_leaf
#undef list_leaf
#undef leaf
#undef opt_list_node
#undef opt_node
#undef list_node
#undef node
#undef terminal


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                   EPDDL VARIANT ELEMENT PARSING FUNCTIONS                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#define node(type)    1, parse_node_simple,   type, null

// Macro argument 'type' comes from X-macro 'epddl_token' that is expanded as a pair 't_type, t_name'
#define leaf(type)    1, parse_leaf_simple,   type

#define end_rule      0, parse_end,           null, null

/* Parsing nodes: we call the correct parse function (i.e., for an element of type 'x', we call 'parse_x')
 *                and we store its value in a corresponding variable
 */
#define parse_node_simple(  var_type, type,   _) \
    std::function<ast::unique_ptr(type)()>                                    \
        _parse_##type = [this] () { return call_parse_node_function(type); }; \
    result = parse_variant_node<ast::var_type, ast::type>(_parse_##type);     \
    if (result.first) return std::move(result.second);

/* Parsing leafs: we call the correct parse function (i.e., for a leaf_token of type 'x', we call 'get_leaf_from_next_token<x>'
 *                with parameter 'is_optional' set to false) and we store its value in a corresponding variable
 */
#define parse_leaf_simple(  var_type, type, tok_type) \
    result = parse_variant_leaf<ast::var_type, type::tok_type>(); \
    if (result.first) return std::move(result.second);

#define parse_end(_, __, ___)

#define element_bnf(nodes...) nodes, end_rule

#define epddl_variant_element(name, nodes) \
    ast::unique_ptr(name) parser::decl_parse_node_function(name) {                                               \
        enter_choice_point();                                                                                    \
        std::pair<bool, ast::unique_ptr(name)> result;                                                           \
        PARSE_VARIANT_ELEMS(name, nodes)                                                                         \
        reset_choice_point();                                                                                    \
        if (m_was_choice_point)                                                                                  \
            enter_choice_point();                                                                                \
        throw_error(get_last_peeked_token(), std::string{""},                                                    \
            std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."}); \
        return {};                                                                                               \
    }

//throw EPDDLParserException{std::string{""},                      \
//            get_last_peeked_token.get_row(),                       \
//            get_last_peeked_token.get_col(),                       \
//            std::string{"Syntax error."}};                         \

    // Parsing choice points functions
     epddl_all_variant_element_defs

#undef epddl_variant_element
#undef element_bnf
#undef parse_end
#undef parse_leaf_simple
#undef parse_node_simple
#undef end_rule
#undef leaf
#undef node

#undef parse_leaf_function
#undef get_token_type
#undef element_name
#undef epddl_token
#undef epddl_token_type
