#include <memory>
#include <optional>
#include <type_traits>
#include "../include/parser/parser.h"
#include "../include/epddl_exception.h"

using namespace epddl;

parser::parser(lexer &lex) :
        m_lex{lex},
        m_current_token{std::nullopt},
        m_next_tokens{},
        m_cursor_token_index{0},
        m_choice_point{false},
        m_lpar_count{0} {}

ast::domain_ptr parser::parse() {
    return std::move(parse_domain());
}

template<typename token_type>
bool parser::has_type(token_ptr &tok) const {
    return std::holds_alternative<token<token_type>>(*tok);
}

void parser::peek_next_token() {
    if (m_lex.good() and not m_lex.eof()) {
        m_next_tokens.push_back(std::move(m_lex.get_next_token()));
    }
}

token_ptr& parser::get_last_peeked_token() {
    return m_next_tokens.back();
}

token_ptr& parser::get_cursor_token() {
    return m_next_tokens[m_cursor_token_index];
}

template<typename token_type>
bool parser::is_next_token_type() {
    // We only look at a new token if we are not in a choice point, since in a (leaf) choice point we want to
    // check the last peeked token multiple times until we find a match with a choice point rule
    if (not m_choice_point) {
        peek_next_token();
    }
    return has_type<token_type>(get_last_peeked_token());
}

/* Assumptions:
 *  - Each production is unambiguously identifiable by a finite sequence of terminals
 *  - There are no nested choice points (i.e., variants of variants)
 *  - There exists a common prefix of terminals p = <t_1,  ..., t_k> such that for each
 *    node n in the choice point we have:
 *     + There exists a terminals t_n such that prefix(n) = p + t_n; and
 *     + For each node m != n, it holds that t_m != t_n.
 */
template<typename token_type>
bool parser::check_next_peeked_token() {
    bool result = true;

    if (m_next_tokens.empty()) {
        result = is_next_token_type<token_type>();
        m_cursor_token_index = 0;
    } else {
        if (has_type<token_type>(get_cursor_token())) {
            ++m_cursor_token_index;
        } else {
            result = false;
        }
    }
    return result;
}

void parser::get_next_token() {
    if (m_choice_point) {
        peek_next_token();
        // todo: if last peeked token is not a terminal, throw error (probably add <is_terminal> field to token macros)
        return;
    }

    if (m_next_tokens.empty() and m_lex.good() and not m_lex.eof()) {
        m_current_token.emplace(std::move(m_lex.get_next_token()));
    } else {
        m_current_token.emplace(std::move(m_next_tokens.back()));
        m_next_tokens.clear();
    }

    std::visit([this](auto &&tok) {
        using token_type = get_argument_t<std::decay_t<decltype(tok)>>;

        if constexpr (std::is_same_v<token_type, punctuation_token::lpar>) {
            ++m_lpar_count;
        } else if constexpr (std::is_same_v<token_type, punctuation_token::rpar>) {
            if (m_lpar_count == m_scopes.top().first) {
                m_scopes.pop();
            }
            --m_lpar_count;
        } else {
            if (token_type::is_scope) {
                m_scopes.emplace(m_lpar_count, &*m_current_token);
            }
        }
    }, **m_current_token);
}

template<typename token_type>
void parser::check_current_token() {
    if (not has_type<token_type>(*m_current_token)) {
        std::visit([](auto &&tok) {
            std::string type;

            // We only check for basic values, punctuation or valid keywords
            // todo: check behaviour for all token types
            #define epddl_token_type(token_type) token_type
            if constexpr (std::is_same_v<epddl_pattern_token_type, get_super_t<token_type>>) {
                type = std::string{token_type::name};
            } else {
                type = std::string{"'"} + std::string{token_type::lexeme} + std::string{"'"};
            }
            #undef epddl_token_type
            // todo: create function 'throw_error' to print more detailed errors (using scope tokens)
            throw EPDDLException{std::string{""}, tok.get_row(), tok.get_col(),
                                 std::string{"Expected " + type + std::string{"."}}};
        }, **m_current_token);
    }
}

