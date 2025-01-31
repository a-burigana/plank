#include "../../../include/parser/libraries/act_type_library_parser.h"
#include "../../../include/parser/libraries/observability_groups_decl_parser.h"
#include "../../../include/parser/libraries/act_type_decl_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include "../../../include/error-manager/epddl_exception.h"
#include "../../../include/parser/domains/requirements_parser.h"
#include "../../../include/parser/common/modalities_decl_parser.h"

using namespace epddl;

ast::act_type_library_ptr act_type_library_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::library>();    // Eating 'library'
    ast::identifier_ptr library_name = tokens_parser::parse_identifier(helper);    // Eating library name (identifier)
    helper.check_next_token<punctuation_token::rpar>();        // Eating ')'

    auto library_items = helper.parse_list<ast::act_type_library_item>([&] () { return act_type_library_parser::parse_act_type_library_item(helper); });

    return std::make_unique<ast::act_type_library>(std::move(library_name), std::move(library_items));
}

ast::act_type_library_item act_type_library_parser::parse_act_type_library_item(epddl::parser_helper &helper) {
    helper.check_next_token<punctuation_token::lpar>();    // Eating '('
    const token_ptr &tok = helper.peek_next_token();       // Eating keyword

    ast::act_type_library_item item;

    if (tok->has_type<keyword_token::requirements>())
        item = requirements_parser::parse(helper);
    else if (tok->has_type<keyword_token::modalities>())
        item = modalities_decl_parser::parse(helper);
    else if (tok->has_type<keyword_token::obs_groups>())
        item = observability_groups_decl_parser::parse(helper);
    else if (tok->has_type<keyword_token::act_type>())
        item = act_type_decl_parser::parse(helper);
    else
        throw EPDDLException{std::string{""}, tok->get_row(), tok->get_col(), std::string{"Expected keyword."}};

    helper.check_next_token<punctuation_token::rpar>();    // Eating ')'
    return item;
}