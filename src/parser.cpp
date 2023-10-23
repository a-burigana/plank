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

void parser::throw_error(token_ptr& token, const std::string& file, const std::string& error) const {
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
    // did not already peeked an extra token to avoid losing the extra token that we already peeked.
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
            reset_extra_token();        // If the extra token has the correct type, we simply reset it
            m_is_optional_node = false;    // We can now safely conclude that the optional node exists
        } else
            throw_error(*m_extra_token);
    } else {
        if (has_type<token_type>(get_cursor_token()))
            ++m_cursor_token_index;
        else
            throw_error(get_cursor_token(), std::string{"Expected "} + lexer::get_lexeme(get_cursor_token()) + std::string{"."});
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
    if (not has_type<token_type>(*m_current_token)) {
        // We only check for identifiers, punctuation and valid keywords
        // todo: check behaviour for all token types
        #define epddl_token_type(token_type) token_type
        std::string type = (std::is_same_v<epddl_pattern_token_type, get_super_t<token_type>>)
                ? std::string{token_type::name}
                : std::string{"'"} + std::string{token_type::lexeme} + std::string{"'"};
        #undef epddl_token_type

        throw_error(*m_current_token, std::string{""}, std::string{"Expected " + type + std::string{"."}});
    }

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
    return has_type<epddl_punctuation_token_type::rpar>(*m_extra_token);
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
//    epddl_all_element_defs

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
//     epddl_all_variant_element_defs

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












ast::epddl_true_formula_ptr parser::parse_epddl_true_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<atomic_formula_token::top>();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::epddl_true_formula>();
}
ast::epddl_false_formula_ptr parser::parse_epddl_false_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<atomic_formula_token::bot>();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::epddl_false_formula>();
}
ast::predicate_ptr parser::parse_predicate(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    exit_choice_point();
    std::function<ast::term_ptr()> parse_terms = [this]() { return parse_term(); };
    std::list<ast::term_ptr> terms = parse_list(parse_terms, true);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::predicate>(std::move(name), std::move(terms));
}
ast::negated_predicate_ptr parser::parse_negated_predicate(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::negation>();
    exit_choice_point();
    ast::predicate_ptr pred = parse_predicate();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::negated_predicate>(std::move(pred));
}
ast::formula_variable_ptr parser::parse_formula_variable(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    pattern_token_variable_ptr var = std::move(get_leaf_from_next_token<pattern_token::variable>(false));
    exit_choice_point();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::formula_variable>(std::move(var));
}
ast::eq_formula_ptr parser::parse_eq_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<punctuation_token::eq>();
    exit_choice_point();
    ast::term_ptr t1 = parse_term();
    exit_choice_point();
    ast::term_ptr t2 = parse_term();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::eq_formula>(std::move(t1), std::move(t2));
}
ast::not_formula_ptr parser::parse_not_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::negation>();
    exit_choice_point();
    ast::formula_ptr f = parse_formula();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::not_formula>(std::move(f));
}
ast::and_formula_ptr parser::parse_and_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::conjunction>();
    exit_choice_point();
    std::function<ast::formula_ptr()> parse_fs = [this]() { return parse_formula(); };
    std::list<ast::formula_ptr> fs = parse_list(parse_fs, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::and_formula>(std::move(fs));
}
ast::or_formula_ptr parser::parse_or_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::disjunction>();
    exit_choice_point();
    std::function<ast::formula_ptr()> parse_fs = [this]() { return parse_formula(); };
    std::list<ast::formula_ptr> fs = parse_list(parse_fs, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::or_formula>(std::move(fs));
}
ast::imply_formula_ptr parser::parse_imply_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::disjunction>();
    exit_choice_point();
    ast::formula_ptr f1 = parse_formula();
    exit_choice_point();
    ast::formula_ptr f2 = parse_formula();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::imply_formula>(std::move(f1), std::move(f2));
}
ast::modality_ptr parser::parse_modality(bool is_optional) {
    std::optional<pattern_token_modality_ptr> mod = std::move(get_leaf_from_next_token<pattern_token::modality>(true));
    exit_choice_point();
    std::function<ast::agent_ptr()> parse_ags = [this]() { return parse_agent(); };
    std::list<ast::agent_ptr> ags = parse_list(parse_ags, false);
    return std::make_unique<ast::modality>(std::move(mod), std::move(ags));
}
ast::box_formula_ptr parser::parse_box_formula(bool is_optional) {
    check_next_token<punctuation_token::lbrack>();
    exit_choice_point();
    ast::modality_ptr mod = parse_modality();
    check_next_token<punctuation_token::rbrack>();
    exit_choice_point();
    ast::formula_ptr f = parse_formula();
    return std::make_unique<ast::box_formula>(std::move(mod), std::move(f));
}
ast::diamond_formula_ptr parser::parse_diamond_formula(bool is_optional) {
    check_next_token<punctuation_token::langle>();
    exit_choice_point();
    ast::modality_ptr mod = parse_modality();
    check_next_token<punctuation_token::rangle>();
    exit_choice_point();
    ast::formula_ptr f = parse_formula();
    return std::make_unique<ast::diamond_formula>(std::move(mod), std::move(f));
}
ast::exists_formula_ptr parser::parse_exists_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<quantifier_token::exists>();
    check_next_token<punctuation_token::lpar>();
    exit_choice_point();
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, false);
    check_next_token<punctuation_token::rpar>();
    exit_choice_point();
    ast::formula_ptr f = parse_formula();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::exists_formula>(std::move(params), std::move(f));
}
ast::forall_formula_ptr parser::parse_forall_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<quantifier_token::forall>();
    check_next_token<punctuation_token::lpar>();
    exit_choice_point();
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, false);
    check_next_token<punctuation_token::rpar>();
    exit_choice_point();
    ast::formula_ptr f = parse_formula();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::forall_formula>(std::move(params), std::move(f));
}
ast::parameters_ptr parser::parse_parameters(bool is_optional) {
    check_next_token<keyword_token::parameters>();
    check_next_token<punctuation_token::lpar>();
    exit_choice_point();
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, true);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::parameters>(std::move(params));
}
ast::cond_effect_conjunction_ptr parser::parse_cond_effect_conjunction(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::conjunction>();
    exit_choice_point();
    std::function<ast::cond_effect_ptr()> parse_effects = [this]() { return parse_cond_effect(); };
    std::list<ast::cond_effect_ptr> effects = parse_list(parse_effects, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::cond_effect_conjunction>(std::move(effects));
}
ast::forall_effect_ptr parser::parse_forall_effect(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<quantifier_token::forall>();
    check_next_token<punctuation_token::lpar>();
    exit_choice_point();
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, false);
    check_next_token<punctuation_token::rpar>();
    exit_choice_point();
    ast::effect_ptr effect = parse_effect();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::forall_effect>(std::move(params), std::move(effect));
}
ast::when_effect_ptr parser::parse_when_effect(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<post_connective_token::when>();
    exit_choice_point();
    ast::formula_ptr cond = parse_formula();
    exit_choice_point();
    ast::effect_condition_ptr effect = parse_effect_condition();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::when_effect>(std::move(cond), std::move(effect));
}
ast::iff_effect_ptr parser::parse_iff_effect(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<post_connective_token::iff>();
    exit_choice_point();
    ast::formula_ptr cond = parse_formula();
    exit_choice_point();
    ast::effect_condition_ptr effect = parse_effect_condition();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::iff_effect>(std::move(cond), std::move(effect));
}
ast::literal_conjunction_ptr parser::parse_literal_conjunction(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::conjunction>();
    exit_choice_point();
    std::function<ast::literal_ptr()> parse_literals = [this]() { return parse_literal(); };
    std::list<ast::literal_ptr> literals = parse_list(parse_literals, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::literal_conjunction>(std::move(literals));
}
ast::signature_ptr parser::parse_signature(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    exit_choice_point();
    std::function<ast::typed_expression_ptr()> parse_expr = [this]() { return parse_typed_expression(); };
    std::list<ast::typed_expression_ptr> expr = parse_list(parse_expr, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::signature>(std::move(name), std::move(expr));
}
ast::object_typed_expression_ptr parser::parse_object_typed_expression(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<expr_type_token::object_type>();
    exit_choice_point();
    ast::term_ptr object = parse_term();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::object_typed_expression>(std::move(object));
}
ast::agent_typed_expression_ptr parser::parse_agent_typed_expression(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<expr_type_token::agent_type>();
    exit_choice_point();
    ast::term_ptr agent = parse_term();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::agent_typed_expression>(std::move(agent));
}
ast::predicate_typed_expression_ptr parser::parse_predicate_typed_expression(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<expr_type_token::predicate_type>();
    exit_choice_point();
    ast::predicate_ptr pred = parse_predicate();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::predicate_typed_expression>(std::move(pred));
}
ast::literal_typed_expression_ptr parser::parse_literal_typed_expression(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<expr_type_token::literal_type>();
    exit_choice_point();
    ast::literal_ptr lit = parse_literal();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::literal_typed_expression>(std::move(lit));
}
ast::formula_typed_expression_ptr parser::parse_formula_typed_expression(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<expr_type_token::formula_type>();
    exit_choice_point();
    ast::formula_ptr formula = parse_formula();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::formula_typed_expression>(std::move(formula));
}
ast::effects_typed_expression_ptr parser::parse_effects_typed_expression(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<expr_type_token::effects_type>();
    exit_choice_point();
    ast::effect_ptr effect = parse_effect();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::effects_typed_expression>(std::move(effect));
}
ast::type_ptr parser::parse_type(bool is_optional) {
    check_next_token<punctuation_token::dash>();
    pattern_token_identifier_ptr elem_type = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    return std::make_unique<ast::type>(std::move(elem_type));
}
ast::typed_ident_ptr parser::parse_typed_ident(bool is_optional) {
    pattern_token_identifier_ptr id = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    std::function<ast::type_ptr()> parse_id_type = [this]() { return parse_type(); };
    std::pair<bool, std::optional<ast::type_ptr>> opt_id_type = parse_optional_node<ast::type>(parse_id_type);
    std::optional<ast::type_ptr> id_type = opt_id_type.first ? std::move(opt_id_type.second) : std::nullopt;
    return std::make_unique<ast::typed_ident>(std::move(id), std::move(id_type));
}
ast::typed_var_ptr parser::parse_typed_var(bool is_optional) {
    pattern_token_variable_ptr var = std::move(get_leaf_from_next_token<pattern_token::variable>(false));
    exit_choice_point();
    std::function<ast::type_ptr()> parse_var_type = [this]() { return parse_type(); };
    std::pair<bool, std::optional<ast::type_ptr>> opt_var_type = parse_optional_node<ast::type>(parse_var_type);
    std::optional<ast::type_ptr> var_type = opt_var_type.first ? std::move(opt_var_type.second) : std::nullopt;
    return std::make_unique<ast::typed_var>(std::move(var), std::move(var_type));
}
ast::domain_ptr parser::parse_domain(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::define>();
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::domain>();
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    check_next_token<punctuation_token::rpar>();
    exit_choice_point();
    std::function<ast::domain_item_ptr()> parse_items = [this]() { return parse_domain_item(); };
    std::list<ast::domain_item_ptr> items = parse_list(parse_items, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain>(std::move(name), std::move(items));
}
ast::domain_requirements_ptr parser::parse_domain_requirements(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::requirements>();
    exit_choice_point();
    std::function<ast::requirement_ptr()> parse_reqs = [this]() { return parse_requirement(); };
    std::list<ast::requirement_ptr> reqs = parse_list(parse_reqs, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_requirements>(std::move(reqs));
}
ast::simple_requirement_ptr parser::parse_simple_requirement(bool is_optional) {
    pattern_token_requirement_ptr req = std::move(get_leaf_from_next_token<pattern_token::requirement>(false));
    exit_choice_point();
    return std::make_unique<ast::simple_requirement>(std::move(req));
}
ast::val_requirement_ptr parser::parse_val_requirement(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    pattern_token_requirement_ptr req = std::move(get_leaf_from_next_token<pattern_token::requirement>(false));
    exit_choice_point();
    pattern_token_integer_ptr val = std::move(get_leaf_from_next_token<pattern_token::integer>(false));
    exit_choice_point();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::val_requirement>(std::move(req), std::move(val));
}
ast::domain_libraries_ptr parser::parse_domain_libraries(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::act_type_lib>();
    exit_choice_point();
    std::function<pattern_token_identifier_ptr()> parse_libs = [this]() {
        return std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    };
    std::list<pattern_token_identifier_ptr> libs = parse_list(parse_libs, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_libraries>(std::move(libs));
}
ast::domain_types_ptr parser::parse_domain_types(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::types>();
    exit_choice_point();
    std::function<ast::typed_ident_ptr()> parse_types = [this]() { return parse_typed_ident(); };
    std::list<ast::typed_ident_ptr> types = parse_list(parse_types, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_types>(std::move(types));
}
ast::domain_predicates_ptr parser::parse_domain_predicates(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::predicates>();
    exit_choice_point();
    std::function<ast::predicate_signature_ptr()> parse_signatures = [this]() { return parse_predicate_signature(); };
    std::list<ast::predicate_signature_ptr> signatures = parse_list(parse_signatures, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_predicates>(std::move(signatures));
}
ast::predicate_signature_ptr parser::parse_predicate_signature(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    exit_choice_point();
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, true);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::predicate_signature>(std::move(name), std::move(params));
}
ast::domain_modalities_ptr parser::parse_domain_modalities(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::modalities>();
    exit_choice_point();
    std::function<pattern_token_modality_ptr()> parse_modalities = [this]() {
        return std::move(get_leaf_from_next_token<pattern_token::modality>(false));
    };
    std::list<pattern_token_modality_ptr> modalities = parse_list(parse_modalities, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_modalities>(std::move(modalities));
}
ast::domain_action_ptr parser::parse_domain_action(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::action>();
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    exit_choice_point();
    ast::parameters_ptr parameters = parse_parameters();
    exit_choice_point();
    ast::precondition_ptr precondition = parse_precondition();
    exit_choice_point();
    ast::action_type_signature_ptr signature = parse_action_type_signature();
    std::function<ast::action_obs_conditions_ptr()> parse_obs_conditions = [this]() { return parse_action_obs_conditions(); };
    std::pair<bool, std::optional<ast::action_obs_conditions_ptr>> opt_obs_conditions = parse_optional_node<ast::action_obs_conditions>(
            parse_obs_conditions);
    std::optional<ast::action_obs_conditions_ptr> obs_conditions = opt_obs_conditions.first ? std::move(
            opt_obs_conditions.second) : std::nullopt;
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_action>(std::move(name), std::move(parameters), std::move(precondition),
                                                std::move(signature), std::move(obs_conditions));
}
ast::action_type_signature_ptr parser::parse_action_type_signature(bool is_optional) {
    check_next_token<keyword_token::act_type>();
    exit_choice_point();
    ast::signature_ptr signature = parse_signature();
    return std::make_unique<ast::action_type_signature>(std::move(signature));
}
ast::precondition_ptr parser::parse_precondition(bool is_optional) {
    check_next_token<keyword_token::precondition>();
    exit_choice_point();
    ast::formula_ptr precondition = parse_formula();
    return std::make_unique<ast::precondition>(std::move(precondition));
}
ast::action_obs_conditions_ptr parser::parse_action_obs_conditions(bool is_optional) {
    check_next_token<keyword_token::obs_conditions>();
    exit_choice_point();
    std::function<ast::obs_condition_ptr()> parse_conditions = [this]() { return parse_obs_condition(); };
    std::list<ast::obs_condition_ptr> conditions = parse_list(parse_conditions, false);
    return std::make_unique<ast::action_obs_conditions>(std::move(conditions));
}
ast::conditional_obs_conjunction_ptr parser::parse_conditional_obs_conjunction(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::conjunction>();
    exit_choice_point();
    std::function<ast::conditional_obs_ptr()> parse_effects = [this]() { return parse_conditional_obs(); };
    std::list<ast::conditional_obs_ptr> effects = parse_list(parse_effects, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::conditional_obs_conjunction>(std::move(effects));
}
ast::static_obs_condition_ptr parser::parse_static_obs_condition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    exit_choice_point();
    ast::agent_ptr agent = parse_agent();
    pattern_token_identifier_ptr group = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::static_obs_condition>(std::move(agent), std::move(group));
}
ast::if_obs_condition_ptr parser::parse_if_obs_condition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<observability_token::if_cond>();
    exit_choice_point();
    ast::formula_ptr cond = parse_formula();
    exit_choice_point();
    ast::agent_ptr agent = parse_agent();
    pattern_token_identifier_ptr group = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::if_obs_condition>(std::move(cond), std::move(agent), std::move(group));
}
ast::otherwise_obs_condition_ptr parser::parse_otherwise_obs_condition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<observability_token::else_cond>();
    exit_choice_point();
    ast::agent_ptr agent = parse_agent();
    pattern_token_identifier_ptr group = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    exit_choice_point();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::otherwise_obs_condition>(std::move(agent), std::move(group));
}
ast::forall_obs_condition_ptr parser::parse_forall_obs_condition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<quantifier_token::forall>();
    check_next_token<punctuation_token::lpar>();
    exit_choice_point();
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, false);
    check_next_token<punctuation_token::rpar>();
    exit_choice_point();
    std::function<ast::simple_obs_condition_ptr()> parse_obs_conds = [this]() { return parse_simple_obs_condition(); };
    std::list<ast::simple_obs_condition_ptr> obs_conds = parse_list(parse_obs_conds, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::forall_obs_condition>(std::move(params), std::move(obs_conds));
}











ast::term_ptr parser::parse_term(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::term_ptr> result;
    result = parse_variant_leaf<ast::term, pattern_token::identifier>();
    if (result.first)return std::move(result.second);
    result = parse_variant_leaf<ast::term, pattern_token::variable>();
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::atomic_formula_ptr parser::parse_atomic_formula(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::atomic_formula_ptr> result;
    std::function<ast::predicate_ptr()> _parse_predicate = [this]() { return parse_predicate(); };
    result = parse_variant_node<ast::atomic_formula, ast::predicate>(_parse_predicate);
    if (result.first)return std::move(result.second);
    std::function<ast::formula_variable_ptr()> _parse_formula_variable = [this]() { return parse_formula_variable(); };
    result = parse_variant_node<ast::atomic_formula, ast::formula_variable>(_parse_formula_variable);
    if (result.first)return std::move(result.second);
    std::function<ast::epddl_true_formula_ptr()> _parse_epddl_true_formula = [this]() { return parse_epddl_true_formula(); };
    result = parse_variant_node<ast::atomic_formula, ast::epddl_true_formula>(_parse_epddl_true_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::epddl_false_formula_ptr()> _parse_epddl_false_formula = [this]() { return parse_epddl_false_formula(); };
    result = parse_variant_node<ast::atomic_formula, ast::epddl_false_formula>(_parse_epddl_false_formula);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::literal_ptr parser::parse_literal(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::literal_ptr> result;
    std::function<ast::predicate_ptr()> _parse_predicate = [this]() { return parse_predicate(); };
    result = parse_variant_node<ast::literal, ast::predicate>(_parse_predicate);
    if (result.first)return std::move(result.second);
    std::function<ast::negated_predicate_ptr()> _parse_negated_predicate = [this]() { return parse_negated_predicate(); };
    result = parse_variant_node<ast::literal, ast::negated_predicate>(_parse_negated_predicate);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::propositional_formula_ptr parser::parse_propositional_formula(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::propositional_formula_ptr> result;
    std::function<ast::atomic_formula_ptr()> _parse_atomic_formula = [this]() { return parse_atomic_formula(); };
    result = parse_variant_node<ast::propositional_formula, ast::atomic_formula>(_parse_atomic_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::eq_formula_ptr()> _parse_eq_formula = [this]() { return parse_eq_formula(); };
    result = parse_variant_node<ast::propositional_formula, ast::eq_formula>(_parse_eq_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::not_formula_ptr()> _parse_not_formula = [this]() { return parse_not_formula(); };
    result = parse_variant_node<ast::propositional_formula, ast::not_formula>(_parse_not_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::and_formula_ptr()> _parse_and_formula = [this]() { return parse_and_formula(); };
    result = parse_variant_node<ast::propositional_formula, ast::and_formula>(_parse_and_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::or_formula_ptr()> _parse_or_formula = [this]() { return parse_or_formula(); };
    result = parse_variant_node<ast::propositional_formula, ast::or_formula>(_parse_or_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::imply_formula_ptr()> _parse_imply_formula = [this]() { return parse_imply_formula(); };
    result = parse_variant_node<ast::propositional_formula, ast::imply_formula>(_parse_imply_formula);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::modal_formula_ptr parser::parse_modal_formula(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::modal_formula_ptr> result;
    std::function<ast::box_formula_ptr()> _parse_box_formula = [this]() { return parse_box_formula(); };
    result = parse_variant_node<ast::modal_formula, ast::box_formula>(_parse_box_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::diamond_formula_ptr()> _parse_diamond_formula = [this]() { return parse_diamond_formula(); };
    result = parse_variant_node<ast::modal_formula, ast::diamond_formula>(_parse_diamond_formula);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::quantified_formula_ptr parser::parse_quantified_formula(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::quantified_formula_ptr> result;
    std::function<ast::exists_formula_ptr()> _parse_exists_formula = [this]() { return parse_exists_formula(); };
    result = parse_variant_node<ast::quantified_formula, ast::exists_formula>(_parse_exists_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::forall_formula_ptr()> _parse_forall_formula = [this]() { return parse_forall_formula(); };
    result = parse_variant_node<ast::quantified_formula, ast::forall_formula>(_parse_forall_formula);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::formula_ptr parser::parse_formula(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::formula_ptr> result;
    std::function<ast::propositional_formula_ptr()> _parse_propositional_formula = [this]() { return parse_propositional_formula(); };
    result = parse_variant_node<ast::formula, ast::propositional_formula>(_parse_propositional_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::modal_formula_ptr()> _parse_modal_formula = [this]() { return parse_modal_formula(); };
    result = parse_variant_node<ast::formula, ast::modal_formula>(_parse_modal_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::quantified_formula_ptr()> _parse_quantified_formula = [this]() { return parse_quantified_formula(); };
    result = parse_variant_node<ast::formula, ast::quantified_formula>(_parse_quantified_formula);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::agent_ptr parser::parse_agent(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::agent_ptr> result;
    result = parse_variant_leaf<ast::agent, pattern_token::identifier>();
    if (result.first)return std::move(result.second);
    result = parse_variant_leaf<ast::agent, pattern_token::variable>();
    if (result.first)return std::move(result.second);
    result = parse_variant_leaf<ast::agent, agent_group_token::all>();
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::cond_effect_ptr parser::parse_cond_effect(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::cond_effect_ptr> result;
    std::function<ast::forall_effect_ptr()> _parse_forall_effect = [this]() { return parse_forall_effect(); };
    result = parse_variant_node<ast::cond_effect, ast::forall_effect>(_parse_forall_effect);
    if (result.first)return std::move(result.second);
    std::function<ast::when_effect_ptr()> _parse_when_effect = [this]() { return parse_when_effect(); };
    result = parse_variant_node<ast::cond_effect, ast::when_effect>(_parse_when_effect);
    if (result.first)return std::move(result.second);
    std::function<ast::iff_effect_ptr()> _parse_iff_effect = [this]() { return parse_iff_effect(); };
    result = parse_variant_node<ast::cond_effect, ast::iff_effect>(_parse_iff_effect);
    if (result.first)return std::move(result.second);
    std::function<ast::literal_ptr()> _parse_literal = [this]() { return parse_literal(); };
    result = parse_variant_node<ast::cond_effect, ast::literal>(_parse_literal);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::effect_ptr parser::parse_effect(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::effect_ptr> result;
    std::function<ast::cond_effect_ptr()> _parse_cond_effect = [this]() { return parse_cond_effect(); };
    result = parse_variant_node<ast::effect, ast::cond_effect>(_parse_cond_effect);
    if (result.first)return std::move(result.second);
    std::function<ast::cond_effect_conjunction_ptr()> _parse_cond_effect_conjunction = [this]() { return parse_cond_effect_conjunction(); };
    result = parse_variant_node<ast::effect, ast::cond_effect_conjunction>(_parse_cond_effect_conjunction);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::effect_condition_ptr parser::parse_effect_condition(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::effect_condition_ptr> result;
    std::function<ast::literal_ptr()> _parse_literal = [this]() { return parse_literal(); };
    result = parse_variant_node<ast::effect_condition, ast::literal>(_parse_literal);
    if (result.first)return std::move(result.second);
    std::function<ast::literal_conjunction_ptr()> _parse_literal_conjunction = [this]() { return parse_literal_conjunction(); };
    result = parse_variant_node<ast::effect_condition, ast::literal_conjunction>(_parse_literal_conjunction);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::typed_expression_ptr parser::parse_typed_expression(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::typed_expression_ptr> result;
    std::function<ast::object_typed_expression_ptr()> _parse_object_typed_expression = [this]() { return parse_object_typed_expression(); };
    result = parse_variant_node<ast::typed_expression, ast::object_typed_expression>(_parse_object_typed_expression);
    if (result.first)return std::move(result.second);
    std::function<ast::agent_typed_expression_ptr()> _parse_agent_typed_expression = [this]() { return parse_agent_typed_expression(); };
    result = parse_variant_node<ast::typed_expression, ast::agent_typed_expression>(_parse_agent_typed_expression);
    if (result.first)return std::move(result.second);
    std::function<ast::predicate_typed_expression_ptr()> _parse_predicate_typed_expression = [this]() { return parse_predicate_typed_expression(); };
    result = parse_variant_node<ast::typed_expression, ast::predicate_typed_expression>(
            _parse_predicate_typed_expression);
    if (result.first)return std::move(result.second);
    std::function<ast::literal_typed_expression_ptr()> _parse_literal_typed_expression = [this]() { return parse_literal_typed_expression(); };
    result = parse_variant_node<ast::typed_expression, ast::literal_typed_expression>(_parse_literal_typed_expression);
    if (result.first)return std::move(result.second);
    std::function<ast::formula_typed_expression_ptr()> _parse_formula_typed_expression = [this]() { return parse_formula_typed_expression(); };
    result = parse_variant_node<ast::typed_expression, ast::formula_typed_expression>(_parse_formula_typed_expression);
    if (result.first)return std::move(result.second);
    std::function<ast::effects_typed_expression_ptr()> _parse_effects_typed_expression = [this]() { return parse_effects_typed_expression(); };
    result = parse_variant_node<ast::typed_expression, ast::effects_typed_expression>(_parse_effects_typed_expression);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::domain_item_ptr parser::parse_domain_item(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::domain_item_ptr> result;
    std::function<ast::domain_requirements_ptr()> _parse_domain_requirements = [this]() { return parse_domain_requirements(); };
    result = parse_variant_node<ast::domain_item, ast::domain_requirements>(_parse_domain_requirements);
    if (result.first)return std::move(result.second);
    std::function<ast::domain_libraries_ptr()> _parse_domain_libraries = [this]() { return parse_domain_libraries(); };
    result = parse_variant_node<ast::domain_item, ast::domain_libraries>(_parse_domain_libraries);
    if (result.first)return std::move(result.second);
    std::function<ast::domain_types_ptr()> _parse_domain_types = [this]() { return parse_domain_types(); };
    result = parse_variant_node<ast::domain_item, ast::domain_types>(_parse_domain_types);
    if (result.first)return std::move(result.second);
    std::function<ast::domain_predicates_ptr()> _parse_domain_predicates = [this]() { return parse_domain_predicates(); };
    result = parse_variant_node<ast::domain_item, ast::domain_predicates>(_parse_domain_predicates);
    if (result.first)return std::move(result.second);
    std::function<ast::domain_modalities_ptr()> _parse_domain_modalities = [this]() { return parse_domain_modalities(); };
    result = parse_variant_node<ast::domain_item, ast::domain_modalities>(_parse_domain_modalities);
    if (result.first)return std::move(result.second);
    std::function<ast::domain_action_ptr()> _parse_domain_action = [this]() { return parse_domain_action(); };
    result = parse_variant_node<ast::domain_item, ast::domain_action>(_parse_domain_action);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::requirement_ptr parser::parse_requirement(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::requirement_ptr> result;
    std::function<ast::simple_requirement_ptr()> _parse_simple_requirement = [this]() { return parse_simple_requirement(); };
    result = parse_variant_node<ast::requirement, ast::simple_requirement>(_parse_simple_requirement);
    if (result.first)return std::move(result.second);
    std::function<ast::val_requirement_ptr()> _parse_val_requirement = [this]() { return parse_val_requirement(); };
    result = parse_variant_node<ast::requirement, ast::val_requirement>(_parse_val_requirement);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::simple_obs_condition_ptr parser::parse_simple_obs_condition(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::simple_obs_condition_ptr> result;
    std::function<ast::static_obs_condition_ptr()> _parse_static_obs_condition = [this]() { return parse_static_obs_condition(); };
    result = parse_variant_node<ast::simple_obs_condition, ast::static_obs_condition>(_parse_static_obs_condition);
    if (result.first)return std::move(result.second);
    std::function<ast::if_obs_condition_ptr()> _parse_if_obs_condition = [this]() { return parse_if_obs_condition(); };
    result = parse_variant_node<ast::simple_obs_condition, ast::if_obs_condition>(_parse_if_obs_condition);
    if (result.first)return std::move(result.second);
    std::function<ast::otherwise_obs_condition_ptr()> _parse_otherwise_obs_condition = [this]() { return parse_otherwise_obs_condition(); };
    result = parse_variant_node<ast::simple_obs_condition, ast::otherwise_obs_condition>(
            _parse_otherwise_obs_condition);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::conditional_obs_ptr parser::parse_conditional_obs(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::conditional_obs_ptr> result;
    std::function<ast::simple_obs_condition_ptr()> _parse_simple_obs_condition = [this]() { return parse_simple_obs_condition(); };
    result = parse_variant_node<ast::conditional_obs, ast::simple_obs_condition>(_parse_simple_obs_condition);
    if (result.first)return std::move(result.second);
    std::function<ast::forall_obs_condition_ptr()> _parse_forall_obs_condition = [this]() { return parse_forall_obs_condition(); };
    result = parse_variant_node<ast::conditional_obs, ast::forall_obs_condition>(_parse_forall_obs_condition);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
ast::obs_condition_ptr parser::parse_obs_condition(bool is_optional) {
    enter_choice_point();
    std::pair<bool, ast::obs_condition_ptr> result;
    std::function<ast::conditional_obs_ptr()> _parse_conditional_obs = [this]() { return parse_conditional_obs(); };
    result = parse_variant_node<ast::obs_condition, ast::conditional_obs>(_parse_conditional_obs);
    if (result.first)return std::move(result.second);
    std::function<ast::conditional_obs_conjunction_ptr()> _parse_conditional_obs_conjunction = [this]() { return parse_conditional_obs_conjunction(); };
    result = parse_variant_node<ast::obs_condition, ast::conditional_obs_conjunction>(
            _parse_conditional_obs_conjunction);
    if (result.first)return std::move(result.second);
    reset_choice_point();
    if (m_was_choice_point)enter_choice_point();
    throw_error(get_last_peeked_token(), std::string{""},
                std::string{"Unexpected symbol: " + lexer::get_lexeme(get_last_peeked_token())} + std::string{"."});
    return {};
}
