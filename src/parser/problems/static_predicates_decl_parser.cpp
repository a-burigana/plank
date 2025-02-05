#include "../../../include/parser/problems/static_predicates_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;

ast::problem_predicates_ptr static_predicates_decl_parser::parse(epddl::parser_helper &parser) {
    parser.check_next_token<keyword_token::static_predicates>();
    auto preds = parser.parse_list<ast::static_predicate_decl_ptr>([&] () { return static_predicates_decl_parser::parse_static_predicate_decl(parser); });

    return std::make_unique<ast::problem_predicates>(std::move(preds));
}

ast::static_predicate_decl_ptr static_predicates_decl_parser::parse_static_predicate_decl(epddl::parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();                     // Eating '('
    ast::identifier_ptr name = tokens_parser::parse_identifier(parser);     // Eating predicate name (identifier)
    auto formal_params = parser.parse_list<ast::typed_variable_ptr>([&] () { return typed_elem_parser::parse_typed_variable(parser); }, true);
    parser.check_next_token<punctuation_token::rpar>();                     // Eating ')'

    return std::make_unique<ast::static_predicate_decl>(std::move(name), std::move(formal_params));
}
