#include "../../../../include/parser/libraries/act_types/act_type_preconditions_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"

using namespace epddl;

//ast::event_precondition_list act_type_preconditions_parser::parse(epddl::parser_helper &helper) {
//    helper.check_next_token<keyword_token::precondition>();
//    return helper.parse_list<ast::event_precondition>([&] () { return act_type_preconditions_parser::parse_event_precondition(helper); }, true);
//}
//
//ast::event_precondition act_type_preconditions_parser::parse_event_precondition(epddl::parser_helper &helper) {
//    helper.check_next_token<punctuation_token::lpar>();
//    ast::identifier_ptr event = tokens_parser::parse_identifier(helper);
//    ast::formula_ptr pre = formulas_parser::parse_formula(helper);
//    helper.check_next_token<punctuation_token::rpar>();
//
//    return std::make_pair(std::move(event), std::move(pre));
//}