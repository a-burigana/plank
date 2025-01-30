#ifndef EPDDL_TOKENS_PARSER_H
#define EPDDL_TOKENS_PARSER_H

#include "../../ast/main_decl_ast.h"
#include "../parser_helper.h"

namespace epddl {
    class tokens_parser {
    public:
        template<typename ast_leaf_type>
        static std::unique_ptr<ast_leaf_type> parse_token(parser_helper &parser) {
            return std::make_unique<ast_leaf_type>(parser.get_leaf_from_next_token<typename ast_leaf_type::token_type>());
        }

        static ast::identifier_ptr parse_identifier(parser_helper &parser);
        static ast::variable_ptr parse_variable(parser_helper &parser);
        static ast::modality_name_ptr parse_modality_name(parser_helper &parser);
        static ast::requirement_ptr parse_requirement(parser_helper &parser);
        static ast::integer_ptr parse_integer(parser_helper &parser);
    };
}

#endif //EPDDL_TOKENS_PARSER_H
