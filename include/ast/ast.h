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

#include "../lexer/lexer.h"

#include "tokens/tokens_ast.h"
#include "common/formulas_ast.h"

//using namespace epddl::utils::ast_node;

namespace epddl::ast {



    /*class action_type;
    class event;
    class library;
    class agent_group;
    class epistemic_state;
    class init;
    class problem;
    class planning_task;*/


    /*using action_type_ptr           = std::unique_ptr<ast::action_type>;
    using event_ptr                 = std::unique_ptr<ast::event>;
    using library_ptr               = std::unique_ptr<ast::library>;
    using agent_group_ptr           = std::unique_ptr<ast::agent_group>;
    using epistemic_state_ptr       = std::unique_ptr<ast::epistemic_state>;
    using init_ptr                  = std::unique_ptr<ast::init>;
    using problem_ptr               = std::unique_ptr<ast::problem>;
    using planning_task_ptr         = std::unique_ptr<ast::planning_task>;*/






    /*
    using predicate_list        = std::list<predicate_ptr>;
    using literal_list          = std::list<literal_ptr>;



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

    using library_list          = std::list<library_ptr>;*/

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

//    enum class obs_cond_type : uint8_t {
//        simple,
//        if_cond,
//        otherwise
//    };  // todo: vedi come usare token::observability
//
//    enum class post_type : uint8_t {
//        iff,
//        when,
//        literal
//    };

//    class ast_node {
//    public:
//        explicit ast_node() :
//                m_parent{} {}
//
//        ast_node(const ast_node&) = delete;
//        ast_node(ast_node&&) = default;
//
//        ast_node& operator=(const ast_node&) = delete;
//        ast_node& operator=(ast_node&&) = delete;
//
//        virtual ~ast_node() = default;
//
//        void set_parent(ast_node_ptr parent) {
//            if (!m_parent) {
//                m_parent = std::move(parent);
//            }
//        }
//
//    private:
//        ast_node_ptr m_parent;
//    };

//    class precondition : public ast_node {
//    public:
//        explicit precondition(formula_ptr formula) :
//            m_formula(std::move(formula)) {}
//
//    private:
//        const formula_ptr m_formula;
//    };















/*
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
        explicit library(identifier_ptr name, requirement_list reqs, modality_index_list mods,
                         ident_list obs_groups, action_type_list act_types) :
                m_name{std::move(name)},
                m_reqs{std::move(reqs)},
                m_mods{std::move(mods)},
                m_obs_groups{std::move(obs_groups)},
                m_act_types{std::move(act_types)} {}

    private:
        const identifier_ptr m_name;
        const requirement_list m_reqs;
        const modality_index_list m_mods;
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
        explicit problem(identifier_ptr name, requirement_list reqs, modality_index_list mods, ident_list agents,
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
        const modality_index_list m_mods;
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
*/

}

#endif //EPDDL_AST_H