template<typename token_type>
void parser::check_next_token() {
    get_next_token();

    if (m_choice_point)
        check_next_peeked_token<token_type>();
    else
        check_current_token<token_type>();
}

template<typename token_type>
std::unique_ptr<token<token_type>> parser::get_leaf_from_next_token(bool is_optional) {
    std::unique_ptr<token<token_type>> leaf;
    bool consume_token = true;

    if (is_optional) {
        if (is_next_token_type<token_type>())
            get_next_token();
        else
            consume_token = false;
    } else {
        check_next_token<token_type>();
    }

    if (consume_token) {
        std::visit([&leaf](auto &&tok) {
            using tok_type = std::decay_t<decltype(tok)>;

            if constexpr (std::is_same_v<token<token_type>, tok_type>) {
                leaf = std::move(std::make_unique<tok_type>(std::forward<tok_type>(tok)));
            }
        }, **m_current_token);
        m_current_token->reset();
        m_current_token = std::nullopt;
    }

    return leaf;
}

template<class node_type>
std::list<node_type> parser::parse_list(std::function<node_type()> parse_elem, bool is_optional_list) {
    std::list<node_type> elems;
    bool end_list = false, is_empty_list = true;

    #define epddl_token_type(token_type) token_type
    do {
        peek_next_token();
        if (has_type<epddl_punctuation_token_type::rpar>(get_last_peeked_token())) {
            // If we peek ')'
            end_list = true;
        } else {
            // Otherwise we parse the element and, if we are successful, we add it to the list
            // We assume that parse_elem() takes care of errors concerning unexpected tokens
            elems.push_back(std::move(parse_elem()));
            is_empty_list = false;
        }
    } while (not end_list);

    check_next_token<epddl_punctuation_token_type::rpar>();
    #undef epddl_token_type

    if (not is_optional_list and is_empty_list) {
        // todo: create better error description
        std::visit([](auto &&tok) {
            throw EPDDLException{std::string{""}, tok.get_row(), tok.get_col(), std::string{"Empty list."}};
        }, **m_current_token);
    }
    return std::move(elems);
}

template<class variant_node_type, class node_type>
std::pair<bool, std::unique_ptr<variant_node_type>> parser::parse_variant_node(std::function<std::unique_ptr<node_type>()> parse_elem) {
    try {
        std::unique_ptr<node_type> element = parse_elem();
        return std::make_pair<bool, std::unique_ptr<variant_node_type>>
                (true, std::move(std::make_unique<variant_node_type>(std::move(element))));
    } catch (EPDDLException &e) {
        return std::make_pair<bool, std::unique_ptr<variant_node_type>>(false, {});
    }
}

