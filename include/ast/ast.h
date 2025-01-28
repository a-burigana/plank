#ifndef EPDDL_AST_H
#define EPDDL_AST_H

#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <set>
#include <list>
#include <map>
#include <utility>

#include "ast_types.h"
#include "../lexer/lexer.h"

//using namespace epddl::utils::ast_node;

namespace epddl::ast {
    class ast_node;
    class identifier;
    class variable;
    class integer;
//    class modality;
    class requirement;
//    class term;
    class predicate;
    class predicate_formula;
    class eq_formula;
    class not_formula;
    class and_formula;
    class or_formula;
    class imply_formula;
    class box_formula;
    class diamond_formula;
    class forall_formula;
    class exists_formula;
    class parameters;
    class actual_parameter;
    class action_signature;
    class precondition;

    class always_obs_condition;
    class if_then_else_obs_condition;
    class if_obs_condition;
    class else_if_obs_condition;
    class else_obs_condition;
    class forall_obs_condition;
    class default_obs_condition;

    class action;
    class domain_libraries;
    class domain_requirements;
    class domain_types;
    class predicate_def;
    class domain_predicates;
    class domain_modalities;
    class domain;
    class action_type;
    class literal;

    class literal_postcondition;
    class iff_postcondition;
    class when_postcondition;
    class forall_postcondition;

    class event;
    class library;
    class agent_group;
    class epistemic_state;
    class init;
    class problem;
    class planning_task;

    using ast_node_ptr              = std::unique_ptr<ast::ast_node>;
    using identifier_ptr            = std::unique_ptr<ast::identifier>;
    using variable_ptr              = std::unique_ptr<ast::variable>;
    using integer_ptr               = std::unique_ptr<ast::integer>;
    using requirement_ptr           = std::unique_ptr<ast::requirement>;

    using single_modality_ptr       = std::variant<identifier_ptr, variable_ptr>;
    using group_modality_ptr        = std::list<single_modality_ptr>;
//    using modality                  = std::variant<single_modality_ptr, group_modality_ptr>;
    using modality_ptr              = std::variant<single_modality_ptr, group_modality_ptr>; // std::unique_ptr<modality>;

    using predicate_formula_ptr     = std::unique_ptr<predicate_formula>;
    using eq_formula_ptr            = std::unique_ptr<eq_formula>;
    using not_formula_ptr           = std::unique_ptr<not_formula>;
    using and_formula_ptr           = std::unique_ptr<and_formula>;
    using or_formula_ptr            = std::unique_ptr<or_formula>;
    using imply_formula_ptr         = std::unique_ptr<imply_formula>;
    using box_formula_ptr           = std::unique_ptr<box_formula>;
    using diamond_formula_ptr       = std::unique_ptr<diamond_formula>;
    using forall_formula_ptr        = std::unique_ptr<forall_formula>;
    using exists_formula_ptr        = std::unique_ptr<exists_formula>;
    using formula_ptr               = std::variant<predicate_formula_ptr, eq_formula_ptr, not_formula_ptr, and_formula_ptr, or_formula_ptr, imply_formula_ptr, box_formula_ptr, diamond_formula_ptr, forall_formula_ptr, exists_formula_ptr>;

//    using term_ptr                  = std::unique_ptr<ast::term>;
    using predicate_ptr             = std::unique_ptr<ast::predicate>;
    using eq_formula_ptr            = std::unique_ptr<ast::eq_formula>;
    using parameters_ptr            = std::unique_ptr<ast::parameters>;
    using actual_parameter_ptr      = std::unique_ptr<ast::actual_parameter>;
    using action_signature_ptr      = std::unique_ptr<ast::action_signature>;
    using precondition_ptr          = std::unique_ptr<ast::precondition>;

    using always_obs_cond_ptr       = std::unique_ptr<ast::always_obs_condition>;
    using if_then_else_obs_cond_ptr = std::unique_ptr<ast::if_then_else_obs_condition>;
    using if_obs_cond_ptr           = std::unique_ptr<ast::if_obs_condition>;
    using else_if_obs_cond_ptr      = std::unique_ptr<ast::else_if_obs_condition>;
    using else_obs_cond_ptr         = std::unique_ptr<ast::else_obs_condition>;
    using forall_obs_cond_ptr       = std::unique_ptr<ast::forall_obs_condition>;
    using default_obs_cond_ptr      = std::unique_ptr<ast::default_obs_condition>;

