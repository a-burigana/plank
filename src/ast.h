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


// Forward declarations
class ASTNode;
class Ident;
class Variable;
class Integer;
class Type;
class Modality;
class Requirement;
class ValuedRequirement;
class Term;
class Formula;
class QuantifiedFormula;
class ModalFormula;
class Predicate;
class EqFormula;
class TrueFormula;
class FalseFormula;
class ActualParameter;
class Signature;
class SimpleObsCondition;
class IfObsCondition;
class ForallObsCondition;
class Action;
class Domain;

class Literal;
class SimplePostcondition;
class ForallPostcondition;
class Event;
class ActionType;
class Library;

class AgentGroup;
class EpistemicState;
class Init;
class Problem;

class EPDDLPlanningTask;


using ident                 = std::unique_ptr<Ident>;
using variable              = std::unique_ptr<Variable>;
using type                  = std::unique_ptr<Type>;
using formal_param          = std::pair<variable, type>;
using integer               = std::unique_ptr<Integer>;
using ident_set             = std::set<ident>;
using requirement_set       = std::set<std::unique_ptr<Requirement>>;
using type_set              = std::set<type>;
using formal_param_list     = std::list<formal_param>;

using term                  = std::unique_ptr<Term>;
using predicate             = std::unique_ptr<Predicate>;
using literal               = std::unique_ptr<Literal>;
using modality              = std::unique_ptr<Modality>;
using modality_agent        = std::variant<ident, ident_set>;
using formula               = std::unique_ptr<Formula>;
using formula_list          = std::list<formula>;
using formula_arg           = std::variant<std::monostate, formula, formula_list>;
using term_list             = std::list<term>;
using predicate_set         = std::set<predicate>;
using literal_set           = std::set<literal>;
using modality_set          = std::set<modality>;

using simple_post           = std::unique_ptr<SimplePostcondition>;
using forall_post           = std::unique_ptr<ForallPostcondition>;
using postcondition         = std::variant<simple_post, forall_post>;
using simple_post_list      = std::list<simple_post>;
using postcondition_list    = std::list<postcondition>;

using expression            = std::variant<term, formula, postcondition, variable>;
using assignment            = std::pair<variable, expression>;
using assignment_list       = std::list<assignment>;

using observing_agent       = std::variant<ident, variable>;
using simple_obs_cond       = std::unique_ptr<SimpleObsCondition>;
using forall_obs_cond       = std::unique_ptr<ForallObsCondition>;
using obs_cond              = std::variant<simple_obs_cond, forall_obs_cond>;
using simple_obs_cond_list  = std::list<simple_obs_cond>;
using obs_cond_list         = std::list<obs_cond>;

using signature             = std::unique_ptr<Signature>;
using action                = std::unique_ptr<Action>;
using action_type           = std::unique_ptr<ActionType>;

using action_set            = std::set<action>;
using action_type_set       = std::set<action_type>;
using signature_list        = std::list<signature>;

using agent_relation        = std::optional<std::set<std::pair<ident, ident>>>;
using relations             = std::map<ident, agent_relation>;
using valuation_function    = std::map<ident, literal_set>;

using agent_group           = std::unique_ptr<AgentGroup>;
using object_type           = std::pair<ident, type>;
using agent_group_list      = std::list<agent_group>;
using object_type_list      = std::list<object_type>;

using finitary_s5_theory     = formula_list;
using epistemic_state       = std::unique_ptr<EpistemicState>;
using init_descr            = std::variant<finitary_s5_theory, epistemic_state>;

using domain                = std::unique_ptr<Domain>;
using library               = std::unique_ptr<Library>;
using library_set           = std::set<library>;
using problem               = std::unique_ptr<Problem>;


enum class connective : uint8_t {
    negation,
    conjunction,
    disjunction,
    implication
};

enum class quantifier : uint8_t {
    exists,
    forall
};

enum class obs_cond_type : uint8_t {
    simple,
    if_cond,
    otherwise
};

enum class post_type : uint8_t {
    iff,
    when,
    literal
};


class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class Ident : public ASTNode {
public:
    explicit Ident(token tok) :
        m_token{std::move(tok)} {}

    [[nodiscard]] const token& get_token() const { return m_token; }

private:
    const token m_token;
};

class Variable : public Ident {
public:
    explicit Variable(token var) :
        Ident{std::move(var)} {}
};

class Integer : public ASTNode {
public:
    explicit Integer(token val) :
        m_token{std::move(val)} {}

    [[nodiscard]] token get_val() const { return m_token; }

private:
    const token m_token;
};

class Type : public Ident {
public:
    explicit Type(token type, const std::optional<Type *> parent = std::nullopt) :
        Ident{std::move(type)},
        m_parent(parent) {}

private:
    const std::optional<Type*> m_parent;
};

class Modality : public Ident {
public:
    explicit Modality(token modality) :
        Ident{std::move(modality)} {}
};

class Requirement : public Ident {
public:
    explicit Requirement(token req) :
        Ident{std::move(req)} {}
};

class ValuedRequirement : public Requirement {
public:
    explicit ValuedRequirement(token req, integer val) :
        Requirement{std::move(req)},
        m_val{std::move(val)} {}

private:
    const integer m_val;
};

class Term : public ASTNode {
public:
    explicit Term(std::variant<ident, variable> term) :
            m_term{std::move(term)} {}

private:
    const std::variant<ident, variable> m_term;
};

class Formula : public ASTNode {
public:
    explicit Formula(std::optional<connective> connective = std::nullopt, formula_arg args = std::monostate()) :
        m_connective{connective},
        m_args{std::move(args)},
        m_var{std::nullopt} {}