template<class variant_leaf_type, typename token_type>
std::pair<bool, std::unique_ptr<variant_leaf_type>> parser::parse_variant_leaf() {
    std::unique_ptr<variant_leaf_type> result;
    if (is_next_token_type<token_type>()) {
        std::visit([&result](auto &&tok) {
            using tok_type = std::decay_t<decltype(tok)>;

            if constexpr (std::is_same_v<token_type, tok_type>) {
                std::unique_ptr<token_type> tok_ptr = std::move(std::make_unique<token_type>(tok));
                result = std::move(std::make_unique<variant_leaf_type>(tok_ptr));
            }
        }, *get_last_peeked_token());
        m_next_tokens.clear();
        return std::make_pair<bool, std::unique_ptr<variant_leaf_type>>(true, std::move(result));
    }
    return std::make_pair<bool, std::unique_ptr<variant_leaf_type>>(false, {});
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
    ast::unique_ptr(type) name = call_parse_node_function(type);

/* Parsing lists of nodes: we pass the correct parse function to the function parse_list (with parameter 'is_optional'
 *                         set to false) and we store its value in a corresponding variable
 */
#define parse_node_list(    type,   _,      name) \
    std::function<ast::unique_ptr(type)()>                                   \
        parse_##name = [this] () { return call_parse_node_function(type); }; \
    list_(ast::unique_ptr(type)) name = parse_list(parse_##name, false);

/* Parsing optional nodes: we call the correct parse function and we store its value in a corresponding variable.
 *                         If nothing is returned, we assign std::nullopt to the variable
 */
#define parse_node_opt(     type,   _,      name) \
    optional_(ast::unique_ptr(type)) name = call_parse_node_function_opt(type); \
    if (not *name) {                                                            \
        name = std::nullopt;                                                    \
    }

/* Parsing optional lists of nodes: we pass the correct parse function to the function parse_list (with parameter
 *                                  'is_optional' set to true) and we store its value in a corresponding variable
 */
#define parse_node_opt_list(type,   _,      name) \
    std::function<ast::unique_ptr(type)()>                                   \
        parse_##name = [this] () { return call_parse_node_function(type); }; \
    list_(ast::unique_ptr(type)) name = parse_list(parse_##name, true);


/* Parsing leafs: we call the correct parse function (i.e., for a leaf_token of type 'x', we call 'get_leaf_from_next_token<x>'
 *                with parameter 'is_optional' set to false) and we store its value in a corresponding variable
 */
#define parse_leaf_simple(  type, tok_type, name) \
    token_ptr_alias(type, tok_type) name = parse_leaf_function(type, tok_type, false);

/* Parsing lists of leafs: we pass the correct parse function to the function parse_list (with parameter 'is_optional'
 *                         set to false) and we store its value in a corresponding variable
 */
#define parse_leaf_list(    type, tok_type, name) \
    std::function<token_ptr_alias(type, tok_type)()>                                     \
        parse_##name = [this] () { return parse_leaf_function(type, tok_type, false); }; \
    list_(token_ptr_alias(type, tok_type)) name = parse_list(parse_##name, false);

/* Parsing optional leafs: we call the correct parse function (i.e., for a leaf_token of type 'x', we call 'get_leaf_from_next_token<x>'
 *                         with parameter 'is_optional' set to true) and we store its value in a corresponding variable
 */
#define parse_leaf_opt(     type, tok_type, name) \
    optional_(token_ptr_alias(type, tok_type)) name = parse_leaf_function(type, tok_type, true);

/* Parsing lists of leafs: we pass the correct parse function to the function parse_list (with parameter 'is_optional'
 *                         set to true) and we store its value in a corresponding variable
 */
#define parse_leaf_opt_list(type, tok_type, name) \
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


#define node(type) 1, parse_node_simple,   type, null

// Macro argument 'type' comes from X-macro 'epddl_token' that is expanded as a pair 't_type, t_name'
#define leaf(type) 1, parse_leaf_simple,   type

#define end_rule   0, parse_end,           null, null

/* Parsing nodes: we call the correct parse function (i.e., for an element of type 'x', we call 'parse_x')
 *                and we store its value in a corresponding variable
 */
#define parse_node_simple(  var_type, type,   _) \
    std::function<ast::unique_ptr(type)()>                                    \
        _parse_##type = [this] () { return call_parse_node_function(type); }; \
    result = parse_variant_node<ast::var_type, ast::type>(_parse_##type);  \
    if (result.first) return std::move(result.second);

/* Parsing leafs: we call the correct parse function (i.e., for a leaf_token of type 'x', we call 'get_leaf_from_next_token<x>'
 *                with parameter 'is_optional' set to false) and we store its value in a corresponding variable
 */
#define parse_leaf_simple(  var_type, type, tok_type) \
    result = parse_variant_leaf<ast::var_type, type::tok_type>(); \
    if (result.first) return std::move(result.second);

// todo: fix leafs and you're done

#define parse_end(_, __, ___)

#define element_bnf(nodes...) nodes, end_rule

#define epddl_variant_element(name, nodes) \
    ast::unique_ptr(name) parser::decl_parse_node_function(name) { \
        m_choice_point = true;                                     \
        std::pair<bool, ast::unique_ptr(name)> result;             \
        PARSE_VARIANT_ELEMS(name, nodes)                           \
        m_choice_point = false;                                    \
        return {};                                                 \
    }
// todo: handle errors

//throw EPDDLException{std::string{""},                      \
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
