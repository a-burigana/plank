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

#ifndef EPDDL_CONTEXT_TYPES_H
#define EPDDL_CONTEXT_TYPES_H

#include "../entity_kinds.h"
#include "../type.h"
#include "../../ast/libraries/act_type_library_ast.h"
#include "../../ast/domains/domain_ast.h"
#include "../../ast/problems/problem_ast.h"
#include "../../ast/common/formulas_ast.h"
#include "../../utils/bit_deque.h"
#include <set>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace epddl::type_checker {
    using planning_specification = std::tuple<ast::problem_ptr, ast::domain_ptr, std::list<ast::act_type_library_ptr>>;

    using type_map             = std::unordered_map<std::string, either_type>;
    using term_set             = std::set<ast::term>;
    using string_set           = std::unordered_set<std::string>;
    using typed_var            = std::pair<std::string, either_type>;
    using typed_var_list       = std::list<typed_var>;
    using signature_map        = std::unordered_map<std::string, typed_var_list>;   // either_type_list
    using static_predicate_map = std::unordered_map<std::string, bool>;

    using name_vector          = std::vector<std::string>;
    using name_id_map          = std::unordered_map<std::string, unsigned long>;
    using bit_deque_vector     = std::vector<bit_deque>;

    template<typename ast_node_type>
    using ast_node_map = std::unordered_map<std::string, ast_node_type>;
}

#endif //EPDDL_CONTEXT_TYPES_H
