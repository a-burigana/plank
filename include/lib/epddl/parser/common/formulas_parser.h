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

#ifndef PLANK_FORMULAS_PARSER_H
#define PLANK_FORMULAS_PARSER_H

#include "../../ast/common/formulas_ast.h"
#include "../parser_helper.h"
#include <cstdint>

namespace epddl::parser {
    enum class formula_type : std::uint8_t {
        precondition,
        postcondition,
        obs_condition,
        goal,
        list_formula,
        finitary_S5_formula,
        cli_user_formula
    };

    class formulas_parser {
    public:
        static ast::formula_ptr parse_formula(parser_helper &helper, const formula_type &f_type, bool parse_outer_pars = true);
        static ast::formula_ptr parse_propositional_formula(parser_helper &helper, const formula_type &f_type, bool parse_outer_pars = true);

//        static ast::agent_group_ptr parse_agent_group(parser_helper &helper);
        static ast::list_comprehension_ptr parse_list_comprehension(parser_helper &helper, bool allow_empty_params = false);

        static ast::predicate_ptr parse_predicate(parser_helper &helper, bool parse_outer_pars = true);
        static ast::literal_ptr parse_literal(parser_helper &helper, bool parse_outer_pars = true);
        static ast::term parse_term(parser_helper &helper, const std::string &msg);

        static ast::simple_agent_group_ptr parse_simple_agent_group(parser_helper &helper);

        template<typename Elem, typename... Tokens>
        static ast::list<Elem> parse_list(parser_helper &helper, const std::string &err_info,
                                          const std::function<Elem()> &parse_elem, bool parse_outer_pars = true) {
            ast::list<Elem> list;

            if (parse_outer_pars) helper.check_left_par(err_info);
            const token_ptr &tok = helper.peek_next_token();

            if (tok->has_either_type<Tokens...>())
                list = formulas_parser::parse_singleton_list<Elem>(helper, err_info, parse_elem);
            else if (tok->has_type<keyword_token::list_and>())
                list = formulas_parser::parse_and_list<Elem, Tokens...>(helper, err_info, parse_elem);
            else if (tok->has_type<keyword_token::list_forall>())
                list = formulas_parser::parse_forall_list<Elem, Tokens...>(helper, err_info, parse_elem);
            else
                helper.throw_error(error_type::token_mismatch, tok, err_info + " list");

            if (parse_outer_pars) helper.check_right_par(err_info);

            return list;
        }

    private:
        static ast::formula_ptr parse_formula_helper(parser_helper &helper, const formula_type &f_type, bool is_propositional = false, bool parse_outer_pars = true);

        static ast::formula_ptr parse_true_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);
        static ast::formula_ptr parse_false_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);

        static ast::formula_ptr parse_predicate_formula(parser_helper &helper, bool is_propositional = false);
        static ast::formula_ptr parse_eq_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);
        static ast::formula_ptr parse_neq_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);
//        static ast::formula_ptr parse_in_formula(parser_helper &helper, bool is_propositional = false);

        static ast::formula_ptr parse_not_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);
        static ast::formula_ptr parse_and_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);
        static ast::formula_ptr parse_or_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);
        static ast::formula_ptr parse_imply_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);

        static ast::formula_ptr parse_box_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);
        static ast::formula_ptr parse_diamond_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);

        static ast::formula_ptr parse_forall_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);
        static ast::formula_ptr parse_exists_formula(parser_helper &helper, const formula_type &f_type, bool is_propositional = false);

//        static ast::list_ptr parse_list_name(parser_helper &helper);
//        static ast::agent_group_ptr parse_and_agent_group(parser_helper &helper);
//        static ast::agent_group_ptr parse_forall_agent_group(parser_helper &helper);

        static ast::formula_ptr parse_such_that(parser_helper &helper);

        static ast::modality_ptr parse_modality(parser_helper &helper);
        static ast::modality_index_ptr parse_modality_index(parser_helper &helper);
        static ast::all_group_modality_ptr parse_all_group_modality(parser_helper &helper);

        static ast::term_list parse_group_modality(parser_helper &helper);

        static std::string get_formula_type_str(const formula_type &f_type);

        template<typename Elem>
        static ast::singleton_list_ptr<Elem> parse_singleton_list(parser_helper &helper, const std::string &err_info,
                                                                  const std::function<Elem()> &parse_elem) {
            ast::info info = helper.get_next_token_info();
            return std::make_shared<ast::singleton_list<Elem>>(std::move(info), std::move(parse_elem()));
        }

        template<typename Elem, typename... Tokens>
        static ast::and_list_ptr<Elem> parse_and_list(parser_helper &helper, const std::string &err_info,
                                                      const std::function<Elem()> &parse_elem) {
            ast::info info = helper.get_next_token_info();
            info.add_requirement(":lists", "List declarations require ':lists'.");

            helper.check_next_token<keyword_token::list_and>();
            auto lists = helper.parse_list<ast::list<Elem>>([&]() {
                return formulas_parser::parse_list<Elem, Tokens...>(helper, err_info, parse_elem);
            });
            return std::make_shared<ast::and_list<Elem>>(std::move(info), std::move(lists));
        }

        template<typename Elem, typename... Tokens>
        static ast::forall_list_ptr<Elem> parse_forall_list(parser_helper &helper, const std::string &err_info,
                                                            const std::function<Elem()> &parse_elem) {
            ast::info info = helper.get_next_token_info();
            info.add_requirement(":lists", "List declarations require ':lists'.");

            helper.check_next_token<keyword_token::list_forall>();
            helper.check_next_token<punctuation_token::lpar>();
            ast::list_comprehension_ptr params = formulas_parser::parse_list_comprehension(helper);
            helper.check_next_token<punctuation_token::rpar>();
            ast::list<Elem> list = formulas_parser::parse_list<Elem, Tokens...>(helper, err_info, parse_elem);

            return std::make_shared<ast::forall_list<Elem>>(std::move(info), std::move(params), std::move(list));
        }
    };
}

#endif //PLANK_FORMULAS_PARSER_H
