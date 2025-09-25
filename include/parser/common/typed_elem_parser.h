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
        static ast::type parse_type(parser_helper &helper);
        static ast::either_type_ptr parse_either_type(parser_helper &helper);
    };
}

#endif //EPDDL_TYPED_ELEM_PARSER_H
