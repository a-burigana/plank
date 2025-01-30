#include "../../../include/parser/problems/goal_parser.h"
#include "../../../include/parser/common/formulas_parser.h"

using namespace epddl;

ast::goal_decl_ptr goal_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::goal>();
    auto goal = formulas_parser::parse_formula(helper);

    return std::make_unique<ast::goal_decl>(std::move(goal));
}
