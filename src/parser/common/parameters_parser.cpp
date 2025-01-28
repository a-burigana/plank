#include "../../../include/parser/common/parameters_parser.h"
#include "../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;

ast::parameters_ptr parameters_parser::parse(epddl::parser_helper &parser) {
    parser.check_next_token<keyword_token::parameters>();       // Eating ':parameters'

    parser.check_next_token<punctuation_token::lpar>();        // Eating '('
    auto params = parser.parse_list<ast::formal_param>([&] () { return typed_elem_parser::parse_typed_elem<ast::variable>(parser); });
    parser.check_next_token<punctuation_token::rpar>();        // Eating ')'

    return std::make_unique<ast::parameters>(std::move(params));
}
