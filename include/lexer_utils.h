#ifndef EPDDL_LEXER_UTILS_H
#define EPDDL_LEXER_UTILS_H

#include <cctype>
#include <variant>

namespace epddl::utils::token {
    enum class special : uint8_t {
        eof,
        invalid
    };

    enum class punctuation : uint8_t {
        lpar,                   // (
        rpar,                   // )
        lbrack,                 // [
        rbrack,                 // ]
        lt,                     // <
        gt,                     // >
        dash,                   // -
        eq,                     // =
        gets                    // <-
    };

    enum class basic : uint8_t {
        // Basic elements
        ident,                  // [_a-zA-Z][_'a-zA-Z0-9]*
        variable,                    // \?[_a-zA-Z][_'a-zA-Z0-9]*
        modality,               // [a-z][_a-zA-Z0-9]*\.
        integer                 // [0-9]|[1-9][0-9]+
    };

    enum class scope : uint8_t {
        // Main scope
        define,                  // define
        domain,                 // domain
        library,                // library
        problem,                // problem

        // Block scopes
        action,                 // :action
        act_type,               // :action-type
        act_type_lib,           // :action-type-libraries
        agents,                 // :agents
        agent_groups,           // :agent-groups
        designated,             // :designated
        prob_domain,            // :domain
        event,                  // :event
        events,                 // :events
        goal,                   // :goal
        init,                   // :init
        objects,                // :objects
        obs_conditions,         // :observability-conditions
        obs_groups,             // :observability-groups
        modalities,             // :modalities
        parameters,             // :parameters
        postconditions,         // :postconditions
        precondition,           // :precondition
        predicates,             // :predicates
        relations,              // :relations
        requirements,           // :requirements
        state,                  // :state
        state_name,             // :state-name
        static_preds,           // :static
        types,                  // :types
        valuation,              // :valuation
        where,                  // :where
        worlds                  // :worlds
    };

    class connective {
    public:
        enum class unary : uint8_t {
            negation               // not
        };

        enum class binary : uint8_t {
            implication,           // imply
        };

        enum class n_ary : uint8_t {
            conjunction,           // and
            disjunction            // or
        };
    };

    enum class quantifier : uint8_t {
        exists,           // exists
        forall            // forall
    };

    enum class atomic_formula : uint8_t {
        bot,             // false
        top              // true
    };

    enum class postcondition : uint8_t {
        iff,              // iff
        when              // when
    };

    enum class observability : uint8_t {
        if_cond,           // if
        otherwise          // otherwise
    };

    enum class reserved_type : uint8_t {
        agent,                  // agent
        formula,                // formula
        literal,                // literal
        postcondition,          // postcondition
        predicate,              // predicate
        predicate_formula       // predicate-formula
    };

    enum class agents : uint8_t {
        // Agent groups keyword
        all              // All
    };

    enum class requirement : uint8_t {
        ck,                // :common-knowledge
        del,               // :del
        dyn_ck,            // :dynamic-common-knowledge
        eq,                // :equality
        exist_form,        // :existential-formulae
        fin_s5_th,          // :finitary-S5-theory
        max_depth,         // :maximum-modal-depth
        max_pre_depth,     // :maximum-postconditions-depth
        max_post_depth,    // :maximum-preconditions-depth
        mod_post,          // :modal-postconditions
        mod_pre,           // :modal-preconditions
        ontic,             // :ontic-change
        typing,            // :typing
        univ_form,         // :universal-formulae
        univ_post          // :universal-postconditions
    };

    using type = std::variant<
            special,
            punctuation,
            basic,
            scope,
            connective::unary,
            connective::binary,
            connective::n_ary,
            quantifier,
            atomic_formula,
            postcondition,
            observability,
            reserved_type,
            agents,
            requirement>;
}

#endif //EPDDL_LEXER_UTILS_H
