#ifndef EPDDL_TYPED_ELEM_PARSER_H
#define EPDDL_TYPED_ELEM_PARSER_H

#include "../../ast/common/typed_elem_ast.h"
#include "../parser_helper.h"
#include "../../../include/parser/tokens/tokens_parser.h"
#include <memory>

namespace epddl::parser {
    class typed_elem_parser {
    public:
        static ast::typed_identifier_ptr parse_typed_identifier(parser_helper &helper);
        static ast::typed_variable_ptr parse_typed_variable(parser_helper &helper);

    private:
        template<typename ast_leaf_type>
        static std::unique_ptr<ast::typed_elem<ast_leaf_type>> parse_typed_elem(parser_helper &helper) {
            std::unique_ptr<ast_leaf_type> elem = tokens_parser::parse_token<ast_leaf_type>(helper);
            std::optional<ast::identifier_ptr> type = std::nullopt;

            const token_ptr &tok = helper.peek_next_token();            // Peeking either '-' or another ast_leaf_type token

            if (tok->has_type<punctuation_token::dash>()) {
                helper.check_next_token<punctuation_token::dash>();     // Actually eating '-'
                type = tokens_parser::parse_identifier(helper);
            }
            return std::make_unique<ast::typed_elem<ast_leaf_type>>(std::move(elem), std::move(type));
        }
    };
}

#endif //EPDDL_TYPED_ELEM_PARSER_H