    using observing_agent           = std::variant<identifier_ptr, variable_ptr>;
    using simple_obs_cond           = std::variant<always_obs_cond_ptr, if_then_else_obs_cond_ptr>;
//    using simple_obs_cond_list      = std::list<simple_obs_cond>;
    using single_obs_cond           = std::variant<always_obs_cond_ptr, if_then_else_obs_cond_ptr, forall_obs_cond_ptr, default_obs_cond_ptr>;
    using else_if_obs_cond_list     = std::list<else_if_obs_cond_ptr>;
    using obs_cond_list             = std::list<single_obs_cond>;
//    using obs_cond_list_ptr         = std::unique_ptr<obs_cond_list>;
    using obs_cond                  = std::variant<single_obs_cond, obs_cond_list>;

    using action_ptr                = std::unique_ptr<ast::action>;
    using domain_libraries_ptr      = std::unique_ptr<ast::domain_libraries>;
    using domain_requirements_ptr   = std::unique_ptr<ast::domain_requirements>;
    using domain_types_ptr          = std::unique_ptr<ast::domain_types>;
    using predicate_def_ptr         = std::unique_ptr<ast::predicate_def>;
    using domain_predicates_ptr     = std::unique_ptr<ast::domain_predicates>;
    using domain_modalities_ptr     = std::unique_ptr<ast::domain_modalities>;
    using domain_ptr                = std::unique_ptr<ast::domain>;
    using action_type_ptr           = std::unique_ptr<ast::action_type>;
    using literal_ptr               = std::unique_ptr<ast::literal>;
    using event_ptr                 = std::unique_ptr<ast::event>;
    using library_ptr               = std::unique_ptr<ast::library>;
    using agent_group_ptr           = std::unique_ptr<ast::agent_group>;
    using epistemic_state_ptr       = std::unique_ptr<ast::epistemic_state>;
    using init_ptr                  = std::unique_ptr<ast::init>;
    using problem_ptr               = std::unique_ptr<ast::problem>;
    using planning_task_ptr         = std::unique_ptr<ast::planning_task>;

    using domain_item           = std::variant<domain_libraries_ptr, domain_requirements_ptr, domain_types_ptr,
            domain_predicates_ptr, domain_modalities_ptr, action_ptr>;
    using domain_item_list      = std::list<domain_item>;

    template<typename token_type>
    class typed_elem;
    template<typename token_type>
    using typed_elem_ptr        = std::unique_ptr<ast::typed_elem<token_type>>;
    template<typename token_type>
    using typed_elem_list       = std::list<typed_elem_ptr<token_type>>;

    using typed_identifier_ptr  = typed_elem_ptr<identifier>;
    using typed_variable_ptr    = typed_elem_ptr<variable>;
    using typed_identifier_list = std::list<typed_identifier_ptr>;
    using typed_variable_list   = std::list<typed_variable_ptr>;

    using formal_param          = typed_variable_ptr;           // std::pair<variable_ptr, std::optional<identifier_ptr>>;
    using ident_list            = std::list<identifier_ptr>;
    using requirement_list      = std::list<requirement_ptr>;
    using formal_param_list     = std::list<formal_param>;

    using modality_agent        = std::variant<identifier_ptr, ident_list>;
    using formula_list          = std::list<formula_ptr>;
    using formula_arg           = std::variant<std::monostate, predicate_ptr, variable_ptr, formula_ptr, formula_list>;
    using term                  = std::variant<identifier_ptr, variable_ptr>;
    using term_list             = std::list<term>;
    using predicate_def_list    = std::list<predicate_def_ptr>;
    using predicate_list        = std::list<predicate_ptr>;
    using literal_list          = std::list<literal_ptr>;
    using modality_list         = std::list<modality_ptr>;

    using literal_postcondition_ptr = std::unique_ptr<literal_postcondition>;
    using iff_postcondition_ptr     = std::unique_ptr<iff_postcondition>;
    using when_postcondition_ptr    = std::unique_ptr<when_postcondition>;
    using forall_postcondition_ptr  = std::unique_ptr<ast::forall_postcondition>;

    using simple_postcondition      = std::variant<literal_postcondition_ptr, iff_postcondition_ptr, when_postcondition_ptr>;
    using simple_postcondition_list = std::list<simple_postcondition>;

