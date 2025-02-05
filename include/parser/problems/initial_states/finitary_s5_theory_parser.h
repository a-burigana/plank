#ifndef EPDDL_FINITARY_S5_THEORY_PARSER_H
#define EPDDL_FINITARY_S5_THEORY_PARSER_H

#include "../../parser_helper.h"
#include "../../../ast/problems/initial_states/finitary_s5_theory_ast.h"

namespace epddl {
    class finitary_s5_theory_parser {
    public:
        static ast::finitary_s5_theory_ptr parse(parser_helper &helper);

        static ast::theory_formula_ptr parse_theory_formula(parser_helper &parser);
        static ast::ck_formula_ptr parse_ck_formula(parser_helper &parser);
        static ast::atomic_formula_ptr parse_atomic_formula(parser_helper &parser);

        static ast::atomic_formula_ptr parse_pred_atomic_formula(parser_helper &parser);
        static ast::atomic_formula_ptr parse_not_atomic_formula(parser_helper &parser);
        static ast::atomic_formula_ptr parse_and_atomic_formula(parser_helper &parser);
        static ast::atomic_formula_ptr parse_or_atomic_formula(parser_helper &parser);
        static ast::atomic_formula_ptr parse_imply_atomic_formula(parser_helper &parser);
        static ast::atomic_formula_ptr parse_forall_atomic_formula(parser_helper &parser);
        static ast::atomic_formula_ptr parse_exists_atomic_formula(parser_helper &parser);

        static ast::ck_K_formula_ptr parse_K_formula(parser_helper &parser);
        static ast::ck_Kw_formula_ptr parse_Kw_formula(parser_helper &parser);
        static ast::ck_not_Kw_formula_ptr parse_not_Kw_formula(parser_helper &parser);
    };
}

#endif //EPDDL_FINITARY_S5_THEORY_PARSER_H
