#ifndef EPDDL_AST_UTILS_H
#define EPDDL_AST_UTILS_H

#include <cstdint>
#include <list>
#include <map>
#include <utility>
#include <variant>
#include "../../lex/dictionary.h"

namespace epddl::ast {
    // Forward declarations
    class ASTNode;
    class Identifier;
    class Variable;
    class Integer;
    class Type;
    class Modality;
    class Requirement;
    class Formula;
    class QuantifiedFormula;
    class ModalFormula;
    class Term;
    class Predicate;
    class EqFormula;
    class Parameters;
    class ActualParameter;
    class Signature;
    class SimpleObsCondition;
    class IfObsCondition;
    class ForallObsCondition;
    class Action;
    class DomainLibraries;
    class DomainRequirements;
    class DomainTypes;
    class PredicateDef;
    class DomainPredicates;
    class DomainModalities;
    class Domain;
    class ActionType;
    class Literal;
    class SimplePostcondition;
    class ForallPostcondition;
    class Event;
    class Library;
    class AgentGroup;
    class EpistemicState;
    class Init;
    class Problem;
    class PlanningTask;
}


namespace epddl::utils::ast_node {
    // Easier type names
    using ast_node              = std::unique_ptr<ast::ASTNode>;
    using identifier            = std::unique_ptr<ast::Identifier>;
    using variable              = std::unique_ptr<ast::Variable>;
    using integer               = std::unique_ptr<ast::Integer>;
    using type                  = std::unique_ptr<ast::Type>;
    using modality              = std::unique_ptr<ast::Modality>;
    using requirement           = std::unique_ptr<ast::Requirement>;
    using formula               = std::unique_ptr<ast::Formula>;
    using quantified_formula    = std::unique_ptr<ast::QuantifiedFormula>;
    using modal_formula         = std::unique_ptr<ast::ModalFormula>;
    using term                  = std::unique_ptr<ast::Term>;
    using predicate             = std::unique_ptr<ast::Predicate>;
    using eq_formula            = std::unique_ptr<ast::EqFormula>;
    using parameters            = std::unique_ptr<ast::Parameters>;
    using actual_parameter      = std::unique_ptr<ast::ActualParameter>;
    using signature             = std::unique_ptr<ast::Signature>;
    using simple_obs_cond       = std::unique_ptr<ast::SimpleObsCondition>;
    using if_obs_cond           = std::unique_ptr<ast::IfObsCondition>;
    using forall_obs_cond       = std::unique_ptr<ast::ForallObsCondition>;
    using action                = std::unique_ptr<ast::Action>;
    using domain_libraries      = std::unique_ptr<ast::DomainLibraries>;
    using domain_requirements   = std::unique_ptr<ast::DomainRequirements>;
    using domain_types          = std::unique_ptr<ast::DomainTypes>;
    using predicate_def         = std::unique_ptr<ast::PredicateDef>;
    using domain_predicates     = std::unique_ptr<ast::DomainPredicates>;
    using domain_modalities     = std::unique_ptr<ast::DomainModalities>;
    using domain                = std::unique_ptr<ast::Domain>;
    using action_type           = std::unique_ptr<ast::ActionType>;
    using literal               = std::unique_ptr<ast::Literal>;
    using simple_post           = std::unique_ptr<ast::SimplePostcondition>;
    using forall_post           = std::unique_ptr<ast::ForallPostcondition>;
    using event                 = std::unique_ptr<ast::Event>;
    using library               = std::unique_ptr<ast::Library>;
    using agent_group           = std::unique_ptr<ast::AgentGroup>;
    using epistemic_state       = std::unique_ptr<ast::EpistemicState>;
    using init                  = std::unique_ptr<ast::Init>;
    using problem               = std::unique_ptr<ast::Problem>;
    using planning_task         = std::unique_ptr<ast::PlanningTask>;

    using domain_item           = std::variant<domain_libraries, domain_requirements, domain_types,
                                               domain_predicates, domain_modalities, action>;
    using domain_item_list      = std::list<domain_item>;

    using formal_param          = std::pair<variable, std::optional<type>>;
    using ident_list            = std::list<identifier>;
    using requirement_list      = std::list<requirement>;
    using type_list             = std::list<type>;
    using formal_param_list     = std::list<formal_param>;

    using modality_agent        = std::variant<identifier, ident_list>;
    using formula_list          = std::list<formula>;
    using formula_arg           = std::variant<std::monostate, formula, formula_list>;
    using term_list             = std::list<term>;
    using predicate_def_list    = std::list<predicate_def>;
    using predicate_list        = std::list<predicate>;
    using literal_list          = std::list<literal>;
    using modality_list         = std::list<modality>;

    using postcondition         = std::variant<simple_post, forall_post>;
    using simple_post_list      = std::list<simple_post>;
    using postcondition_list    = std::list<postcondition>;

    using expression            = std::variant<term, formula, postcondition, variable>;
    using assignment            = std::pair<variable, expression>;
    using assignment_list       = std::list<assignment>;

    using observing_agent       = std::variant<identifier, variable>;
    using obs_cond              = std::variant<simple_obs_cond, if_obs_cond, forall_obs_cond>;
    using simple_obs_cond_list  = std::list<simple_obs_cond>;
    using obs_cond_list         = std::list<obs_cond>;

    using action_list           = std::list<action>;
    using action_type_list      = std::list<action_type>;
    using signature_list        = std::list<signature>;

    using agent_relation        = std::optional<std::list<std::pair<identifier, identifier>>>;
    using relations             = std::map<identifier, agent_relation>;
    using valuation_function    = std::map<identifier, literal_list>;

    using object_type           = std::pair<identifier, type>;
    using agent_group_list      = std::list<agent_group>;
    using object_type_list      = std::list<object_type>;

    using finitary_s5_theory     = formula_list;
    using init_descr            = std::variant<finitary_s5_theory, epistemic_state>;

    using library_list          = std::list<library>;

//    using connective            = connective_value;
//    using quantifier             = quantifier_value;

    enum class obs_cond_type : uint8_t {
        simple,
        if_cond,
        otherwise
    };  // todo: vedi come usare token::observability

    enum class post_type : uint8_t {
        iff,
        when,
        literal
    };
}

#endif //EPDDL_AST_UTILS_H
