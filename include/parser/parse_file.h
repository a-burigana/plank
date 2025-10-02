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

#ifndef EPDDL_PARSE_FILE_H
#define EPDDL_PARSE_FILE_H

#include "libraries/act_type_library_parser.h"
#include "domains/domain_parser.h"
#include "problems/problem_parser.h"
#include <cassert>

namespace epddl::parser {
    template<typename decl_type>
    decl_type parse_file(const std::string &path) {
        assert((std::is_same_v<decl_type, ast::act_type_library_ptr> or
                std::is_same_v<decl_type, ast::domain_ptr> or
                std::is_same_v<decl_type, ast::problem_ptr>));

        parser_helper helper{path};

        if constexpr (std::is_same_v<decl_type, ast::act_type_library_ptr>)
            return act_type_library_parser::parse(helper);
        else if constexpr (std::is_same_v<decl_type, ast::domain_ptr>)
            return domain_parser::parse(helper);
        else if constexpr (std::is_same_v<decl_type, ast::problem_ptr>)
            return problem_parser::parse(helper);
    }
}

#endif //EPDDL_PARSE_FILE_H