    explicit Formula(variable var) :
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
    explicit QuantifiedFormula(quantifier quantifier, formal_param_list params, formula formula) :
        Formula{std::nullopt, std::move(formula)},
        m_quantifier{quantifier},
        m_params{std::move(params)} {}

private:
    const quantifier m_quantifier;
    const formal_param_list m_params;
};

class ModalFormula : Formula {
public:
    explicit ModalFormula(std::optional<modality> modality, modality_agent agent, formula formula) :
            Formula{std::nullopt, std::move(formula)},
            m_modality{std::move(modality)},
            m_agent{std::move(agent)} {}

private:
    const std::optional<modality> m_modality;
    const modality_agent m_agent;
};

class Predicate : public Formula {
public:
    explicit Predicate(ident ident, std::optional<term_list> args = std::nullopt) :
        Formula{},
        m_ident{std::move(ident)},
        m_args{std::move(args)} {}

private:
    const ident m_ident;
    const std::optional<term_list> m_args;
};

class EqFormula : public Formula {
public:
    explicit EqFormula(term t1, term t2) :
        Formula{},
        m_t1{std::move(t1)},
        m_t2{std::move(t2)} {}

private:
    const term m_t1, m_t2;
};

class ActualParameter : ASTNode {
public:
    explicit ActualParameter(expression expr) :
        m_expr{std::move(expr)} {}

private:
    const expression m_expr;
};

class Signature : public ASTNode {
public:
    explicit Signature(ident name, std::optional<assignment_list> assign_list = std::nullopt) :
            m_name{std::move(name)},
            m_assign_list{std::move(assign_list)} {}

private:
    const ident m_name;
    const std::optional<assignment_list> m_assign_list;
};

class SimpleObsCondition : public ASTNode {
public:
    explicit SimpleObsCondition(observing_agent agent, obs_cond_type type = obs_cond_type::simple) :
        m_agent{std::move(agent)},
        m_type{type} {}

private:
    const observing_agent m_agent;
    const obs_cond_type m_type;
};

class IfObsCondition : public SimpleObsCondition {
public:
    explicit IfObsCondition(observing_agent agent, formula cond) :
        SimpleObsCondition{std::move(agent), obs_cond_type::if_cond},
        m_cond{std::move(cond)} {}

private:
    const formula m_cond;
};

class ForallObsCondition : public ASTNode {
public:
    explicit ForallObsCondition(variable var, type type, simple_obs_cond_list obs_conditions) :
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
    explicit Action(ident name, std::optional<formal_param_list> params, signature signature,
                    formula precondition, std::optional<obs_cond_list> obs_conditions) :
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

class Domain : public ASTNode {
public:
    explicit Domain(ident name, ident_set libs, requirement_set reqs, type_set types,
                    predicate_set preds, modality_set mods, action_set acts) :
        m_name{std::move(name)},
        m_libs{std::move(libs)},
        m_reqs{std::move(reqs)},
        m_types{std::move(types)},
        m_preds{std::move(preds)},
        m_mods{std::move(mods)},
        m_acts{std::move(acts)} {}

private:
    const ident m_name;
    const ident_set m_libs;
    const requirement_set m_reqs;
    const type_set m_types;
    const predicate_set m_preds;
    const modality_set m_mods;
    const action_set m_acts;
};

class ActionType : public ASTNode {
public:
    explicit ActionType(ident name, std::optional<formal_param_list> params, std::optional<ident_set> obs_groups,
                        signature_list event_signatures, relations relations, ident_set designated) :
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
    explicit Literal(bool positive, predicate pred) :
        m_positive{positive},
        m_pred{std::move(pred)} {}

private:
    const bool m_positive;
    const predicate m_pred;
};

class SimplePostcondition : public ASTNode {
public:
    explicit SimplePostcondition(literal literal, std::optional<formula> cond = std::nullopt,
                                 post_type type = post_type::literal) :
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
    explicit ForallPostcondition(formal_param_list params, simple_post_list post) :
        m_params{std::move(params)},
        m_post{std::move(post)} {}

private:
    const formal_param_list m_params;
    const simple_post_list m_post;
};

class Event : public ASTNode {
public:
    explicit Event(ident name, std::optional<formal_param_list> params,
                   formula precondition, std::optional<postcondition_list> postconditions = std::nullopt) :
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
    explicit Library(ident name, requirement_set reqs, modality_set mods,
                     ident_set obs_groups, action_type_set act_types) :
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
    explicit AgentGroup(ident group_name, ident_set agents) :
        m_group_name{std::move(group_name)},
        m_agents{std::move(agents)} {}

private:
    const ident m_group_name;
    const ident_set m_agents;
};

class EpistemicState : public ASTNode {
public:
    explicit EpistemicState(ident name, ident_set worlds, relations relations,
                            valuation_function valuation, ident_set designated) :
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
    explicit Init(finitary_s5_theory theory) :
        m_init{std::move(theory)} {}

    explicit Init(epistemic_state state) :
        m_init{std::move(state)} {}

private:
    const init_descr m_init;
};

class Problem : public ASTNode {
public:
    explicit Problem(ident name, requirement_set reqs, modality_set mods, ident_set agents,
                     std::optional<agent_group_list> agent_groups, object_type_list objects,
                     predicate_set static_preds, init_descr init, formula goal) :
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

class EPDDLPlanningTask : public ASTNode {
public:
    explicit EPDDLPlanningTask(domain domain, library_set libraries, problem problem) :
        m_domain{std::move(domain)},
        m_libraries{std::move(libraries)},
        m_problem{std::move(problem)} {}

private:
    const domain m_domain;
    const library_set m_libraries;
    const problem m_problem;
};

#endif //EPDDL_AST_H
