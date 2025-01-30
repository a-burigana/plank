#include "../../../include/parser/common/types_decl_parser.h"
#include "../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;

ast::types_decl_ptr types_decl_parser::parse(parser_helper &parser) {
    parser.check_next_token<keyword_token::types>();
    auto types_decl = parser.parse_list<ast::typed_elem_ptr<ast::identifier>>([&] () {
        return typed_elem_parser::parse_typed_elem<ast::identifier>(parser);
    });
    return std::make_unique<ast::types_decl>(std::move(types_decl));
}
