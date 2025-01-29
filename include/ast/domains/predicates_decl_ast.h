#ifndef EPDDL_PREDICATES_DECL_AST_H
#define EPDDL_PREDICATES_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/typed_elem_ast.h"
#include <memory>

namespace epddl::ast {
    class predicate_decl;
    class domain_predicates;

    using domain_predicates_ptr = std::unique_ptr<ast::domain_predicates>;
    using predicate_decl_ptr    = std::unique_ptr<ast::predicate_decl>;
    using predicate_decl_list   = std::list<predicate_decl_ptr>;


    class predicate_decl : public ast_node {
    public:
        explicit predicate_decl(identifier_ptr name, formal_param_list params) :
                m_name{std::move(name)},
                m_params{std::move(params)} {}

    private:
        const identifier_ptr m_name;
        const formal_param_list m_params;
    };

    class domain_predicates : public ast_node {
    public:
        explicit domain_predicates(predicate_decl_list preds) :
                m_preds{std::move(preds)} {}

    private:
        const predicate_decl_list m_preds;
    };
}

#endif //EPDDL_PREDICATES_DECL_AST_H
