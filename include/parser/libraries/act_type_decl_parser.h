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

#ifndef PLANK_ACT_TYPE_DECL_PARSER_H
#define PLANK_ACT_TYPE_DECL_PARSER_H

#include "../../ast/libraries/act_type_decl_ast.h"
#include "../parser_helper.h"

namespace epddl::parser {
    class act_type_decl_parser {
    public:
        static ast::action_type_ptr parse(parser_helper &helper);

        static ast::variable_list parse_events(parser_helper &helper, const std::string &action_type_name);
        static ast::identifier_list parse_obs_types(parser_helper &helper, const std::string &action_type_name);
        static ast::variable_list parse_designated(parser_helper &helper, const std::string &action_type_name);
    };
}

#endif //PLANK_ACT_TYPE_DECL_PARSER_H
