#include "../../../../include/parser/domains/actions/action_signatures_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"
#include "../../../../include/parser/domains/actions/expressions_parser.h"

using namespace epddl;using namespace epddl;
using namespace epddl::parser;

ast::action_signature_ptr action_signatures_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::act_type>();                // Eating ':action-type'
    helper.check_next_token<punctuation_token::lpar>();                // Eating '('
    ast::identifier_ptr act_type_name = tokens_parser::parse_token<ast::identifier>(helper);     // Eating action type name (identifier)

//    ast::expression_list assignments = helper.parse_list<ast::expression>([&] () { return expressions_parser::parse(helper); });
    helper.check_next_token<punctuation_token::rpar>();                // Eating ')'

    return std::make_unique<ast::action_signature>(std::move(act_type_name));   //, std::move(assignments)
}
