#include "../../../../include/parser/libraries/act_types/act_type_designated_parser.h"
#include "../../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::ident_list act_type_designated_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::designated>();
    helper.check_next_token<punctuation_token::lpar>();
    auto designated_names = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });
    helper.check_next_token<punctuation_token::rpar>();

    return designated_names;
}
