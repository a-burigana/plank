#include "../../../include/parser/common/typed_elem_parser.h"
#include <memory>

using namespace epddl;

ast::typed_identifier_ptr typed_elem_parser::parse_typed_identifier(epddl::parser_helper &parser) {
    return typed_elem_parser::parse_typed_elem<ast::identifier>(parser);
}

ast::typed_variable_ptr typed_elem_parser::parse_typed_variable(parser_helper &parser) {
    return typed_elem_parser::parse_typed_elem<ast::variable>(parser);
}
