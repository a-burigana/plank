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

#ifndef EPDDL_EVENT_POSTCONDITIONS_PARSER_H
#define EPDDL_EVENT_POSTCONDITIONS_PARSER_H

#include "../../parser_helper.h"
#include "../../../ast/domains/events/event_postconditions_ast.h"

namespace epddl::parser {
    class event_postconditions_parser {
    public:
        static std::optional<ast::postconditions> parse(parser_helper &helper);
        static ast::postconditions parse_event_postcondition(parser_helper &helper);

        static ast::literal_postcondition_ptr parse_literal_postcondition(parser_helper &helper);
        static ast::when_postcondition_ptr parse_when_postcondition(parser_helper &helper);
        static ast::iff_postcondition_ptr parse_iff_postcondition(parser_helper &helper);
        static ast::forall_postcondition_ptr parse_forall_postcondition(parser_helper &helper);
        static ast::and_postcondition_ptr parse_and_postcondition(parser_helper &helper);
    };
}

#endif //EPDDL_EVENT_POSTCONDITIONS_PARSER_H
