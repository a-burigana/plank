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

#ifndef EPDDL_EXPLICIT_INITIAL_STATE_PARSER_H
#define EPDDL_EXPLICIT_INITIAL_STATE_PARSER_H

#include "../../../ast/problems/init/explicit_inititial_state_ast.h"
#include "../../../ast/tokens/tokens_ast.h"
#include "../../../ast/problems/labels_ast.h"
#include "../../parser_helper.h"

namespace epddl::parser {
    class explicit_initial_state_parser {
    public:
        static ast::explicit_initial_state_ptr parse(parser_helper &helper);

        static ast::identifier_list parse_worlds(parser_helper &helper);
        static ast::world_label_list parse_labels(parser_helper &helper);
        static ast::world_label_ptr parse_world_label(parser_helper &helper);
        static ast::identifier_list parse_designated(parser_helper &helper);
    };
}

#endif //EPDDL_EXPLICIT_INITIAL_STATE_PARSER_H
