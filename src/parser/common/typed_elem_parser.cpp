#include "../../../include/parser/common/typed_elem_parser.h"
#include <memory>

using namespace epddl;
using namespace epddl::parser;

ast::typed_identifier_ptr typed_elem_parser::parse_typed_identifier(parser_helper &helper) {
    return typed_elem_parser::parse_typed_elem<ast::identifier>(helper);
}

ast::typed_variable_ptr typed_elem_parser::parse_typed_variable(parser_helper &helper) {
    return typed_elem_parser::parse_typed_elem<ast::variable>(helper);
}
