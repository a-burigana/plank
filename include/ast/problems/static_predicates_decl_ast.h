#ifndef EPDDL_STATIC_PREDICATES_DECL_AST_H
#define EPDDL_STATIC_PREDICATES_DECL_AST_H

#include "../ast_node.h"
#include "../tokens/tokens_ast.h"
#include "../common/typed_elem_ast.h"
#include <list>
#include <memory>

namespace epddl::ast {
    class static_predicate_decl;
    class problem_predicates;

    using static_predicate_decl_ptr  = std::unique_ptr<static_predicate_decl>;
    using static_predicate_decl_list = std::list<static_predicate_decl_ptr>;
    using problem_predicates_ptr     = std::unique_ptr<problem_predicates>;

    class static_predicate_decl : public ast_node {
    public:
        explicit static_predicate_decl(identifier_ptr name, formal_param_list params) :
                m_name{std::move(name)},
                m_params{std::move(params)} {}

    private:
        const identifier_ptr m_name;
        const formal_param_list m_params;
    };

    class problem_predicates : public ast_node {
    public:
        explicit problem_predicates(static_predicate_decl_list preds) :
                m_preds{std::move(preds)} {}

    private:
        const static_predicate_decl_list m_preds;
    };
}

#endif //EPDDL_STATIC_PREDICATES_DECL_AST_H