    using single_postcondition      = std::variant<literal_postcondition_ptr, iff_postcondition_ptr, when_postcondition_ptr, forall_postcondition_ptr>;
    using postcondition_list        = std::list<single_postcondition>;
    using postcondition_list_ptr    = std::unique_ptr<postcondition_list>;
    using postconditions            = std::variant<single_postcondition, postcondition_list_ptr>;

    using expression            = std::variant<identifier_ptr, variable_ptr, predicate_ptr, literal_ptr, formula_ptr, postconditions>;
//    using assignment            = std::pair<variable_ptr, expression>;
    using expression_list       = std::list<expression>;

    using action_list           = std::list<action_ptr>;
    using action_type_list      = std::list<action_type_ptr>;
    using signature_list        = std::list<action_signature_ptr>;

    using agent_relation        = std::optional<std::list<std::pair<identifier_ptr, identifier_ptr>>>;
    using relations             = std::map<identifier_ptr, agent_relation>;
    using valuation_function    = std::map<identifier_ptr, literal_list>;

//    using object_type           = std::pair<identifier_ptr, identifier_ptr>;
    using agent_group_list      = std::list<agent_group_ptr>;
//    using object_type_list      = std::list<object_type>;

    using finitary_s5_theory    = formula_list;
    using init_descr            = std::variant<finitary_s5_theory, epistemic_state_ptr>;

    using library_list          = std::list<library_ptr>;

//    enum class connective : uint8_t {
//        negation,
//        conjunction,
//        disjunction,
//        implication
//    };
//
//    enum class quantifier : uint8_t {
//        universal,
//        existential
//    };

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

    class ast_node {
    public:
        explicit ast_node() :
                m_parent{} {}

        ast_node(const ast_node&) = delete;
        ast_node(ast_node&&) = default;

        ast_node& operator=(const ast_node&) = delete;
        ast_node& operator=(ast_node&&) = delete;

        virtual ~ast_node() = default;

        void set_parent(ast_node_ptr parent) {
            if (!m_parent) {
                m_parent = std::move(parent);
            }
        }

    private:
        ast_node_ptr m_parent;
    };

    class identifier : public ast_node {
    public:
        using token_type = pattern_token::identifier;

        explicit identifier(token_ptr tok) :
                m_token{std::move(tok)} {}

        [[nodiscard]] const token& get_token() const { return *m_token; }

    private:
        const token_ptr m_token;
    };

    class variable : public identifier {
    public:
        using token_type = pattern_token::variable;

        explicit variable(token_ptr var) :
                identifier{std::move(var)} {}
    };

    class integer : public ast_node {
    public:
        using token_type = pattern_token::integer;

        explicit integer(token_ptr val) :
                m_token{std::move(val)} {}

        [[nodiscard]] std::string get_val() const { return m_token->get_lexeme(); }

    private:
        const token_ptr m_token;
    };

    template<typename token_type>
    class typed_elem : public ast_node {
    public:
        explicit typed_elem(identifier_ptr id, std::optional<identifier_ptr> type = std::nullopt) :
                m_id{std::move(id)},
                m_type{std::move(type)} {}

    private:
        const identifier_ptr m_id;
        const std::optional<identifier_ptr> m_type;
    };

//    class modality : public identifier {
//    public:
//        explicit modality(token_ptr modality) :
//                identifier{std::move(modality)} {}
//    };

    class requirement : public ast_node {
    public:
        using token_type = pattern_token::requirement;

        explicit requirement(token_ptr req, std::optional<integer_ptr> val = std::nullopt) :
                m_req{std::move(req)},
                m_val{std::move(val)} {}

    private:
        const token_ptr m_req;
        const std::optional<integer_ptr> m_val;
    };

    class predicate : public ast_node {
    public:
        explicit predicate(identifier_ptr name, term_list args) :
                m_name{std::move(name)},
                m_args{std::move(args)} {}

    private:
        const identifier_ptr m_name;
        const term_list m_args;
    };

    class predicate_formula : public ast_node {
    public:
        explicit predicate_formula(predicate_ptr predicate) :
            m_predicate{std::move(predicate)} {}

    private:
        const predicate_ptr m_predicate;
    };

    class eq_formula : public ast_node {
    public:
        explicit eq_formula(term t1, term t2) :
                m_t1{std::move(t1)},
                m_t2{std::move(t2)} {}

