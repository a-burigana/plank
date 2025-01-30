#include "../../../include/parser/problems/objects_parser.h"
#include "../../../include/parser/tokens/tokens_parser.h"

using namespace epddl;

ast::objects_decl_ptr objects_parser::parse(epddl::parser_helper &helper) {
    helper.check_next_token<keyword_token::objects>();
    auto objects = helper.parse_list<ast::identifier_ptr>([&] () { return tokens_parser::parse_identifier(helper); });

    return std::make_unique<ast::objects_decl>(std::move(objects));
}