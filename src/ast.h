#ifndef EPDDL_AST_H
#define EPDDL_AST_H

#include <cstdlib>
#include <optional>
#include <string>
#include <set>
#include <list>
#include <utility>


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
class ActionTypeSignature;
class SimpleObsCondition;
class IfObsCondition;
class ForallObsCondition;
class Action;
class Domain;

class Postcondition;

using ident                 = std::unique_ptr<Ident>;
using ident_set             = std::set<ident>;
using variable              = std::unique_ptr<Variable>;
using formal_param          = std::pair<std::unique_ptr<Variable>, std::unique_ptr<Type>>;
using formal_param_list     = std::list<formal_param>;
using requirement_set       = std::set<std::unique_ptr<Requirement>>;
using type                  = std::unique_ptr<Type>;
using type_set              = std::set<type>;
using integer               = std::unique_ptr<Integer>;
using predicate_set         = std::set<std::unique_ptr<Predicate>>;
using modality              = std::unique_ptr<Modality>;
using modality_set          = std::set<std::unique_ptr<Modality>>;
using term                  = std::unique_ptr<Term>;
using term_list             = std::list<term>;
using formula               = std::unique_ptr<Formula>;
using formula_list          = std::list<std::unique_ptr<Formula>>;
using formula_arg           = std::variant<std::monostate, formula, formula_list>;
using postcondition         = std::unique_ptr<Postcondition>;
using expression            = std::variant<term, formula, postcondition>;
using assignment            = std::pair<variable, expression>;
using signature             = std::list<assignment>;
using act_type_signature    = std::unique_ptr<ActionTypeSignature>;
using observing_agent       = std::variant<ident, variable>;
using simple_obs_cond       = std::unique_ptr<SimpleObsCondition>;
using simple_obs_cond_list  = std::list<simple_obs_cond>;
using forall_obs_cond       = std::unique_ptr<ForallObsCondition>;
using obs_cond              = std::variant<simple_obs_cond, forall_obs_cond>;
using obs_cond_list         = std::list<obs_cond>;
using actual_param_list     = std::list<std::unique_ptr<ActualParameter>>;
using action_set            = std::set<std::unique_ptr<Action>>;

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


class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class Ident : public ASTNode {
public:
    explicit Ident(std::string ident) :
        m_ident{std::move(ident)} {}

    [[nodiscard]] const std::string& get_ident() const { return m_ident; }

private:
    const std::string m_ident;
};

class Variable : public Ident {
public:
    explicit Variable(std::string var) :
        Ident{std::move(var)} {}
};

class Integer : public ASTNode {
public:
    explicit Integer(unsigned long val) :
            m_val{val} {}

    [[nodiscard]] unsigned long get_val() const { return m_val; }

private:
    const unsigned long m_val;
};

class Type : public Ident {
public:
    explicit Type(std::string type, const std::optional<Type *> parent = std::nullopt) :
        Ident{std::move(type)},
        m_parent(parent) {}

private:
    const std::optional<Type*> m_parent;
};

class Modality : public Ident {
public:
    explicit Modality(std::string modality) :
            Ident{std::move(modality)} {}
};

class Requirement : public Ident {
public:
    explicit Requirement(std::string req) :
        Ident{std::move(req)} {}
};

class ValuedRequirement : public Requirement {
public:
    explicit ValuedRequirement(std::string req, integer val) :
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
    explicit ModalFormula(modality modality, ident_set agents, formula formula) :
        Formula{std::nullopt, std::move(formula)},
        m_agents{std::move(agents)},
        m_modality{std::move(modality)} {}

private:
    const modality m_modality;
    const ident_set m_agents;
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

class TrueFormula : public Predicate {
public:
    explicit TrueFormula() :
        Predicate{std::make_unique<Ident>(Ident{"true"})} {}
};

class FalseFormula : public Predicate {
public:
    explicit FalseFormula() :
        Predicate{std::make_unique<Ident>(Ident{"false"})} {}
};

class ActualParameter : ASTNode {
public:
    explicit ActualParameter(expression expr) :
        m_expr{std::move(expr)} {}

private:
    const expression m_expr;
};

class ActionTypeSignature : public ASTNode {
public:
    explicit ActionTypeSignature(ident name, std::optional<signature> signature = std::nullopt) :
        m_name{std::move(name)},
        m_signature{std::move(signature)} {}

private:
    const ident m_name;
    const std::optional<signature> m_signature;
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
    explicit Action(ident name, formal_param_list params, act_type_signature signature,
                    formula precondition, obs_cond_list obs_conditions) :
        m_name{std::move(name)},
        m_params{std::move(params)},
        m_signature{std::move(signature)},
        m_precondition{std::move(precondition)},
        m_obs_conditions{std::move(obs_conditions)} {}

private:
    const ident m_name;
    const formal_param_list m_params;
    const act_type_signature m_signature;
    const formula m_precondition;
    const obs_cond_list m_obs_conditions;
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

#endif //EPDDL_AST_H
