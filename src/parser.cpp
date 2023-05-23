#include <memory>
#include <optional>
#include <type_traits>
#include "../include/parser/parser.h"
#include "../include/epddl_exception.h"

//#include <typeinfo>
#include <iostream>

//template <typename T> std::string type_name();

// todo: use robe qui sopra per stampare tipi su std output

using namespace epddl;

parser::parser(lexer &lex) :
        m_lex{lex},
        m_current_token{std::nullopt},
        m_end_list_token{std::nullopt},
        m_next_tokens{},
        m_cursor_token_index{0},
        m_choice_point{false},
        m_first_choice_point_rule{false},
        m_lpar_count{0} {}

ast::domain_ptr parser::parse() {
    return std::move(parse_domain());
}

template<typename token_type>
bool parser::has_type(token_ptr &tok) const {
    return std::holds_alternative<token<token_type>>(*tok);
}

void parser::peek_next_token() {
    if (m_end_list_token.has_value()) {
        m_next_tokens.push_back(std::move(*m_end_list_token));
        m_end_list_token->reset();
        m_end_list_token = std::nullopt;
    } else if (m_lex.good() and not m_lex.eof()) {
        m_next_tokens.push_back(std::move(m_lex.get_next_token()));
    }

    update_scopes(get_last_peeked_token());

    std::visit([this](auto &&tok) {
        using tok_type = std::decay_t<decltype(tok)>;

        if constexpr (std::is_same_v<pattern_token, get_super_t<get_argument_t<tok_type>>>) {
            m_current_token.emplace(std::move(get_last_peeked_token()));
            m_next_tokens.clear();
        }
    }, *get_last_peeked_token());
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
            std::visit([](auto &&tok) {
                using tok_type = get_argument_t<std::decay_t<decltype(tok)>>;

                throw EPDDLException{std::string{""}, tok.get_row(), tok.get_col(),
                                     std::string{"Expected "} + std::string{tok_type::lexeme} + std::string{"."}};
            }, *get_cursor_token());
        }
    }
    return result;
}

void parser::get_next_token() {
    if (m_choice_point) {
        // If we currently are inside a choice point and this is our first rule we are checking
        if (m_first_choice_point_rule)
            peek_next_token();
        // todo: if last peeked token is not a terminal, throw error (probably add <is_terminal> field to token macros)
    } else {
        if (m_next_tokens.empty() and not m_end_list_token.has_value() and m_lex.good() and not m_lex.eof()) {
            m_current_token.emplace(std::move(m_lex.get_next_token()));
        } else {
            if (m_end_list_token.has_value()) {
                m_next_tokens.push_back(std::move(*m_end_list_token));
                m_end_list_token->reset();
                m_end_list_token = std::nullopt;
            }
            m_current_token.emplace(std::move(m_next_tokens.back()));
            m_next_tokens.clear();
        }

        update_scopes(*m_current_token);
    }
}

void parser::update_scopes(const token_ptr& token) {
    std::visit([this](auto &&tok) {
        using tok_type = get_argument_t<std::decay_t<decltype(tok)>>;

        if constexpr (std::is_same_v<tok_type, punctuation_token::lpar>) {
            ++m_lpar_count;
        } else if constexpr (std::is_same_v<tok_type, punctuation_token::rpar>) {
            if (m_lpar_count == m_scopes.top().first) {
                m_scopes.pop();
            }
            --m_lpar_count;
        } else {
            if constexpr (tok_type::is_scope) {
                m_scopes.emplace(m_lpar_count, &*m_current_token);
            }
        }
    }, *token);
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

        // If we were inside a choice point and we find a leaf token, we eat it and we exit from the
        // choice point: we do so because we are now sure to have done the right choice and we do not
        // need to explore other alternatives
//        m_choice_point = false;
    }

    return leaf;
}

bool parser::is_end_list() {
    if (m_lex.good() and not m_lex.eof()) {
        m_end_list_token.emplace(std::move(m_lex.get_next_token()));
    }
    #define epddl_token_type(token_type) token_type
    return has_type<epddl_punctuation_token_type::rpar>(*m_end_list_token);
    #undef epddl_token_type
}