    private:
        const term m_t1, m_t2;
    };

    class not_formula : public ast_node {
    public:
        explicit not_formula(formula_ptr f) :
                m_f{std::move(f)} {}

    private:
        const formula_ptr m_f;
    };

    class and_formula : public ast_node {
    public:
        explicit and_formula(formula_list fs) :
                m_fs{std::move(fs)} {}

    private:
        const formula_list m_fs;
    };

    class or_formula : public ast_node {
    public:
        explicit or_formula(formula_list fs) :
                m_fs{std::move(fs)} {}

    private:
        const formula_list m_fs;
    };

    class imply_formula : public ast_node {
    public:
        explicit imply_formula(formula_ptr f1, formula_ptr f2) :
                m_f1{std::move(f1)},
                m_f2{std::move(f2)}{}

    private:
        const formula_ptr m_f1, m_f2;
    };

    class box_formula : public ast_node {
    public:
        explicit box_formula(modality_ptr mod, formula_ptr f) :
            m_mod{std::move(mod)},
            m_f{std::move(f)} {}

    private:
        const modality_ptr m_mod;
        const formula_ptr m_f;
    };

    class diamond_formula : public ast_node {
    public:
        explicit diamond_formula(modality_ptr mod, formula_ptr f) :
                m_mod{std::move(mod)},
                m_f{std::move(f)} {}

    private:
        const modality_ptr m_mod;
        const formula_ptr m_f;
    };

    class forall_formula : public ast_node {
    public:
        explicit forall_formula(formal_param_list params, formula_ptr f) :
                m_params{std::move(params)},
                m_f{std::move(f)} {}

    private:
        const formal_param_list m_params;
        const formula_ptr m_f;
    };

    class exists_formula : public ast_node {
    public:
        explicit exists_formula(formal_param_list params, formula_ptr f) :
                m_params{std::move(params)},
                m_f{std::move(f)} {}

    private:
        const formal_param_list m_params;
        const formula_ptr m_f;
    };

    class parameters : public ast_node {
    public:
        explicit parameters(formal_param_list params) :
        m_params{std::move(params)} {}

    private:
        const formal_param_list m_params;
    };

    class actual_parameter : public ast_node {
    public:
        explicit actual_parameter(expression expr) :
                m_expr{std::move(expr)} {}

    private:
        const expression m_expr;
    };

    class action_signature : public ast_node {
    public:
        explicit action_signature(identifier_ptr name, expression_list assign_list) :
                m_name{std::move(name)},
                m_assign_list{std::move(assign_list)} {}

    private:
        const identifier_ptr m_name;
        const expression_list m_assign_list;
    };

//    class precondition : public ast_node {
//    public:
//        explicit precondition(formula_ptr formula) :
//            m_formula(std::move(formula)) {}
//
//    private:
//        const formula_ptr m_formula;
//    };

    class always_obs_condition : public ast_node {
    public:
        explicit always_obs_condition(observing_agent agent, identifier_ptr obs_group) :
                m_agent{std::move(agent)},
                m_obs_group{std::move(obs_group)} {}

    private:
        const observing_agent m_agent;
        const identifier_ptr m_obs_group;
    };

    class if_then_else_obs_condition : public ast_node {
    public:
        explicit if_then_else_obs_condition(if_obs_cond_ptr if_cond, else_if_obs_cond_list else_if_conds, std::optional<else_obs_cond_ptr> else_cond) :
                m_if_cond{std::move(if_cond)},
                m_else_if_conds{std::move(else_if_conds)},
                m_else_cond{std::move(else_cond)} {}

    private:
        const if_obs_cond_ptr m_if_cond;
        const else_if_obs_cond_list m_else_if_conds;
        const std::optional<else_obs_cond_ptr> m_else_cond;
    };

    class if_obs_condition : public ast_node {
    public:
        explicit if_obs_condition(formula_ptr cond, observing_agent agent, identifier_ptr obs_group) :
                m_cond{std::move(cond)},
                m_agent{std::move(agent)},
                m_obs_group{std::move(obs_group)} {}

    private:
        const observing_agent m_agent;
        const identifier_ptr m_obs_group;
        const formula_ptr m_cond;
    };

    class else_if_obs_condition : if_obs_condition {
    public:
        explicit else_if_obs_condition(formula_ptr cond, observing_agent agent, identifier_ptr obs_group) :
            if_obs_condition(std::move(cond), std::move(agent), std::move(obs_group)) {}
    };

