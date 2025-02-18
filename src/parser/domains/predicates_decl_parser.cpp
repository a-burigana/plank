#include "../../../include/parser/domains/predicates_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::domain_predicates_ptr predicates_decl_parser::parse(parser_helper &helper) {
    helper.check_next_token<keyword_token::predicates>();
    auto preds = helper.parse_list<ast::predicate_decl_ptr>([&] () { return predicates_decl_parser::parse_predicate_decl(helper); });

    return std::make_unique<ast::domain_predicates>(std::move(preds));
}

ast::predicate_decl_ptr predicates_decl_parser::parse_predicate_decl(parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();                     // Eating '('
    ast::identifier_ptr name = tokens_parser::parse_identifier(helper);     // Eating predicate name (identifier)
    auto formal_params = helper.parse_list<ast::typed_variable_ptr>([&] () { return typed_elem_parser::parse_typed_variable(helper); }, true);
    helper.check_next_token<punctuation_token::rpar>();                     // Eating ')'

    return std::make_unique<ast::predicate_decl>(std::move(name), std::move(formal_params));
}