template<class node_type>
std::list<node_type> parser::parse_list(std::function<node_type()> parse_elem, bool is_optional_list) {
    // If we are parsing a list and we were in a choice point, then it means that all the previous terminals
    // have been correctly parsed and we can exit the choice point
    // todo: what if we have a variant of a node that is defined as a list of nodes?
//    m_choice_point = false;

    std::list<node_type> elems;
    bool is_empty_list = true;

    while (not is_end_list()) {
        // If we do not peek ')', we parse the element and, if we are successful, we add it to the list.
        // We assume that parse_elem() takes care of its relative syntax errors
        elems.push_back(std::move(parse_elem()));
        is_empty_list = false;
    }

    if (not is_optional_list and is_empty_list) {
        // todo: create better error description
        std::visit([](auto &&tok) {
            throw EPDDLException{std::string{""}, tok.get_row(), tok.get_col(), std::string{"Empty list."}};
        }, **m_current_token);
    }

    // We actually consume the ')' token
//    #define epddl_token_type(token_type) token_type
//    check_next_token<epddl_punctuation_token_type::rpar>();
//    #undef epddl_token_type

    return elems;
}

template<class variant_node_type, class node_type>
std::pair<bool, std::unique_ptr<variant_node_type>> parser::parse_variant_node(std::function<std::unique_ptr<node_type>()> parse_elem) {
    bool is_succesful = true;
    std::unique_ptr<node_type> element = {};
    m_cursor_token_index = 0;

    try {
        element = std::move(parse_elem());
    } catch (EPDDLException &e) {
        is_succesful = false;
//        element = {};
    }

    m_first_choice_point_rule = false;
    return std::make_pair<bool, std::unique_ptr<variant_node_type>>
            (std::forward<bool>(is_succesful), std::move(std::make_unique<variant_node_type>(std::move(element))));
}

