#ifndef EPDDL_ACTION_POSTCONDITIONS_AST_H
#define EPDDL_ACTION_POSTCONDITIONS_AST_H

#include "../../tokens/tokens_ast.h"
#include "../../common/formulas_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class literal_postcondition;
    class iff_postcondition;
    class when_postcondition;
    class forall_postcondition;

    using literal_postcondition_ptr  = std::unique_ptr<literal_postcondition>;
    using iff_postcondition_ptr      = std::unique_ptr<iff_postcondition>;
    using when_postcondition_ptr     = std::unique_ptr<when_postcondition>;
    using forall_postcondition_ptr   = std::unique_ptr<forall_postcondition>;

    using single_postcondition       = std::variant<literal_postcondition_ptr, iff_postcondition_ptr, when_postcondition_ptr, forall_postcondition_ptr>;
    using postcondition_list         = std::list<single_postcondition>;

    using postconditions             = std::variant<single_postcondition, postcondition_list>;

    using event_postconditions       = std::pair<identifier_ptr, postconditions>;
    using event_postconditions_list  = std::list<event_postconditions>;

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
        explicit forall_postcondition(int_list_comprehension_ptr params, postconditions post) :
                m_params{std::move(params)},
                m_post{std::move(post)} {}

    private:
        const int_list_comprehension_ptr m_params;
        const postconditions m_post;
    };
}

#endif //EPDDL_ACTION_POSTCONDITIONS_AST_H
