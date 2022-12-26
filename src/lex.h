#ifndef EPDDL_LEX_H_
#define EPDDL_LEX_H_

#include <cctype>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <set>
#include <string>
#include <utility>

class token {
public:
    enum class type : uint8_t {
        _EOF     = 0,
        _INVALID = 1,

        // PUNCTUATION
        _LPAR,                  // (
        _RPAR,                  // )
        _LBRACK,                // [
        _RBRACK,                // ]
//        _LBRACE,                // {
//        _RBRACE,                // }
        _LT,                    // <
        _GT,                    // >
        _DASH,                  // -
        _EQ,                    // =
//        _COLON,                 // :
        _GETS,                  // <-

        // BASIC ELEMENTS
        _IDENT,                 // [_a-zA-Z][_'a-zA-Z0-9]*
        _VAR,                   // \?[_a-zA-Z][_'a-zA-Z0-9]*
        _INT,                   // [0-9]|[1-9][0-9]+

        // MODALITIES
        _FORM_MODALITY,         // [a-z][_a-zA-Z0-9]*\.

        // BLOCKS KEYWORDS
        _BLOCK_ACT,             // :action
        _BLOCK_ACT_TYPE,        // :action-type
        _BLOCK_ACT_TYPE_LIB,    // :action-type-libraries
        _BLOCK_AGENTS,          // :agents
        _BLOCK_AGENT_GROUPS,    // :agent-groups
        _BLOCK_DESIGNATED,      // :designated
        _BLOCK_DOMAIN,          // :domain
        _BLOCK_EVENT,           // :event
        _BLOCK_EVENTS,          // :events
        _BLOCK_GOAL,            // :goal
        _BLOCK_INIT,            // :init
        _BLOCK_OBJECTS,         // :objects
        _BLOCK_OBS_COND,        // :observability-conditions
        _BLOCK_OBS_GROUP,       // :observability-groups
        _BLOCK_MODALITIES,      // :modalities
        _BLOCK_PARAM,           // :parameters
        _BLOCK_POSTCOND,        // :postconditions
        _BLOCK_PRECOND,         // :precondition
        _BLOCK_PREDICATES,      // :predicates
        _BLOCK_REL,             // :relations
        _BLOCK_REQ,             // :requirements
        _BLOCK_STATE,           // :state
        _BLOCK_STATE_NAME,      // :state-name
        _BLOCK_STATIC,          // :static
        _BLOCK_TYPES,           // :types
        _BLOCK_VAL,             // :valuation
        _BLOCK_WHERE,           // :where
        _BLOCK_WORLDS,          // :worlds

        // MAIN EPDDL KEYWORDS
        _EPDDL_DEF,             // define
        _EPDDL_DOM,             // domain
        _EPDDL_LIB,             // library
        _EPDDL_PROB,            // problem

        // FORMULAE KEYWORDS
        _FORM_TRUE,             // true
        _FORM_FALSE,            // false
        _FORM_NOT,              // not
        _FORM_AND,              // and
        _FORM_OR,               // or
        _FORM_IMPLY,            // imply
        _FORM_EXISTS,           // exists
        _FORM_FORALL,           // forall

        // POSTCONDITIONS KEYWORDS
        _POST_IFF,              // iff
        _POST_WHEN,             // when

        // OBSERVABILITY CONDITIONS KEYWORDS
        _OBS_IF,                // if
        _OBS_OTHERWISE,         // otherwise

        // AGENT GROUPS KEYWORDS
        _AG_GROUP_ALL,          // All
//        _AG_GROUP_AS,           // as

        // EPDDL TYPES KEYWORDS
        _TYPE_AG,               // agent
        _TYPE_PRED,             // predicate
        _TYPE_LIT,              // literal
        _TYPE_PRED_FORM,        // predicate-formula
        _TYPE_FORM,             // formula
        _TYPE_POSTCOND,         // postcondition

        // REQUIREMENTS KEYWORDS
        _REQ_CK,                // :common-knowledge
        _REQ_DEL,               // :del
        _REQ_DYN_CK,            // :dynamic-common-knowledge
        _REQ_EQ,                // :equality
        _REQ_EXIST_FORM,        // :existential-formulae
        _REQ_FIN_S5_TH,         // :finitary-S5-theory
        _REQ_MAX_DEPTH,         // :maximum-modal-depth
        _REQ_MAX_PRE_DEPTH,     // :maximum-postconditions-depth
        _REQ_MAX_POST_DEPTH,    // :maximum-preconditions-depth
        _REQ_MOD_POST,          // :modal-postconditions
        _REQ_MOD_PRE,           // :modal-preconditions
        _REQ_ONTIC,             // :ontic-change
        _REQ_TYPING,            // :typing
        _REQ_UNIV_FORM,         // :universal-formulae
        _REQ_UNIV_POST,         // :universal-postconditions
    };

    token() = default;
    token(type type, std::string lexeme, long row, long col) : m_type(type), m_lexeme{std::move(lexeme)}, m_row(row), m_col(col) {}
    token(type type,                     long row, long col) : m_type(type), m_lexeme{std::nullopt},      m_row(row), m_col(col) {}

    const type        get_type()   const { return m_type; }
    const std::string get_string() const { return m_lexeme.has_value() ? m_lexeme.value() : ""; }

    std::string to_string();

private:
    type m_type;
    std::optional<std::string> m_lexeme;
    long m_row, m_col;

    static std::string to_string(type t);
};

class lexer {
public:
    using error_handler = std::function<void(long, long, std::string)>;

    lexer() = default;
    explicit lexer(std::ifstream stream, error_handler error);

