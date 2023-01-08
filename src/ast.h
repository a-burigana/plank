#ifndef EPDDL_AST_H
#define EPDDL_AST_H

#include <cstdlib>
#include <optional>
#include <string>
#include <set>
#include <list>
#include <map>
#include <utility>

#include "lex.h"
#include "../include/ast_utils.h"

using namespace epddl::utils::ast_node;

namespace epddl::ast {
    class ASTNode {
    public:
        explicit ASTNode(scope scope) :
                m_scope{scope},
                m_parent{nullptr} {}

        ASTNode(const ASTNode&) = delete;
        virtual ~ASTNode() = default;

        ASTNode& operator=(ASTNode const&) = delete;

        void set_parent(ast_node* parent) {
            if (!m_parent) {
                m_parent = parent;
            }
        }

    private:
        const scope m_scope;
        ast_node* m_parent;
    };

    class Ident : public ASTNode {
    public:
        explicit Ident(scope scope, token tok) :
                ASTNode{scope},
                m_token{std::move(tok)} {}

        [[nodiscard]] const token &get_token() const { return m_token; }

    private:
        const token m_token;
    };

    class Variable : public Ident {
    public:
        explicit Variable(scope scope, token var) :
                Ident{scope, std::move(var)} {}
    };

    class Integer : public ASTNode {
    public:
        explicit Integer(scope scope, token val) :
                ASTNode{scope},
                m_token{std::move(val)} {}

        [[nodiscard]] std::string get_val() const { return m_token->get_string(); }

    private:
        const token m_token;
    };

    class Type : public Ident {
    public:
        explicit Type(scope scope, token type) :     // , const std::optional<Type *> parent = std::nullopt
                Ident{scope, std::move(type)} {}
//                m_parent(parent) {}

//    private:
//        const std::optional<Type *> m_parent;
    };

    class Modality : public Ident {
    public:
        explicit Modality(scope scope, token modality) :
                Ident{scope, std::move(modality)} {}
    };

    class Requirement : public Ident {
    public:
        explicit Requirement(scope scope, token req) :
                Ident{scope, std::move(req)} {}
    };

    class ValuedRequirement : public Requirement {
    public:
        explicit ValuedRequirement(scope scope, token req, integer val) :
                Requirement{scope, std::move(req)},
                m_val{std::move(val)} {}

    private:
        const integer m_val;
    };

    class Formula : public ASTNode {
    public:
        explicit Formula(scope scope, std::optional<connective> connective = std::nullopt,
                         formula_arg args = std::monostate()) :
                ASTNode{scope},
                m_connective{connective},
                m_args{std::move(args)},
                m_var{std::nullopt} {}

        explicit Formula(scope scope, variable var) :
                ASTNode{scope},
                m_connective{std::nullopt},
                m_args{std::monostate()},
                m_var{std::move(var)} {}

    private:
        const std::optional<connective> m_connective;
        const formula_arg m_args;
        const std::optional<variable> m_var;
    };

    class QuantifiedFormula : Formula {
    public:
        explicit QuantifiedFormula(scope scope, quantifier quantifier, formal_param_list params, formula formula) :
                Formula{scope, std::nullopt, std::move(formula)},
                m_quantifier{quantifier},
                m_params{std::move(params)} {}

    private:
        const quantifier m_quantifier;
        const formal_param_list m_params;
    };

    class ModalFormula : Formula {
    public:
        explicit ModalFormula(scope scope, std::optional<modality> modality, modality_agent agent, formula formula) :
                Formula{scope, std::nullopt, std::move(formula)},
                m_modality{std::move(modality)},
                m_agent{std::move(agent)} {}

    private:
        const std::optional<modality> m_modality;
        const modality_agent m_agent;
    };

    class Term : public ASTNode {
    public:
        explicit Term(scope scope, std::variant<ident, variable> term) :
                ASTNode{scope},
                m_term{std::move(term)} {}

    private:
        const std::variant<ident, variable> m_term;
    };

    class Predicate : public Formula {
    public:
        explicit Predicate(scope scope, ident ident, std::optional<term_list> args = std::nullopt) :
                Formula{scope},
                m_ident{std::move(ident)},
                m_args{std::move(args)} {}

    private:
        const ident m_ident;
        const std::optional<term_list> m_args;
    };

    class EqFormula : public Formula {
    public:
        explicit EqFormula(scope scope, term t1, term t2) :
                Formula{scope},
                m_t1{std::move(t1)},
                m_t2{std::move(t2)} {}