    class else_obs_condition : public ast_node {
    public:
        explicit else_obs_condition(observing_agent agent, identifier_ptr obs_group) :
                m_agent{std::move(agent)},
                m_obs_group{std::move(obs_group)} {}

    private:
        const observing_agent m_agent;
        const identifier_ptr m_obs_group;
    };

    class forall_obs_condition : public ast_node {
    public:
        explicit forall_obs_condition(formal_param_list params, simple_obs_cond obs_condition) :
                m_params{std::move(params)},
                m_obs_condition{std::move(obs_condition)} {}

    private:
        const formal_param_list m_params;
        const simple_obs_cond m_obs_condition;
    };

    class default_obs_condition : public ast_node {
    public:
        explicit default_obs_condition(identifier_ptr obs_group) :
                m_obs_group{std::move(obs_group)} {}

    private:
        const identifier_ptr m_obs_group;
    };

    class action : public ast_node {
    public:
        explicit action(identifier_ptr name, parameters_ptr params, action_signature_ptr signature,
                        formula_ptr precondition, std::optional<obs_cond> obs_conditions) :
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_signature{std::move(signature)},
                m_precondition{std::move(precondition)},
                m_obs_conditions{std::move(obs_conditions)} {}

    private:
        const identifier_ptr m_name;
        const parameters_ptr m_params;
        const action_signature_ptr m_signature;
        const formula_ptr m_precondition;
        const std::optional<obs_cond> m_obs_conditions;
    };

    class domain_libraries : public ast_node {
    public:
        explicit domain_libraries(ident_list libs) :
                m_libs{std::move(libs)} {}

    private:
        const ident_list m_libs;
    };

    class domain_requirements : public ast_node {
    public:
        explicit domain_requirements(requirement_list reqs) :
                m_reqs{std::move(reqs)} {}

    private:
        const requirement_list m_reqs;
    };

    class domain_types : public ast_node {
    public:
        explicit domain_types(typed_identifier_list types) :
                m_types{std::move(types)} {}

    private:
        const typed_identifier_list m_types;
    };

    class predicate_def : public ast_node {
    public:
        explicit predicate_def(identifier_ptr name, formal_param_list params) :
            m_name{std::move(name)},
            m_params{std::move(params)} {}

    private:
        const identifier_ptr m_name;
        const formal_param_list m_params;
    };

    class domain_predicates : public ast_node {
    public:
        explicit domain_predicates(predicate_def_list preds) :
                m_preds{std::move(preds)} {}

    private:
        const predicate_def_list m_preds;
    };

    class domain_modalities : public ast_node {
    public:
        explicit domain_modalities(modality_list mods) :
                m_mods{std::move(mods)} {}

    private:
        const modality_list m_mods;
    };

    class domain : public ast_node {
    public:
        explicit domain(identifier_ptr name, domain_item_list items) :
                m_name{std::move(name)},
                m_items{std::move(items)} {}

    private:
        const identifier_ptr m_name;
        const domain_item_list m_items;
    };

    class action_type : public ast_node {
    public:
        explicit action_type(identifier_ptr name, parameters_ptr params,
                            std::optional<ident_list> obs_groups, signature_list event_signatures,
                            relations relations, ident_list designated) :
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_obs_groups{std::move(obs_groups)},
                m_event_signatures{std::move(event_signatures)},
                m_relations{std::move(relations)},
                m_designated{std::move(designated)} {}

    private:
        const identifier_ptr m_name;
        const parameters_ptr m_params;
        const std::optional<ident_list> m_obs_groups;
        const signature_list m_event_signatures;
        const relations m_relations;
        const ident_list m_designated;
    };

    class literal : public ast_node {
    public:
        explicit literal(bool positive, predicate_ptr pred) :
                m_positive{positive},
                m_pred{std::move(pred)} {}

    private:
        const bool m_positive;
        const predicate_ptr m_pred;
    };

    class literal_postcondition : public ast_node {
    public:
        explicit literal_postcondition(literal_ptr literal) :
                m_literal{std::move(literal)} {}

    private:
        const literal_ptr m_literal;
    };

    class iff_postcondition : public ast_node {
    public:
        explicit iff_postcondition(formula_ptr cond, literal_ptr literal) :
                m_cond{std::move(cond)},
                m_literal{std::move(literal)} {}

