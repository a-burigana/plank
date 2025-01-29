#ifndef EPDDL_ACTION_DECL_AST_H
#define EPDDL_ACTION_DECL_AST_H

#include "../../ast_node.h"
#include "../../tokens/tokens_ast.h"
#include "../../common/formulas_ast.h"
#include "../../common/parameters_ast.h"
#include "action_signatures_ast.h"
#include "obs_conditions_ast.h"

namespace epddl::ast {
    class action;
    using action_ptr = std::unique_ptr<ast::action>;

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
}

#endif //EPDDL_ACTION_DECL_AST_H