    private:
        const term m_t1, m_t2;
    };

    class ActualParameter : ASTNode {
    public:
        explicit ActualParameter(scope scope, expression expr) :
                ASTNode{scope},
                m_expr{std::move(expr)} {}

    private:
        const expression m_expr;
    };

    class Signature : public ASTNode {
    public:
        explicit Signature(scope scope, ident name, std::optional<assignment_list> assign_list = std::nullopt) :
                ASTNode{scope},
                m_name{std::move(name)},
                m_assign_list{std::move(assign_list)} {}

    private:
        const ident m_name;
        const std::optional<assignment_list> m_assign_list;
    };

    class SimpleObsCondition : public ASTNode {
    public:
        explicit SimpleObsCondition(scope scope, observing_agent agent, obs_cond_type type = obs_cond_type::simple) :
                ASTNode{scope},
                m_agent{std::move(agent)},
                m_type{type} {}

    private:
        const observing_agent m_agent;
        const obs_cond_type m_type;
    };

    class IfObsCondition : public SimpleObsCondition {
    public:
        explicit IfObsCondition(scope scope, observing_agent agent, formula cond) :
                SimpleObsCondition{scope, std::move(agent), obs_cond_type::if_cond},
                m_cond{std::move(cond)} {}

    private:
        const formula m_cond;
    };

    class ForallObsCondition : public ASTNode {
    public:
        explicit ForallObsCondition(scope scope, variable var, type type, simple_obs_cond_list obs_conditions) :
                ASTNode{scope},
                m_var{std::move(var)},
                m_type{std::move(type)},
                m_obs_conditions{std::move(obs_conditions)} {}

    private:
        const variable m_var;
        const type m_type;
        const simple_obs_cond_list m_obs_conditions;
    };

    class Action : public ASTNode {
    public:
        explicit Action(scope scope, ident name, std::optional<formal_param_list> params, signature signature,
                        formula precondition, std::optional<obs_cond_list> obs_conditions) :
                ASTNode{scope},
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_signature{std::move(signature)},
                m_precondition{std::move(precondition)},
                m_obs_conditions{std::move(obs_conditions)} {}

    private:
        const ident m_name;
        const std::optional<formal_param_list> m_params;
        const signature m_signature;
        const formula m_precondition;
        const std::optional<obs_cond_list> m_obs_conditions;
    };

    class DomainLibraries : public ASTNode {
    public:
        explicit DomainLibraries(scope scope, ident_set libs) :
                ASTNode{scope},
                m_libs{std::move(libs)} {}

    private:
        const ident_set m_libs;
    };

    class DomainRequirements : public ASTNode {
    public:
        explicit DomainRequirements(scope scope, requirement_set reqs) :
                ASTNode{scope},
                m_reqs{std::move(reqs)} {}

    private:
        const requirement_set m_reqs;
    };

    class DomainTypes : public ASTNode {
    public:
        explicit DomainTypes(scope scope, type_set types) :
                ASTNode{scope},
                m_types{std::move(types)} {}

    private:
        const type_set m_types;
    };

    class DomainPredicates : public ASTNode {
    public:
        explicit DomainPredicates(scope scope, predicate_set preds) :
                ASTNode{scope},
                m_preds{std::move(preds)} {}

    private:
        const predicate_set m_preds;
    };

    class DomainModalities : public ASTNode {
    public:
        explicit DomainModalities(scope scope, modality_set mods) :
                ASTNode{scope},
                m_mods{std::move(mods)} {}

    private:
        const modality_set m_mods;
    };

    class Domain : public ASTNode {
    public:
        explicit Domain(scope scope, ident name, domain_item_set items) :
                ASTNode{scope},
                m_name{std::move(name)},
                m_items{std::move(items)} {}

    private:
        const ident m_name;
        const domain_item_set m_items;
    };

    class ActionType : public ASTNode {
    public:
        explicit ActionType(scope scope, ident name, std::optional<formal_param_list> params,
                            std::optional<ident_set> obs_groups, signature_list event_signatures,
                            relations relations, ident_set designated) :
                ASTNode{scope},
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_obs_groups{std::move(obs_groups)},
                m_event_signatures{std::move(event_signatures)},
                m_relations{std::move(relations)},
                m_designated{std::move(designated)} {}

    private:
        const ident m_name;
        const std::optional<formal_param_list> m_params;
        const std::optional<ident_set> m_obs_groups;
        const signature_list m_event_signatures;
        const relations m_relations;
        const ident_set m_designated;
    };

