#include "../../../include/parser/domains/predicates_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;

ast::domain_predicates_ptr predicates_decl_parser::parse(epddl::parser_helper &parser) {
    parser.check_next_token<keyword_token::predicates>();
    auto preds = parser.parse_list<ast::predicate_def_ptr>([&] () { return predicates_decl_parser::parse_predicate_decl(parser); });

    return std::make_unique<ast::domain_predicates>(std::move(preds));
}

ast::predicate_def_ptr predicates_decl_parser::parse_predicate_decl(epddl::parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();                     // Eating '('
    ast::identifier_ptr name = tokens_parser::parse_identifier(parser);     // Eating predicate name (identifier)
    auto formal_params = parser.parse_list<ast::typed_elem_ptr<ast::variable>>([&] () {
        return typed_elem_parser::parse_typed_elem<ast::variable>(parser);
    }, true);
    parser.check_next_token<punctuation_token::rpar>();                     // Eating ')'

    return std::make_unique<ast::predicate_def>(std::move(name), std::move(formal_params));
}