    [[nodiscard]] bool good() const;
    [[nodiscard]] bool eof() const;

    token get_next_token();

private:
    char m_current_char;
    long m_input_row, m_input_col;
    bool m_good;

    std::ifstream m_stream;
    error_handler m_error;

    std::map<std::string, token::type> m_valid_keywords;

    token scan_keyword();
    token scan_variable();
    token scan_punctuation();
    token scan_identifier();
    token scan_integer();

    [[nodiscard]] bool is_valid_keyword(const std::string& s) const;

    void ignore_spaces();
    void ignore_comments();

    [[nodiscard]] char peek_next_char();
    char get_next_char();

    static bool is_ident_char(char c);
    static bool is_keyword_char(char c);
};

#endif  // EPDDL_LEX_H_

//class token_type {
//public:
//    static const uint8_t eof     = 0;
//    static const uint8_t invalid = 1;
//
//    enum class punctuation : uint8_t {
//        lpar,                  // (
//        rpar,                  // )
//        lbrack,                // [
//        rbrack,                // ]
//        lbrace,                // {
//        rbrace,                // }
//        lt,                    // <
//        gt,                    // >
//        dash,                  // -
//        eq,                    // =
////        colon,                 // :
//        gets,                  // <-
//    };
//
//    enum class basic : uint8_t {
//        ident,                 // [_a-zA-Z][_'a-zA-Z0-9]*
//        var,                   // \?[_a-zA-Z][_'a-zA-Z0-9]*
//        modality,              // [a-z][_a-zA-Z0-9]*\.
//        integer,               // [0-9]|[1-9][0-9]+
//    };
//
//    enum class type : uint8_t {
//        agent,                 // agent
//        predicate,             // predicate
//        literal,               // literal
//        predicate_formula,     // predicate-formula
//        formula,               // formula
//        postcondition          // postcondition
//    };
//
//    enum class keyword : uint8_t {
//        // Main keywords
//        _EPDDL_DEF,             // define
//        _EPDDL_DOM,             // domain
//        _EPDDL_LIB,             // library
//        _EPDDL_PROB,            // problem
//
//        // Block keywords
//        _BLOCK_ACT,             // :action
//        _BLOCK_ACT_TYPE,        // :action-type
//        _BLOCK_ACT_TYPE_LIB,    // :action-type-libraries
//        _BLOCK_AGENTS,          // :agents
//        _BLOCK_AGENT_GROUPS,    // :agent-groups
//        _BLOCK_DESIGNATED,      // :designated
//        _BLOCK_DOMAIN,          // :domain
//        _BLOCK_EVENT,           // :event
//        _BLOCK_EVENTS,          // :events
//        _BLOCK_GOAL,            // :goal
//        _BLOCK_INIT,            // :init
//        _BLOCK_OBJECTS,         // :objects
//        _BLOCK_OBS_COND,        // :observability-conditions
//        _BLOCK_OBS_GROUP,       // :observability-groups
//        _BLOCK_MODALITIES,      // :modalities
//        _BLOCK_PARAM,           // :parameters
//        _BLOCK_POSTCOND,        // :postconditions
//        _BLOCK_PRECOND,         // :precondition
//        _BLOCK_PREDICATES,      // :predicates
//        _BLOCK_REL,             // :relations
//        _BLOCK_REQ,             // :requirements
//        _BLOCK_STATE,           // :state
//        _BLOCK_STATE_NAME,      // :state-name
//        _BLOCK_STATIC,          // :static
//        _BLOCK_TYPES,           // :types
//        _BLOCK_VAL,             // :valuation
//        _BLOCK_WHERE,           // :where
//        _BLOCK_WORLDS,          // :worlds
//
//        // Agent groups keywords
//        _AG_GROUP_ALL,          // All
//        _AG_GROUP_AS,           // as
//    };
//
//    enum class requirement : uint8_t {
//        _REQ_CK,                // :common-knowledge
//        _REQ_DEL,               // :del
//        _REQ_DYN_CK,            // :dynamic-common-knowledge
//        _REQ_EQ,                // :equality
//        _REQ_EXIST_FORM,        // :existential-formulae
//        _REQ_FIN_S5_TH,         // :finitary-S5-theory
//        _REQ_MAX_DEPTH,         // :maximum-modal-depth
//        _REQ_MAX_PRE_DEPTH,     // :maximum-postconditions-depth
//        _REQ_MAX_POST_DEPTH,    // :maximum-preconditions-depth
//        _REQ_MOD_POST,          // :modal-postconditions
//        _REQ_MOD_PRE,           // :modal-preconditions
//        _REQ_ONTIC,             // :ontic-change
//        _REQ_TYPING,            // :typing
//        _REQ_UNIV_FORM,         // :universal-formulae
//        _REQ_UNIV_POST          // :universal-postconditions
//    };
//
//    class formula {
//    public:
//        class connective {
//            enum class unary : uint8_t {
//                negation               // not
//            };
//
//            enum class binary : uint8_t {
//                implication,           // imply
//            };
//
//            enum class n_ary : uint8_t {
//                conjunction,           // and
//                disjunction            // or
//            };
//        };
//
//        enum class quantifier : uint8_t {
//            exists,           // exists
//            forall,           // forall
//        };
//
//        enum class constant : uint8_t {
//            top,             // true
//            bot              // false
//        };
//    };
//
//    enum class postcondition : uint8_t {
//        iff,              // iff
//        when              // when
//    };
//
//    enum class observability : uint8_t {
//        if_,               // if
//        otherwise          // otherwise
//    };
//};