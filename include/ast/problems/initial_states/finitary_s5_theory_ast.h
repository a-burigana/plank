#ifndef EPDDL_FINITARY_S5_THEORY_AST_H
#define EPDDL_FINITARY_S5_THEORY_AST_H

#include "../../ast_node.h"
#include "../../common/formulas_ast.h"
#include <list>
#include <memory>
#include <variant>

namespace epddl::ast {
    class pred_atomic_formula;
    class not_atomic_formula;
    class and_atomic_formula;
    class or_atomic_formula;
    class imply_atomic_formula;
    class forall_atomic_formula;
    class exists_atomic_formula;

    class ck_atomic_formula;
    class ck_K_formula;
    class ck_Kw_formula;
    class ck_not_Kw_formula;
    class finitary_s5_theory;

    using pred_atomic_formula_ptr   = std::unique_ptr<pred_atomic_formula>;
    using not_atomic_formula_ptr    = std::unique_ptr<not_atomic_formula>;
    using and_atomic_formula_ptr    = std::unique_ptr<and_atomic_formula>;
    using or_atomic_formula_ptr     = std::unique_ptr<or_atomic_formula>;
    using imply_atomic_formula_ptr  = std::unique_ptr<imply_atomic_formula>;
    using forall_atomic_formula_ptr = std::unique_ptr<forall_atomic_formula>;
    using exists_atomic_formula_ptr = std::unique_ptr<exists_atomic_formula>;

    using atomic_formula_ptr        = std::variant<pred_atomic_formula_ptr, not_atomic_formula_ptr, and_atomic_formula_ptr, or_atomic_formula_ptr, imply_atomic_formula_ptr, forall_atomic_formula_ptr, exists_atomic_formula_ptr>;
    using atomic_formula_list       = std::list<atomic_formula_ptr>;

    using ck_atomic_formula_ptr     = std::unique_ptr<ck_atomic_formula>;
    using ck_K_formula_ptr          = std::unique_ptr<ck_K_formula>;
    using ck_Kw_formula_ptr         = std::unique_ptr<ck_Kw_formula>;
    using ck_not_Kw_formula_ptr     = std::unique_ptr<ck_not_Kw_formula>;

    using ck_formula_ptr            = std::variant<ck_atomic_formula_ptr, ck_K_formula_ptr, ck_Kw_formula_ptr, ck_not_Kw_formula_ptr>;
    using theory_formula_ptr        = std::variant<atomic_formula_ptr, ck_formula_ptr>;
    using theory_formula_list       = std::list<theory_formula_ptr>;

    using finitary_s5_theory_ptr    = std::unique_ptr<finitary_s5_theory>;

    class pred_atomic_formula : public ast_node {
    public:
        explicit pred_atomic_formula(predicate_ptr predicate) :
                m_predicate{std::move(predicate)} {}

    private:
        const predicate_ptr m_predicate;
    };

    class not_atomic_formula : public ast_node {
    public:
        explicit not_atomic_formula(atomic_formula_ptr f) :
                m_f{std::move(f)} {}

    private:
        const atomic_formula_ptr m_f;
    };

    class and_atomic_formula : public ast_node {
    public:
        explicit and_atomic_formula(atomic_formula_list fs) :
                m_fs{std::move(fs)} {}

    private:
        const atomic_formula_list m_fs;
    };

    class or_atomic_formula : public ast_node {
    public:
        explicit or_atomic_formula(atomic_formula_list fs) :
                m_fs{std::move(fs)} {}

    private:
        const atomic_formula_list m_fs;
    };

    class imply_atomic_formula : public ast_node {
    public:
        explicit imply_atomic_formula(atomic_formula_ptr f1, atomic_formula_ptr f2) :
                m_f1{std::move(f1)},
                m_f2{std::move(f2)}{}

    private:
        const atomic_formula_ptr m_f1, m_f2;
    };

    class forall_atomic_formula : public ast_node {
    public:
        explicit forall_atomic_formula(formal_param_list params, atomic_formula_ptr f) :
                m_params{std::move(params)},
                m_f{std::move(f)} {}

    private:
        const formal_param_list m_params;
        const atomic_formula_ptr m_f;
    };

    class exists_atomic_formula : public ast_node {
    public:
        explicit exists_atomic_formula(formal_param_list params, atomic_formula_ptr f) :
                m_params{std::move(params)},
                m_f{std::move(f)} {}

    private:
        const formal_param_list m_params;
        const atomic_formula_ptr m_f;
    };

    class ck_atomic_formula : public ast_node {
    public:
        explicit ck_atomic_formula(atomic_formula_ptr f) :
                m_f{std::move(f)} {}

    private:
        const atomic_formula_ptr m_f;
    };

    class ck_K_formula : public ast_node {
    public:
        explicit ck_K_formula(modality_index_ptr mod, atomic_formula_ptr f) :
                m_mod{std::move(mod)},
                m_f{std::move(f)} {}

    private:
        const modality_index_ptr m_mod;
        const atomic_formula_ptr m_f;
    };

    class ck_Kw_formula : public ast_node {
    public:
        explicit ck_Kw_formula(modality_index_ptr mod, atomic_formula_ptr f) :
                m_mod{std::move(mod)},
                m_f{std::move(f)} {}

    private:
        const modality_index_ptr m_mod;
        const atomic_formula_ptr m_f;
    };

    class ck_not_Kw_formula : public ast_node {
    public:
        explicit ck_not_Kw_formula(modality_index_ptr mod, atomic_formula_ptr f) :
                m_mod{std::move(mod)},
                m_f{std::move(f)} {}

    private:
        const modality_index_ptr m_mod;
        const atomic_formula_ptr m_f;
    };

    class finitary_s5_theory : public ast_node {
    public:
        explicit finitary_s5_theory(theory_formula_list fs) :
                m_fs{std::move(fs)} {}

    private:
        const theory_formula_list m_fs;
    };
}
#endif //EPDDL_FINITARY_S5_THEORY_AST_H
