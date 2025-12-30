// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef PLANK_RELATIONS_PARSER_H
#define PLANK_RELATIONS_PARSER_H

#include "../parser_helper.h"
#include "../../ast/common/relations_ast.h"
#include "../tokens/tokens_parser.h"
#include "formulas_parser.h"

namespace epddl::parser {
    class relations_parser {
    public:
        template<typename node_type>
        static ast::agent_relation_list<node_type>
        parse_model_relations(parser_helper &helper, const std::function<node_type()> &parse_elem,
                              const decl_type decl_type, const std::string &decl_name) {
            // Model relations
            helper.check_next_token<keyword_token::relations>();
            const std::string err_info = error_manager::get_error_info(decl_type, decl_name);

            helper.check_left_par(err_info);
            helper.push_error_info(err_info);

            auto agents_relations = helper.parse_list<ast::agent_relation_ptr<node_type>>(
                    [&]() {
                        return relations_parser::parse_agent_relation<node_type>(helper, parse_elem);
                    }, true);

            // End model relations
            helper.pop_error_info();
            helper.check_right_par(err_info);

            return agents_relations;
        }

        template<typename node_type>
        static ast::agent_relation_ptr<node_type>
        parse_agent_relation(parser_helper &helper, const std::function<node_type()> &parse_elem) {
            ast::info info = helper.get_next_token_info();
            const std::string obs_type_ag_name = std::is_same_v<node_type, ast::term>
                    ? "observability type name"
                    : "agent name";

            ast::identifier_ptr obs_type_ag = tokens_parser::parse_identifier(helper, obs_type_ag_name);
            auto relation = formulas_parser::parse_list<ast::simple_relation_ptr<node_type>, ast_token::identifier,
                    ast_token::variable>(helper, "relation declaration", [&]() {
                        return relations_parser::parse_simple_relation<node_type>(helper, parse_elem);
                    });

            return std::make_shared<ast::agent_relation<node_type>>(std::move(info), std::move(obs_type_ag), std::move(relation));
        }

        template<typename node_type>
        static ast::simple_relation_ptr<node_type>
        parse_simple_relation(parser_helper &helper, const std::function<node_type()> &parse_elem) {
            ast::info info = helper.get_next_token_info();
            node_type node_1 = parse_elem();
            node_type node_2 = parse_elem();
            return std::make_shared<ast::simple_relation<node_type>>(std::move(info), std::move(node_1), std::move(node_2));
        }
    };
}

#endif //PLANK_RELATIONS_PARSER_H