template<class variant_leaf_type, typename token_type>
std::pair<bool, std::unique_ptr<variant_leaf_type>> parser::parse_variant_leaf() {
    std::unique_ptr<variant_leaf_type> result;
    std::unique_ptr<token<token_type>> leaf;

    if (is_next_token_type<token_type>()) {
        std::visit([&leaf](auto &&tok) {
            using tok_type = std::decay_t<decltype(tok)>;

            if constexpr (std::is_same_v<token<token_type>, tok_type>) {
                leaf = std::move(std::make_unique<tok_type>(std::forward<tok_type>(tok)));
            }
        }, *get_last_peeked_token());

        result = std::move(std::make_unique<variant_leaf_type>(std::move(leaf)));

//        std::visit([&result](auto &&tok) {
//            using tok_type = std::decay_t<decltype(tok)>;
//
//            if constexpr (std::is_same_v<token<token_type>, tok_type>) {
//                std::unique_ptr<tok_type> tok_ptr = std::move(std::make_unique<tok_type>(tok));
//                result = std::move(std::make_unique<variant_leaf_type>(tok_ptr));
//            }
//        }, *get_last_peeked_token());
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
    m_choice_point = false;                                                  \
    ast::unique_ptr(type) name = call_parse_node_function(type);

/* Parsing lists of nodes: we pass the correct parse function to the function parse_list (with parameter 'is_optional'
 *                         set to false) and we store its value in a corresponding variable
 */
#define parse_node_list(    type,   _,      name) \
    m_choice_point = false;                                                  \
    std::function<ast::unique_ptr(type)()>                                   \
        parse_##name = [this] () { return call_parse_node_function(type); }; \
    list_(ast::unique_ptr(type)) name = parse_list(parse_##name, false);

/* Parsing optional nodes: we call the correct parse function and we store its value in a corresponding variable.
 *                         If nothing is returned, we assign std::nullopt to the variable
 */
#define parse_node_opt(     type,   _,      name) \
    m_choice_point = false;                                                     \
    optional_(ast::unique_ptr(type)) name = call_parse_node_function_opt(type); \
    if (not *name) {                                                            \
        name = std::nullopt;                                                    \
    }

/* Parsing optional lists of nodes: we pass the correct parse function to the function parse_list (with parameter
 *                                  'is_optional' set to true) and we store its value in a corresponding variable
 */
#define parse_node_opt_list(type,   _,      name) \
    m_choice_point = false;                                                  \
    std::function<ast::unique_ptr(type)()>                                   \
        parse_##name = [this] () { return call_parse_node_function(type); }; \
    list_(ast::unique_ptr(type)) name = parse_list(parse_##name, true);


/* Parsing leafs: we call the correct parse function (i.e., for a leaf_token of type 'x', we call 'get_leaf_from_next_token<x>'
 *                with parameter 'is_optional' set to false) and we store its value in a corresponding variable
 */
#define parse_leaf_simple(  type, tok_type, name) \
    m_choice_point = false;                                                              \
    token_ptr_alias(type, tok_type) name = parse_leaf_function(type, tok_type, false);

/* Parsing lists of leafs: we pass the correct parse function to the function parse_list (with parameter 'is_optional'
 *                         set to false) and we store its value in a corresponding variable
 */
#define parse_leaf_list(    type, tok_type, name) \
    m_choice_point = false;                                                              \
    std::function<token_ptr_alias(type, tok_type)()>                                     \
        parse_##name = [this] () { return parse_leaf_function(type, tok_type, false); }; \
    list_(token_ptr_alias(type, tok_type)) name = parse_list(parse_##name, false);

/* Parsing optional leafs: we call the correct parse function (i.e., for a leaf_token of type 'x', we call 'get_leaf_from_next_token<x>'
 *                         with parameter 'is_optional' set to true) and we store its value in a corresponding variable
 */
#define parse_leaf_opt(     type, tok_type, name) \
    m_choice_point = false;                                                              \
    optional_(token_ptr_alias(type, tok_type)) name = parse_leaf_function(type, tok_type, true);

/* Parsing lists of leafs: we pass the correct parse function to the function parse_list (with parameter 'is_optional'
 *                         set to true) and we store its value in a corresponding variable
 */
#define parse_leaf_opt_list(type, tok_type, name) \
    m_choice_point = false;                                                              \
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
    ast::unique_ptr(name) parser::decl_parse_node_function(name) { \
        m_choice_point = true;                                     \
        m_first_choice_point_rule = true;                          \
        std::pair<bool, ast::unique_ptr(name)> result;             \
        PARSE_VARIANT_ELEMS(name, nodes)                           \
        return {};                                                 \
    }
// todo: handle errors

//throw EPDDLException{std::string{""},                      \
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
    m_choice_point = false;
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    m_choice_point = false;
    std::function<ast::term_ptr()> parse_terms = [this]() { return parse_term(); };
    std::list<ast::term_ptr> terms = parse_list(parse_terms, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::predicate>(std::move(name), std::move(terms));
}
ast::negated_predicate_ptr parser::parse_negated_predicate(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::negation>();
    m_choice_point = false;
    ast::predicate_ptr pred = parse_predicate();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::negated_predicate>(std::move(pred));
}
ast::formula_variable_ptr parser::parse_formula_variable(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    pattern_token_variable_ptr var = std::move(get_leaf_from_next_token<pattern_token::variable>(false));
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::formula_variable>(std::move(var));
}
ast::eq_formula_ptr parser::parse_eq_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<punctuation_token::eq>();
    m_choice_point = false;
    ast::term_ptr t1 = parse_term();
    m_choice_point = false;
    ast::term_ptr t2 = parse_term();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::eq_formula>(std::move(t1), std::move(t2));
}
ast::not_formula_ptr parser::parse_not_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::negation>();
    m_choice_point = false;
    ast::formula_ptr f = parse_formula();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::not_formula>(std::move(f));
}
ast::and_formula_ptr parser::parse_and_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::conjunction>();
    m_choice_point = false;
    std::function<ast::formula_ptr()> parse_fs = [this]() { return parse_formula(); };
    std::list<ast::formula_ptr> fs = parse_list(parse_fs, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::and_formula>(std::move(fs));
}
ast::or_formula_ptr parser::parse_or_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::disjunction>();
    m_choice_point = false;
    std::function<ast::formula_ptr()> parse_fs = [this]() { return parse_formula(); };
    std::list<ast::formula_ptr> fs = parse_list(parse_fs, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::or_formula>(std::move(fs));
}
ast::imply_formula_ptr parser::parse_imply_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<connective_token::disjunction>();
    m_choice_point = false;
    ast::formula_ptr f1 = parse_formula();
    m_choice_point = false;
    ast::formula_ptr f2 = parse_formula();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::imply_formula>(std::move(f1), std::move(f2));
}
ast::modality_ptr parser::parse_modality(bool is_optional) {
    m_choice_point = false;
    std::optional<pattern_token_modality_ptr> mod = std::move(get_leaf_from_next_token<pattern_token::modality>(true));
    m_choice_point = false;
    std::function<ast::agent_ptr()> parse_ags = [this]() { return parse_agent(); };
    std::list<ast::agent_ptr> ags = parse_list(parse_ags, false);
    return std::make_unique<ast::modality>(std::move(mod), std::move(ags));
}
ast::box_formula_ptr parser::parse_box_formula(bool is_optional) {
    check_next_token<punctuation_token::lbrack>();
    m_choice_point = false;
    ast::modality_ptr mod = parse_modality();
    check_next_token<punctuation_token::rbrack>();
    m_choice_point = false;
    ast::formula_ptr f = parse_formula();
    return std::make_unique<ast::box_formula>(std::move(mod), std::move(f));
}
ast::diamond_formula_ptr parser::parse_diamond_formula(bool is_optional) {
    check_next_token<punctuation_token::lt>();
    m_choice_point = false;
    ast::modality_ptr mod = parse_modality();
    check_next_token<punctuation_token::gt>();
    m_choice_point = false;
    ast::formula_ptr f = parse_formula();
    return std::make_unique<ast::diamond_formula>(std::move(mod), std::move(f));
}
ast::exists_formula_ptr parser::parse_exists_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<quantifier_token::exists>();
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, false);
    check_next_token<punctuation_token::rpar>();
    m_choice_point = false;
    ast::formula_ptr f = parse_formula();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::exists_formula>(std::move(params), std::move(f));
}
ast::forall_formula_ptr parser::parse_forall_formula(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<quantifier_token::forall>();
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, false);
    check_next_token<punctuation_token::rpar>();
    m_choice_point = false;
    ast::formula_ptr f = parse_formula();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::forall_formula>(std::move(params), std::move(f));
}
ast::parameters_ptr parser::parse_parameters(bool is_optional) {
    check_next_token<keyword_token::parameters>();
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, true);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::parameters>(std::move(params));
}
ast::iff_postcondition_ptr parser::parse_iff_postcondition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<post_connective_token::iff>();
    m_choice_point = false;
    ast::formula_ptr cond = parse_formula();
    m_choice_point = false;
    ast::literal_ptr l = parse_literal();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::iff_postcondition>(std::move(cond), std::move(l));
}
ast::when_postcondition_ptr parser::parse_when_postcondition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<post_connective_token::when>();
    m_choice_point = false;
    ast::formula_ptr cond = parse_formula();
    m_choice_point = false;
    ast::literal_ptr l = parse_literal();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::when_postcondition>(std::move(cond), std::move(l));
}
ast::always_postcondition_ptr parser::parse_always_postcondition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<post_connective_token::always>();
    m_choice_point = false;
    ast::literal_ptr l = parse_literal();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::always_postcondition>(std::move(l));
}
ast::forall_postcond_ptr parser::parse_forall_postcond(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<quantifier_token::forall>();
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, false);
    check_next_token<punctuation_token::rpar>();
    m_choice_point = false;
    std::function<ast::simple_postcondition_ptr()> parse_postconds = [this]() { return parse_simple_postcondition(); };
    std::list<ast::simple_postcondition_ptr> postconds = parse_list(parse_postconds, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::forall_postcond>(std::move(params), std::move(postconds));
}
ast::signature_ptr parser::parse_signature(bool is_optional) {
    check_next_token<keyword_token::act_type>();
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    m_choice_point = false;
    std::function<ast::assignment_ptr()> parse_assignments = [this]() { return parse_assignment(); };
    std::list<ast::assignment_ptr> assignments = parse_list(parse_assignments, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::signature>(std::move(name), std::move(assignments));
}
ast::assignment_ptr parser::parse_assignment(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    pattern_token_variable_ptr var = std::move(get_leaf_from_next_token<pattern_token::variable>(false));
    check_next_token<punctuation_token::gets>();
    m_choice_point = false;
    ast::expression_ptr expr = parse_expression();
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::assignment>(std::move(var), std::move(expr));
}
ast::type_ptr parser::parse_type(bool is_optional) {
    check_next_token<punctuation_token::dash>();
    m_choice_point = false;
    pattern_token_identifier_ptr elem_type = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    return std::make_unique<ast::type>(std::move(elem_type));
}
ast::typed_ident_ptr parser::parse_typed_ident(bool is_optional) {
    m_choice_point = false;
    pattern_token_identifier_ptr id = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    m_choice_point = false;
    std::optional<ast::type_ptr> id_type = parse_type(true);
    if (not*id_type) { id_type = std::nullopt; }
    return std::make_unique<ast::typed_ident>(std::move(id), std::move(id_type));
}
ast::typed_var_ptr parser::parse_typed_var(bool is_optional) {
    m_choice_point = false;
    pattern_token_variable_ptr var = std::move(get_leaf_from_next_token<pattern_token::variable>(false));
    m_choice_point = false;
    std::optional<ast::type_ptr> var_type = parse_type(true);
    if (not*var_type) { var_type = std::nullopt; }
    return std::make_unique<ast::typed_var>(std::move(var), std::move(var_type));
}
ast::domain_ptr parser::parse_domain(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::define>();
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::domain>();
    m_choice_point = false;
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    check_next_token<punctuation_token::rpar>();
    m_choice_point = false;
    std::function<ast::domain_item_ptr()> parse_items = [this]() { return parse_domain_item(); };
    std::list<ast::domain_item_ptr> items = parse_list(parse_items, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain>(std::move(name), std::move(items));
}
ast::domain_requirements_ptr parser::parse_domain_requirements(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::requirements>();
    m_choice_point = false;
    std::function<ast::requirement_ptr()> parse_reqs = [this]() { return parse_requirement(); };
    std::list<ast::requirement_ptr> reqs = parse_list(parse_reqs, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_requirements>(std::move(reqs));
}
ast::simple_requirement_ptr parser::parse_simple_requirement(bool is_optional) {
    // todo: e qui so cazzi (empty terminal prefix)
    m_choice_point = false;
    pattern_token_requirement_ptr req = std::move(get_leaf_from_next_token<pattern_token::requirement>(false));
    return std::make_unique<ast::simple_requirement>(std::move(req));
}
ast::val_requirement_ptr parser::parse_val_requirement(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    pattern_token_requirement_ptr req = std::move(get_leaf_from_next_token<pattern_token::requirement>(false));
    m_choice_point = false;
    pattern_token_integer_ptr val = std::move(get_leaf_from_next_token<pattern_token::integer>(false));
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::val_requirement>(std::move(req), std::move(val));
}
ast::domain_libraries_ptr parser::parse_domain_libraries(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::act_type_lib>();
    m_choice_point = false;
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
    m_choice_point = false;
    std::function<ast::typed_ident_ptr()> parse_types = [this]() { return parse_typed_ident(); };
    std::list<ast::typed_ident_ptr> types = parse_list(parse_types, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_types>(std::move(types));
}
ast::domain_predicates_ptr parser::parse_domain_predicates(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::predicates>();
    m_choice_point = false;
    std::function<ast::predicate_signature_ptr()> parse_signatures = [this]() { return parse_predicate_signature(); };
    std::list<ast::predicate_signature_ptr> signatures = parse_list(parse_signatures, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_predicates>(std::move(signatures));
}
ast::predicate_signature_ptr parser::parse_predicate_signature(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    m_choice_point = false;
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, true);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::predicate_signature>(std::move(name), std::move(params));
}
ast::domain_modalities_ptr parser::parse_domain_modalities(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<keyword_token::modalities>();
    m_choice_point = false;
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
    m_choice_point = false;
    pattern_token_identifier_ptr name = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    m_choice_point = false;
    ast::parameters_ptr parameters = parse_parameters();
    m_choice_point = false;
    ast::signature_ptr signature = parse_signature();
    m_choice_point = false;
    ast::formula_ptr precondition = parse_formula();
    m_choice_point = false;
    std::optional<ast::action_obs_conditions_ptr> obs_conditions = parse_action_obs_conditions(true);
    if (not*obs_conditions) { obs_conditions = std::nullopt; }
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::domain_action>(std::move(name), std::move(parameters), std::move(signature),
                                                std::move(precondition), std::move(obs_conditions));
}
ast::action_obs_conditions_ptr parser::parse_action_obs_conditions(bool is_optional) {
    check_next_token<keyword_token::obs_conditions>();
    m_choice_point = false;
    std::function<ast::obs_condition_ptr()> parse_conditions = [this]() { return parse_obs_condition(); };
    std::list<ast::obs_condition_ptr> conditions = parse_list(parse_conditions, false);
    return std::make_unique<ast::action_obs_conditions>(std::move(conditions));
}
ast::static_obs_condition_ptr parser::parse_static_obs_condition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    ast::agent_ptr agent = parse_agent();
    m_choice_point = false;
    pattern_token_identifier_ptr group = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::static_obs_condition>(std::move(agent), std::move(group));
}
ast::if_obs_condition_ptr parser::parse_if_obs_condition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<observability_token::if_cond>();
    m_choice_point = false;
    ast::formula_ptr cond = parse_formula();
    m_choice_point = false;
    ast::agent_ptr agent = parse_agent();
    m_choice_point = false;
    pattern_token_identifier_ptr group = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::if_obs_condition>(std::move(cond), std::move(agent), std::move(group));
}
ast::otherwise_obs_condition_ptr parser::parse_otherwise_obs_condition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<observability_token::otherwise>();
    m_choice_point = false;
    ast::agent_ptr agent = parse_agent();
    m_choice_point = false;
    pattern_token_identifier_ptr group = std::move(get_leaf_from_next_token<pattern_token::identifier>(false));
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::otherwise_obs_condition>(std::move(agent), std::move(group));
}
ast::forall_obs_condition_ptr parser::parse_forall_obs_condition(bool is_optional) {
    check_next_token<punctuation_token::lpar>();
    check_next_token<quantifier_token::forall>();
    check_next_token<punctuation_token::lpar>();
    m_choice_point = false;
    std::function<ast::typed_var_ptr()> parse_params = [this]() { return parse_typed_var(); };
    std::list<ast::typed_var_ptr> params = parse_list(parse_params, false);
    check_next_token<punctuation_token::rpar>();
    m_choice_point = false;
    std::function<ast::simple_obs_condition_ptr()> parse_obs_conds = [this]() { return parse_simple_obs_condition(); };
    std::list<ast::simple_obs_condition_ptr> obs_conds = parse_list(parse_obs_conds, false);
    check_next_token<punctuation_token::rpar>();
    return std::make_unique<ast::forall_obs_condition>(std::move(params), std::move(obs_conds));
}






ast::term_ptr parser::parse_term(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::term_ptr> result;
    result = parse_variant_leaf<ast::term, pattern_token::identifier>();
    if (result.first)return std::move(result.second);
    result = parse_variant_leaf<ast::term, pattern_token::variable>();
    if (result.first)return std::move(result.second);
    return {};
}
ast::atomic_formula_ptr parser::parse_atomic_formula(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
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
    return {};
}
ast::literal_ptr parser::parse_literal(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::literal_ptr> result;
    std::function<ast::predicate_ptr()> _parse_predicate = [this]() { return parse_predicate(); };
    result = parse_variant_node<ast::literal, ast::predicate>(_parse_predicate);
    if (result.first)return std::move(result.second);
    std::function<ast::negated_predicate_ptr()> _parse_negated_predicate = [this]() { return parse_negated_predicate(); };
    result = parse_variant_node<ast::literal, ast::negated_predicate>(_parse_negated_predicate);
    if (result.first)return std::move(result.second);
    return {};
}
ast::propositional_formula_ptr parser::parse_propositional_formula(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
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
    return {};
}
ast::modal_formula_ptr parser::parse_modal_formula(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::modal_formula_ptr> result;
    std::function<ast::box_formula_ptr()> _parse_box_formula = [this]() { return parse_box_formula(); };
    result = parse_variant_node<ast::modal_formula, ast::box_formula>(_parse_box_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::diamond_formula_ptr()> _parse_diamond_formula = [this]() { return parse_diamond_formula(); };
    result = parse_variant_node<ast::modal_formula, ast::diamond_formula>(_parse_diamond_formula);
    if (result.first)return std::move(result.second);
    return {};
}
ast::quantified_formula_ptr parser::parse_quantified_formula(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::quantified_formula_ptr> result;
    std::function<ast::exists_formula_ptr()> _parse_exists_formula = [this]() { return parse_exists_formula(); };
    result = parse_variant_node<ast::quantified_formula, ast::exists_formula>(_parse_exists_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::forall_formula_ptr()> _parse_forall_formula = [this]() { return parse_forall_formula(); };
    result = parse_variant_node<ast::quantified_formula, ast::forall_formula>(_parse_forall_formula);
    if (result.first)return std::move(result.second);
    return {};
}
ast::formula_ptr parser::parse_formula(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
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
    return {};
}
ast::agent_ptr parser::parse_agent(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::agent_ptr> result;
    result = parse_variant_leaf<ast::agent, pattern_token::identifier>();
    if (result.first)return std::move(result.second);
    result = parse_variant_leaf<ast::agent, pattern_token::variable>();
    if (result.first)return std::move(result.second);
    result = parse_variant_leaf<ast::agent, agent_group_token::all>();
    if (result.first)return std::move(result.second);
    return {};
}
ast::simple_postcondition_ptr parser::parse_simple_postcondition(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::simple_postcondition_ptr> result;
    std::function<ast::iff_postcondition_ptr()> _parse_iff_postcondition = [this]() { return parse_iff_postcondition(); };
    result = parse_variant_node<ast::simple_postcondition, ast::iff_postcondition>(_parse_iff_postcondition);
    if (result.first)return std::move(result.second);
    std::function<ast::when_postcondition_ptr()> _parse_when_postcondition = [this]() { return parse_when_postcondition(); };
    result = parse_variant_node<ast::simple_postcondition, ast::when_postcondition>(_parse_when_postcondition);
    if (result.first)return std::move(result.second);
    std::function<ast::always_postcondition_ptr()> _parse_always_postcondition = [this]() { return parse_always_postcondition(); };
    result = parse_variant_node<ast::simple_postcondition, ast::always_postcondition>(_parse_always_postcondition);
    if (result.first)return std::move(result.second);
    return {};
}
ast::postcondition_ptr parser::parse_postcondition(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::postcondition_ptr> result;
    std::function<ast::simple_postcondition_ptr()> _parse_simple_postcondition = [this]() { return parse_simple_postcondition(); };
    result = parse_variant_node<ast::postcondition, ast::simple_postcondition>(_parse_simple_postcondition);
    if (result.first)return std::move(result.second);
    std::function<ast::forall_postcond_ptr()> _parse_forall_postcond = [this]() { return parse_forall_postcond(); };
    result = parse_variant_node<ast::postcondition, ast::forall_postcond>(_parse_forall_postcond);
    if (result.first)return std::move(result.second);
    return {};
}
ast::expression_ptr parser::parse_expression(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::expression_ptr> result;
    std::function<ast::term_ptr()> _parse_term = [this]() { return parse_term(); };
    result = parse_variant_node<ast::expression, ast::term>(_parse_term);
    if (result.first)return std::move(result.second);
    std::function<ast::formula_ptr()> _parse_formula = [this]() { return parse_formula(); };
    result = parse_variant_node<ast::expression, ast::formula>(_parse_formula);
    if (result.first)return std::move(result.second);
    std::function<ast::postcondition_ptr()> _parse_postcondition = [this]() { return parse_postcondition(); };
    result = parse_variant_node<ast::expression, ast::postcondition>(_parse_postcondition);
    if (result.first)return std::move(result.second);
    return {};
}
ast::domain_item_ptr parser::parse_domain_item(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
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
    return {};
}
ast::requirement_ptr parser::parse_requirement(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::requirement_ptr> result;
    std::function<ast::simple_requirement_ptr()> _parse_simple_requirement = [this]() { return parse_simple_requirement(); };
    result = parse_variant_node<ast::requirement, ast::simple_requirement>(_parse_simple_requirement);
    if (result.first)return std::move(result.second);
    std::function<ast::val_requirement_ptr()> _parse_val_requirement = [this]() { return parse_val_requirement(); };
    result = parse_variant_node<ast::requirement, ast::val_requirement>(_parse_val_requirement);
    if (result.first)return std::move(result.second);
    return {};
}
ast::simple_obs_condition_ptr parser::parse_simple_obs_condition(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
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
    return {};
}
ast::obs_condition_ptr parser::parse_obs_condition(bool is_optional) {
    m_choice_point = true;
    m_first_choice_point_rule = true;
    std::pair<bool, ast::obs_condition_ptr> result;
    std::function<ast::simple_obs_condition_ptr()> _parse_simple_obs_condition = [this]() { return parse_simple_obs_condition(); };
    result = parse_variant_node<ast::obs_condition, ast::simple_obs_condition>(_parse_simple_obs_condition);
    if (result.first)return std::move(result.second);
    std::function<ast::forall_obs_condition_ptr()> _parse_forall_obs_condition = [this]() { return parse_forall_obs_condition(); };
    result = parse_variant_node<ast::obs_condition, ast::forall_obs_condition>(_parse_forall_obs_condition);
    if (result.first)return std::move(result.second);
    return {};
}
