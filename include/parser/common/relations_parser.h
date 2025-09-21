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

#ifndef EPDDL_RELATIONS_PARSER_H
#define EPDDL_RELATIONS_PARSER_H

#include "../parser_helper.h"
#include "../../ast/common/relations_ast.h"

namespace epddl::parser {
    class relations_parser {
    public:
        static ast::agent_relation_list parse_model_relations(parser_helper &helper);
        static ast::agent_relation_ptr parse_agent_relation(parser_helper &helper);
        static ast::relation_ptr parse_relation(parser_helper &helper);

        static ast::simple_relation_ptr parse_simple_relation(parser_helper &helper, bool parse_outer_pars = true);
        static ast::and_relation_ptr parse_and_relation(parser_helper &helper, bool parse_outer_pars = true);
        static ast::forall_relation_ptr parse_forall_relation(parser_helper &helper, bool parse_outer_pars = true);
    };
}

#endif //EPDDL_RELATIONS_PARSER_H
