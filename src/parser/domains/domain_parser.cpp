#include <memory>
#include "../../../include/parser/domains/domain_parser.h"
#include "../../../include/ast/ast.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include "../../../include/parser/domains/act_type_libraries_parser.h"
#include "../../../include/parser/domains/requirements_parser.h"
#include "../../../include/parser/domains/types_decl_parser.h"
#include "../../../include/parser/domains/predicates_decl_parser.h"
#include "../../../include/parser/domains/actions/action_decl_parser.h"

using namespace epddl;

ast::domain_ptr domain_parser::parse(epddl::parser_helper &parser) {
    parser.check_next_token<punctuation_token::lpar>();        // Eating '('
    parser.check_next_token<keyword_token::define>();          // Eating 'define'
    parser.check_next_token<punctuation_token::lpar>();        // Eating '('
    parser.check_next_token<keyword_token::domain>();          // Eating 'domain'
    ast::identifier_ptr domain_name = tokens_parser::parse_identifier(parser);    // Eating domain name (identifier)
    parser.check_next_token<punctuation_token::rpar>();        // Eating ')'

    ast::domain_item_list domain_items = parser.parse_list<ast::domain_item>([&] () { return domain_parser::parse_domain_item(parser); });
    parser.check_next_token<punctuation_token::rpar>();        // Eating ')'

    return std::make_unique<ast::domain>(std::move(domain_name), std::move(domain_items));
}

ast::domain_item domain_parser::parse_domain_item(epddl::parser_helper &parser) {
    auto domain_lib = choice<ast::domain_item>{keyword_token::act_type_lib{}, [&]() { return act_type_libraries_parser::parse(parser); }};
    auto choices = std::deque{std::move(domain_lib)};

//    parser.parse_choice_point(parser.open_par(), choices, parser.close_par());
    parser.check_next_token<punctuation_token::lpar>();    // Eating '('
    const token_ptr &tok = parser.peek_next_token();       // Eating keyword

    ast::domain_item item;

    if (tok->has_type<keyword_token::act_type_lib>())
        item = act_type_libraries_parser::parse(parser);
    else if (tok->has_type<keyword_token::requirements>())
        item = requirements_parser::parse(parser);
    else if (tok->has_type<keyword_token::types>())
        item = types_decl_parser::parse(parser);
    else if (tok->has_type<keyword_token::predicates>())
        item = predicates_decl_parser::parse(parser);
//    else if (tok->has_type<keyword_token::modalities>()) {        // todo: implement new idea on modalities
//        item = parse_domain_modalities();
    else if (tok->has_type<keyword_token::action>())
        item = action_decl_parser::parse(parser);
    else
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(), std::string{"Expected keyword."}};

    parser.check_next_token<punctuation_token::rpar>();    // Eating ')'
    return item;
}