    class Literal : public ASTNode {
    public:
        explicit Literal(scope scope, bool positive, predicate pred) :
                ASTNode{scope},
                m_positive{positive},
                m_pred{std::move(pred)} {}

    private:
        const bool m_positive;
        const predicate m_pred;
    };

    class SimplePostcondition : public ASTNode {
    public:
        explicit SimplePostcondition(scope scope, literal literal, std::optional<formula> cond = std::nullopt,
                                     post_type type = post_type::literal) :
                ASTNode{scope},
                m_literal{std::move(literal)},
                m_cond{std::move(cond)},
                m_type{type} {}

    private:
        const literal m_literal;
        const std::optional<formula> m_cond;
        const post_type m_type;
    };

    class ForallPostcondition : public ASTNode {
    public:
        explicit ForallPostcondition(scope scope, formal_param_list params, simple_post_list post) :
                ASTNode{scope},
                m_params{std::move(params)},
                m_post{std::move(post)} {}

    private:
        const formal_param_list m_params;
        const simple_post_list m_post;
    };

    class Event : public ASTNode {
    public:
        explicit Event(scope scope, ident name, std::optional<formal_param_list> params,
                       formula precondition, std::optional<postcondition_list> postconditions = std::nullopt) :
                ASTNode{scope},
                m_name{std::move(name)},
                m_params{std::move(params)},
                m_precondition{std::move(precondition)},
                m_postconditions{std::move(postconditions)} {}

    private:
        const ident m_name;
        const std::optional<formal_param_list> m_params;
        const formula m_precondition;
        const std::optional<postcondition_list> m_postconditions;
    };

    class Library : public ASTNode {
    public:
        explicit Library(scope scope, ident name, requirement_set reqs, modality_set mods,
                         ident_set obs_groups, action_type_set act_types) :
                ASTNode{scope},
                m_name{std::move(name)},
                m_reqs{std::move(reqs)},
                m_mods{std::move(mods)},
                m_obs_groups{std::move(obs_groups)},
                m_act_types{std::move(act_types)} {}

    private:
        const ident m_name;
        const requirement_set m_reqs;
        const modality_set m_mods;
        const ident_set m_obs_groups;
        const action_type_set m_act_types;
    };

    class AgentGroup : public ASTNode {
    public:
        explicit AgentGroup(scope scope, ident group_name, ident_set agents) :
                ASTNode{scope},
                m_group_name{std::move(group_name)},
                m_agents{std::move(agents)} {}

    private:
        const ident m_group_name;
        const ident_set m_agents;
    };

    class EpistemicState : public ASTNode {
    public:
        explicit EpistemicState(scope scope, ident name, ident_set worlds, relations relations,
                                valuation_function valuation, ident_set designated) :
                ASTNode{scope},
                m_name{std::move(name)},
                m_worlds{std::move(worlds)},
                m_relations{std::move(relations)},
                m_valuation{std::move(valuation)},
                m_designated{std::move(designated)} {}

    private:
        const ident m_name;
        const ident_set m_worlds, m_designated;
        const relations m_relations;
        const valuation_function m_valuation;
    };

    class Init : public ASTNode {
    public:
        explicit Init(scope scope, finitary_s5_theory theory) :
                ASTNode{scope},
                m_init{std::move(theory)} {}

        explicit Init(scope scope, epistemic_state state) :
                ASTNode{scope},
                m_init{std::move(state)} {}

    private:
        const init_descr m_init;
    };

    class Problem : public ASTNode {
    public:
        explicit Problem(scope scope, ident name, requirement_set reqs, modality_set mods, ident_set agents,
                         std::optional<agent_group_list> agent_groups, object_type_list objects,
                         predicate_set static_preds, init_descr init, formula goal) :
                ASTNode{scope},
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
        const ident m_name;
        const requirement_set m_reqs;
        const modality_set m_mods;
        const ident_set m_agents;
        const std::optional<agent_group_list> m_agent_groups;
        const object_type_list m_objects;
        const predicate_set m_static_preds;
        const init_descr m_init;
        const formula m_goal;
    };

    class PlanningTask : public ASTNode {
    public:
        explicit PlanningTask(scope scope, domain domain, library_set libraries, problem problem) :
                ASTNode{scope},
                m_domain{std::move(domain)},
                m_libraries{std::move(libraries)},
                m_problem{std::move(problem)} {}

    private:
        const domain m_domain;
        const library_set m_libraries;
        const problem m_problem;
    };

}

#endif //EPDDL_AST_H
