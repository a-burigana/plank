#ifndef EPDDL_FORMULAS_PARSER_H
#define EPDDL_FORMULAS_PARSER_H

#include "../../ast/common/formulas_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class formulas_parser {
    public:
        static ast::formula_ptr parse_formula(parser_helper &parser);

        static ast::formula_ptr parse_predicate_formula(parser_helper &parser);
        static ast::formula_ptr parse_eq_formula(parser_helper &parser);
        static ast::formula_ptr parse_not_formula(parser_helper &parser);
        static ast::formula_ptr parse_and_formula(parser_helper &parser);
        static ast::formula_ptr parse_or_formula(parser_helper &parser);
        static ast::formula_ptr parse_imply_formula(parser_helper &parser);
        static ast::formula_ptr parse_box_formula(parser_helper &parser);
        static ast::formula_ptr parse_diamond_formula(parser_helper &parser);

        static ast::formula_ptr parse_such_that(parser_helper &parser);
        static ast::ext_list_comprehension_ptr parse_ext_list_comprehension(parser_helper &parser, ast::variable_list &&prefix = ast::variable_list{});
        static ast::int_list_comprehension_ptr parse_int_list_comprehension(parser_helper &parser);
        static ast::list_comprehension_ptr parse_list_comprehension(parser_helper &parser);
        static ast::formula_ptr parse_in_formula(parser_helper &parser);

        static ast::formula_ptr parse_forall_formula(parser_helper &parser);
        static ast::formula_ptr parse_exists_formula(parser_helper &parser);

        static ast::predicate_ptr parse_predicate(parser_helper &parser, bool parse_outer_pars = true);
        static ast::literal_ptr parse_literal(parser_helper &parser);
        static ast::term parse_term(parser_helper &parser);

        static ast::modality_ptr parse_modality(parser_helper &parser);
        static ast::single_modality_index_ptr parse_single_modality(parser_helper &parser);
        static ast::group_modality_index_ptr parse_group_modality(parser_helper &parser);
    };
}

#endif //EPDDL_FORMULAS_PARSER_H
