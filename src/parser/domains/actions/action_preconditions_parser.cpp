#include "../../../../include/parser/domains/actions/action_preconditions_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/common/formulas_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::event_precondition_list action_preconditions_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::precondition>();
    helper.check_next_token<punctuation_token::lpar>();
    auto pre = helper.parse_list<ast::event_precondition>([&] () { return action_preconditions_parser::parse_event_precondition(helper); }, true);
    helper.check_next_token<punctuation_token::rpar>();

    return pre;
}

ast::event_precondition action_preconditions_parser::parse_event_precondition(parser_helper &helper) {
    ast::identifier_ptr event = tokens_parser::parse_identifier(helper);
    ast::formula_ptr pre = formulas_parser::parse_formula(helper);

    return std::make_pair(std::move(event), std::move(pre));
}

//ast::formula_ptr action_preconditions_parser::parse(parser_helper &helper) {
//    helper.check_next_token<keyword_token::precondition>();
//    return formulas_parser::parse_formula(helper);
//}
