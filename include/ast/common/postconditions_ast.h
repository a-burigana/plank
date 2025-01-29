#ifndef EPDDL_POSTCONDITIONS_AST_H
#define EPDDL_POSTCONDITIONS_AST_H

#include "../../ast/ast_node.h"
#include "formulas_ast.h"
#include <list>

namespace epddl::ast {
    class literal_postcondition;
    class iff_postcondition;
    class when_postcondition;
    class forall_postcondition;

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
}

#endif //EPDDL_POSTCONDITIONS_AST_H