    private:
        const formula_ptr m_cond;
        const literal_ptr m_literal;
    };

    class when_postcondition : public ast_node {
    public:
        explicit when_postcondition(formula_ptr cond, literal_ptr literal) :
                m_cond{std::move(cond)},
                m_literal{std::move(literal)} {}

    private:
        const formula_ptr m_cond;
        const literal_ptr m_literal;
    };

    class forall_postcondition : public ast_node {
    public:
        explicit forall_postcondition(formal_param_list params, simple_postcondition_list post) :
                m_params{std::move(params)},
                m_post{std::move(post)} {}

    private:
        const formal_param_list m_params;
        const simple_postcondition_list m_post;
    };

    class event : public ast_node {
    public:
        explicit event(identifier_ptr name, parameters_ptr params,
                       formula_ptr precondition, std::optional<postcondition_list> postconditions = std::nullopt) :
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_precondition{std::move(precondition)},
                m_postconditions{std::move(postconditions)} {}

    private:
        const identifier_ptr m_name;
        const parameters_ptr m_params;
        const formula_ptr m_precondition;
        const std::optional<postcondition_list> m_postconditions;
    };

    class library : public ast_node {
    public:
        explicit library(identifier_ptr name, requirement_list reqs, modality_list mods,
                         ident_list obs_groups, action_type_list act_types) :
                m_name{std::move(name)},
                m_reqs{std::move(reqs)},
                m_mods{std::move(mods)},
                m_obs_groups{std::move(obs_groups)},
                m_act_types{std::move(act_types)} {}

    private:
        const identifier_ptr m_name;
        const requirement_list m_reqs;
        const modality_list m_mods;
        const ident_list m_obs_groups;
        const action_type_list m_act_types;
    };

    class agent_group : public ast_node {
    public:
        explicit agent_group(identifier_ptr group_name, ident_list agents) :
                m_group_name{std::move(group_name)},
                m_agents{std::move(agents)} {}

    private:
        const identifier_ptr m_group_name;
        const ident_list m_agents;
    };

    class epistemic_state : public ast_node {
    public:
        explicit epistemic_state(identifier_ptr name, ident_list worlds, relations relations,
                                valuation_function valuation, ident_list designated) :
                m_name{std::move(name)},
                m_worlds{std::move(worlds)},
                m_relations{std::move(relations)},
                m_valuation{std::move(valuation)},
                m_designated{std::move(designated)} {}

    private:
        const identifier_ptr m_name;
        const ident_list m_worlds, m_designated;
        const relations m_relations;
        const valuation_function m_valuation;
    };

    class init : public ast_node {
    public:
        explicit init(finitary_s5_theory theory) :
                m_init{std::move(theory)} {}

        explicit init(epistemic_state_ptr state) :
                m_init{std::move(state)} {}

    private:
        const init_descr m_init;
    };

    class problem : public ast_node {
    public:
        explicit problem(identifier_ptr name, requirement_list reqs, modality_list mods, ident_list agents,
                         std::optional<agent_group_list> agent_groups, typed_identifier_list objects,
                         predicate_list static_preds, init_descr init, formula_ptr goal) :
                m_name{std::move(name)},
                m_reqs{std::move(reqs)},
                m_mods{std::move(mods)},
                m_agents{std::move(agents)},
                m_agent_groups{std::move(agent_groups)},
                m_objects{std::move(objects)},
                m_static_preds{std::move(static_preds)},
                m_init{std::move(init)},
                m_goal{std::move(goal)} {}

    private:
        const identifier_ptr m_name;
        const requirement_list m_reqs;
        const modality_list m_mods;
        const ident_list m_agents;
        const std::optional<agent_group_list> m_agent_groups;
        const typed_identifier_list m_objects;
        const predicate_list m_static_preds;
        const init_descr m_init;
        const formula_ptr m_goal;
    };

    class planning_task : public ast_node {
    public:
        explicit planning_task(domain_ptr domain, library_list libraries, problem_ptr problem) :
                m_domain{std::move(domain)},
                m_libraries{std::move(libraries)},
                m_problem{std::move(problem)} {}

    private:
        const domain_ptr m_domain;
        const library_list m_libraries;
        const problem_ptr m_problem;
    };

}

#endif //EPDDL_AST_H
