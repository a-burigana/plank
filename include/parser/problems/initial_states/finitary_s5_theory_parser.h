#ifndef EPDDL_FINITARY_S5_THEORY_PARSER_H
#define EPDDL_FINITARY_S5_THEORY_PARSER_H

#include "../../parser_helper.h"
#include "../../../ast/problems/initial_states/finitary_s5_theory_ast.h"

namespace epddl::parser {
    class finitary_s5_theory_parser {
    public:
        static ast::finitary_s5_theory_ptr parse(parser_helper &helper);

        static ast::theory_formula_ptr parse_theory_formula(parser_helper &helper);
        static ast::ck_formula_ptr parse_ck_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_atomic_formula(parser_helper &helper);

        static ast::atomic_formula_ptr parse_pred_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_not_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_and_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_or_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_imply_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_forall_atomic_formula(parser_helper &helper);
        static ast::atomic_formula_ptr parse_exists_atomic_formula(parser_helper &helper);

        static ast::ck_formula_ptr parse_K_or_Kw_formula(parser_helper &helper);
        static ast::ck_not_Kw_formula_ptr parse_not_Kw_formula(parser_helper &helper);
    };
}

#endif //EPDDL_FINITARY_S5_THEORY_PARSER_H
