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

#include "../../../include/parser/common/parameters_parser.h"
#include "../../../include/parser/common/formulas_parser.h"
#include "../../../include/parser/common/typed_elem_parser.h"

using namespace epddl;
using namespace epddl::parser;

ast::list_comprehension_ptr parameters_parser::parse_list_comprehension_params(parser_helper &helper,
                                                                               const std::string &action_name) {
    // Parameters
    helper.check_next_token<keyword_token::parameters>();
    const std::string err_info = error_manager::get_error_info(decl_type::action_params_decl, action_name);

    helper.check_left_par(err_info);
    helper.push_error_info(err_info);

    auto params = formulas_parser::parse_list_comprehension(helper, true);

    // End parameters
    helper.pop_error_info();
    helper.check_right_par(err_info);

    return params;
}

ast::formal_param_list parameters_parser::parse_variable_list_params(parser_helper &helper,
                                                                     const std::string &event_name) {
    // Parameters
    helper.check_next_token<keyword_token::parameters>();
    const std::string err_info = error_manager::get_error_info(decl_type::event_params_decl, event_name);

    helper.check_left_par(err_info);
    helper.push_error_info(err_info);

    auto params = helper.parse_list<ast::typed_variable_ptr>([&]() {
        return typed_elem_parser::parse_typed_variable(helper);
    }, true);

    // End parameters
    helper.pop_error_info();
    helper.check_right_par(err_info);

    return params;
}
