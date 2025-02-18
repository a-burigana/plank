#include "../../../include/parser/common/parameters_parser.h"
#include "../../../include/parser/common/formulas_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::parameters_ptr parameters_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::parameters>();       // Eating ':parameters'

    helper.check_next_token<punctuation_token::lpar>();        // Eating '('
    auto params = formulas_parser::parse_int_list_comprehension(helper, true);
    helper.check_next_token<punctuation_token::rpar>();        // Eating ')'

    return std::make_unique<ast::parameters>(std::move(params));
}
