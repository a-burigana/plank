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

#ifndef PLANK_OBS_CONDITIONS_PARSER_H
#define PLANK_OBS_CONDITIONS_PARSER_H

#include "ast/domains/actions/obs_conditions_ast.h"
#include "parser/parser_helper.h"

namespace epddl::parser {
    class obs_conditions_parser {
    public:
        static ast::list<ast::obs_cond> parse_action_obs_cond(parser_helper &helper, const std::string &action_name);

        static ast::obs_cond parse_obs_cond(parser_helper &helper, bool parse_outer_pars = true);

        static ast::obs_cond parse_static_or_ite_obs_cond(parser_helper &helper, bool parse_outer_pars = true);
        static ast::if_obs_cond_ptr parse_if_obs_cond(parser_helper &helper);
        static ast::else_if_obs_cond_ptr parse_else_if_obs_cond(parser_helper &helper);
        static ast::else_obs_cond_ptr parse_else_obs_cond(parser_helper &helper);
        static ast::default_obs_cond_ptr parse_default_obs_cond(parser_helper &helper);

        static ast::term parse_observing_agent(parser_helper &helper);
    };
}

#endif //PLANK_OBS_CONDITIONS_PARSER_H
